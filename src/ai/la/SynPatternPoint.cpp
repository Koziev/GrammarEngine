// Морфологический анализатор - опорные точки для правил фильтрации и сортировки
//
// CD->12.06.2009
// LC->18.04.2018

#include <lem/solarix/dictionary.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/form_table.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/LA_SynPatternPointCall.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/PatternLinks.h>
#include <lem/solarix/PatternNGrams.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/PredicateTemplate.h>
#include <lem/solarix/PatternLinkEdge.h>
#include <lem/solarix/PatternConstraints.h>
#include <lem/solarix/PatternOptionalPoints.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/TrMorphologyTracer.h>
#include <lem/solarix/LA_SynPatternTrees.h>

#if LEM_DEBUGGING==1
#include <lem/solarix/LexiconStorage.h>
#endif

using namespace lem;
using namespace Solarix;

#undef GetForm


SynPatternPoint::SynPatternPoint()
{
    iclass = UNKNOWN;
    ekey = UNKNOWN;
    ThesaurusCheck_Link = ThesaurusCheck_Entry = UNKNOWN;
    greedy = false;
    links = nullptr;
    ngrams = nullptr;
    predicates = nullptr;
    export_section = nullptr;
    pattern_constraints = nullptr;
    optional_points = nullptr;
    id_tree = UNKNOWN;

    return;
}



SynPatternPoint::SynPatternPoint(const SynPatternPoint &x)
    : mark_name(x.mark_name), id_tree(x.id_tree), greedy(x.greedy), lexeme(x.lexeme), iclass(x.iclass),
    ekey(x.ekey), coords(x.coords), back_correls(x.back_correls), kb_checkers(x.kb_checkers), set_checkers(x.set_checkers),
    ThesaurusCheck_Link(x.ThesaurusCheck_Link), ThesaurusCheck_Entry(x.ThesaurusCheck_Entry),
    tokenizer_flags(x.tokenizer_flags), not_tokenizer_flags(x.not_tokenizer_flags),
    function_name(x.function_name), terminator(x.terminator), str_arg(x.str_arg),
    correl_fun(x.correl_fun), check_fun(x.check_fun),
    PatternSequenceNumber(x.PatternSequenceNumber), id_src(x.id_src), rx_string(x.rx_string), rx(x.rx)
{
    for (lem::Container::size_type i = 0; i < x.args.size(); ++i)
        args.push_back(new SynPatternPoint(*x.args[i]));

    if (x.links != nullptr)
        links = new PatternLinks(*x.links);
    else
        links = nullptr;

    if (x.ngrams != nullptr)
        ngrams = new PatternNGrams(*x.ngrams);
    else
        ngrams = nullptr;

    if (x.predicates != nullptr)
        predicates = new PredicateTemplates(*x.predicates);
    else
        predicates = nullptr;

    if (x.pattern_constraints != nullptr)
        pattern_constraints = new PatternConstraints(*x.pattern_constraints);
    else
        pattern_constraints = nullptr;

    if (x.optional_points != nullptr)
        optional_points = new PatternOptionalPoints(*x.optional_points);
    else
        optional_points = nullptr;

    if (x.export_section != nullptr)
        export_section = new PatternExportSection(*x.export_section);
    else
        export_section = nullptr;

    return;
}


SynPatternPoint::~SynPatternPoint(void)
{
    for (lem::Container::size_type i = 0; i < args.size(); ++i)
        delete args[i];

    delete links;
    delete ngrams;
    delete predicates;
    delete export_section;
    delete pattern_constraints;
    delete optional_points;

    return;
}


void SynPatternPoint::operator=(const SynPatternPoint &x)
{
    mark_name = x.mark_name;
    id_tree = x.id_tree;
    greedy = x.greedy;
    lexeme = x.lexeme;
    iclass = x.iclass;
    ekey = x.ekey;
    coords = x.coords;
    back_correls = x.back_correls;
    tokenizer_flags = x.tokenizer_flags;
    not_tokenizer_flags = x.not_tokenizer_flags;
    ThesaurusCheck_Link = x.ThesaurusCheck_Link;
    ThesaurusCheck_Entry = x.ThesaurusCheck_Entry;
    terminator = x.terminator;
    PatternSequenceNumber = x.PatternSequenceNumber;
    rx_string = x.rx_string;
    rx = x.rx;

    for (auto arg : args)
    {
        delete arg;
    }

    args.clear();
    for (auto arg : x.args)
    {
        args.push_back(new SynPatternPoint(*arg));
    }

    str_arg = x.str_arg;

    correl_fun = x.correl_fun;
    check_fun = x.check_fun;
    id_src = x.id_src;

    delete links;
    if (x.links != nullptr)
        links = new PatternLinks(*x.links);
    else
        links = nullptr;

    delete ngrams;
    if (x.ngrams != nullptr)
        ngrams = new PatternNGrams(*x.ngrams);
    else
        ngrams = nullptr;

    if (x.predicates != nullptr)
        predicates = new PredicateTemplates(*x.predicates);
    else
        predicates = nullptr;

    if (x.pattern_constraints != nullptr)
        pattern_constraints = new PatternConstraints(*x.pattern_constraints);
    else
        pattern_constraints = nullptr;

    if (x.optional_points != nullptr)
        optional_points = new PatternOptionalPoints(*x.optional_points);
    else
        optional_points = nullptr;

    return;
}


bool SynPatternPoint::Equal(const SynPatternPoint &x) const
{
    if (!EqualHead(x) || coords.size() != x.coords.size())
        return false;

    if (!mark_name.GetName().eqi(x.mark_name.GetName()))
        return false;

    if (id_tree != x.id_tree || greedy != x.greedy)
        return false;

    if (!lexeme.eqi(x.lexeme))
        return false;

    if (back_correls != x.back_correls)
        return false;

    if (ThesaurusCheck_Link != x.ThesaurusCheck_Link || ThesaurusCheck_Entry != x.ThesaurusCheck_Entry)
        return false;

    if (coords != x.coords)
        return false;

    if (tokenizer_flags != x.tokenizer_flags || not_tokenizer_flags != x.not_tokenizer_flags)
        return false;

    if (!function_name.eqi(x.function_name))
        return false;

    if (args.size() != x.args.size())
        return false;

    for (lem::Container::size_type i = 0; i < args.size(); ++i)
    {
        if (!args[i]->Equal(*x.args[i]))
            return false;
    }

    if (str_arg != x.str_arg || rx_string != x.rx_string)
        return false;

    if (correl_fun.NotNull() != x.correl_fun.NotNull())
        return false;

    if (correl_fun.NotNull())
    {
        return false;
    }


    if (set_checkers.size() != x.set_checkers.size())
        return false;

    for (lem::Container::size_type i = 0; i < set_checkers.size(); ++i)
    {
        if (set_checkers[i] != x.set_checkers[i])
            return false;
    }


    if (kb_checkers.size() != x.kb_checkers.size())
        return false;

    for (lem::Container::size_type i = 0; i < kb_checkers.size(); ++i)
    {
        if (kb_checkers[i] != x.kb_checkers[i])
            return false;
    }

    if (check_fun.NotNull() != x.check_fun.NotNull())
        return false;


    if (check_fun.NotNull())
    {
        // Мы не проверяем идентичность вызова функции. Это приводит к потере производительности.
        return false;
    }

    if (links == nullptr && x.links != nullptr) return false;
    if (x.links == nullptr && links == nullptr) return false;
    if (links != nullptr && x.links != nullptr && (*links) != (*x.links)) return false;

    if (ngrams == nullptr && x.ngrams != nullptr) return false;
    if (x.ngrams == nullptr && ngrams != nullptr) return false;
    if (ngrams != nullptr && x.ngrams != nullptr && (*ngrams) != (*x.ngrams)) return false;

    if (predicates == nullptr && x.predicates != nullptr) return false;
    if (x.predicates == nullptr && predicates != nullptr) return false;
    if (predicates != nullptr && x.predicates != nullptr && (*predicates) != (*x.predicates)) return false;

    if (pattern_constraints == nullptr && x.pattern_constraints != nullptr) return false;
    if (x.pattern_constraints == nullptr && pattern_constraints != nullptr) return false;
    if (pattern_constraints != nullptr && x.pattern_constraints != nullptr && (*pattern_constraints) != (*x.pattern_constraints)) return false;

    if (optional_points == nullptr && x.optional_points != nullptr) return false;
    if (x.optional_points == nullptr && optional_points != nullptr) return false;
    if (optional_points != nullptr && x.optional_points != nullptr && (*optional_points) != (*x.optional_points)) return false;

    if (export_section == nullptr && x.export_section != nullptr) return false;
    if (export_section != nullptr && x.export_section == nullptr) return false;
    if (export_section != nullptr && x.export_section != nullptr && (*export_section) != (*x.export_section)) return false;

    return true;
}


bool SynPatternPoint::EqualHead(const SynPatternPoint &x) const
{
    return lexeme.empty() ? iclass == x.iclass && ekey == x.ekey : lexeme.eqi(x.lexeme);
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPatternPoint::RegisterRootNodeExport(SynPatternCompilation & compilation_context) const
{
    if (export_section != nullptr)
    {
        // Экспорт переменной с именем ROOT_NODE надо отслеживать особо, чтобы потом в директиве :LINKS проверить корневой узел.
        if (export_section->HasRootNode())
        {
            compilation_context.RegisterRootNode(mark_name.mark_name);
        }
    }

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER

namespace {
    inline bool ApostropheOrQuote(wchar_t c) { return c == L'"' || c == L'\''; }
}

void SynPatternPoint::LoadTxt(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    const SynPatterns & pattern_declarations,
    SynPatternCompilation & compilation_context,
    TrFunctions & functions,
    bool ParseExportSection
)
{
    PatternSequenceNumber.push_back(compilation_context.GetSequenceNumber());

    lem::Iridium::BSourceState point_begin = txtfile.tellp();
    const int src_location = dict.GetDebugSymbols().RegisterLocation(txtfile, point_begin);
    id_src.push_back(src_location);

    const bool exact_entry = true;

    const lem::Iridium::BethToken &t1 = txtfile.read();

    // Это может быть имя класса для точки в формате
    //
    // класс:статья{}
    //
    // Либо словом с однозначной проекцией на лексикон.
    //
    // Либо лексемой в одиночных кавычках
    //
    // Либо именем другого фильтрующего дерева (из известных в pattern_names)
    //
    // Либо именем встроенной функции:
    //
    //    @mark(узел,имя)
    //    @and(узел1,узел2)
    //         ...


    bool it_is_mark = false;


    if (t1.string() == L'@')
    {
        // загружаем вызов встроенной функции

        lem::Iridium::BethToken tfun = txtfile.read();
        function_name = tfun.string();
        txtfile.read_it(B_OROUNDPAREN);

        if (function_name.eqi(L"mark"))
        {
            SynPatternPoint *arg = new SynPatternPoint();
            arg->LoadTxt(dict, txtfile, pattern_declarations, compilation_context, functions);
            args.push_back(arg);

            txtfile.read_it(B_COMMA);

            lem::Iridium::BethToken t = txtfile.read();
            mark_name.mark_name = lem::to_upper(t.string());
            mark_name.pattern_seq = compilation_context.GetSequenceNumber();

            if (compilation_context.Find(mark_name.GetName()) != UNKNOWN)
            {
                lem::Iridium::Print_Error(t, txtfile);
                dict.GetIO().merr().printf("Marker [%vfE%us%vn] is already used in this pattern\n", mark_name.GetName().c_str());
                throw lem::E_BaseException();
            }

            compilation_context.Add(mark_name.GetName());
            RegisterRootNodeExport(compilation_context);

            txtfile.read_it(B_CROUNDPAREN);
        }
        else if (function_name.eqi(L"regex") || function_name.eqi(L"regex_strict"))
        {
            // по умолчанию снимаем требования к словарной статье и части речи.
            // явно задать их можно в идущей следом секции уточнения @regex(....){ ... }
            ekey = UNKNOWN;
            iclass = ANY_STATE;

            // Строковое представление паттерна
            rx_string = txtfile.read().GetFullStr();

            if (rx_string.front() == L'"')
                rx_string.strip(L'"');
            else if (rx_string.front() == L'\'')
                rx_string.strip(L'\'');

            const SynPattern * pattern = compilation_context.GetPattern();
            const int id_language = pattern->GetLanguageId();

            // если указан язык для паттерна, то из описания языка возьмем символьные подстановки
            if (id_language != UNKNOWN)
            {
                const SG_Language &lang = dict.GetSynGram().languages()[id_language];

                for (lem::Container::size_type j = 0; j < lang.params.size(); ++j)
                {
                    const SG_LanguageParam &param = *lang.params[j];
                    if (param.name == L"TokenizerSubst")
                    {
                        for (lem::Container::size_type k = 0; k < param.values.size(); k += 2)
                        {
                            const UFString & macro = param.values[k];
                            const UFString & value = param.values[k + 1];
                            rx_string.subst_all(macro, value);
                        }
                    }
                }
            }

            txtfile.read_it(B_CROUNDPAREN);

            if (txtfile.probe(B_OFIGPAREN))
            {
                LoadPreciser(
                    dict.GetLexAuto(),
                    dict.GetSynGram(),
                    txtfile,
                    compilation_context,
                    functions,
                    iclass,
                    coords,
                    back_correls,
                    set_checkers
                );
            }
        }
        else if (function_name.eqi(L"in_wordentry_set"))
        {
            str_arg = txtfile.read().string();
            txtfile.read_it(B_CROUNDPAREN);
        }
        else if (function_name.eqi(L"not_in_wordentry_set"))
        {
            str_arg = txtfile.read().string();
            txtfile.read_it(B_CROUNDPAREN);
        }
        else if (function_name.eqi(L"in_word_set") || function_name.eqi(L"in_wordform_set"))
        {
            str_arg = txtfile.read().string();
            txtfile.read_it(B_CROUNDPAREN);
        }
        else if (function_name.eqi(L"in_collocation_set"))
        {
            str_arg = txtfile.read().string();
            txtfile.read_it(B_CROUNDPAREN);
        }
        else if (function_name.eqi(L"not_in_word_set"))
        {
            str_arg = txtfile.read().string();
            txtfile.read_it(B_CROUNDPAREN);
        }
        else if (function_name.eqi(L"not_in_collocation_set"))
        {
            str_arg = txtfile.read().string();
            txtfile.read_it(B_CROUNDPAREN);
        }
        else
        {
            if (
                function_name.eqi(L"not") ||
                function_name.eqi(L"or") ||
                function_name.eqi(L"and") ||
                function_name.eqi(L"optional") ||
                function_name.eqi(L"coalesce") ||
                function_name.eqi(L"do_not_filter") ||
                function_name.eqi(L"untill") ||
                function_name.eqi(L"noshift") ||
                function_name.eqi(L"probe_left") ||
                function_name.eqi(L"all_versions")
                )
            {
                while (!txtfile.eof())
                {
                    if (txtfile.probe(B_CROUNDPAREN))
                        break;

                    if (!args.empty())
                        txtfile.read_it(B_COMMA);

                    SynPatternPoint *arg = new SynPatternPoint();
                    arg->LoadTxt(dict, txtfile, pattern_declarations, compilation_context, functions);
                    args.push_back(arg);
                }
            }
            else
            {
                lem::Iridium::Print_Error(tfun, txtfile);
                dict.GetIO().merr().printf("Unknown function [%vfE%us%vn]\n", function_name.c_str());
                throw lem::E_BaseException();
            }
        }

        if (ParseExportSection)
        {
            LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);

            if (function_name.eqi(L"and") || function_name.eqi(L"or") || function_name.eqi(L"optional") || function_name.eqi(L"coalesce"))
            {
                if (export_section != nullptr)
                {
                    lem::Iridium::Print_Error(tfun, txtfile);
                    dict.GetIO().merr().printf("Export section is not allowed for functional point\n");
                    throw lem::E_BaseException();
                }
            }
        }

        return;
    }


    // Вместо функциональной записи @mark(xxx,yyy) может быть использована yyy=xxx
    // Но с ограничением: если у xxx есть секция экспорта, то во избежание неправильного сопоставления следует использовать
    // старую форму @mark.
    // 06.03.2012 - расширил синтаксический сахар, теперь yyy=xxx:export{...} обрабатывается как @mark(xxx,yyy):export{}
    if (!in_quotes(t1.string()) && !in_apostrophes(t1.string()))
    {
        if (txtfile.probe(B_EQUAL))
        {
            function_name = L"mark";

            mark_name.mark_name = lem::to_upper(t1.string());
            mark_name.pattern_seq = compilation_context.GetSequenceNumber();

            if (compilation_context.Find(mark_name.GetName()) != UNKNOWN)
            {
                lem::Iridium::Print_Error(t1, txtfile);
                dict.GetIO().merr().printf("Marker [%vfE%us%vn] is already used in this pattern\n", mark_name.GetName().c_str());
                throw lem::E_BaseException();
            }

            compilation_context.Add(mark_name.GetName());

            SynPatternPoint *arg = new SynPatternPoint();
            arg->LoadTxt(dict, txtfile, pattern_declarations, compilation_context, functions, false);
            args.push_back(arg);

            if (arg->export_section != nullptr)
            {
                lem::Iridium::Print_Error(t1, txtfile);
                dict.GetIO().merr().printf("Use @mark(...,%vfE%us%vn) instead of %vfE%us%vn=... in this context\n", mark_name.GetName().c_str());
                throw lem::E_BaseException();
            }

            LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);
            RegisterRootNodeExport(compilation_context);

            return;
        }
    }



    lem::UCString class_name(t1.string());

    if (compilation_context.IsWordEntrySet(class_name))
    {
        // Фактически это синтаксический сахар для вызова функции @in_wordentry_set(...)
        function_name = L"in_wordentry_set";
        str_arg = class_name;

        // может идти доп. фильтр по координатам
        if (txtfile.probe(B_OFIGPAREN))
        {
            LoadPreciser(
                dict.GetLexAuto(),
                dict.GetSynGram(),
                txtfile,
                compilation_context,
                functions,
                iclass,
                coords,
                back_correls,
                set_checkers
            );
        }

        // опциональный список ре-экспортируемых координат
        if (ParseExportSection)
            LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);

        return;
    }


    if (compilation_context.IsWordSet(class_name))
    {
        function_name = L"in_word_set";
        str_arg = class_name;

        // может идти доп. фильтр по координатам
        if (txtfile.probe(B_OFIGPAREN))
        {
            LoadPreciser(
                dict.GetLexAuto(),
                dict.GetSynGram(),
                txtfile,
                compilation_context,
                functions,
                iclass,
                coords,
                back_correls,
                set_checkers
            );
        }

        if (ParseExportSection)
            LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);

        return;
    }


    if (compilation_context.IsWordformSet(class_name))
    {
        function_name = L"in_wordform_set";
        str_arg = class_name;

        // может идти доп. фильтр по координатам
        if (txtfile.probe(B_OFIGPAREN))
        {
            LoadPreciser(
                dict.GetLexAuto(),
                dict.GetSynGram(),
                txtfile,
                compilation_context,
                functions,
                iclass,
                coords,
                back_correls,
                set_checkers
            );
        }

        if (ParseExportSection)
            LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);

        return;
    }


    if (compilation_context.IsCollocationSet(class_name))
    {
        function_name = L"in_collocation_set";
        str_arg = class_name;

        // может идти доп. фильтр по координатам
        if (txtfile.probe(B_OFIGPAREN))
        {
            LoadPreciser(
                dict.GetLexAuto(),
                dict.GetSynGram(),
                txtfile,
                compilation_context,
                functions,
                iclass,
                coords,
                back_correls,
                set_checkers
            );
        }

        if (ParseExportSection)
            LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);

        return;
    }


    if (pattern_declarations.IsPatternName(class_name))
    {
        // Будет вызвано именованое дерево.
        lem::UCString tree_name = class_name;
        id_tree = pattern_declarations.GetPatternID(tree_name);

        const SynPatternOptions & pattern_options = pattern_declarations.GetOptions(class_name);

        if (pattern_options.IsTopDown() && compilation_context.GetPointNumber() == 0 && compilation_context.GetPatternName().eqi(tree_name))
        {
            // первая опорная точка ссылается на свой же паттерн - это приведет к бесконечной
            // головной рекурсии. Леворекурсивные правила разрешены только для правил восходящего анализа.
            lem::Iridium::Print_Error(point_begin, txtfile);
            dict.GetIO().merr().printf("Possibly infinite recursion with pattern [%vfE%us%vn]\n", tree_name.c_str());
            throw lem::E_BaseException();
        }

        greedy = pattern_options.IsGreedy();

        // Могут быть заданы требования на экспортируемые вызываемым деревом координаты.
        if (txtfile.probe(B_OFIGPAREN))
        {
            int id_class_dummy = UNKNOWN;
            LoadPreciser(
                dict.GetLexAuto(),
                dict.GetSynGram(),
                txtfile,
                compilation_context,
                functions,
                id_class_dummy,
                coords,
                back_correls,
                set_checkers
            );

            // Проверим, что проверяемые координаты действительно экспортируются группой паттернов.
            for (lem::Container::size_type k = 0; k < coords.size(); ++k)
            {
                if (!pattern_options.GetExport().ContainsCoord(coords[k].GetPair().GetCoord().GetIndex()))
                {
                    const GramCoord & c = dict.GetSynGram().coords().GetCoord(coords[k].GetPair().GetCoord().GetIndex());
                    lem::Iridium::Print_Error(point_begin, txtfile);
                    dict.GetIO().merr().printf("Coordinate %vfE%us%vn is not exported by pattern group %vfE%us%vn\n", c.GetName().string().c_str(), tree_name.c_str());
                    throw lem::E_BaseException();
                }
            }
        }

        // опциональный список ре-экспортируемых координат
        if (ParseExportSection)
        {
            LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);

            if (export_section != nullptr)
            {
                // Проверим, что экспортируемые координаты экспортируются вызываемым паттерном.
                for (lem::Container::size_type k = 0; k < export_section->export_coords.size(); ++k)
                {
                    if (!pattern_options.GetExport().ContainsCoord(export_section->export_coords[k]))
                    {
                        const GramCoord & c = dict.GetSynGram().coords().GetCoord(export_section->export_coords[k]);
                        lem::Iridium::Print_Error(point_begin, txtfile);
                        dict.GetIO().merr().printf("Coordinate %vfE%us%vn is not exported by pattern %vfE%us%vn\n", c.GetName().string().c_str(), tree_name.c_str());
                        throw lem::E_BaseException();
                    }
                }
            }
        }

        return;
    }


    if (functions.IsFunction(class_name))
    {
        // это вызов функции для проверки любых свойств словоформы. при этом доступны следующие локальные
        // переменные:
        //
        // _ проверямая словоформа
        // _0 текущий анализируемый вариатор
        // _i позиция текущей словоформы

        TrKnownVars known_vars(&functions.global_known_vars);

        // Объявленные оператором declare внутри правила переменные-маркировки.
        //for( lem::Container::size_type i=0; i<compilation_context.GetContext().GetVars().size(); ++i )
        //known_vars.RegisterVar( TrTreesType(), compilation_context.GetContext().GetVars()[i] );

        known_vars.RegisterVar(TrTreesType(), L"_"); // проверямая словоформа
        known_vars.RegisterVar(TrTreesType(), L"_0"); // текущий анализируемый вариатор
        known_vars.RegisterVar(TrIntType(), L"_i");

        txtfile.seekp(t1);
        check_fun = functions.CompileCall(dict.GetLexAuto(), txtfile, known_vars);

        return;
    }


    if (
        (class_name.front() == L'\'' && class_name.back() == L'\'') ||
        (class_name.front() == L'"' && class_name.back() == L'"')
        )
    {
        if (class_name.front() == L'\'')
            class_name.strip(L'\'');
        else
            class_name.strip(L'"');

        lexeme = class_name;

        if (txtfile.probe(B_OFIGPAREN))
        {
            LoadPreciser(
                dict.GetLexAuto(),
                dict.GetSynGram(),
                txtfile,
                compilation_context,
                functions,
                iclass,
                coords,
                back_correls,
                set_checkers
            );
        }
    }
    else
    {
        if ((iclass = dict.GetSynGram().FindClass(class_name)) == UNKNOWN)
        {
            // Выводим сообщение о неверном имени синтаксического класса/неизвестном слове.
            lem::Iridium::Print_Error(t1, txtfile);

            dict.GetIO().merr().printf(
                "Part of speech [%vfE%us%vn] is not previously declared in grammar\n"
                , class_name.c_str()
            );

            throw lem::E_ParserError();
        }

        if (txtfile.probe(B_COLON))
        {
            lem::Iridium::BSourceState ebeg = txtfile.tellp();
            const UCString mname = sol_read_multyname(dict.GetIO(), txtfile, B_OFIGPAREN);

            // Имеем пару класс:имя_статьи

            // Пытаемся найти статью.
            if (mname.front() != sol_get_token(B_ANY))
            {
                // Считан НЕ квантор всеобщности, так что это должно
                // быть имя статьи.
                // Попытаемся найти статью среди уже загруженных, причем
                // ищем с критерием принадлежности определенному синтаксическому
                // классу.

                const int ientry = dict.GetSynGram().FindEntry(mname, iclass, false);

                // Нашли ?
                if (ientry == UNKNOWN)
                {
                    // Нет! Выводим сообщение об неверном имени словарной статьи.
                    lem::Iridium::Print_Error(ebeg, txtfile);
                    dict.GetIO().merr().printf("The entry [%vfE%us%vn] is not previously declared in grammar\n", mname.c_str());
                    throw E_BaseException();
                }
                else
                {
                    // Запомним КЛЮЧ словарной статьи.
                    ekey = ientry;
                    iclass = UNKNOWN;
                }
            }

            // Далее идут координаты в {}
            LoadPreciser(
                dict.GetLexAuto(),
                dict.GetSynGram(),
                txtfile,
                compilation_context,
                functions,
                iclass,
                coords,
                back_correls,
                set_checkers
            );
        }
        else
        {
            // Указан только грамматический класс, без статьи.
            ekey = UNKNOWN;

            if (txtfile.probe(B_OFIGPAREN))
            {
                LoadPreciser(
                    dict.GetLexAuto(),
                    dict.GetSynGram(),
                    txtfile,
                    compilation_context,
                    functions,
                    iclass,
                    coords,
                    back_correls,
                    set_checkers
                );
            }
        }
    }

    if (ParseExportSection)
        LoadExportTxt(dict, txtfile, pattern_declarations, compilation_context, functions);

    return;
}


// Парсим описание элементов в секции экспорта
void SynPatternPoint::LoadExportTxt(
    Dictionary &dict,
    lem::Iridium::Macro_Parser & txtfile,
    const SynPatterns & pattern_declarations,
    SynPatternCompilation & compilation_context,
    TrFunctions & functions
)
{
    LEM_CHECKIT_Z(export_section == nullptr);

    if (txtfile.probe(B_COLON))
    {
        if (txtfile.probe(L"export"))
        {
            export_section = new PatternExportSection();
            export_section->LoadTxt(dict, txtfile, pattern_declarations, compilation_context, functions, *this);
        }
        else
        {
            lem::Iridium::Print_Error(txtfile);
            dict.GetIO().merr().printf("Invalid statement\n");
            throw E_BaseException();
        }
    }

    return;
}



void SynPatternPoint::LoadPreciser(
    LexicalAutomat &la,
    SynGram &sg,
    lem::Iridium::Macro_Parser & txtfile,
    SynPatternCompilation & compilation_context,
    TrFunctions &functions,
    int &iclass,
    lem::MCollect<CoordPairChecker> & coords2,
    lem::MCollect<BackRefCorrel> & correls,
    lem::MCollect<WordSetChecker> & setcheckers
)
{
    while (!txtfile.eof())
    {
        if (txtfile.pick().GetToken() == B_CFIGPAREN)
        {
            txtfile.read();
            break;
        }

        // опциональные доп. атрибуты - штраф за нарушение условий.
        ViolationHandler violation_handler;
        violation_handler.LoadTxt(txtfile);


        // Может быть вызов проверяющей императивной функции
        lem::Iridium::BethToken correl_fun_name = txtfile.read();

        //if( correl_fun_name.string()==L"НеМестоимениеОтладка" )
        //lem::mout->printf( "DEBUG!!!" );

        if (functions.IsFunction(correl_fun_name.string()))
        {
            if (correl_fun.NotNull())
            {
                sg.GetIO().merr().printf("Only one correlation lambda-function is allowed\n");
                lem::Iridium::Print_Error(txtfile);
                throw lem::E_BaseException();
            }

            txtfile.seekp(correl_fun_name.GetBegin());

            //     txtfile.read_it(L"lambda");

            TrKnownVars known_vars(&functions.global_known_vars);

            //lem::Iridium::BSourceState b = txtfile.tellp();
            //txtfile.read_it( B_OFIGPAREN );
            //txtfile.seekp(b);

            // Объявленные оператором declare внутри правила переменные-маркировки.
            //for( lem::Container::size_type i=0; i<compilation_context.GetContext().GetVars().size(); ++i )
            // known_vars.RegisterVar( TrTreesType(), compilation_context.GetContext().GetVars()[i] );

            known_vars.RegisterVar(TrTreesType(), L"_"); // проверямая словоформа

            correl_fun = functions.CompileCall(la, txtfile, known_vars);

            continue;
        }
        else
        {
            txtfile.seekp(correl_fun_name.GetBegin());
        }




        // может быть задание простой проверки на связь в тезаурусе
        if (txtfile.pick().GetToken() == B_OTRIPAREN)
        {
            if (ThesaurusCheck_Link != UNKNOWN)
            {
                sg.GetIO().merr().printf("Only one thesaurus check is allowed\n");
                lem::Iridium::Print_Error(txtfile);
                throw lem::E_BaseException();
            }

            Solarix::Tree_Link link(txtfile, sg);
            ThesaurusCheck_Link = link.GetState();

            // далее идет спецификация словарной статьи.
            lem::Iridium::BethToken class_name = txtfile.read();
            const int iclass = sg.FindClass(class_name.string());
            if (iclass == UNKNOWN)
            {
                sg.GetIO().merr().printf("Unknown class name [%us]\n", class_name.string().c_str());
                lem::Iridium::Print_Error(txtfile);
                throw lem::E_BaseException();
            }

            txtfile.read_it(B_COLON);

            lem::Iridium::BSourceState ebeg = txtfile.tellp();
            const UCString mname = sol_read_multyname(sg.GetIO(), txtfile, B_OFIGPAREN);
            txtfile.read_it(B_CFIGPAREN);

            // Имеем пару класс:имя_статьи
            ThesaurusCheck_Entry = sg.FindEntry(mname, iclass, false);

            // Нашли ?
            if (ThesaurusCheck_Entry == UNKNOWN)
            {
                // Нет! Выводим сообщение об неверном имени словарной статьи.
                lem::Iridium::Print_Error(ebeg, txtfile);
                sg.GetIO().merr().printf("The entry [%us:%vfE%us%vn] is not previously declared in grammar\n", class_name.string().c_str(), mname.c_str());
                throw lem::E_BaseException();
            }

            continue;
        }


        // проверка значения флагов токенизатора
        if (txtfile.probe(L"tokenizer_flag"))
        {
            txtfile.read_it(B_COLON);
            tokenizer_flags = txtfile.read().GetFullStr();
            continue;
        }

        lem::Iridium::BSourceState back1 = txtfile.tellp();
        if (txtfile.probe(B_NEGATIVE))
        {
            if (txtfile.probe(L"tokenizer_flag"))
            {
                not_tokenizer_flags = true;
                txtfile.read_it(B_COLON);
                tokenizer_flags = txtfile.read().GetFullStr();
                continue;
            }
            else
            {
                txtfile.seekp(back1);
            }
        }


        // для обычных: координата:состояние
        // для бистабильных: координата
        // для согласования с координатами в именованных точках слева =имя_точки:координата
        // расширенный формат описания согласования с именованными точками =имя_коорд->имя_точки:имя_коорд
        // Может быть имя множества лексем или статей, или отрицание.

        lem::Iridium::BethToken coord_name = txtfile.read();


        // Если задано имя факта в базе знаний, то загружаем директиву обращения к БЗ
        if (la.GetKnowledgeBase().FindFacts(coord_name.string()) != UNKNOWN)
        {
            txtfile.seekp(coord_name);
            KB_Checker * kb_checker = new KB_Checker();
            kb_checker->LoadTxt(la.GetDict(), txtfile, compilation_context);
            kb_checkers.push_back(kb_checker);
            continue;
        }

        if (coord_name.GetToken() == B_EQUAL || coord_name.GetToken() == B_LOGNE)
        {
            lem::Iridium::BethToken t = txtfile.read();
            lem::UCString mark_name = t.string();

            bool same_coords = true;
            GramCoordAdr iglob_coord0, iglob_coord1;

            if (txtfile.probe(L"->"))
            {
                lem::Iridium::BethToken coord_name0 = t;

                t = txtfile.read();
                mark_name = t.string();

                iglob_coord0 = sg.FindCoord(coord_name0.string());

                if (!iglob_coord0.IsDefined())
                {
                    sg.GetIO().merr().printf("Unknown coordinate [%us]\n", coord_name0.c_str());
                    lem::Iridium::Print_Error(coord_name0, txtfile);
                    throw lem::E_BaseException();
                }

                same_coords = false;
            }

            if (compilation_context.Find(mark_name) == UNKNOWN)
            {
                sg.GetIO().merr().printf("Unknown marker %us\n", mark_name.c_str());
                lem::Iridium::Print_Error(t, txtfile);
                throw lem::E_BaseException();
            }

            txtfile.read_it(B_COLON);

            bool for_group = txtfile.probe(B_OSPAREN);
            lem::Iridium::BethToken coord_name1 = txtfile.read();
            if (for_group) txtfile.read_it(B_CSPAREN);

            iglob_coord1 = sg.FindCoord(coord_name1.string());

            if (!iglob_coord1.IsDefined())
            {
                sg.GetIO().merr().printf("Unknown coordinate %us\n", coord_name1.c_str());
                lem::Iridium::Print_Error(coord_name1, txtfile);
                throw lem::E_BaseException();
            }

            if (same_coords)
                iglob_coord0 = iglob_coord1;

            BackRefCorrel c;
            c.affirmative = coord_name.GetToken() == B_EQUAL;
            c.name = lem::to_upper(mark_name);
            c.id_coord0 = iglob_coord0.GetIndex();
            c.id_coord1 = iglob_coord1.GetIndex();
            c.for_group = for_group;
            c.violation_handler = violation_handler;
            correls.push_back(c);
            continue;
        }

        if (coord_name.GetToken() == B_CLASS)
        {
            txtfile.read_it(B_COLON);
            lem::Iridium::BethToken class_name2 = txtfile.read();
            iclass = sg.FindClass(class_name2.string());
            if (iclass == UNKNOWN)
            {
                lem::Iridium::Print_Error(class_name2, txtfile);
                sg.GetIO().merr().printf(
                    "Unknown class [%vfE%us%vn]\n"
                    , class_name2.string().c_str()
                );
                throw E_ParserError();
            }

            continue;
        }

        bool AFFIRM = true;

        if (coord_name.GetToken() == B_NEGATIVE)
        {
            // Оператор отрицания перед определением координаты!
            AFFIRM = false;
            coord_name = txtfile.read();
        }

        if (compilation_context.IsWordSet(coord_name))
        {
            lem::UCString node_name;

            if (txtfile.probe(B_OROUNDPAREN))
            {
                node_name = txtfile.read();
                node_name.to_upper();
                txtfile.read_it(B_CROUNDPAREN);
            }

            WordSetChecker checker(0, coord_name, AFFIRM, node_name, violation_handler);
            setcheckers.push_back(checker);

            continue;
        }
        else if (compilation_context.IsWordEntrySet(coord_name))
        {
            lem::UCString node_name;

            if (txtfile.probe(B_OROUNDPAREN))
            {
                node_name = txtfile.read();
                node_name.to_upper();
                txtfile.read_it(B_CROUNDPAREN);
            }

            WordSetChecker checker(1, coord_name, AFFIRM, node_name, violation_handler);
            setcheckers.push_back(checker);
            continue;
        }
        else if (compilation_context.IsWordformSet(coord_name))
        {
            lem::UCString node_name;

            if (txtfile.probe(B_OROUNDPAREN))
            {
                node_name = txtfile.read();
                node_name.to_upper();
                txtfile.read_it(B_CROUNDPAREN);
            }

            WordSetChecker checker(2, coord_name, AFFIRM, node_name, violation_handler);
            setcheckers.push_back(checker);
            continue;
        }

        const GramCoordAdr iglob_coord = sg.FindCoord(coord_name.string());

        if (!iglob_coord.IsDefined())
        {
            sg.GetIO().merr().printf("Unknown coordinate %us\n", coord_name.c_str());
            lem::Iridium::Print_Error(coord_name, txtfile);
            throw lem::E_BaseException();
        }

        CoordPairChecker pair_checker;
        pair_checker.violation_handler = violation_handler;

        if (sg.coords()[iglob_coord.GetIndex()].IsBistable())
        {
            // Имя состояния не может быть указано.
            pair_checker.pair = GramCoordPair(iglob_coord, AFFIRM);
            coords2.push_back(pair_checker);
        }
        else
        {
            // После двоеточия должно идти имя состояния для координаты.
            txtfile.read_it(B_COLON);

            // Имя состояния.
            BethToken state_name = txtfile.read();

            // Получим индекс состояния для определенной координаты.
            const int istate = sg.coords()[iglob_coord.GetIndex()]
                .FindState(state_name.string());
            if (istate == UNKNOWN)
            {
                // Нет такого состояния для этого измерения.
                lem::Iridium::Print_Error(state_name, txtfile);
                sg.GetIO().merr().printf(
                    "State [%vfE%us%vn] is not declared for coordinate [%vfE%us%vn]\n"
                    , state_name.c_str(), coord_name.c_str()
                );
                throw E_ParserError();
            }

            pair_checker.pair = GramCoordEx(iglob_coord, istate, AFFIRM);
            coords2.push_back(pair_checker);
        }
    }

    return;
}

#endif

#if defined SOL_SAVEBIN
void SynPatternPoint::SaveBin(lem::Stream& bin) const
{
    PatternSequenceNumber.SaveBin(bin);
    bin.write(&mark_name, sizeof(mark_name));
    bin.write(&id_tree, sizeof(id_tree));
    bin.write_bool(greedy);
    bin.write(&lexeme, sizeof(lexeme));
    bin.write(&iclass, sizeof(iclass));
    bin.write(&ekey, sizeof(ekey));

    bin.write(&ThesaurusCheck_Link, sizeof(ThesaurusCheck_Link));
    bin.write(&ThesaurusCheck_Entry, sizeof(ThesaurusCheck_Entry));

    bin.write_bool(terminator);
    coords.SaveBin(bin);
    back_correls.SaveBin(bin);
    kb_checkers.SaveBin(bin);
    set_checkers.SaveBin(bin);

    bin.write_bool(not_tokenizer_flags);
    tokenizer_flags.SaveBin(bin);

    bin.write(&function_name, sizeof(function_name));
    bin.write_int(CastSizeToInt(args.size()));
    for (lem::Container::size_type i = 0; i < args.size(); ++i)
        args[i]->SaveBin(bin);

    bin.write(&str_arg, sizeof(str_arg));
    rx_string.SaveBin(bin);

    bin.write_bool(correl_fun.NotNull());
    if (correl_fun.NotNull())
        correl_fun->SaveBin(bin);

    bin.write_bool(check_fun.NotNull());
    if (check_fun.NotNull())
        check_fun->SaveBin(bin);

    bin.write_bool(export_section != nullptr);
    if (export_section != nullptr)
        export_section->SaveBin(bin);

    id_src.SaveBin(bin);

    bin.write_bool(links != nullptr);
    if (links != nullptr)
        links->SaveBin(bin);

    bin.write_bool(ngrams != nullptr);
    if (ngrams != nullptr)
        ngrams->SaveBin(bin);

    bin.write_bool(predicates != nullptr);
    if (predicates != nullptr)
        predicates->SaveBin(bin);

    bin.write_bool(pattern_constraints != nullptr);
    if (pattern_constraints != nullptr)
        pattern_constraints->SaveBin(bin);

    bin.write_bool(optional_points != nullptr);
    if (optional_points != nullptr)
        optional_points->SaveBin(bin);

    return;
}
#endif


#if defined SOL_LOADBIN 
void SynPatternPoint::LoadBin(lem::Stream& bin)
{
    PatternSequenceNumber.LoadBin(bin);
    bin.read(&mark_name, sizeof(mark_name));
    bin.read(&id_tree, sizeof(id_tree));
    greedy = bin.read_bool();
    bin.read(&lexeme, sizeof(lexeme));
    bin.read(&iclass, sizeof(iclass));
    bin.read(&ekey, sizeof(ekey));

    bin.read(&ThesaurusCheck_Link, sizeof(ThesaurusCheck_Link));
    bin.read(&ThesaurusCheck_Entry, sizeof(ThesaurusCheck_Entry));

    terminator = bin.read_bool();
    coords.LoadBin(bin);
    back_correls.LoadBin(bin);
    kb_checkers.LoadBin(bin);
    set_checkers.LoadBin(bin);

    not_tokenizer_flags = bin.read_bool();
    tokenizer_flags.LoadBin(bin);

    bin.read(&function_name, sizeof(function_name));
    const int n = bin.read_int();
    for (int i = 0; i < n; ++i)
    {
        SynPatternPoint *arg = new SynPatternPoint();
        arg->LoadBin(bin);
        args.push_back(arg);
    }

    bin.read(&str_arg, sizeof(str_arg));

    rx_string.LoadBin(bin);

    if (function_name.eqi(L"regex"))
    {
        // с игнорированием регистра
        rx = boost::wregex(rx_string.c_str(), boost::regex_constants::icase);
    }
    else if (function_name.eqi(L"regex_strict"))
    {
        // с точным учетом регистра
        rx = boost::wregex(rx_string.c_str());
    }

    if (bin.read_bool())
        correl_fun = TrFunCall::load_bin(bin);

    if (bin.read_bool())
        check_fun = TrFunCall::load_bin(bin);

    if (bin.read_bool())
    {
        export_section = new PatternExportSection();
        export_section->LoadBin(bin);
    }
    else
    {
        export_section = nullptr;
    }

    id_src.LoadBin(bin);
#if !defined SOL_DEBUGGING
    id_src.clear();
#endif

    if (bin.read_bool())
    {
        links = new PatternLinks();
        links->LoadBin(bin);
    }
    else
    {
        links = nullptr;
    }

    if (bin.read_bool())
    {
        ngrams = new PatternNGrams();
        ngrams->LoadBin(bin);
    }
    else
    {
        ngrams = nullptr;
    }

    if (bin.read_bool())
    {
        predicates = new PredicateTemplates();
        predicates->LoadBin(bin);
    }
    else
    {
        predicates = nullptr;
    }

    if (bin.read_bool())
    {
        pattern_constraints = new PatternConstraints();
        pattern_constraints->LoadBin(bin);
    }
    else
    {
        pattern_constraints = nullptr;
    }

    if (bin.read_bool())
    {
        optional_points = new PatternOptionalPoints();
        optional_points->LoadBin(bin);
    }
    else
    {
        optional_points = nullptr;
    }

    return;
}


void SynPatternPoint::Link(const TrFunctions &funs)
{
    if (correl_fun.NotNull())
        correl_fun->Link(funs);

    if (check_fun.NotNull())
        check_fun->Link(funs);

    for (auto arg : args)
    {
        arg->Link(funs);
    }

    if (ngrams != nullptr)
    {
        ngrams->Link(funs);
    }

    return;
}

#endif


#if defined SOL_CAA && !defined SOL_NO_AA

static void Append(
    std::multimap< const Word_Form*, int /*iversion*/ > &dst,
    std::multimap< const Word_Form*, int /*iversion*/ > &src
)
{
    for (std::multimap< const Word_Form*, int >::const_iterator it = src.begin();
        it != src.end(); ++it)
        dst.insert(*it);

    return;
}

static void Append(
    std::multimap< int, int > &dst,
    std::multimap< int, int > &src
)
{
    for (std::multimap< int, int >::const_iterator it = src.begin(); it != src.end(); ++it)
        dst.insert(*it);

    return;
}


bool SynPatternPoint::Equal(
    int banned_it_tree,
    PM_Automat &pm,
    SynGram &sg,
    TreeMatchingExperience &experience,
    const ElapsedTimeConstraint & constraints,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    LA_SynPatternTrees &named_filters,
    WordEntrySet &wordentry_sets,
    bool force_greedy,
    bool force_export,
    bool can_skip_outer_tokens,
    lem::PtrCollect<SynPatternResult> & results,
    TrTrace *trace_log,
    int recursion_depth
) const
{
    if (constraints.Exceeded(recursion_depth))
        return false;

    /*
    // ---- DEBUG
    static int debug_count=0;
    debug_count++;
    printf( "DEBUG SynPatternPoint::Equal count=%d\n", debug_count );
    if( debug_count==20522 )
    {
    //  DebugBreak();
    //  printf( "DEBUG 2\n" );
    }
    // ~~~~~~~~~~
    */

#if defined SOL_DEBUGGING
    try
    {
        bool res = Equal_ThrowingExceptions(
            banned_it_tree,
            pm,
            sg,
            experience,
            constraints,
            current_token,
            lexer,
            parent_trace,
            x_result,
            named_filters,
            wordentry_sets,
            force_greedy,
            force_export,
            can_skip_outer_tokens,
            results,
            trace_log,
            recursion_depth
        );


        if (res && trace_log != nullptr)
        {
            const Solarix::Word_Form * wordform = current_token->IsBeyondRight() ? (const Solarix::Word_Form*)nullptr : current_token->GetWordform();

            for (lem::Container::size_type i = 0; i < results.size(); ++i)
            {
                SynPatternResult * result = results[i];
                if (result->res.Length() != 0)
                {
                    SynPatternDebugTrace dbg_point(this, wordform, nullptr);
                    dbg_point.ngram_freq = result->res.GetNGramFreq();
                    result->Append(dbg_point);
                }
            }
        }

        return res;
    }
    catch (...)
    {
        if (!id_src.empty() && trace_log != nullptr)
            trace_log->RaisedExceptionLocation(id_src);

        throw;
    }

#else

    bool res = Equal_ThrowingExceptions(
        banned_it_tree,
        pm,
        sg,
        experience,
        constraints,
        current_token,
        lexer,
        parent_trace,
        x_result,
        named_filters,
        wordentry_sets,
        force_greedy,
        force_export,
        can_skip_outer_tokens,
        results,
        trace_log,
        recursion_depth
    );

    return res;
#endif
}


bool SynPatternPoint::CheckConstraints(
    const Solarix::LexicalAutomat & la,
    const BackTrace *parent_trace,
    SynPatternResult * cur_result
) const
{
    LEM_CHECKIT_Z(pattern_constraints != nullptr);

    PatternConstraintResult res = pattern_constraints->Check(la, parent_trace, PatternSequenceNumber, cur_result);
    if (res.success)
    {
        cur_result->res.AddNGramFreq(Solarix::NGramScore(res.score));

#if defined SOL_DEBUGGING
        SynPatternDebugTrace dbg;
        dbg.ngram_freq = Solarix::NGramScore(res.score);
        cur_result->debug_trace.push_back(dbg);
#endif

        return true;
    }

    return false;
}


NGramScore SynPatternPoint::CalculateNGramFreq(
    Dictionary &dict,
    const SynPatternResultBackTrace * x_result,
    SynPatternResult * cur_result,
    TreeMatchingExperience &experience,
    const ElapsedTimeConstraint & constraints,
    TrTrace *trace_log
) const
{
    LEM_CHECKIT_Z(ngrams != nullptr);

    KnowledgeBase &kbase = dict.GetLexAuto().GetKnowledgeBase();

    NGramScore res = ngrams->Match(
        dict,
        PatternSequenceNumber,
        x_result,
        cur_result,
        kbase,
        experience,
        constraints,
        trace_log
    );

    if (!res.IsZero())
    {
#if defined SOL_DEBUGGING
        SynPatternDebugTrace dbg;
        dbg.ngram_freq = res;
        cur_result->debug_trace.push_back(dbg);
#endif
    }

    return res;
}



void SynPatternPoint::GenerateLinks(const Solarix::LexicalAutomat & la, SynPatternResult * cur_result) const
{
    LEM_CHECKIT_Z(links != nullptr);

    links->Generate(la, PatternSequenceNumber, cur_result);

    return;
}






bool SynPatternPoint::Equal_ThrowingExceptions(
    int banned_id_tree,
    PM_Automat &pm,
    SynGram &sg,
    TreeMatchingExperience &experience,
    const ElapsedTimeConstraint & constraints,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace *parent_trace,
    const SynPatternResultBackTrace * x_result,
    LA_SynPatternTrees &named_filters,
    WordEntrySet &wordentry_sets,
    bool force_greedy,
    bool force_export,
    bool can_skip_outer_tokens,
    lem::PtrCollect<SynPatternResult> & results,
    TrTrace *trace_log,
    int recursion_depth
) const
{
    lem::Ptr<TrMorphologyTracerTx> log_tx;
    const int dbg_mark = TrTraceActor::seq++;

#if defined SOL_DEBUGGING
    if (trace_log != nullptr)
    {
        log_tx = trace_log->GetMorphologyTracer().BeginTx();
        trace_log->Enter(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
    }
#endif

    Dictionary &dict = sg.GetDict();

    if (!function_name.empty())
    {
        if (function_name.eqi(L"mark"))
        {
            bool mark_res = Execute_Mark(
                banned_id_tree,
                pm,
                sg,
                experience,
                constraints,
                current_token,
                lexer,
                parent_trace,
                x_result,
                named_filters,
                wordentry_sets,
                force_greedy,
                force_export,
                can_skip_outer_tokens,
                results,
                trace_log,
                recursion_depth + 1
            );

#if defined SOL_DEBUGGING
            if (trace_log != nullptr)
            {
                trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
            }
#endif

            return mark_res;
        }
        else if (function_name.eqi(L"optional") || function_name.eqi(L"coalesce"))
        {
            LEM_CHECKIT_Z(args.size() == 1);

            lem::PtrCollect<SynPatternResult> subresults;

            bool x = args.front()->Equal(
                banned_id_tree,
                pm,
                sg,
                experience,
                constraints,
                current_token,
                lexer,
                parent_trace,
                x_result,
                named_filters,
                wordentry_sets,
                false,
                force_export,
                can_skip_outer_tokens,
                subresults,
                trace_log,
                recursion_depth + 1
            );

            if (x)
            {
                if (function_name.eqi(L"coalesce"))
                {
                    // Делаем ветвление, пусть будет 2 результата - один с входящей точкой, другой без нее.
                    // Копируем успешные сопоставления, если они есть
                    for (lem::Container::size_type i = 0; i < subresults.size(); ++i)
                    {
                        if (pattern_constraints != nullptr)
                        {
                            bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, subresults[i]);
                            if (constraints_check)
                            {
                                results.push_back(subresults[i]);
                                subresults[i] = nullptr;
                            }
                        }
                        else
                        {
                            results.push_back(subresults[i]);
                            subresults[i] = nullptr;
                        }
                    }

                    // делаем успешное сопоставление нулевой длины
                    SynPatternResult *r = new SynPatternResult(parent_trace);

                    r->res = SynPatternMatchResult(true, 0, current_token, current_token->GetPrev(), NGramScore(0));

                    if (links != nullptr)
                        GenerateLinks(dict.GetLexAuto(), r);

                    if (ngrams != nullptr)
                        r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                    if (pattern_constraints != nullptr)
                    {
                        bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                        if (constraints_check)
                            results.push_back(r);
                        else
                            delete r;
                    }
                    else
                    {
                        results.push_back(r);
                    }
                }
                else
                {
                    for (lem::Container::size_type i = 0; i < subresults.size(); ++i)
                    {
                        if (pattern_constraints != nullptr)
                        {
                            bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, subresults[i]);
                            if (constraints_check)
                            {
                                results.push_back(subresults[i]);
                                subresults[i] = nullptr;
                            }
                        }
                        else
                        {
                            results.push_back(subresults[i]);
                            subresults[i] = nullptr;
                        }
                    }

#if defined SOL_DEBUGGING
                    if (trace_log != nullptr)
                    {
                        lem::MemFormatter mem;

                        for (std::multimap<const Word_Form*, int>::const_iterator it = results[0]->matched_alts.begin();
                            it != results[0]->matched_alts.end(); ++it)
                        {
                            const int ialt = it->second;
                            const Word_Form &wf = *current_token->GetWordform();
                            const Word_Form *head = it->first;
                            const Word_Form *alt = head->GetVersion(ialt);

                            if (ialt == 0)
                            {
                                Word_Form wf0(wf, false);
                                wf0.Print(mem, &sg, true);
                            }
                            else
                            {
                                alt->Print(mem, &sg, true);
                            }

                            lem::UFString str_wordform = mem.string();

                            this->Print(mem, sg);
                            lem::UFString str_point = mem.string();

                            trace_log->GetMorphologyTracer().AddMatchingPoint(&wf, str_wordform, this, str_point);
                        }

                        log_tx->Commit();
                    }
#endif
                }
            }
            else
            {
                SynPatternResult *r = new SynPatternResult(parent_trace);

                LEM_CHECKIT_Z(current_token->GetPrev() != nullptr);

                // успешное сопоставление нулевой длины
                //r->res = SynPatternMatchResult(true,0,current_token,current_token->GetPrev(),NGramScore(0));
                r->res = SynPatternMatchResult(true, 0, current_token, current_token, NGramScore(0));

                if (links != nullptr)
                    GenerateLinks(dict.GetLexAuto(), r);

                if (ngrams != nullptr)
                    r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                if (pattern_constraints != nullptr)
                {
                    bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                    if (constraints_check)
                        results.push_back(r);
                    else
                        delete r;
                }
                else
                {
                    results.push_back(r);
                }
            }

#if defined SOL_DEBUGGING
            if (trace_log != nullptr)
            {
                trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
            }
#endif

            return !results.empty();
        }
        else
        {
            // остальные функции не могут работать за пределами вариатора, поэтому проверяем положение
            // курсора и сразу возвращаем false, если мы на правой границе.
            if (current_token->IsBeyondRight())
            {
#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return false;
            }

            const Word_Form &wf = *current_token->GetWordform();

            if (function_name.eqi(L"regex") || function_name.eqi(L"regex_strict"))
            {
                const lem::UCString & word = *wf.GetName();
                bool rx_matched = boost::regex_match(word.c_str(), rx);

                if (rx_matched)
                {
                    rx_matched = Match_WordformStrict(pm, sg, experience, current_token, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log);

                    /*
                             SynPatternResult *r = new SynPatternResult(parent_trace);
                             r->res = SynPatternMatchResult( true, 1, current_token, current_token, NGramScore(0) );

                             const int nalt = wf.VersionCount();
                             for( int ialt=0; ialt<nalt; ++ialt )
                             {
                             const Word_Form *alt = wf.GetVersion(ialt);
                             r->matched_alts.insert( std::make_pair(&wf,ialt) );
                             }

                             if( export_section!=nullptr )
                             {
                             export_section->ExportPairs_Unconditional(*r);
                             export_section->ExportNodes( *r, &wf );

                             if( export_section->ContainsFunctions() )
                             {
                             PatternExportFuncContext_Wordform export_context( &wf );
                             export_section->ExportByFunctions( *r, export_context );
                             }
                             }

                             if( links!=nullptr )
                             GenerateLinks( dict.GetLexAuto(), r );

                             if( ngrams!=nullptr )
                             r->res.SetNGramFreq( CalculateNGramFreq( dict, x_result, r, experience, trace_log ) );

                             if( pattern_constraints!=nullptr )
                             {
                             bool constraints_check = CheckConstraints( dict.GetLexAuto(), parent_trace, r );
                             if( constraints_check )
                             results.push_back(r);
                             else
                             {
                             rx_matched=false;
                             delete r;
                             }
                             }
                             else
                             {
                             results.push_back(r);
                             }
                             */
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return rx_matched;
            }
            else if (function_name.eqi(L"in_wordentry_set"))
            {
#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->BeforeMatchingTheWord(*this, id_src, lexer, current_token);
                }
#endif

                bool res = Match_WordentrySet(
                    pm,
                    sg,
                    experience,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    wordentry_sets,
                    results,
                    constraints,
                    trace_log
                );

                if (res)
                {
#if defined SOL_DEBUGGING
                    if (trace_log != nullptr)
                        log_tx->Commit();
#endif
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res;
            }
            else if (function_name.eqi(L"not_in_wordentry_set"))
            {
                const int nalt = wf.VersionCount();

                bool res = true;
                SynPatternResult *r = nullptr;

                for (int ialt = 0; ialt < nalt; ++ialt)
                {
                    const Word_Form *alt = wf.GetVersion(ialt);
                    if (wordentry_sets.FindWordEntrySet(str_arg, alt->GetEntryKey()))
                    {
                        // Одна из альтернатив попала под условия.
                        res = false;
                        break;
                    }
                }

                if (res)
                {
                    r = new SynPatternResult(parent_trace);

                    r->res = SynPatternMatchResult(res, res ? 1 : 0, current_token, current_token, NGramScore(0));

                    if (links != nullptr)
                        GenerateLinks(dict.GetLexAuto(), r);

                    if (ngrams != nullptr)
                        r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                    if (pattern_constraints != nullptr)
                    {
                        bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                        if (constraints_check)
                            results.push_back(r);
                        else
                        {
                            res = false;
                            delete r;
                        }
                    }
                    else
                    {
                        results.push_back(r);
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res;
            }
            else if (function_name.eqi(L"in_collocation_set"))
            {
                bool res = false;

                const lem::UCString & alt_word = *wf.GetName();

                // это слово может быть началом словосочетания?
                int min_len = 0, max_len = 0;
                if (wordentry_sets.IsCollocationHeadword(alt_word, min_len, max_len))
                {
                    // да. собираем пробные словосочетаний, с учетом максимальной и минимальной длины и размеров
                    // оставшегося хвоста предложения.

                    // запросим цепочку токенов длины до max_len, включая текущий токен.
                    // Сначала получим несколько конечных токенов. Двигаясь от конечного токена влево до current_token,
                    // получаем слова для сопоставления со словосочетанием.
                    lem::MCollect<const LexerTextPos*> final_tokens;
                    lexer.FetchN(current_token, max_len - 1, final_tokens);

                    /*
                    #if LEM_DEBUGGING==1
                    lem::mout->printf( "final_tokens.count=%d\n", final_tokens.size() );
                    for( int q=0; q<final_tokens.size(); ++q )
                    {
                    lem::mout->printf( "[%d] --> %us", q, final_tokens[q]->GetWordform()->GetName()->c_str() );
                    }
                    lem::mout->eol();
                    #endif
                    */

                    lem::MCollect<const LexerTextPos*> all_collocation_tokens;
                    lem::MCollect<lem::UCString> collocation_words;

                    // Каждый концевик final_tokens анализируем отдельно.
                    for (lem::Container::size_type t = 0; t < final_tokens.size(); ++t)
                    {
                        const LexerTextPos * final_token = final_tokens[t];
                        all_collocation_tokens.clear();
                        final_token->Collect_Right2Left(current_token, all_collocation_tokens);

                        /*
                        #if LEM_DEBUGGING==1
                        lem::mout->printf( "COLLOCATION: " );
                        for( int q=0; q<all_collocation_tokens.size(); ++q )
                        {
                        lem::mout->printf( " %us", all_collocation_tokens[q]->GetWordform()->GetName()->c_str() );
                        }
                        lem::mout->eol();
                        #endif
                        */

                        const int tail = CastSizeToInt(all_collocation_tokens.size());

                        collocation_words.clear();
                        for (int iword = 0; iword < tail; ++iword)
                        {
                            const lem::UCString &normalized_word = *all_collocation_tokens[tail - 1 - iword]->GetWordform()->GetNormalized();
                            collocation_words.push_back(normalized_word);
                        }

                        const int max_len2 = std::min(max_len, tail);

                        // Теперь формируем пробные словосочетания разной длины и проверяем их вхождение в набор.
                        // уменьшаем длину пробного словосочетания - так что можно просто убирать постепенно правый элемент.
                        for (int collocation_len = max_len2; collocation_len >= min_len; --collocation_len)
                        {
                            collocation_words.resize(collocation_len);

                            if (wordentry_sets.FindCollocation(str_arg, collocation_words))
                            {
                                // Эта комбинация подходит!

                                res = true;
                                SynPatternResult *r = new SynPatternResult(parent_trace);
                                const LexerTextPos * colloc_final_token = all_collocation_tokens[tail - collocation_len];
                                r->res = SynPatternMatchResult(true, collocation_len, current_token, colloc_final_token, NGramScore(0));

                                r->named_tree_invoked = true;

                                r->exported_nodes.push_back(std::make_pair(pm.GetDict().GetLexAuto().GetRootNodeName(), current_token->GetWordform()));

#if defined SOL_DEBUGGING
                                SynPatternDebugTrace dbg_point(this, current_token->GetWordform(), &str_arg);
                                r->Append(dbg_point);
#endif

                                if (export_section != nullptr)
                                {
                                    export_section->ExportPairs_Unconditional(*r);

                                    if (export_section->ContainsFunctions())
                                    {
                                        PatternExportFuncContext_Null export_context;
                                        export_section->ExportByFunctions(*r, export_context);
                                    }
                                }

                                for (int iword = 0; iword < collocation_len; ++iword)
                                {
                                    const Word_Form * wf = all_collocation_tokens[all_collocation_tokens.size() - 1 - iword]->GetWordform();
                                    const int nalt = wf->VersionCount();

                                    for (int ialt = 0; ialt < nalt; ++ialt)
                                    {
                                        const Word_Form *alt = wf->GetVersion(ialt);
                                        r->matched_alts.insert(std::make_pair(wf, ialt));
                                    }
                                }


                                // Генерируем связи от головного слова последовательно через все слова.
                                for (int ci = 0; ci < collocation_len - 1; ++ci)
                                {
                                    const int iword2 = all_collocation_tokens.size() - 1 - ci;
                                    const Word_Form * node0 = all_collocation_tokens[iword2]->GetWordform();
                                    const Word_Form * node1 = all_collocation_tokens[iword2 - 1]->GetWordform();
                                    PatternLinkEdge new_edge(node0, UNKNOWN, node1);
                                    r->AddLinkageEdge(new_edge);
                                }

                                if (links != nullptr)
                                    GenerateLinks(dict.GetLexAuto(), r);

                                if (ngrams != nullptr)
                                    r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                                if (pattern_constraints != nullptr)
                                {
                                    bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                                    if (constraints_check)
                                        results.push_back(r);
                                    else
                                        delete r;
                                }
                                else
                                {
                                    results.push_back(r);
                                }
                            }
                        }
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res && !results.empty();
            }
            else if (function_name.eqi(L"in_word_set"))
            {
#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->BeforeMatchingTheWord(*this, id_src, lexer, current_token);
                }
#endif

                bool res = Match_WordSet(
                    pm,
                    sg,
                    experience,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    wordentry_sets,
                    results,
                    constraints,
                    trace_log
                );

                if (res)
                {
#if defined SOL_DEBUGGING
                    if (trace_log != nullptr)
                        log_tx->Commit();
#endif
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res;
            }
            else if (function_name.eqi(L"not_in_word_set"))
            {
                const int nalt = CastSizeToInt(wf.GetAlts().size()) + 1;

                bool res = true;
                SynPatternResult *r = nullptr;

                for (int ialt = 0; ialt < nalt; ++ialt)
                {
                    const Word_Form *alt = wf.GetVersion(ialt);
                    if (wordentry_sets.FindWordSet(str_arg, *alt->GetName()))
                    {
                        // Одна из альтернатив попала под условия.
                        res = false;
                        break;
                    }
                }

                if (res)
                {
                    r = new SynPatternResult(parent_trace);
                    r->res = SynPatternMatchResult(res, res ? 1 : 0, current_token, current_token, NGramScore(0));

                    if (links != nullptr)
                        GenerateLinks(dict.GetLexAuto(), r);

                    if (ngrams != nullptr)
                        r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                    if (pattern_constraints != nullptr)
                    {
                        bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                        if (constraints_check)
                            results.push_back(r);
                        else
                        {
                            delete r;
                            res = false;
                        }
                    }
                    else
                    {
                        results.push_back(r);
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res;
            }
            else if (function_name.eqi(L"in_wordform_set"))
            {
                bool res = Match_WordformSet(
                    pm,
                    sg,
                    experience,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    wordentry_sets,
                    results,
                    constraints,
                    trace_log
                );

                if (res)
                {
#if defined SOL_DEBUGGING
                    if (trace_log != nullptr)
                        log_tx->Commit();
#endif
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res;
            }
            else if (function_name.eqi(L"not"))
            {
                lem::PtrCollect<SynPatternResult> subresults;
                bool res0 = args.front()->Equal(
                    banned_id_tree,
                    pm,
                    sg,
                    experience,
                    constraints,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    named_filters,
                    wordentry_sets,
                    false,
                    false,
                    can_skip_outer_tokens,
                    subresults,
                    trace_log,
                    recursion_depth + 1
                );

                if (!res0)
                {
                    for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
                    {
                        results.push_back(subresults[q]);
                        subresults[q] = nullptr;
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return !res0;
            }


            else if (function_name.eqi(L"untill"))
            {
                // Сдвигает курсор до тех пор, пока не найдется сопоставляющийся токен. Этот токен не включается в
                // в результат, то есть курсор помещается на него.

                bool res = Match_Untill(
                    banned_id_tree,
                    pm,
                    sg,
                    experience,
                    constraints,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    named_filters,
                    wordentry_sets,
                    results,
                    trace_log,
                    recursion_depth
                );

                if (res)
                {
#if defined SOL_DEBUGGING
                    if (trace_log != nullptr)
                        log_tx->Commit();
#endif
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res;
            }
            else if (function_name.eqi(L"noshift"))
            {
                // Эта функция проверяет, что с текущего места идет сопоставляемый фрагмент, но не сдвигает курсор.
                LEM_CHECKIT_Z(args.size() == 1);

                lem::PtrCollect<SynPatternResult> subresults;

                bool x = args.front()->Equal(
                    banned_id_tree,
                    pm,
                    sg,
                    experience,
                    constraints,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    named_filters,
                    wordentry_sets,
                    false,
                    force_export,
                    can_skip_outer_tokens,
                    subresults,
                    trace_log,
                    recursion_depth + 1
                );

                if (x)
                {
                    // делаем успешное сопоставление нулевой длины
                    SynPatternResult *r = new SynPatternResult(parent_trace);

                    r->res = SynPatternMatchResult(true, 0, current_token, current_token->GetPrev(), NGramScore(0));

                    if (links != nullptr)
                        GenerateLinks(dict.GetLexAuto(), r);

                    if (ngrams != nullptr)
                        r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                    if (pattern_constraints != nullptr)
                    {
                        bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                        if (constraints_check)
                            results.push_back(r);
                        else
                            delete r;
                    }
                    else
                    {
                        results.push_back(r);
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return x;
            }



            else if (function_name.eqi(L"probe_left"))
            {
                // Эта функция проверяет, что слева (один ***по умолчанию*** токен слева) находится что-то, сопоставляющееся с аргументом.
                LEM_CHECKIT_Z(args.size() == 1);

                lem::PtrCollect<SynPatternResult> subresults;

                bool x = false;

                if (current_token->GetPrev() != nullptr && current_token->IsRealWord())
                {
                    x = args.front()->Equal(
                        banned_id_tree,
                        pm,
                        sg,
                        experience,
                        constraints,
                        current_token->GetPrev(),
                        lexer,
                        parent_trace,
                        x_result,
                        named_filters,
                        wordentry_sets,
                        false,
                        force_export,
                        can_skip_outer_tokens,
                        subresults,
                        trace_log,
                        recursion_depth + 1
                    );
                }

                if (x)
                {
                    // делаем успешное сопоставление нулевой длины
                    SynPatternResult *r = new SynPatternResult(parent_trace);

                    r->res = SynPatternMatchResult(true, 0, current_token, current_token->GetPrev(), NGramScore(0));

                    if (links != nullptr)
                        GenerateLinks(dict.GetLexAuto(), r);

                    if (ngrams != nullptr)
                        r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                    if (pattern_constraints != nullptr)
                    {
                        bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                        if (constraints_check)
                            results.push_back(r);
                        else
                            delete r;
                    }
                    else
                    {
                        results.push_back(r);
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return x;
            }

            else if (function_name.eqi(L"or"))
            {
                bool matched = false;
                for (lem::Container::size_type i = 0; i < args.size(); ++i)
                {
                    lem::PtrCollect<SynPatternResult> subresults;

                    bool resi = args[i]->Equal(
                        banned_id_tree,
                        pm,
                        sg,
                        experience,
                        constraints,
                        current_token,
                        lexer,
                        parent_trace,
                        x_result,
                        named_filters,
                        wordentry_sets,
                        false,
                        force_export,
                        can_skip_outer_tokens,
                        subresults,
                        trace_log,
                        recursion_depth + 1
                    );

                    if (resi)
                    {
                        matched = true;

                        for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
                        {
                            SynPatternResult * q_result = subresults[q];

                            if (links != nullptr)
                                GenerateLinks(dict.GetLexAuto(), q_result);

                            if (ngrams != nullptr)
                                q_result->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, q_result, experience, constraints, trace_log));

                            if (pattern_constraints != nullptr)
                            {
                                bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, q_result);
                                if (constraints_check)
                                {
                                    results.push_back(q_result);
                                    subresults[q] = nullptr;
                                }
                            }
                            else
                            {
                                results.push_back(q_result);
                                subresults[q] = nullptr;
                            }
                        }

                        break;
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return matched && !results.empty();
            }
            else if (function_name.eqi(L"and"))
            {
                bool res = true;

                // логика проверки такая.
                // первая ветка - производитель экспортируемых наружу результатов.
                // последующие ветки дополнительно фильтруют первую, но ничего наружу не отдают.

                lem::PtrCollect<SynPatternResult> subresults1;

                bool x1 = args.front()->Equal(
                    banned_id_tree,
                    pm,
                    sg,
                    experience,
                    constraints,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    named_filters,
                    wordentry_sets,
                    false,
                    force_export,
                    can_skip_outer_tokens,
                    subresults1,
                    trace_log,
                    recursion_depth + 1
                );
                if (x1)
                {
                    for (lem::Container::size_type i = 1; i < args.size(); ++i)
                    {
                        lem::PtrCollect<SynPatternResult> ignored_subresults;

                        bool y = args[i]->Equal(
                            banned_id_tree,
                            pm,
                            sg,
                            experience,
                            constraints,
                            current_token,
                            lexer,
                            parent_trace,
                            x_result,
                            named_filters,
                            wordentry_sets,
                            false,
                            false,
                            can_skip_outer_tokens,
                            ignored_subresults,
                            trace_log,
                            recursion_depth + 1
                        );

                        if (!y)
                        {
                            res = false;
                            break;
                        }
                    }

                    if (res)
                    {
                        for (lem::Container::size_type q = 0; q < subresults1.size(); ++q)
                        {
                            SynPatternResult * r = subresults1[q];

                            if (links != nullptr)
                                GenerateLinks(dict.GetLexAuto(), r);

                            if (ngrams != nullptr)
                                r->res.SetNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

                            if (pattern_constraints != nullptr)
                            {
                                bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                                if (constraints_check)
                                {
                                    results.push_back(r);
                                    subresults1[q] = nullptr;
                                }
                            }
                            else
                            {
                                results.push_back(r);
                                subresults1[q] = nullptr;
                            }
                        }
                    }
                }
                else
                {
                    res = false;
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return res && !results.empty();
            }
            else if (function_name.eqi(L"do_not_filter"))
            {
                LEM_CHECKIT_Z(args.size() == 1);

                lem::PtrCollect<SynPatternResult> subresults;

                bool x = args.front()->Equal(
                    banned_id_tree,
                    pm,
                    sg,
                    experience,
                    constraints,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    named_filters,
                    wordentry_sets,
                    false,
                    false,
                    can_skip_outer_tokens,
                    subresults,
                    trace_log,
                    recursion_depth + 1
                );

                if (x)
                {
                    for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
                    {
                        subresults[q]->matched_alts.clear();
                        results.push_back(subresults[q]);
                        subresults[q] = nullptr;
                    }
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return x;
            }
            else if (function_name.eqi(L"all_versions"))
            {
                lem::PtrCollect<SynPatternResult> subresults;

                bool x = args.front()->Equal(
                    banned_id_tree,
                    pm,
                    sg,
                    experience,
                    constraints,
                    current_token,
                    lexer,
                    parent_trace,
                    x_result,
                    named_filters,
                    wordentry_sets,
                    false,
                    false,
                    can_skip_outer_tokens,
                    subresults,
                    trace_log,
                    recursion_depth + 1
                );

                if (x)
                {
                    // проверим, что все версии подошли.
                    for (int iver = 0; iver < wf.VersionCount(); ++iver)
                    {
                        const Word_Form *alt = wf.GetVersion(iver);

                        bool alt_found = false;
                        for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
                        {
                            if (subresults[q]->matched_alts.find(alt) != subresults[q]->matched_alts.end())
                            {
                                alt_found = true;
                                break;
                            }
                        }

                        if (!alt_found)
                        {
#if defined SOL_DEBUGGING
                            if (trace_log != nullptr)
                            {
                                trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                            }
#endif

                            return false;
                        }
                    }

#if defined SOL_DEBUGGING
                    if (trace_log != nullptr)
                    {
                        trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                    }
#endif

                    return true;
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
                }
#endif

                return false;
            }
            else
            {
                lem::MemFormatter mem;
                mem.printf("Unknown function in SynPatternPoint: %us", function_name.c_str());
                throw lem::E_BaseException(mem.string());
            }
        }
    } // if( !function_name.empty() ) ...
    else if (id_tree != UNKNOWN)
    {
        // Ссылка на именованное решающее дерево.
        return Match_NamedPatterns(
            banned_id_tree,
            pm, sg, experience, constraints, current_token, lexer, parent_trace, x_result,
            named_filters, wordentry_sets, force_greedy, force_export, can_skip_outer_tokens,
            results, trace_log, dbg_mark, *log_tx.get(), recursion_depth + 1
        );
    }
    else if (check_fun.NotNull())
    {
        if (current_token->IsBeyondRight())
        {
#if defined SOL_DEBUGGING
            if (trace_log != nullptr)
            {
                trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
            }
#endif

            return false;
        }

        TrFunContext ctx0((TrFunContext*)nullptr);
        //   TrContextInCondictor ctx( &ctx0, (Variator&)var, i0 );
        //   TrContextInvokation ctx2( &ctx );

        TrContextInvokation ctx2(&ctx0);

        lem::Ptr<TrValue> this_wordform(new TrValue(new Tree_Node(*current_token->GetWordform()), true));
        ctx2.AddVar(L"_", this_wordform);

        //   lem::Ptr<TrValue> this_var( new TrValue( var ) );
        //   ctx2.AddVar( L"_0", this_var );

        //   lem::Ptr<TrValue> this_pos( new TrIntValue( i0 ) );
        //   ctx2.AddVar( L"_i", this_pos );

        lem::Ptr<TrValue> fun_res = check_fun->Run(constraints, pm, ctx2, trace_log);

        if (fun_res->GetType().IsBool())
        {
            const bool fun_matched = fun_res->GetBool();

#if defined SOL_DEBUGGING
            if (trace_log != nullptr)
            {
                trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
            }
#endif

            return fun_matched;
        }
        else
        {
#if LEM_DEBUGGING==1
            if (trace_log != nullptr)
                trace_log->PrintStack(*lem::mout);
#endif

            lem::UFString msg(lem::format_str(L"Point check function must return bool, not %s", fun_res->GetType().GetName().c_str()));
            throw E_BaseException(msg.c_str());
        }
    }

    if (current_token->IsBeyondRight())
    {
#if defined SOL_DEBUGGING
        if (trace_log != nullptr)
        {
            trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
        }
#endif

        return false;
    }

#if defined SOL_DEBUGGING
    if (trace_log != nullptr)
    {
        trace_log->BeforeMatchingTheWord(*this, id_src, lexer, current_token);
    }
#endif

    bool any_matched = Match_Wordform(
        pm,
        sg,
        experience,
        current_token,
        lexer,
        parent_trace,
        x_result,
        wordentry_sets,
        results,
        constraints,
        trace_log
    );

#if defined SOL_DEBUGGING
    if (trace_log != nullptr)
    {
        if (any_matched)
            log_tx->Commit();

        trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token, parent_trace));
    }
#endif

    return any_matched;
}

#endif




#if defined SOL_CAA
bool SynPatternPoint::Execute_Mark(
    int banned_it_tree,
    PM_Automat &pm,
    SynGram &sg,
    TreeMatchingExperience &experience,
    const ElapsedTimeConstraint & constraints,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace *parent_trace,
    const SynPatternResultBackTrace * x_result,
    LA_SynPatternTrees &named_filters,
    WordEntrySet &wordentry_sets,
    bool force_greedy,
    bool force_export,
    bool can_skip_outer_tokens,
    lem::PtrCollect<SynPatternResult> & results,
    TrTrace *trace_log,
    int recursion_depth
) const
{
    lem::PtrCollect<SynPatternResult> subresults;
    bool matched1 = args.front()->Equal(
        banned_it_tree,
        pm,
        sg,
        experience,
        constraints,
        current_token,
        lexer,
        parent_trace,
        x_result,
        named_filters,
        wordentry_sets,
        false,
        true,
        can_skip_outer_tokens,
        subresults,
        trace_log,
        recursion_depth + 1
    );

    if (matched1)
    {
        Dictionary & dict = pm.GetDict();

        for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
        {
            SynPatternResult * subresult_q = subresults[q];

            SynPatternResult *r = new SynPatternResult(parent_trace);
            r->res = subresult_q->res;

#if defined SOL_DEBUGGING
            r->debug_trace = subresult_q->debug_trace;
#endif

            if (export_section != nullptr)
            {
                // маркировка может экспортировать что-то наружу, для этого применяется синтаксис:
                // @mark( дерево, имя ) : export( координаты )

                /*
                       // состояния всех заданных координат
                       if( !export_section->export_coords.empty() )
                       {
                       if( !subresult_q->named_tree_invoked && !subresults[q]->matched_alts.empty() )
                       {
                       // маркировка для одиночной словоформы (???)
                       const int ialt = subresult_q->matched_alts.begin()->second;
                       const Word_Form * wf0 = subresult_q->matched_alts.begin()->first;
                       const Word_Form * alt = wf0->GetVersion(ialt);

                       for( lem::Container::size_type t=0; t<export_section->export_coords.size(); ++t )
                       {
                       IntCollect states = alt->GetStates( export_section->export_coords[t] );
                       for( lem::Container::size_type u=0; u<states.size(); ++u )
                       {
                       r->exported_coords.insert( std::make_pair( export_section->export_coords[t], states[u] ) );
                       }
                       }

                       // ...
                       }

                       for( std::multimap<int,int>::const_iterator it=subresult_q->exported_coords.begin(); it!=subresult_q->exported_coords.end(); ++it )
                       {
                       if( export_section->export_coords.find(it->first)!=UNKNOWN )
                       r->exported_coords.insert(*it);
                       }
                       }
                       */

                if (!subresult_q->named_tree_invoked)
                {
                    if (!subresults[q]->matched_alts.empty())
                    {
                        // маркировка для одиночной словоформы
                        const int ialt = subresult_q->matched_alts.begin()->second;
                        const Word_Form * wf0 = subresult_q->matched_alts.begin()->first;
                        const Word_Form * alt = wf0->GetVersion(ialt);
                        export_section->ExportCoords_Unconditional(*r, alt);

                        if (export_section->ContainsFunctions())
                        {
                            PatternExportFuncContext_Wordform export_context(alt);
                            export_section->ExportByFunctions(*r, export_context);
                        }
                    }
                    else
                    {
                        // ???
                        LEM_STOPIT;
                    }
                }
                else
                {
                    for (std::multimap<int, int>::const_iterator it = subresult_q->exported_coords.begin(); it != subresult_q->exported_coords.end(); ++it)
                    {
                        if (export_section->export_coords.find(it->first) != UNKNOWN)
                            r->exported_coords.insert(*it);
                    }

                    if (export_section->ContainsFunctions())
                    {
                        lem::MCollect< std::pair<int, int> > raw_tree_export;
                        subresults[q]->GetExportCoordPairs(raw_tree_export);
                        PatternExportFuncContext_Tree export_context(raw_tree_export, parent_trace, PatternSequenceNumber);
                        export_section->ExportByFunctions(*r, export_context);
                    }
                }

                // заданные координатные пары
                export_section->ExportPairs_Unconditional(*r);

                // именованные маркировки
                if (!export_section->export_nodes.empty())
                {
                    // пробросим наружу также экспортируемые ссылки на словоформы
                    if (!subresult_q->named_tree_invoked && !subresult_q->matched_alts.empty())
                    {
                        // маркировка для одиночной словоформы
                        const int ialt = subresult_q->matched_alts.begin()->second;
                        const Word_Form * wf0 = subresult_q->matched_alts.begin()->first;
                        const Word_Form * alt = wf0->GetVersion(ialt);

                        for (lem::Container::size_type p = 0; p < export_section->export_nodes.size(); ++p)
                            r->AddExportedNode(&export_section->export_nodes[p].as_name, alt);
                    }
                    else
                    {
                        // Найдем в экспорте subresult нужные нам ссылки и перебросим их наружу
                        for (lem::Container::size_type p = 0; p < export_section->export_nodes.size(); ++p)
                        {
                            const lem::UCString & name_to_find = export_section->export_nodes[p].node_name;
                            const Word_Form * export_wf = subresult_q->FindExportNode(name_to_find);

                            if (export_wf != nullptr)
                                r->AddExportedNode(&export_section->export_nodes[p].as_name, export_wf);
                            else
                            {
                                lem::MemFormatter mem;
                                mem.printf("Can not find node %us to export", name_to_find.c_str());
                                throw lem::E_BaseException(mem.string());
                            }
                        }
                    }
                }

            }

            if (subresults[q]->named_tree_invoked)
            {
                r->matched_alts = subresult_q->matched_alts;

                CP_Array exported;
                for (std::multimap<int, int>::const_iterator it3 = subresult_q->exported_coords.begin(); it3 != subresult_q->exported_coords.end(); ++it3)
                    exported.push_back(Solarix::GramCoordPair(it3->first, it3->second));

                if (subresult_q->exported_nodes.empty())
                {
                    BackTraceItem & added = r->trace.Add(PatternSequenceNumber, mark_name.GetName(), exported);
                    added.SetRange(current_token, subresult_q->res.GetFinalToken());

                    const Word_Form * root_node = subresult_q->FindExportNode(*dict.GetLexAuto().GetRootNodeName());
                    if (root_node != nullptr)
                        added.SetHeadWord(root_node);
                }
                else
                {
                    BackTraceItem & added = r->trace.Add(PatternSequenceNumber, mark_name.GetName(), exported);
                    added.SetExportedNodes(subresult_q->exported_nodes);

                    const Word_Form * root_node = subresult_q->FindExportNode(*dict.GetLexAuto().GetRootNodeName());
                    if (root_node != nullptr)
                        added.SetHeadWord(root_node);

                    added.SetRange(current_token, subresult_q->res.GetFinalToken());
                }
            }
            else
            {
                if (!subresult_q->matched_alts.empty())
                {
                    const int ialt = subresult_q->matched_alts.begin()->second;
                    const Word_Form * wf0 = subresult_q->matched_alts.begin()->first;
                    const Word_Form * alt = wf0->GetVersion(ialt);

                    r->matched_alts = subresult_q->matched_alts;
                    BackTraceItem & added = r->trace.Add(PatternSequenceNumber, mark_name.GetName(), alt);

                    added.SetRange(subresult_q->res.GetStartToken(), subresult_q->res.GetFinalToken());
                }
            }

            r->linkage_groups = subresult_q->linkage_groups;
            r->linkage_edges = subresult_q->linkage_edges;

            if (links != nullptr)
                GenerateLinks(dict.GetLexAuto(), r);

            if (ngrams != nullptr)
                r->res.AddNGramFreq(CalculateNGramFreq(dict, x_result, r, experience, constraints, trace_log));

            if (pattern_constraints != nullptr)
            {
                bool constraints_check = CheckConstraints(dict.GetLexAuto(), parent_trace, r);
                if (constraints_check)
                    results.push_back(r);
                else
                    delete r;
            }
            else
            {
                results.push_back(r);
            }
        }

        if (results.empty())
            matched1 = false;
    }

    return matched1;
}
#endif


#if defined SOL_CAA
bool SynPatternPoint::Match_NamedPatterns(
    int banned_id_tree,
    PM_Automat &pm,
    SynGram &sg,
    TreeMatchingExperience &experience,
    const ElapsedTimeConstraint & constraints,
    const LexerTextPos * current_token0,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    LA_SynPatternTrees & named_filters,
    WordEntrySet &wordentry_sets,
    bool force_greedy,
    bool force_export,
    bool can_skip_outer_tokens,
    lem::PtrCollect<SynPatternResult> & results,
    TrTrace *trace_log,
    int dbg_mark,
    TrMorphologyTracerTx & log_tx,
    int recursion_depth
) const
{
    if (current_token0->IsBeyondRight())
    {
#if defined SOL_DEBUGGING
        if (trace_log != nullptr)
        {
            trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token0, parent_trace));
        }
#endif

        return false;
    }

    bool tree_matched = false;

    if (Match_NamedPatterns_Strict(
        banned_id_tree,
        pm, sg, experience, constraints, current_token0, lexer, parent_trace, x_result,
        named_filters, wordentry_sets, force_greedy, force_export,
        results, trace_log, dbg_mark, log_tx, recursion_depth
    ))
    {
        tree_matched = true;
    }

    const bool orig_token_matched = tree_matched;

    // если разрешен пропуск токенов - то выполняем его, вне зависимости от успешности текущего сопоставления.
    if (current_token0->IsRealWord() && can_skip_outer_tokens) // граничные токены не будем пропускать
    {
        lem::MCollect<const LexerTextPos *> current_tokens;
        lem::MCollect<int> skip_scores;
        lem::MCollect<SynPatternResult*> skipped_results;

        lem::PtrCollect<SynPatternResult> gc_skipped_results; // для сборки мусора

        lem::PtrCollect<SynPatternResult> skiprule_results;

        const int MAX_ALTS = lexer.GetParams().timeout.max_alt;

        // проход №1 - пропуск по правилам
        // проход №2 - пропуск любых токенов
        for (int skip_pass = 0; skip_pass < 2; skip_pass++)
        {
            current_tokens.clear();
            skip_scores.clear();
            skipped_results.clear();
            gc_skipped_results.clear();

            const int SKIP_TOKEN_SCORE = -5;

            if (skip_pass == 1)
            {
                if ((can_skip_outer_tokens && lexer.GetParams().CanSkipOuterTokens()) && lexer.GetParams().MaxSkipToken > 0)
                {
                    // разрешен пропуск любых токенов.
                    // мы пропустим от 1 до макс. значения участок от current_token0.
                    const int MAX_SKIP_TOKEN = lexer.GetParams().MaxSkipToken;

                    int skip_count = 0;

                    int list_selector = 0;
                    lem::MCollect<const LexerTextPos *> cur_tokens[2];
                    cur_tokens[0].push_back(current_token0);

                    do
                    {
                        skip_count++;

                        bool fetched = false;
                        cur_tokens[(list_selector + 1) % 2].clear();

                        for (lem::Container::size_type k = 0; k < cur_tokens[list_selector % 2].size(); ++k)
                        {
                            const LexerTextPos * t = cur_tokens[list_selector % 2][k];

                            if (!t->IsEnd())
                            {
                                fetched = fetched || lexer.Fetch(t, cur_tokens[(list_selector + 1) % 2]);
                            }
                        }

                        if (!fetched)
                            break;

                        for (lem::Container::size_type k = 0; k < cur_tokens[(list_selector + 1) % 2].size(); ++k)
                        {
                            const LexerTextPos * t = cur_tokens[(list_selector + 1) % 2][k];
                            if (t->IsEnd() || t->IsBeyondRight())
                                continue;

                            current_tokens.push_back(t);
                            skipped_results.push_back(nullptr);
                            const int score = skip_count*SKIP_TOKEN_SCORE;
                            skip_scores.push_back(score);
                        }

                        list_selector++;
                    } while (skip_count < MAX_SKIP_TOKEN && current_tokens.size() < MAX_ALTS);
                }
            }

            bool tree_matched_with_skip = false;

            // есть набор токенов, с которых следует проверять сопоставляемость...
            for (lem::Container::size_type icur = 0; icur < current_tokens.size(); ++icur)
            {
                const LexerTextPos * current_token = current_tokens[icur];

                lem::PtrCollect<SynPatternResult> subresults;

                bool l1 = Match_NamedPatterns_Strict(
                    banned_id_tree,
                    pm, sg, experience, constraints, current_token, lexer, parent_trace, x_result,
                    named_filters, wordentry_sets, force_greedy, force_export,
                    subresults, trace_log, dbg_mark, log_tx, recursion_depth + 1
                );

                for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
                {
                    SynPatternResult * subresult_q = subresults[q];

#if defined SOL_DEBUGGING
                    SynPatternDebugTrace dbg;
                    dbg.ngram_freq = NGramScore(skip_scores[icur]);
                    dbg.scoring_reason = "Skip token";
                    subresult_q->debug_trace.push_back(dbg);
#endif

                    if (skip_scores[icur] != 0 || orig_token_matched)
                    {
                        // добавляем штраф за пропуск токенов.
                        // если было сопоставление в начальном токене (где находится текущий курсор), то штраф усиливаем.
                        int score = skip_scores[icur];
                        if (orig_token_matched)
                        {
                            score = (skip_scores[icur] - 1) * 2;
                        }

                        subresult_q->res.AddNGramFreq(NGramScore(score));
                    }

                    if (skipped_results[icur] != nullptr)
                    {
                        const SynPatternResult & skipped_result = *skipped_results[icur];

                        // скопируем в сопоставленный результат затронутые словоформы из пропущенного фрагмента.
                        subresult_q->AppendMatchedAlts(skipped_result);

                        // Могут быть варианты: есть корень с привязанными узлами, корня нет.
                        // Если есть корень, то добавим еще ребро к основному корню.

                        bool linked_by_roots = false;
                        const Word_Form * skipped_root_node = skipped_result.FindExportNode(*pm.GetDict().GetLexAuto().GetRootNodeName());
                        if (skipped_root_node != nullptr)
                        {
                            const Word_Form * matched_root_node = subresult_q->FindExportNode(*pm.GetDict().GetLexAuto().GetRootNodeName());
                            if (matched_root_node != nullptr)
                            {
                                linked_by_roots = true;
                                PatternLinkEdge root2root(matched_root_node, UNKNOWN, skipped_root_node);
                                subresult_q->AddLinkageEdge(root2root);

                                // Скопируем сюда все связи из пропущенного фрагмента.
                                subresult_q->AppendLinks(skipped_result);
                            }
                        }

                        /*
                        if( !linked_by_roots )
                        {
                        // так как невозможно просто связать корень пропущенного фрагмента с корнем сопоставленного участка, то
                        // придется присоединять группу, созданную из пропущенного фрагмента, к первому токену сопоставленного.
                        const Word_Form * skipped_root_node = skipped_result.res.GetStartToken()->GetWordform();
                        PatternSynLinkedGroup skipped_grp( skipped_result.res.GetStartToken(), skipped_result.res.GetFinalToken(), skipped_root_node );
                        subresult_q->AddLinkageGroup(skipped_grp);

                        const Word_Form * matched_root_node = subresult_q->res.GetStartToken()->GetWordform();
                        PatternLinkEdge new_edge( matched_root_node, UNKNOWN, skipped_root_node );
                        subresult_q->AddLinkageEdge(new_edge);
                        }
                        */
                    }

#if defined SOL_DEBUGGING
                    // Для удобства визуального контроля добавим в трассу инфу об имени вызванного дерева.
                    const lem::UCString & tree_name0 = named_filters.GetPatternName(id_tree);
                    SynPatternDebugTrace dbg_point(this, current_token->GetWordform(), &tree_name0);
                    subresult_q->Append(dbg_point);
#endif

                    results.push_back(subresult_q);
                    subresults[q] = nullptr;
                    tree_matched = tree_matched_with_skip = true;
                }

                // количество найденных результатов достигло допустимого максимума, дальше не проверяем.
                if ((results.size()) > MAX_ALTS * 2)
                    break;
            }

            // после успешного обнаружения сопоставления прекращает дальнейший поиск. это означает, что
            // некоторые решения не будут найдены, так как для них требуется проверить ВСЕ варианты, включая
            // начальное сопоставление и с пропуском. Но такой подход дает преимущество в скорости.
            if (tree_matched_with_skip)
            {
                // обновим кэш ????
                break;
            }
        }
    }

#if defined SOL_DEBUGGING
    if (trace_log != nullptr)
    {
        log_tx.Commit();
        trace_log->GetMorphologyTracer().PopCurrentTree();
        trace_log->Leave(new SynPatternPointCall(dbg_mark, id_src, this, current_token0, parent_trace));
    }
#endif

    return tree_matched;
}
#endif








#if defined SOL_CAA
bool SynPatternPoint::Match_NamedPatterns_Strict(
    int banned_id_tree,
    PM_Automat &pm,
    SynGram &sg,
    TreeMatchingExperience &experience,
    const ElapsedTimeConstraint & constraints,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace *parent_trace,
    const SynPatternResultBackTrace * x_result,
    LA_SynPatternTrees &named_filters,
    WordEntrySet &wordentry_sets,
    bool force_greedy,
    bool force_export,
    lem::PtrCollect<SynPatternResult> & results,
    TrTrace *trace_log,
    int dbg_mark,
    TrMorphologyTracerTx & log_tx,
    int recursion_depth
) const
{
    bool tree_matched = false;

    bool l1;
    lem::PtrCollect<SynPatternResult> subresults;

    /*
         #if LEM_DEBUGGING==1
         lem::UCString tree_name = sg.GetStorage().GetSynPatternTreeName(id_tree);
         if( tree_name.eqi(L"ГруппаСущ4") && current_token->GetWordIndex()==3 )
         {
         for( lem::Container::size_type k=0; k<id_src.size(); ++k )
         {
         int file=UNKNOWN, line=UNKNOWN, column=UNKNOWN;
         sg.GetDict().GetDebugSymbols().GetLocation( id_src[k], file, line, column );

         if( line==2985 )
         {
         lem::mout->printf( "BEFORE rule=%us current_token=%us word_index=%d\n", tree_name.c_str(), current_token->GetWordform()->GetName()->c_str(), current_token->GetWordIndex() );
         lem::mout->eol();
         }
         }
         }
         #endif
         */


#if defined SOL_DEBUGGING
    if (trace_log != nullptr)
    {
        // точка останова ДО выполнения проверки.
        trace_log->BeforeSynPatternTreeProve(*this, id_src, lexer, current_token, parent_trace);
    }
#endif


    const TreeMatchingExperienceItem * found_experience = experience.Find(id_tree, current_token);
    if (found_experience != nullptr)
    {
        l1 = found_experience->success;
        found_experience->Copy(parent_trace, subresults);
    }
    else
    {
        if (banned_id_tree == id_tree)
            return false;

        const SynPatternTreeNode & tree = named_filters.GetNamedFilter(id_tree);

#if defined SOL_DEBUGGING
        const lem::UCString & pattern_name = named_filters.GetPatternName(id_tree);
        if (trace_log != nullptr)
        {
            trace_log->GetMorphologyTracer().PushCurrentTree(pattern_name);
        }
#endif

        l1 = tree.MatchTree(
            id_tree,
            pm,
            sg,
            experience,
            constraints,
            named_filters,
            wordentry_sets,
            lexer,
            current_token,
            parent_trace,
            x_result,
            greedy,
            false,
            subresults,
            trace_log,
            recursion_depth
        );

        experience.Add(id_tree, current_token, l1, subresults);
    }

    if (l1)
    {
#if defined SOL_DEBUGGING
        if (trace_log != nullptr && l1)
        {
            trace_log->SynPatternTreeProved(*this, id_src, lexer, current_token, subresults);
        }
#endif


        /*
         #if LEM_DEBUGGING==1
         if( id_tree==15 )
         {
         lem::UCString tree_name = sg.GetStorage().GetSynPatternTreeName(id_tree);
         lem::mout->printf( "AFTER rule=%us current_token=%us word_index=%d\n", tree_name.c_str(), current_token->GetWordform()->GetName()->c_str(), current_token->GetWordIndex() );

         for( lem::Container::size_type q=0; q<subresults.size(); ++q )
         {
         const SynPatternResult * subresult_q = subresults[q];

         lem::mout->printf( "RESULT[%d]\n", q );

         for( int k=0; k<subresult_q->debug_trace.size(); ++k )
         {
         const SynPatternDebugTrace & t = subresult_q->debug_trace[k];

         lem::mout->printf( "debug[%d]-->", k );
         if( t.pattern_name!=nullptr )
         lem::mout->printf( " pattern=%us", t.pattern_name->c_str() );

         if( t.wordform!=nullptr )
         lem::mout->printf( " wordform=%us", t.wordform->GetName()->c_str() );

         lem::mout->eol();
         }

         }

         lem::mout->eol();
         }
         #endif
         */

         // Для каждого варианта сопоставления дерева выполняем отдельную проверку.

        for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
        {
            SynPatternResult * subresult_q = subresults[q];

            subresult_q->named_tree_invoked = true;

            const std::multimap<int, int> & exported_coords = subresult_q->exported_coords;

            bool set_ok = true;
            bool coords_matched = false;

            int check_score = 0; // если нарушение условий наказывается штрафом, а не полным провалом проверки.

            if (coords.empty())
            {
                // проверять координаты, экспортированные вызванным деревом, не требуется.
                coords_matched = true;
            }
            else
            {
                // если необходима проверка экспортированных из вызванного дерева координат
                bool states_matched = true;
                for (lem::Container::size_type i = 0; i < coords.size(); ++i)
                {
                    const int id_coord = coords[i].GetPair().GetCoord().GetIndex();
                    const int id_state = coords[i].GetPair().GetState();

                    bool state_matched = false;

                    // Ищем состояния этой координаты в экспорте
                    typedef std::multimap<int, int>::const_iterator IT;
                    std::pair<IT, IT> p = exported_coords.equal_range(id_coord);
                    if (p.first == p.second)
                    {
                        // не нашли необходимой координаты вообще.
                        // если требование - бистабильная координата с состоянием 0, то это успех,
                        // в остальных случаях имеем неуспех.
                        if (sg.coords()[id_coord].IsBistable())
                        {
                            if (id_state == 0)
                            {
                                state_matched = true;
                            }
                        }
                        else
                        {
                            if (!coords[i].GetPair().GetAffirm()) // требование было чтобы пара отсутствовала.
                                state_matched = true;
                        }
                    }
                    else
                    {
                        if (coords[i].GetPair().GetAffirm())
                        {
                            for (IT it = p.first; it != p.second; ++it)
                            {
                                if (it->second == id_state)
                                {
                                    state_matched = true;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            state_matched = true;
                            for (IT it = p.first; it != p.second; ++it)
                            {
                                if (it->second == id_state)
                                {
                                    state_matched = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (!state_matched)
                    {
                        if (coords[i].GetViolationHandler().HasFalseScore())
                        {
                            // мягкое нарушение - выписываем штраф.
                            check_score += coords[i].GetViolationHandler().GetFalseScore();
                        }
                        else
                        {
                            states_matched = false;
                            break;
                        }
                    }
                }

                if (states_matched)
                {
                    // все координаты есть в экспорте.
                    coords_matched = true;
                }
            }


            if (coords_matched && correl_fun.NotNull())
            {
                // Вызываем корреляционную функцию для императивных проверок

                //TrFunContext ctx0( &*pm.functions.static_vars, &env );
#if LEM_DEBUGGING
                //matching_vars.PrintVars( sg.GetDict(), *mout );
#endif

                //       TrFunContext ctx0( &matching_vars, &env );
                //       TrContextInCondictor ctx( &ctx0, (Variator&)var, i0 );

                TrFunContext ctx0((TrFunContext*)nullptr);
                TrContextInvokation ctx2(&ctx0);
                ctx2.AddVar(L"((return))", lem::Ptr<TrValue>(new TrTypeValue(TrVariantType())));


                const Word_Form * alt = subresult_q->FindExportNode(L"ROOT_NODE");
                if (alt == nullptr)
                {
                    lem::MemFormatter mem;
                    mem.printf("Can not find exported node %us for set checker", L"ROOT_NODE");
                    throw lem::E_BaseException(mem.string());
                }

                lem::Ptr<TrValue> this_wordform(new TrValue(new Tree_Node(new Word_Form(*alt, false), true), true));
                ctx2.AddVar(L"_", this_wordform);

                lem::Ptr<TrValue> ret = correl_fun->Run(constraints, sg.GetDict().GetLexAuto(), ctx2, trace_log);

                //lem::Ptr<TrValue> p = ctx2.GetVar(L"((return))");

                if (ret->GetType().IsBool())
                {
                    coords_matched = ret->GetBool();
                }
                else if (ret->GetType().IsInt())
                {
                    coords_matched = true;
                    check_score += ret->GetInt();
                }
                else
                {
#if LEM_DEBUGGING==1
                    if (trace_log != nullptr)
                        trace_log->PrintStack(*lem::mout);
#endif

                    lem::UFString msg(lem::format_str(L"Can not use lambda function: inappropriate return type=%s", ret->GetType().GetName().c_str()));
                    throw E_BaseException(msg.c_str());
                }
            }



            if (coords_matched)
            {
                if (!set_checkers.empty())
                {
                    const Word_Form * alt0 = nullptr;

                    for (lem::Container::size_type k = 0; k < set_checkers.size(); ++k)
                    {
                        if (set_checkers[k].RequiresNamedNode())
                        {
                            const Word_Form * altx = subresult_q->FindExportNode(set_checkers[k].GetNodeName());
                            if (altx == nullptr)
                            {
                                lem::MemFormatter mem;
                                mem.printf("Can not find exported node %us for set checker", set_checkers[k].GetNodeName().c_str());
                                throw lem::E_BaseException(mem.string());
                            }

                            if (!set_checkers[k].Check(sg, *altx, wordentry_sets))
                            {
                                if (set_checkers[k].GetViolationHandler().HasFalseScore())
                                {
                                    // мягкое нарушение - выписываем штраф.
                                    check_score += set_checkers[k].GetViolationHandler().GetFalseScore();
                                    set_ok = true;
                                }
                                else
                                {
                                    set_ok = false;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (alt0 == nullptr)
                            {
                                if (subresult_q->res.Length() == 1)
                                {
                                    const Word_Form * wf = subresult_q->matched_alts.begin()->first;
                                    int iver = subresult_q->matched_alts.begin()->second;
                                    alt0 = wf->GetVersion(iver);
                                }
                                else
                                {
                                    alt0 = subresult_q->FindExportNode(L"ROOT_NODE");
                                    if (alt0 == nullptr)
                                    {
                                        lem::MemFormatter mem;
                                        mem.printf("Can not find exported node ROOT_NODE for set checker");
                                        throw lem::E_BaseException(mem.string());
                                    }
                                }
                            }

                            if (!set_checkers[k].Check(sg, *alt0, wordentry_sets))
                            {
                                if (set_checkers[k].GetViolationHandler().HasFalseScore())
                                {
                                    // мягкое нарушение - выписываем штраф.
                                    check_score += set_checkers[k].GetViolationHandler().GetFalseScore();
                                    set_ok = true;
                                }
                                else
                                {
                                    set_ok = false;
                                    break;
                                }

                                break;
                            }
                        }
                    }
                }

                if (set_ok)
                {
                    // проверим согласования с левыми маркировками
                    bool back_states_matched = true;

                    // Проверяем согласования с левыми маркированными точками
                    for (lem::Container::size_type k = 0; k < back_correls.size(); ++k)
                    {
                        const lem::UCString &mark = back_correls[k].name; // искомая маркировка
                        const BackTraceItem & mark_data = *parent_trace->Get(PatternSequenceNumber, mark);

                        if (!mark_data.Check(sg, back_correls[k], exported_coords))
                        {
                            if (back_correls[k].GetViolationHandler().HasFalseScore())
                            {

#if LEM_DEBUGGING==1

                                lem::mout->printf("check=>");
                                back_correls[k].SaveTxt(*lem::mout, sg);
                                lem::mout->eol();

                                lem::mout->printf("\n\nmark_data=>");
                                mark_data.Print(*lem::mout, sg, true);

                                lem::mout->printf("\n\nexported_coords=");
                                for (std::multimap<int, int>::const_iterator it = exported_coords.begin(); it != exported_coords.end(); ++it)
                                {
                                    lem::mout->printf(" %us", sg.coords().GetCoord(it->first).GetName().string().c_str());

                                    if (!sg.coords().GetCoord(it->first).IsBistable())
                                    {
                                        lem::mout->printf(":");
                                        lem::mout->printf("%us", sg.coords().GetCoord(it->first).GetStateName(it->second).c_str());
                                    }
                                    else
                                    {
                                        lem::mout->printf(":=%d", it->second);
                                    }
                                }
                                lem::mout->eol();

#endif
                                /*                                */

                                check_score += back_correls[k].GetViolationHandler().GetFalseScore();
                            }
                            else
                            {
                                back_states_matched = false;
                                break;
                            }
                        }
                    }

                    // выполняем обращения к базе знаний
                    if (back_states_matched)
                    {
                        bool kb_ok = true;
                        if (!kb_checkers.empty())
                        {
                            // В subresults[q]->exported_nodes именованные ссылки для текущего дерева _.y
                            // В parent_trace надо искать именованные ссылки вида X.y

                            KnowledgeBase &kbase = sg.GetDict().GetLexAuto().GetKnowledgeBase();

                            for (lem::Container::size_type i = 0; i < kb_checkers.size(); ++i)
                            {
                                const KB_Checker & checker = *kb_checkers[i];

                                KB_CheckerReturn check_result = checker.Check(PatternSequenceNumber, parent_trace, subresult_q, nullptr, kbase, experience);
                                kb_ok = check_result.success;
                                if (!kb_ok)
                                    break;

                                check_score += check_result.false_score;
                            }
                        }

                        if (kb_ok && ThesaurusCheck_Link != UNKNOWN)
                        {
                            // ищем HEAD в результате сопоставления дерева
                            const Word_Form * headword = nullptr;
                            if (subresult_q->res.Length() == 1)
                            {
                                const Word_Form * wf = subresult_q->matched_alts.begin()->first;
                                int iver = subresult_q->matched_alts.begin()->second;
                                headword = wf->GetVersion(iver);
                            }
                            else
                            {
                                headword = subresult_q->FindExportNode(L"ROOT_NODE");
                                if (headword == nullptr)
                                {
                                    lem::MemFormatter mem;
                                    mem.printf("Can not find exported node ROOT_NODE for thesaurus checker");
                                    throw lem::E_BaseException(mem.string());
                                }
                            }

                            // проверяем, что данная статья связана в тезаурусе в указанной статьей заданным типом связи
                            int id_link = sg.Get_Net().Find_Linked_Entry(headword->GetEntryKey(), ThesaurusCheck_Link, ThesaurusCheck_Entry);
                            kb_ok = id_link != UNKNOWN;
                        }

                        if (kb_ok)
                        {
                            if (export_section != nullptr)
                            {
                                lem::MCollect< std::pair<int, int> > raw_tree_export;

                                if (export_section->ContainsFunctions())
                                {
                                    subresult_q->GetExportCoordPairs(raw_tree_export);
                                }

                                if (!force_export)
                                {
                                    subresult_q->FilterExportedCoords(export_section->export_coords);

                                    subresult_q->FilterExportedNodes(export_section->export_nodes);

#if defined SOL_DEBUGGING==1
                                    for (lem::Container::size_type ii = 0; ii < export_section->export_nodes.size(); ++ii)
                                    {
                                        if (!subresult_q->FindExportedNode(export_section->export_nodes[ii].as_name))
                                        {
                                            lem::MemFormatter mem;
                                            mem.printf("Can not find exported node %us to re-export", export_section->export_nodes[ii].as_name.c_str());
                                            throw lem::E_BaseException(mem.string());
                                        }
                                    }
#endif
                                }

                                export_section->ExportPairs_Unconditional(*subresult_q);

                                if (export_section->ContainsFunctions())
                                {
                                    PatternExportFuncContext_Tree export_context(raw_tree_export, parent_trace, PatternSequenceNumber);
                                    export_section->ExportByFunctions(*subresult_q, export_context);
                                }
                            }

#if defined SOL_DEBUGGING
                            // Для удобства визуального контроля добавим в трассу инфу об имени вызванного дерева.
                            SynPatternDebugTrace dbg_point(this, current_token->GetWordform(), &named_filters.GetPatternName(id_tree));
                            subresult_q->Append(dbg_point);
#endif

                            if (links != nullptr)
                                GenerateLinks(pm.GetDict().GetLexAuto(), subresult_q);

                            if (check_score != 0)
                            {
                                subresult_q->res.AddNGramFreq(Solarix::NGramScore(check_score));

#if defined SOL_DEBUGGING
                                SynPatternDebugTrace dbg;
                                dbg.ngram_freq = Solarix::NGramScore(check_score);
                                subresult_q->debug_trace.push_back(dbg);
#endif
                            }

                            if (ngrams != nullptr)
                                subresult_q->res.AddNGramFreq(CalculateNGramFreq(pm.GetDict(), x_result, subresult_q, experience, constraints, trace_log));

                            if (pattern_constraints != nullptr)
                            {
                                bool constraints_check = CheckConstraints(pm.GetDict().GetLexAuto(), parent_trace, subresult_q);
                                if (constraints_check)
                                {
                                    results.push_back(subresult_q);
                                    subresults[q] = nullptr;
                                    tree_matched = true;
                                }
                            }
                            else
                            {
                                results.push_back(subresult_q);
                                subresults[q] = nullptr;
                                tree_matched = true;
                            }
                        }
                    }
                }
            }
        }
    }

    return tree_matched;
}
#endif




#if defined SOL_CAA
bool SynPatternPoint::Match_Untill(
    int banned_id_tree,
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const ElapsedTimeConstraint & constraints,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    LA_SynPatternTrees &named_filters,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    TrTrace * trace_log,
    int recursion_depth
) const
{
    bool any_matched = false;

    int list_selector = 1;
    lem::MCollect<const LexerTextPos *> cur_tokens[2];
    cur_tokens[0].push_back(current_token);

    const int MAX_ALTS = lexer.GetParams().timeout.max_alt;

    while (true)
    {
        for (lem::Container::size_type k = 0; k < cur_tokens[(list_selector + 1) % 2].size(); ++k)
        {
            const LexerTextPos * t = cur_tokens[(list_selector + 1) % 2][k];
            if (t->IsEnd() || t->IsBeyondRight())
                continue;

            lem::PtrCollect<SynPatternResult> subresults;

            bool x = args.front()->Equal(
                banned_id_tree,
                pm,
                sg,
                experience,
                constraints,
                t,
                lexer,
                parent_trace,
                x_result,
                named_filters,
                wordentry_sets,
                false,
                false,
                false,
                subresults,
                trace_log,
                recursion_depth + 1
            );

            if (x)
            {
                any_matched = true;
                cur_tokens[(list_selector + 1) % 2][k] = nullptr; // дальше справа от этого токена не проверяем

                for (lem::Container::size_type q = 0; q < subresults.size(); ++q)
                {
                    const SynPatternResult * q_result = subresults[q];

                    SynPatternResult *r = new SynPatternResult(parent_trace);

                    r->res = SynPatternMatchResult(true, t->GetWordIndex() - current_token->GetWordIndex(), current_token, t->GetPrev(), NGramScore(0));

                    r->matched_alts.insert(std::make_pair(current_token->GetWordform(), 0));


                    if (links != nullptr)
                        GenerateLinks(pm.GetDict().GetLexAuto(), r);

                    if (ngrams != nullptr)
                        r->res.SetNGramFreq(CalculateNGramFreq(pm.GetDict(), x_result, r, experience, constraints, trace_log));

                    if (pattern_constraints != nullptr)
                    {
                        bool constraints_check = CheckConstraints(pm.GetDict().GetLexAuto(), parent_trace, r);
                        if (constraints_check)
                            results.push_back(r);
                        else
                            delete r;
                    }
                    else
                    {
                        results.push_back(r);
                    }
                }
            }
        }

        if (MAX_ALTS > 0 && results.size() > MAX_ALTS)
            break;

        list_selector++;

        bool fetched = false;
        cur_tokens[(list_selector + 1) % 2].clear();

        for (lem::Container::size_type k = 0; k < cur_tokens[list_selector % 2].size(); ++k)
        {
            const LexerTextPos * t = cur_tokens[list_selector % 2][k];

            if (t != nullptr && !t->IsEnd())
            {
                fetched = fetched || lexer.Fetch(t, cur_tokens[(list_selector + 1) % 2]);
            }
        }

        if (!fetched)
            break;
    }

    return any_matched;
}
#endif






#if defined SOL_CAA
bool SynPatternPoint::Match_WordformSet(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    if (!Match_WordformSet_Strict(pm, sg, experience, current_token, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
    {
        bool any_matched = false;
        if (lexer.GetParams().CanSkipInnerTokens())
        {
            // Разрешен неполный и нечеткий анализ - попробуем пропустить токены в поисках подходящего.
            int skip_count = 0;

            int list_selector = 0;
            lem::MCollect<const LexerTextPos *> cur_tokens[2];
            cur_tokens[0].push_back(current_token);

            do
            {
                skip_count++;

                bool fetched = false;
                cur_tokens[(list_selector + 1) % 2].clear();

                for (lem::Container::size_type k = 0; k < cur_tokens[list_selector % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[list_selector % 2][k];

                    if (!t->IsEnd())
                    {
                        fetched = fetched || lexer.Fetch(t, cur_tokens[(list_selector + 1) % 2]);
                    }
                }

                if (!fetched)
                    break;

                for (lem::Container::size_type k = 0; k < cur_tokens[(list_selector + 1) % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[(list_selector + 1) % 2][k];
                    if (t->IsEnd() || t->IsBeyondRight())
                        continue;

                    const lem::Container::size_type n0 = results.size();
                    if (Match_WordformSet_Strict(pm, sg, experience, t, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
                    {
                        any_matched = true;

                        // скорректируем новые результаты
                        for (lem::Container::size_type j = n0; j < results.size(); ++j)
                        {
                            // 1) скорректируем длину сопоставленного участка с учетом пропущенных токенов.
                            const int span_size = t->GetWordIndex() - current_token->GetWordIndex() + 1;

                            // 2) штраф за пропущенные токены.
                            SynPatternMatchResult new_res(
                                true,
                                span_size,
                                t,
                                t,
                                NGramScore(results[j]->res.GetNGramFreq(), NGramScore(-skip_count))
                            );
                            results[j]->res = new_res;

                            // пропущенные токены будут прикреплены к сопоставленному как умолчальная группа
                            PatternSynLinkedGroup skipped_and_matched(current_token, t, t->GetWordform());
                            results[j]->AddLinkageGroup(skipped_and_matched);
                        }
                    }
                }

                list_selector++;
            } while (skip_count < lexer.GetParams().MaxSkipToken);
        }

        return any_matched;
    }
    else
    {
        return true;
    }

}
#endif




#if defined SOL_CAA
bool SynPatternPoint::Match_WordformSet_Strict(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    /*
     int dirty_matching=-2;
     bool accel_matching=false;

     if( id_accel!=UNKNOWN )
     {
     dirty_matching = experience.FindAccelerator( current_token, id_accel );

     if( dirty_matching==0 )
     return false;
     }
     */

    bool res = false;

    const Word_Form &wf = *current_token->GetWordform();
    const int nalt = CastSizeToInt(wf.GetAlts().size()) + 1;
    for (int ialt = 0; ialt < nalt; ++ialt)
    {
        const Word_Form *alt = wf.GetVersion(ialt);

        if (wordentry_sets.FindWordformSet(sg, str_arg, *alt))
        {
            //     accel_matching = true;

            // Нужна проверка по списку координатных пар?
            bool alt_ok = true;
            if (!coords.empty())
            {
                // да, проверяем
                bool m1 = true;

                for (lem::Container::size_type j = 0; j < coords.size(); ++j)
                {
                    const GramCoordEx &p = coords[j].GetPair();

                    if (p.GetAffirm())
                    {
                        const GramCoord &c = sg.coords()[p.GetCoord().GetIndex()];
                        if (c.IsBistable())
                        {
                            const int istate = p.GetState();
                            if (istate == 0)
                            {
                                // Координаты быть не должно, или она должна иметь состояние 0.
                                lem::MCollect<int> bstates = alt->GetStates(p.GetCoord());
                                if (!bstates.empty())
                                {
                                    if (bstates.front() != 0)
                                    {
                                        m1 = false;
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                // Координата должна присутствовать
                                if (alt->GetPairs().FindOnce(p) == UNKNOWN)
                                {
                                    m1 = false;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (alt->GetPairs().FindOnce(p) == UNKNOWN)
                            {
                                m1 = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        if (alt->GetPairs().FindOnce(p) != UNKNOWN)
                        {
                            m1 = false;
                            break;
                        }
                    }
                }

                alt_ok = m1;
            }

            if (!alt_ok)
                continue;

            bool m = true;
            // согласования с левыми маркированными точками
            for (lem::Container::size_type k = 0; k < back_correls.size() && m; ++k)
            {
                const lem::UCString &mark = back_correls[k].name; // искомая маркировка
                const BackTraceItem & mark_data = *parent_trace->Get(PatternSequenceNumber, mark);

                if (!mark_data.Check(sg, back_correls[k], *alt))
                {
                    m = false;
                    break;
                }
            }

            alt_ok = m;

            if (alt_ok)
            {
                // Одна из альтернатив попала под условия.

                SynPatternResult *r = new SynPatternResult(parent_trace);

#if defined SOL_DEBUGGING
                SynPatternDebugTrace dbg_point(this, &wf, &str_arg);
                r->Append(dbg_point);
#endif

                r->matched_alts.insert(std::make_pair(&wf, ialt));

                if (export_section != nullptr)
                {
                    // Если нужно экспортировать координаты...
                    export_section->ExportCoords_Unconditional(*r, alt);
                    export_section->ExportPairs_Unconditional(*r);
                    export_section->ExportNodes(*r, alt);
                }

                res = true;

                r->res = SynPatternMatchResult(true, 1, current_token, current_token, NGramScore(0));

                if (links != nullptr)
                    GenerateLinks(pm.GetDict().GetLexAuto(), r);

                if (ngrams != nullptr)
                    r->res.SetNGramFreq(CalculateNGramFreq(pm.GetDict(), x_result, r, experience, constraints, trace_log));

                if (pattern_constraints != nullptr)
                {
                    bool constraints_check = CheckConstraints(pm.GetDict().GetLexAuto(), parent_trace, r);
                    if (constraints_check)
                        results.push_back(r);
                    else
                        delete r;
                }
                else
                {
                    results.push_back(r);
                }

#if defined SOL_DEBUGGING==1
                if (trace_log != nullptr)
                {
                    lem::MemFormatter mem;

                    alt->Print(mem, &sg, true);
                    lem::UFString str_wordform = mem.string();

                    this->Print(mem, sg);
                    lem::UFString str_point = mem.string();

                    trace_log->GetMorphologyTracer().AddMatchingPoint(&wf, str_wordform, this, str_point);
                }
#endif
            }
        }
    }

    /*
     if( dirty_matching==-1 )
     {
     experience.StoreAccelerator( current_token, id_accel, accel_matching );
     }
     */

    return res && !results.empty();
}
#endif



#if defined SOL_CAA && !defined SOL_NO_AA
bool SynPatternPoint::Match_Wordform(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    if (!Match_WordformStrict(pm, sg, experience, current_token, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
    {
        bool any_matched = false;
        if (lexer.GetParams().CanSkipInnerTokens())
        {
            if (ekey == pm.GetDict().GetSynGram().I_BEGIN || ekey == pm.GetDict().GetSynGram().I_END)
                return false;

            // Разрешен неполный и нечеткий анализ - попробуем пропустить токены в поисках подходящего.
            int skip_count = 0;

            int list_selector = 0;
            lem::MCollect<const LexerTextPos *> cur_tokens[2];
            cur_tokens[0].push_back(current_token);

            do
            {
                skip_count++;

                bool fetched = false;
                cur_tokens[(list_selector + 1) % 2].clear();

                for (lem::Container::size_type k = 0; k < cur_tokens[list_selector % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[list_selector % 2][k];

                    if (!t->IsEnd())
                    {
                        fetched = fetched || lexer.Fetch(t, cur_tokens[(list_selector + 1) % 2]);
                    }
                }

                if (!fetched)
                    break;

                for (lem::Container::size_type k = 0; k < cur_tokens[(list_selector + 1) % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[(list_selector + 1) % 2][k];
                    if (t->IsEnd() || t->IsBeyondRight())
                        continue;

                    const lem::Container::size_type n0 = results.size();
                    if (Match_WordformStrict(pm, sg, experience, t, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
                    {
                        any_matched = true;

                        // скорректируем новые результаты
                        for (lem::Container::size_type j = n0; j < results.size(); ++j)
                        {
                            // 1) скорректируем длину сопоставленного участка с учетом пропущенных токенов.
                            const int span_size = t->GetWordIndex() - current_token->GetWordIndex() + 1;

                            // 2) штраф за пропущенные токены.
                            SynPatternMatchResult new_res(
                                true,
                                span_size,
                                t,
                                t,
                                NGramScore(results[j]->res.GetNGramFreq(), NGramScore(-skip_count))
                            );
                            results[j]->res = new_res;

                            // пропущенные токены будут прикреплены к сопоставленному как умолчальная группа
                            PatternSynLinkedGroup skipped_and_matched(current_token, t, t->GetWordform());
                            results[j]->AddLinkageGroup(skipped_and_matched);
                        }
                    }
                }

                list_selector++;
            } while (skip_count < lexer.GetParams().MaxSkipToken);
        }

        return any_matched;
    }
    else
    {
        return true;
    }
}
#endif



#if defined SOL_CAA && !defined SOL_NO_AA
bool SynPatternPoint::Match_WordformStrict(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    // Проверяем словоформу на соответствие требованиям опорной точки
    const Word_Form & wf = *current_token->GetWordform();

    bool any_matched = false;

    const int nalt = wf.VersionCount();

    for (int ialt = 0; ialt < nalt; ++ialt)
    {
        const Word_Form * alt = wf.GetVersion(ialt);
        bool m = false;

        int check_score = 0; // для накопления штрафов за мягкие нарушения.

        const int is_ekey = alt->GetEntryKey();

        // Может быть либо сравнение буквального значение слова с заданной лексемой, или сравнение
        // с id словарной статьи, или проверка на часть речи.

        if (!lexeme.empty())
        {
            m = lexeme.eqi(*alt->GetName());

            if (m && iclass != UNKNOWN)
            {
                // есть дополнительное требование на часть речи у этой версии.
                if (is_ekey == UNKNOWN)
                    continue;

                const SG_Entry &e = sg.GetEntry(is_ekey);
                if (e.GetClass() != iclass)
                    continue;
            }
        }
        else if (ekey != UNKNOWN && ekey != ANY_STATE)
        {
            // Проверяем на совпадение с заданным id словарной статьи.
            if (is_ekey != ekey)
                continue;

            m = true;
        }
        else if (iclass != UNKNOWN && iclass != ANY_STATE)
        {
            // Проверяем только часть речи.
            const SG_Entry &e = sg.GetEntry(is_ekey);

            if (e.GetClass() != iclass)
                continue;

            m = true;
        }
        else if (ekey == UNKNOWN && iclass == ANY_STATE)
        {
            m = true;
        }


        if (m)
        {
            // Осталось проверить координаты 
            m = false;

            if (coords.empty())
            {
                m = true;
            }
            else
            {
                m = true;

                for (lem::Container::size_type j = 0; j < coords.size(); ++j)
                {
                    const GramCoordEx &p = coords[j].GetPair();

                    if (p.GetAffirm())
                    {
                        const GramCoord &c = sg.coords()[p.GetCoord().GetIndex()];
                        if (c.IsBistable())
                        {
                            const int istate = p.GetState();
                            if (istate == 0)
                            {
                                // Координаты быть не должно, или она должна иметь состояние 0.
                                lem::MCollect<int> bstates = alt->GetStates(p.GetCoord());
                                if (!bstates.empty())
                                {
                                    if (bstates.front() != 0)
                                    {
                                        if (coords[j].GetViolationHandler().HasFalseScore())
                                        {
                                            check_score += coords[j].GetViolationHandler().GetFalseScore();
                                        }
                                        else
                                        {
                                            m = false;
                                            break;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                // Координата должна присутствовать
                                if (alt->GetPairs().FindOnce(p) == UNKNOWN)
                                {
                                    if (coords[j].GetViolationHandler().HasFalseScore())
                                    {
                                        check_score += coords[j].GetViolationHandler().GetFalseScore();
                                    }
                                    else
                                    {
                                        m = false;
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (alt->GetPairs().FindOnce(p) == UNKNOWN)
                            {
                                if (coords[j].GetViolationHandler().HasFalseScore())
                                {
                                    check_score += coords[j].GetViolationHandler().GetFalseScore();
                                }
                                else
                                {
                                    m = false;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (alt->GetPairs().FindOnce(p) != UNKNOWN)
                        {
                            if (coords[j].GetViolationHandler().HasFalseScore())
                            {
                                check_score += coords[j].GetViolationHandler().GetFalseScore();
                            }
                            else
                            {
                                m = false;
                                break;
                            }
                        }
                    }
                }
            }

            if (m && ThesaurusCheck_Link != UNKNOWN)
            {
                // проверяем, что данная статья связана в тезаурусе в указанной статьей заданным типом связи
                int id_link = sg.Get_Net().Find_Linked_Entry(is_ekey, ThesaurusCheck_Link, ThesaurusCheck_Entry);
                m = id_link != UNKNOWN;
            }

            if (m)
            {
                // согласования с левыми маркированными точками

                for (lem::Container::size_type k = 0; k < back_correls.size() && m; ++k)
                {
                    const lem::UCString &mark = back_correls[k].name; // искомая маркировка
                    const BackTraceItem & mark_data = *parent_trace->Get(PatternSequenceNumber, mark);

                    if (!mark_data.Check(sg, back_correls[k], *alt))
                    {
                        if (back_correls[k].GetViolationHandler().HasFalseScore())
                        {
                            check_score += back_correls[k].GetViolationHandler().GetFalseScore();
                        }
                        else
                        {
                            m = false;
                            break;
                        }
                    }
                }
            }

            if (m && correl_fun.NotNull())
            {
                // Вызываем корреляционную функцию для императивных проверок

                //TrFunContext ctx0( &*pm.functions.static_vars, &env );
#if LEM_DEBUGGING
                //matching_vars.PrintVars( sg.GetDict(), *mout );
#endif

                //       TrFunContext ctx0( &matching_vars, &env );
                //       TrContextInCondictor ctx( &ctx0, (Variator&)var, i0 );

                TrFunContext ctx0((TrFunContext*)nullptr);
                TrContextInvokation ctx2(&ctx0);
                //       ctx2.AddVar( L"((return))", lem::Ptr<TrValue>( new TrTypeValue( TrVariantType() ) ) );

                lem::Ptr<TrValue> this_wordform(new TrValue(new Tree_Node(new Word_Form(*alt, false), true), true));
                ctx2.AddVar(L"_", this_wordform);

                lem::Ptr<TrValue> p = correl_fun->Run(constraints, sg.GetDict().GetLexAuto(), ctx2, trace_log);

                //       lem::Ptr<TrValue> p = ctx2.GetVar(L"((return))");

                if (p->GetType().IsBool())
                {
                    m = p->GetBool();
                }
                else if (p->GetType().IsInt())
                {
                    m = true;
                    check_score += p->GetInt();
                }
                else
                {
#if LEM_DEBUGGING==1
                    if (trace_log != nullptr)
                        trace_log->PrintStack(*lem::mout);
#endif

                    lem::UFString msg(lem::format_str(L"Can not use lambda function: inappropriate return type=%s", p->GetType().GetName().c_str()));
                    throw E_BaseException(msg.c_str());
                }
            }
        }

        if (m)
        {
            if (!tokenizer_flags.empty())
            {
                if (not_tokenizer_flags)
                    m = !alt->MatchTokenizerFlag(tokenizer_flags);
                else
                    m = alt->MatchTokenizerFlag(tokenizer_flags);
            }

            if (m && !kb_checkers.empty())
            {
                // В parent_trace надо искать именованные ссылки вида X.y

                KnowledgeBase &kbase = sg.GetDict().GetLexAuto().GetKnowledgeBase();

                for (lem::Container::size_type i = 0; i < kb_checkers.size(); ++i)
                {
                    const KB_Checker & checker = *kb_checkers[i];

                    KB_CheckerReturn kbret = checker.Check(PatternSequenceNumber, parent_trace, nullptr, alt, kbase, experience);

                    if (!kbret.success)
                    {
                        m = false;
                        break;
                    }
                    else
                    {
                        check_score += kbret.false_score;
                    }
                }
            }


            if (m && !set_checkers.empty())
            {
                for (lem::Container::size_type k = 0; k < set_checkers.size(); ++k)
                    if (!set_checkers[k].Check(sg, *alt, wordentry_sets))
                    {
                        if (set_checkers[k].GetViolationHandler().HasFalseScore())
                        {
                            check_score += set_checkers[k].GetViolationHandler().GetFalseScore();
                        }
                        else
                        {
                            m = false;
                            break;
                        }
                    }
            }

            if (m)
            {
                // Альтернатива подходит под условия опорной точки

                SynPatternResult *r = new SynPatternResult(parent_trace);
                r->res = SynPatternMatchResult(true, 1, current_token, current_token, NGramScore(0));

#if defined SOL_DEBUGGING
                SynPatternDebugTrace dbg_point(this, alt);
                r->Append(dbg_point);
#endif

                if (export_section != nullptr)
                {
                    // экспорт состояний заданных координат
                    export_section->ExportCoords_Unconditional(*r, alt);

                    // Экспорт явно заданных пар
                    export_section->ExportPairs_Unconditional(*r);

                    // Если необходимо экспортировать именованную ссылку на словоформу
                    export_section->ExportNodes(*r, alt);

                    if (export_section->ContainsFunctions())
                    {
                        PatternExportFuncContext_Wordform export_context(alt);
                        export_section->ExportByFunctions(*r, export_context);
                    }
                }

                r->matched_alts.insert(std::make_pair(&wf, ialt));

                if (links != nullptr)
                    GenerateLinks(pm.GetDict().GetLexAuto(), r);

                if (check_score != 0)
                {
                    r->res.AddNGramFreq(Solarix::NGramScore(check_score));

#if defined SOL_DEBUGGING
                    SynPatternDebugTrace dbg;
                    dbg.ngram_freq = Solarix::NGramScore(check_score);
                    r->debug_trace.push_back(dbg);
#endif
                }

                if (ngrams != nullptr)
                    r->res.AddNGramFreq(CalculateNGramFreq(pm.GetDict(), x_result, r, experience, constraints, trace_log));

                if (alt->GetScore() != 0)
                {
                    r->res.AddNGramFreq(Solarix::NGramScore(alt->GetScore()));

#if defined SOL_DEBUGGING
                    SynPatternDebugTrace dbg;
                    dbg.ngram_freq = Solarix::NGramScore(alt->GetScore());
                    dbg.scoring_reason = "wordform_score";
                    r->debug_trace.push_back(dbg);
#endif
                }

                if (pattern_constraints != nullptr)
                {
                    bool constraints_check = CheckConstraints(pm.GetDict().GetLexAuto(), parent_trace, r);
                    if (constraints_check)
                    {
                        results.push_back(r);
                        any_matched = true;
                    }
                    else
                    {
                        delete r;
                    }
                }
                else
                {
                    results.push_back(r);
                    any_matched = true;
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    lem::MemFormatter mem;

                    if (ialt == 0)
                    {
                        Word_Form wf0(wf, false);
                        wf0.Print(mem, &sg, true);
                        wf0.SetOriginPos(wf.GetOriginPos());
                    }
                    else
                    {
                        alt->Print(mem, &sg, true);
                    }

                    lem::UFString str_wordform = mem.string();

                    this->Print(mem, sg);
                    lem::UFString str_point = mem.string();

                    trace_log->GetMorphologyTracer().AddMatchingPoint(&wf, str_wordform, this, str_point);
                }
#endif
            }
        }
    }

    /*
     if( dirty_matching==-1 )
     {
     experience.StoreAccelerator( current_token, id_accel, accel_matching );
     }
     */

    return any_matched;
}
#endif




#if defined SOL_CAA
bool SynPatternPoint::Match_WordSet_Strict(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    /*
     int dirty_matching=-2;
     bool accel_matching=false;

     if( id_accel!=UNKNOWN )
     {
     dirty_matching = experience.FindAccelerator( current_token, id_accel );

     if( dirty_matching==0 )
     return false; // точно не подходит.
     }
     */

    bool res = false;

    const Word_Form &wf = *current_token->GetWordform();

    const int nalt = wf.VersionCount();
    for (int ialt = 0; ialt < nalt; ++ialt)
    {
        const Word_Form *alt = wf.GetVersion(ialt);

        if (wordentry_sets.FindWordSet(str_arg, *alt->GetName()))
        {
            // Одна из альтернатив попала под условия.
            //accel_matching = true;

            SynPatternResult *r = new SynPatternResult(parent_trace);

#if defined SOL_DEBUGGING
            SynPatternDebugTrace dbg_point(this, &wf, &str_arg);
            r->Append(dbg_point);
#endif

            r->matched_alts.insert(std::make_pair(&wf, ialt));

            if (export_section != nullptr)
            {
                export_section->ExportCoords_Unconditional(*r, alt);
                export_section->ExportPairs_Unconditional(*r);
                export_section->ExportNodes(*r, alt);

                if (export_section->ContainsFunctions())
                {
                    PatternExportFuncContext_Wordform export_context(alt);
                    export_section->ExportByFunctions(*r, export_context);
                }
            }

            res = true;

            r->res = SynPatternMatchResult(true, 1, current_token, current_token, NGramScore(0));

            if (links != nullptr)
                GenerateLinks(pm.GetDict().GetLexAuto(), r);

            if (ngrams != nullptr)
                r->res.SetNGramFreq(CalculateNGramFreq(pm.GetDict(), x_result, r, experience, constraints, trace_log));

            if (alt->GetScore() != 0)
            {
                r->res.AddNGramFreq(Solarix::NGramScore(alt->GetScore()));

#if defined SOL_DEBUGGING
                SynPatternDebugTrace dbg;
                dbg.ngram_freq = Solarix::NGramScore(alt->GetScore());
                dbg.scoring_reason = "wordform_score";
                r->debug_trace.push_back(dbg);
#endif
            }

            if (pattern_constraints != nullptr)
            {
                bool constraints_check = CheckConstraints(pm.GetDict().GetLexAuto(), parent_trace, r);
                if (constraints_check)
                    results.push_back(r);
                else
                    delete r;
            }
            else
            {
                results.push_back(r);
            }

#if defined SOL_DEBUGGING
            if (trace_log != nullptr)
            {
                lem::MemFormatter mem;

                alt->Print(mem, &sg, true);
                lem::UFString str_wordform = mem.string();

                this->Print(mem, sg);
                lem::UFString str_point = mem.string();

                trace_log->GetMorphologyTracer().AddMatchingPoint(&wf, str_wordform, this, str_point);
            }
#endif
        }
    }

    /*
     if( dirty_matching==-1 )
     {
     experience.StoreAccelerator( current_token, id_accel, accel_matching );
     }
     */

    return res && !results.empty();
}
#endif





#if defined SOL_CAA
bool SynPatternPoint::Match_WordSet(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    if (!Match_WordSet_Strict(pm, sg, experience, current_token, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
    {
        bool any_matched = false;
        if (lexer.GetParams().CanSkipInnerTokens())
        {
            // Разрешен неполный и нечеткий анализ - попробуем пропустить токены в поисках подходящего.
            int skip_count = 0;

            int list_selector = 0;
            lem::MCollect<const LexerTextPos *> cur_tokens[2];
            cur_tokens[0].push_back(current_token);

            do
            {
                skip_count++;

                bool fetched = false;
                cur_tokens[(list_selector + 1) % 2].clear();

                for (lem::Container::size_type k = 0; k < cur_tokens[list_selector % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[list_selector % 2][k];

                    if (!t->IsEnd())
                    {
                        fetched = fetched || lexer.Fetch(t, cur_tokens[(list_selector + 1) % 2]);
                    }
                }

                if (!fetched)
                    break;

                for (lem::Container::size_type k = 0; k < cur_tokens[(list_selector + 1) % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[(list_selector + 1) % 2][k];
                    if (t->IsEnd() || t->IsBeyondRight())
                        continue;

                    const lem::Container::size_type n0 = results.size();
                    if (Match_WordSet_Strict(pm, sg, experience, t, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
                    {
                        any_matched = true;

                        // скорректируем новые результаты
                        for (lem::Container::size_type j = n0; j < results.size(); ++j)
                        {
                            // 1) скорректируем длину сопоставленного участка с учетом пропущенных токенов.
                            const int span_size = t->GetWordIndex() - current_token->GetWordIndex() + 1;

                            // 2) штраф за пропущенные токены.
                            SynPatternMatchResult new_res(
                                true,
                                span_size,
                                t,
                                t,
                                NGramScore(results[j]->res.GetNGramFreq(), NGramScore(-skip_count))
                            );
                            results[j]->res = new_res;

                            // пропущенные токены будут прикреплены к сопоставленному как умолчальная группа
                            PatternSynLinkedGroup skipped_and_matched(current_token, t, t->GetWordform());
                            results[j]->AddLinkageGroup(skipped_and_matched);
                        }
                    }
                }

                list_selector++;
            } while (skip_count < lexer.GetParams().MaxSkipToken);
        }

        return any_matched;
    }
    else
    {
        return true;
    }

}
#endif


#if defined SOL_CAA
bool SynPatternPoint::Match_WordentrySet_Strict(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    /*
     int dirty_matching=-2;
     bool accel_matching=false;

     if( id_accel!=UNKNOWN )
     {
     dirty_matching = experience.FindAccelerator( current_token, id_accel );

     if( dirty_matching==0 )
     return false; // точно не подходит.
     }
     */

    bool res = false;

    const Word_Form &wf = *current_token->GetWordform();

    const int nalt = wf.VersionCount();

    for (int ialt = 0; ialt < nalt; ++ialt)
    {
        const Word_Form *alt = wf.GetVersion(ialt);
        if (wordentry_sets.FindWordEntrySet(str_arg, alt->GetEntryKey()))
        {
            //     accel_matching=true;

            // Нужна проверка по списку координатных пар?
            bool alt_ok = true;
            if (!coords.empty())
            {
                // да, проверяем
                bool m1 = true;

                for (lem::Container::size_type j = 0; j < coords.size(); ++j)
                {
                    const GramCoordEx &p = coords[j].GetPair();

                    if (p.GetAffirm())
                    {
                        const GramCoord &c = sg.coords()[p.GetCoord().GetIndex()];
                        if (c.IsBistable())
                        {
                            const int istate = p.GetState();
                            if (istate == 0)
                            {
                                // Координаты быть не должно, или она должна иметь состояние 0.
                                lem::MCollect<int> bstates = alt->GetStates(p.GetCoord());
                                if (!bstates.empty())
                                {
                                    if (bstates.front() != 0)
                                    {
                                        m1 = false;
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                // Координата должна присутствовать
                                if (alt->GetPairs().FindOnce(p) == UNKNOWN)
                                {
                                    m1 = false;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (alt->GetPairs().FindOnce(p) == UNKNOWN)
                            {
                                m1 = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        if (alt->GetPairs().FindOnce(p) != UNKNOWN)
                        {
                            m1 = false;
                            break;
                        }
                    }
                }

                alt_ok = m1;
            }

            if (!alt_ok)
                continue;

            bool m = true;
            // согласования с левыми маркированными точками
            for (lem::Container::size_type k = 0; k < back_correls.size() && m; ++k)
            {
                const lem::UCString &mark = back_correls[k].name; // искомая маркировка
                const BackTraceItem & mark_data = *parent_trace->Get(PatternSequenceNumber, mark);

                if (!mark_data.Check(sg, back_correls[k], *alt))
                {
                    m = false;
                    break;
                }
            }

            alt_ok = m;


            if (alt_ok)
            {
                // Одна из альтернатив попала под условия.

                SynPatternResult *r = new SynPatternResult(parent_trace);

#if defined SOL_DEBUGGING
                SynPatternDebugTrace dbg_point(this, &wf, &str_arg);
                r->Append(dbg_point);
#endif

                r->matched_alts.insert(std::make_pair(&wf, ialt));

                if (export_section != nullptr)
                {
                    export_section->ExportCoords_Unconditional(*r, alt);
                    export_section->ExportPairs_Unconditional(*r);
                    export_section->ExportNodes(*r, alt);

                    if (export_section->ContainsFunctions())
                    {
                        PatternExportFuncContext_Wordform export_context(alt);
                        export_section->ExportByFunctions(*r, export_context);
                    }
                }

                res = true;

                r->res = SynPatternMatchResult(true, 1, current_token, current_token, NGramScore(0));

                if (links != nullptr)
                    GenerateLinks(pm.GetDict().GetLexAuto(), r);

                if (ngrams != nullptr)
                    r->res.SetNGramFreq(CalculateNGramFreq(pm.GetDict(), x_result, r, experience, constraints, trace_log));

                if (alt->GetScore() != 0)
                {
                    r->res.AddNGramFreq(Solarix::NGramScore(alt->GetScore()));

#if defined SOL_DEBUGGING
                    SynPatternDebugTrace dbg;
                    dbg.ngram_freq = Solarix::NGramScore(alt->GetScore());
                    dbg.scoring_reason = "wordform_score";
                    r->debug_trace.push_back(dbg);
#endif
                }

                if (pattern_constraints != nullptr)
                {
                    bool constraints_check = CheckConstraints(pm.GetDict().GetLexAuto(), parent_trace, r);
                    if (constraints_check)
                        results.push_back(r);
                    else
                        delete r;
                }
                else
                {
                    results.push_back(r);
                }

#if defined SOL_DEBUGGING
                if (trace_log != nullptr)
                {
                    lem::MemFormatter mem;

                    alt->Print(mem, &sg, true);
                    lem::UFString str_wordform = mem.string();

                    this->Print(mem, sg);
                    lem::UFString str_point = mem.string();

                    trace_log->GetMorphologyTracer().AddMatchingPoint(&wf, str_wordform, this, str_point);
                }
#endif
            }
        }
    }

    /*
     if( dirty_matching==-1 )
     {
     experience.StoreAccelerator( current_token, id_accel, accel_matching );
     }
     */

    return res && !results.empty();
}
#endif



#if defined SOL_CAA
bool SynPatternPoint::Match_WordentrySet(
    PM_Automat & pm,
    SynGram & sg,
    TreeMatchingExperience & experience,
    const LexerTextPos * current_token,
    BasicLexer & lexer,
    const BackTrace * parent_trace,
    const SynPatternResultBackTrace * x_result,
    WordEntrySet &wordentry_sets,
    lem::PtrCollect<SynPatternResult> & results,
    const ElapsedTimeConstraint & constraints,
    TrTrace * trace_log
) const
{
    if (!Match_WordentrySet_Strict(pm, sg, experience, current_token, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
    {
        bool any_matched = false;
        if (lexer.GetParams().CanSkipInnerTokens())
        {
            // Разрешен неполный и нечеткий анализ - попробуем пропустить токены в поисках подходящего.
            int skip_count = 0;

            int list_selector = 0;
            lem::MCollect<const LexerTextPos *> cur_tokens[2];
            cur_tokens[0].push_back(current_token);

            do
            {
                skip_count++;

                bool fetched = false;
                cur_tokens[(list_selector + 1) % 2].clear();

                for (lem::Container::size_type k = 0; k < cur_tokens[list_selector % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[list_selector % 2][k];

                    if (!t->IsEnd())
                    {
                        fetched = fetched || lexer.Fetch(t, cur_tokens[(list_selector + 1) % 2]);
                    }
                }

                if (!fetched)
                    break;

                for (lem::Container::size_type k = 0; k < cur_tokens[(list_selector + 1) % 2].size(); ++k)
                {
                    const LexerTextPos * t = cur_tokens[(list_selector + 1) % 2][k];
                    if (t->IsEnd() || t->IsBeyondRight())
                        continue;

                    const lem::Container::size_type n0 = results.size();
                    if (Match_WordentrySet_Strict(pm, sg, experience, t, lexer, parent_trace, x_result, wordentry_sets, results, constraints, trace_log))
                    {
                        any_matched = true;

                        // скорректируем новые результаты
                        for (lem::Container::size_type j = n0; j < results.size(); ++j)
                        {
                            // 1) скорректируем длину сопоставленного участка с учетом пропущенных токенов.
                            const int span_size = t->GetWordIndex() - current_token->GetWordIndex() + 1;

                            // 2) штраф за пропущенные токены.
                            SynPatternMatchResult new_res(
                                true,
                                span_size,
                                t,
                                t,
                                NGramScore(results[j]->res.GetNGramFreq(), NGramScore(-skip_count))
                            );
                            results[j]->res = new_res;

                            // пропущенные токены будут прикреплены к сопоставленному как умолчальная группа
                            PatternSynLinkedGroup skipped_and_matched(current_token, t, t->GetWordform());
                            results[j]->AddLinkageGroup(skipped_and_matched);
                        }
                    }
                }

                list_selector++;
            } while (skip_count < lexer.GetParams().MaxSkipToken);
        }

        return any_matched;
    }
    else
    {
        return true;
    }
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool SynPatternPoint::operator<(const SynPatternPoint &x) const
{
    return GetScores() < x.GetScores();
}
#endif


#if defined SOL_DEBUGGING
void SynPatternPoint::Print(OFormatter &to, SynGram &sg) const
{
    if (!id_src.empty())
    {
        to.printf("Source code:");

        for (lem::Container::size_type i = 0; i < id_src.size(); ++i)
        {
            const int src = id_src[i];
            lem::Path filename;
            int line = 0, column = 0;

            if (sg.GetDict().GetDebugSymbols().GetLocation(src, filename, line, column))
            {
                to.printf(" %us:%d", filename.GetFileName().c_str(), line);
            }
        }

        to.eol();
    }

    if (check_fun.NotNull())
    {
        to.printf("...function call...");
    }
    else if (!lexeme.empty())
    {
        to.printf("'%vfA%us%vn'", lexeme.c_str());
    }
    else if (id_tree != UNKNOWN)
    {
        to.printf("%vfB%us%vn", sg.GetDict().GetLexAuto().GetSynPatternTrees().GetPatternName(id_tree).c_str());

        if (greedy)
            to.printf("/greedy/");
    }
    else if (!function_name.empty())
    {
        if (!str_arg.empty())
        {
            to.printf("@%vf5%us%vn(%us)", function_name.c_str(), str_arg.c_str());
        }
        else
        {
            to.printf("@%vf5%us%vn(", function_name.c_str());

            for (lem::Container::size_type k = 0; k < args.size(); ++k)
            {
                if (k > 0)
                    to.printf(",");

                args[k]->Print(to, sg);
            }

            to.printf(")");
        }
    }
    else
    {
        if (!lem::is_quantor(iclass))
        {
            to.printf("%vfA%us%vn", sg.GetClass(iclass).GetName().c_str());
        }

        if (!lem::is_quantor(ekey))
        {
            to.printf("%vf6:%vfD%us%vn", sg.GetEntry(ekey).GetName().c_str());
        }
    }

    to.printf(' ');


    to.printf(" %vf6{%vn");

    for (lem::Container::size_type i = 0; i < coords.size(); ++i)
    {
        to.printf(' ');

        const GramCoordEx & p = coords[i].GetPair();

        if (!p.GetAffirm())
            to.printf("~");

        p.SaveTxt(to, sg);
    }

    to.printf(" %vf6}%vn ");

    if (!mark_name.empty())
    {
        to.printf("as %us ", mark_name.GetName().c_str());
    }

    if (export_section != nullptr)
    {
        if (!export_section->export_coords.empty())
        {
            to.printf(" : %vfCexport%vn {");

            for (lem::Container::size_type i = 0; i < export_section->export_coords.size(); ++i)
            {
                const int id_coord = export_section->export_coords[i];
                lem::UCString cname = sg.coords()[id_coord].GetName()[0];
                to.printf(" %us", cname.c_str());
            }

            to.printf(" }");
        }
    }

    return;
}
#endif


int SynPatternPoint::GetScores(void) const
{
    int scores = 0;

    if (id_tree != UNKNOWN)
        scores = 10000;

    if (!lexeme.empty())
        scores = 1000;

    scores += CastSizeToInt(coords.size());

    if (ThesaurusCheck_Link != UNKNOWN)
        scores++;

    scores += CastSizeToInt(back_correls.size());

    scores += (iclass != UNKNOWN ? 10 : 0);
    scores += (ekey != UNKNOWN ? 100 : 0);

    if (!function_name.empty())
        scores += 100;

    scores += CastSizeToInt(args.size());

    if (!tokenizer_flags.empty())
    {
        scores++;
    }

    return scores;
}


void SynPatternPoint::Merge(const SynPatternPoint &src)
{
    std::copy(src.PatternSequenceNumber.begin(), src.PatternSequenceNumber.end(), std::back_inserter(PatternSequenceNumber));
    std::copy(src.id_src.begin(), src.id_src.end(), std::back_inserter(id_src));

    if (src.terminator)
        terminator = true;

    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPatternPoint::OptimizeAfterCompilation(const SynPatternCompilation & compilation_context)
{
    return;
}
#endif

void SynPatternPoint::SetLinks(PatternLinks *links_to_store)
{
    LEM_CHECKIT_Z(links == nullptr);
    LEM_CHECKIT_Z(links_to_store != nullptr);
    links = links_to_store;
    return;
}


void SynPatternPoint::SetNGrams(PatternNGrams *ngrams_to_store)
{
    LEM_CHECKIT_Z(ngrams == nullptr);
    LEM_CHECKIT_Z(ngrams_to_store != nullptr);
    ngrams = ngrams_to_store;
    return;
}



void SynPatternPoint::SetConstraints(PatternConstraints *constraints_to_store)
{
    LEM_CHECKIT_Z(pattern_constraints == nullptr);
    LEM_CHECKIT_Z(constraints_to_store != nullptr);
    pattern_constraints = constraints_to_store;
    return;
}


void SynPatternPoint::SetOptionalPoints(PatternOptionalPoints *optional_points_to_store)
{
    LEM_CHECKIT_Z(optional_points == nullptr);
    LEM_CHECKIT_Z(optional_points_to_store != nullptr);
    optional_points = optional_points_to_store;
    return;
}


void SynPatternPoint::SetPredicates(PredicateTemplates * predicates_to_store)
{
    LEM_CHECKIT_Z(predicates == nullptr);
    LEM_CHECKIT_Z(predicates_to_store != nullptr);
    predicates = predicates_to_store;
    return;
}


void SynPatternPoint::AddRootNodeExport(Dictionary & dict)
{
    if (export_section == nullptr)
        export_section = new PatternExportSection();

    LEM_CHECKIT_Z(export_section->export_nodes.empty());

    ExportNode e;
    e.node_name = *dict.GetLexAuto().GetRootNodeName();
    e.as_name = *dict.GetLexAuto().GetRootNodeName();

    export_section->export_nodes.push_back(e);

    return;
}
