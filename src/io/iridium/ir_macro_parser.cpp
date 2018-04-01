// -----------------------------------------------------------------------------
// File IR_MACRO_PARSER.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Класс Macro_Parser - добавочные методы для класса UTextSource<LEM_CSTRING_LEN>.
// Реализация Препроцессора для облегчения описания деревьев-beth и улучшени
// механизма работы с включаемыми файлами. Предварительная загрузка всего текста
// Словаря в память с одновременным разбитием на токены для ускорения трансляции,
// в которой интенсивно используется look-ahead parsing с откатами на несколько
// лексем. Реализованный препроцессор почти полностью совместим с препроцессором
// C/C++.
// -----------------------------------------------------------------------------
//
// CD->17.10.1996
// LC->01.04.2018
// --------------

#include <algorithm>

#include <lem/logfile.h>
#include <lem/conversions.h>
#include <lem/ir_parser.h>
#include <lem/user_interface.h>
#include <lem/macro_parser.h>

using namespace std;
using namespace boost;
using namespace lem;
using namespace lem::Iridium;
using namespace lem::Char_Stream;

UCString Macro_Parser::t_Diez(L"#");
UCString Macro_Parser::t_Double_Diez(L"##");
UCString Macro_Parser::t_Define(L"define");
UCString Macro_Parser::t_Undefine(L"undef");
UCString Macro_Parser::t_If(L"if");
UCString Macro_Parser::t_Elif(L"elif");
UCString Macro_Parser::t_Else(L"else");
UCString Macro_Parser::t_Endif(L"endif");
UCString Macro_Parser::t_Include(L"include");
UCString Macro_Parser::t_Error(L"error");
UCString Macro_Parser::t_Print(L"print");
UCString Macro_Parser::t_Stop(L"stop");
UCString Macro_Parser::t_File(L"file");
UCString Macro_Parser::t_Line(L"line");
UCString Macro_Parser::t_Enum(L"enum");
UCString Macro_Parser::t_Pragma(L"pragma");
UCString Macro_Parser::t_OroundParen(L"(");
UCString Macro_Parser::t_CroundParen(L")");
UCString Macro_Parser::t_Comma(L",");
UCString Macro_Parser::t_Backslash(L"\\");
UCString Macro_Parser::t_End(L"end");
UCString Macro_Parser::t_Equal(L"=");
UCString Macro_Parser::t_Begin(L"begin");
UCString Macro_Parser::t_Floating(L"floating");
UCString Macro_Parser::t_Lisp(L"lisp");
UCString Macro_Parser::t_Prolog(L"prolog");
UCString Macro_Parser::t_Pascal(L"pascal");
UCString Macro_Parser::t_Cpp(L"cpp");
UCString Macro_Parser::t_C(L"c");
UCString Macro_Parser::t_Comment(L"comment");
UCString Macro_Parser::t_On(L"on");
UCString Macro_Parser::t_Seq(L"seq");
UCString Macro_Parser::t_Cast(L"cast");
UCString Macro_Parser::t_LanguageMix(L"language_mix");
UCString Macro_Parser::t_Region(L"region");
UCString Macro_Parser::t_EndRegion(L"endregion");



// ***************************************************
// Returns TRUE if cyrillic and latin chars are mixed.
// ***************************************************
static bool check_mixage(const UCString &s)
{
    bool has_cyr = false, has_lat = false;

    for (lem::UCString::size_type i = 0; i < s.size(); i++)
    {
        wchar_t c = s[i];

        if (is_cyr(c))
            has_cyr = true;
        else if (is_lat(c))
            has_lat = true;
        else if (c == '_' || c == '%' || c == '-' || c == '=')
            // ???
            has_lat = has_cyr = false;
    }

    return has_cyr && has_lat;
}

// Константы для идентификации конструкций на стеке Препроцессора.
const int SOL_IR_DO_IGNORE_ELSE = 0;
const int SOL_IR_DO_PROCESS_ELSE = 1;

/***********************************************************************
 Для ускорения загрузки текста в буфер мы устанавливаем шаг наращивани
 размера буфера в 4096 элементов. Константу можно увеличить, но тогда
 неиспользованный 'хвост' (из-за не кратного новому шагу числу токенов)
 будет бесполезно отвлекать ресурсы памяти. Каждый хранимый элемент
 занимает примерно 46 байтов (для UNICODE-символов).
************************************************************************/
Macro_Parser::Macro_Parser(void)
    :global_var_table(NULL)
{
    text.reserve(4096);

    do_check_mixage = true;

    ios.err = merr; // Потоки вывода по умолчанию - консоль 
    ios.echo = mout;

    options = 0;
    i_last_tok = -1;

    // Чтобы не было проблем далее с нулевым поинтером на кодовую,
    // инициализируем дефолтной - она работает только с латиницей.
    //code_page = &cp1252;
    code_page = &lem::UI::get_UI().GetSessionCp();


    include_level = 0;

    n_error =
        n_warning = 0;

    src_set_flags =
        SRC_READ_FLOATING |
        SRC_READ_CHAR |
        SRC_READ_STRING |
        SRC_PROCESS_C_CHAR |
        SRC_SKIP_C_COMMENTARY |
        SRC_SKIP_CPP_COMMENTARY;

    src_clr_flags =
        SRC_STRIP_STRING |
        SRC_IGNORE_TOKCASE |
        SRC_SKIP_EOL;

    line_count = 0;

    return;
}


#if defined LEM_UNIX
// Do not delete this destructor, otherways GCC will generate invalid code!!!
Macro_Parser::~Macro_Parser(void)
{
    return;
}
#endif


void Macro_Parser::SetTokens(const MCollect<UCString> &Tokens)
{
    tokens.clear();
    copy(Tokens.begin(), Tokens.end(), back_inserter(tokens));
    return;
}



void Macro_Parser::SetComplDelims(const MCollect<UCString> &Delims)
{
    compl_delims.clear();
    copy(Delims.begin(), Delims.end(), back_inserter(compl_delims));
    return;
}



void Macro_Parser::SetTokens(int n, const UCString *list)
{
    tokens.clear();
    copy(list, list + n, back_inserter(tokens));
}


void Macro_Parser::SetComplDelims(int n, const UCString *list)
{
    compl_delims.clear();
    copy(list, list + n, back_inserter(compl_delims));
}


/*********************************************************************
 Member function opens the file specified by name, "preprocesses"
 it and loads the inner token list up.
*********************************************************************/
void Macro_Parser::Open(const wchar_t *filename)
{
    if (options&SRC_BETH_JOURNALIZE && lem::LogFile::IsOpen())
        lem::LogFile::logfile->printf("Loading [%vf9%us%vn]...\n", filename);

    next = 0;

    LoadText(filename);

    const BethToken bt(UToken(B_EOF_REACHED, SourceState()), UNKNOWN, UNKNOWN_TOKEN);
    text.push_back(bt);

    if (!block.empty())
    {
        // Имел место быть конец файла при незакрытых препроцессорных
        // скобках #if ... #else ... #endif
        ios.merr().printf("%vfDPreprocessor directive #if...#else...#endif syntax error%vn\n");
        throw E_ParserError();
    }

    if (options&SRC_BETH_JOURNALIZE && lem::LogFile::IsOpen())
        // Статистика загрузки: сколько файлов и токенов считано.
        lem::LogFile::logfile->printf(
            "Loaded: %d file(s), %ld token(s)\n"
            , flist.size()
            , text.size()
        );

    return;
}

void Macro_Parser::Open(lem::Stream *file)
{
    next = 0;
    LoadText(file);

    // Добавляем специальный токен - конец файла.
    text.push_back(
        BethToken(
            UToken(
                B_EOF_REACHED,
                SourceState()
            ),
            UNKNOWN,
            UNKNOWN_TOKEN
        )
    );

    return;
}



/****************************************************************
 Добавляет в глобальную таблицу макросов элементы, создаваемые из
 подаваемых строк. Получающиеся макросы будут являться флагами,
 то есть самим своим существованием указывать на некие состояния.
*****************************************************************/
void Macro_Parser::SetDefines(const MCollect<UCString> &defines)
{
    for (Container::size_type i = 0; i < defines.size(); i++)
        // Такой макрос еще не был определен?
        if (IsMacro(defines[i]))
        {
            // Повторное определение макроса.
            ios.merr().printf(
                "%vfDRedefinition of macro [%us]%vn\n"
                , defines[i].c_str()
            );
            throw E_ParserError();
        }
        else
        {
            IR_Macro *m = new IR_Macro(defines[i], L"");
            macro.push_back(m);

            IR_Parser_Variable *var = m->GetVariable(ios);
            if (var)
                global_var_table.push_back(var);
        }

    return;
}

/************************************************************************
 Загружаем весь текст из файла во внутренний буфер (список токенов).
 Это позволяет очень быстро перемещаться по файлу при последующем анализе
 Автоматами, так как не требуется перемещать указатель файла,
 перезагружать буфер и так далее.
*************************************************************************/
void Macro_Parser::LoadText(const wchar_t *filename)
{
    LEM_CHECKIT_Z(lem::lem_is_empty(filename) == false);

    if (options&SRC_BETH_JOURNALIZE && lem::LogFile::IsOpen())
        lem::LogFile::logfile->printf("Preprocessing [%vfE%us%vn]...\n", filename);

    flist.push_back(lem::Path(filename));

    vector<UCString> toks;
    copy(tokens.begin(), tokens.end(), back_inserter(toks));
    UTextParser txtfile(toks);

    // Создаем подходящий для данного типа файлов ридер.
    WideStreamPtr reader = Char_Stream::WideStream::GetReader(StreamPtr(new BinaryReader(lem::Path(filename))));
    if (code_page)
        reader->SetEncoding(code_page);

    txtfile.Open(reader);
    LoadText(txtfile);

    return;
}

void Macro_Parser::LoadText(lem::Stream *file)
{
    LEM_CHECKIT_Z(file != NULL);

    flist.push_back(file->GetName());

    WideStreamPtr reader;

    reader = Char_Stream::WideStream::GetReader(StreamPtr(file, null_deleter()));

    UTextParser txtfile;
    txtfile.Open(reader);
    LoadText(txtfile);

    return;
}


void Macro_Parser::LoadText(UTextParser &txtfile)
{
    include_level++;

    const size_t  file_size = txtfile.fsize();
    const size_t part_on_dot = file_size / 10l + 1l;

    const int ifile = CastSizeToInt(flist.size()) - 1;

    vector<UCString> toks, delims;

    copy(tokens.begin(), tokens.end(), back_inserter(toks));
    copy(compl_delims.begin(), compl_delims.end(), back_inserter(delims));

    txtfile.SetTokens(toks);
    txtfile.SetComplDelims(delims);

    txtfile.SetFlag(src_set_flags, true);
    txtfile.SetFlag(src_clr_flags, false);

    bool eof_reached = false; // Был достигнут естественный конец файла либо
                            // была считана директива #eof

    int i_token = 0;
    bool was_included = false;

    lem::UFString full_string;

    // Читаем и сохраняем все токены в оперативной памяти.
    while (!txtfile.eof() && !eof_reached)
    {
        UToken t;

        bool ready = false;
        while (!eof_reached && !ready)
        {
            t = txtfile.read(full_string, true);

            if (
                options&SRC_BETH_ECHO_PRINT &&
                !was_included &&
                !(i_token % 100) &&
                !(txtfile.tellp().GetPos() % part_on_dot)
                )
                // Индикация прогресса
                Echo_Progress_Dot(100 * txtfile.tellp().GetPos() / (file_size + 1));

            if (t.string().empty())
            {
                eof_reached = true;
                continue;
            }

            if (t.GetToken() == LEM_SOURCE_EOL)
            {
                line_count++;
                continue; // Символ конца строки нужен только препроцессору.
            }

            if (t == t_Double_Diez)
            {
                // Макрооперация слияния двух лексем. Лексему слева уже поместили 
                // в результирующий список.
                Merge(txtfile);
                continue;
            }

            if (do_check_mixage && check_mixage(t.string()))
            {
                txtfile.Error(t, t.length());
                ios.merr().printf(
                    "%vfDMixing cyrillic and latin chars in token [%us]%vn\n"
                    , t.c_str()
                );
                throw E_ParserError();
            }

            if (t == t_Diez)
            {
                // В исходном тексте встретился символ '#' - начало некой
                // препроцессорной операции.
                const UToken tnext = txtfile.read();

                if (tnext.GetToken() == B_EOF_REACHED)
                    eof_reached = true;
                else if (tnext == t_Region || tnext == t_EndRegion)
                {
                    // Считываем все токены до конца строки, больше никаких действий не предпринимаем.
                    while (!txtfile.eof())
                    {
                        UToken probe = txtfile.read();
                        if (probe.GetToken() == LEM_SOURCE_EOL || tnext.GetToken() == B_EOF_REACHED)
                            break;
                    }
                }
                else if (tnext == t_Include)
                {
                    UFString fn;
                    try
                    {
                        // Имя файла может быть строковым выражением.
                        IR_Parser_Stack parser(ios);
                        parser.Parse(txtfile, global_var_table, macro);
                        fn = root_dir + parser.get_string_exp(global_var_table, macro);
                    }
                    catch (...)
                    {
                        txtfile.Error(tnext, t_Include.length());
                        ios.merr().printf("Error when parsing %vfE#include%vn preprocessor directive: invalid string expression\n");
                        throw;
                    }

                    full_string.clear();
                    LoadText(fn.c_str());
                    was_included = true;
                    break;
                }
                else if (tnext == t_Define)
                    AddMacro(txtfile);
                else if (tnext == t_Undefine)
                    DelMacro(txtfile);
                else if (tnext == t_If)
                    DeclareIf(txtfile);
                else if (tnext == t_Else || tnext == t_Elif)
                    ProcessElse(txtfile, t);
                else if (tnext == t_Endif)
                    ProcessEndif(txtfile, t);
                else if (tnext == t_Error)
                    ErrorMessage(txtfile);
                else if (tnext == t_Print)
                    PrintMessage(txtfile);
                else if (tnext == t_Stop)
                    StopReading(txtfile);
                else if (tnext == t_Seq)
                    Sequence(txtfile);
                else if (tnext == t_Pragma)
                    Pragma(txtfile);
                else if (tnext == t_File || tnext == t_Line)
                    Reach_EOL(txtfile);
                else if (tnext == t_Enum)
                    InsertEnumerated(txtfile);
                else if (tnext == t_Cast)
                    CastString(txtfile);
                else
                {
                    txtfile.seekp(tnext.GetBegin());
                    ready = true;
                }

                if (!ready)
                    continue;
            }

            if (IsMacro(t.string()))
            {
                // Считанная лексема является именем макроса, поэтому необходимо
                // начать процедуру итерационного разворачивания макроса в список
                // лексем, который мы и добавим в общий список загруженных токенов.
                lem::Collect<UFString> list;

                try
                {
                    Unroll(t, list, txtfile);
                }
                catch (const std::exception &x)
                {
                    txtfile.Error(t, t.length());
                    throw E_ParserError(to_unicode(x.what()).c_str());
                }
                catch (const E_BaseException &x)
                {
                    txtfile.Error(t, t.length());
                    throw E_ParserError(x.what());
                }
                catch (...)
                {
                    txtfile.Error(t, t.length());
                    throw E_ParserError();
                }

                Postprocess(list);
                const int na = CastSizeToInt(list.size());
                for (int i = 0; i < na; i++)
                {
                    // Каждую лексему пребразуем в токен - то есть ищем соответствие
                    // для нее в текущей таблице токенов.
                    const bool ignore_case = ProbeOption(BETH_NO_CASE);

                    const lem::UFString & full_string2 = list[i];
                    if (full_string2.length() >= lem::UCString::max_len)
                    {
                        full_str.push_back(new lem::UFString(full_string2));

                        lem::UCString short_string(lem::left(full_string2, lem::UCString::max_len).c_str());
                        const UToken token(
                            short_string,
                            t.GetBegin(),
                            ignore_case,
                            txtfile.GetTokens()
                        );

                        text.push_back(BethToken(token, full_str.back()->c_str(), ifile, text.size()));
                    }
                    else
                    {
                        const UToken token(
                            UCString(list[i].c_str()),
                            t.GetBegin(),
                            ignore_case,
                            txtfile.GetTokens()
                        );

                        text.push_back(BethToken(token, ifile, text.size()));
                    }
                }
            }
            else
            {
                // Считанная лексема - не макрос, помещаем в контейнер без изменений.

                if (full_string.length() >= lem::UCString::max_len)
                {
                    full_str.push_back(new lem::UFString(full_string));
                    text.push_back(BethToken(t, full_str.back()->c_str(), ifile, text.size()));
                }
                else
                {
                    text.push_back(BethToken(t, ifile, text.size()));
                }
            }

            break;
        } // end of while(!eof_reached)
    } // end of while( !txtfile.eof() ...

    if (!--include_level)
    {
        // Препроцессор работает в предположении о независимости модулей-файлов.
        // После трансляции одного модуля полностью очищаем таблицы макросов.
        ZAP_A(macro);
        ZAP_A(global_var_table);
    }

    /*
     #if LEM_DEBUGGING==1
     for( lem::Container::size_type i=0; i<text.size(); ++i )
      {
       mout->printf( "%3d %us %us\n", i, text[i].c_str(), text[i].GetFullStr() );
      }
     #endif
    */
    return;
}

// ***************************************************************
// В списке list заменяем все тройки X##Y на одиночные токены XY.
// Алгоритм допускает цепочечные слияния типа:
//
//                X##Y##Z      --->     XYZ
//
// ***************************************************************
void Macro_Parser::Postprocess(lem::Collect<UFString> & /*list*/) const
{
    return;
    /*
     int iscan=1;
     while( iscan < list.Items()-1 )
      if( list(iscan)==sol_get_token(B_DIEZ_DUP) )
       {
        const UCString united = list(iscan-1)+list(iscan+1);
        list[iscan-1] = united; // Вписываем 'XY' вместо 'X'
        list.Remove(iscan); // Удаляем '##'
        list.Remove(iscan); // А теперь 'Y'
       }
      else
       iscan++;

     return;
    */
}


// **********************************************************************
// Обрабатываем конструкцию #enum(arg_name[,delimiter]). Необязательный
// аргумент delimiter задает токен, который будет впечатан после каждого
// элемента списка, кроме последнего.
// **********************************************************************
void Macro_Parser::InsertEnumerated(UTextParser &txtfile)
{
    txtfile.read_it(t_OroundParen);

    /*const UCString arg_name =*/ txtfile.read().string();
    UCString delimiter;

    const SourceState back = txtfile.tellp();

    if ((delimiter = txtfile.read()) != t_Comma)
        txtfile.seekp(back);

    txtfile.read_it(t_CroundParen);

    // Теперь можем впечатывать токены.

    // ?????

    return;
}


/************************************************************************
 Часть процедуры макроподстановки. Исходный токен t, который оказался
 именем макроса (был найден в таблице текущих макросов), разворачивается
 методом итераций в список токенов list, после чего эти токены можно
 добавить к общему списку лексем загружаемого файла.
*************************************************************************/
void Macro_Parser::Unroll(
    const UToken &t,
    lem::Collect<UFString> &list,
    UTextParser &txtfile
)
{
    // Возможна макрооперация #seq, которая вставляет целое число. Так что если
    // затравка - токен #, то смотрим токен следом за ним.

    if (t == t_Diez)
    {
        UToken t2 = txtfile.read();
        if (t2 == t_Seq)
        {
            UToken tt = t;
            tt.string() = to_ustr(iseq++);
            list.push_back(tt.c_str());
            return;
        }
        else
            throw E_BaseException(L"Incorrect use of #seq");
    }

    // Затравка - исходный токен.
    list.push_back(t.string().c_str());

    // Данный алгоритм может оказаться вовлеченным в бесконечную
    // рекурсию, к примеру, для фрагмента:
    //                          #define f(x) f(x)
    //                          f(a);
    // Мы ограничиваем максимальную глубину рекурсии, чтобы хоть как-то
    // подстраховаться.
    const int rec_limit = 100;
    int rec_counter = 0;

    // Итерации продолжаем, пока происходят изменения с списке лексем.
    bool changed;
    lem::Collect<UFString> tail;
    lem::Collect<IR_Macro_Subst> subst;

    do
    {
        if (rec_counter++ == rec_limit)
        {
            // 'Актуальная бесконечность' числа итераций - превышен установленный
            // на них лимит.
            Print_Error(ios, txtfile);
            ios.merr().printf("%vfD[%us] macro substitution error: infinite recursion probably%vn\n", t.c_str());
            throw E_ParserError();
        }

        changed = false;

        // This loop is to process ##-directive which merges two lexem on both
        // side.
        for (int il = 1; il < CastSizeToInt(list.size()) - 1; il++)
            if (list[il] == t_Double_Diez.c_str())
            {
                if (!il || (list.size() - il) <= 1)
                {
                    Print_Error(ios, txtfile);
                    ios.merr().printf(
                        "%vfD[%us] macro substitution error: incorrect "
                        "use of token merge macro directive ##%vn\n"
                        , t.c_str()
                    );
                    throw E_ParserError();
                }

                // Merge two lexems on each side of ## directive.
                const UFString result = list[il - 1] + list[il + 1];
                list[il - 1] = result;
                list.Remove(il);
                list.Remove(il);
                changed = true;
                break;
            }

        // Пробуем применить макроподстановки. Ищем в списке макросов определение,
        // которое можно унифицировать с употреблением макроса в тексте.
        const int nmacro = CastSizeToInt(macro.size());
        const IR_Macro* m = NULL;
        for (int im = 0; im < nmacro; im++)
        {
            m = macro[im];

            // Сейчас в списке list пытаемся найти лексему == a. NB: список list
            // может менять свой размер ВНУТРИ цикла, поэтому вызов size() нельзя
            // выносить из шапки цикла!
            for (int ifirst = 0; ifirst < CastSizeToInt(list.size()); ifirst++)
            {
                // В этом списке получим списки лексем, которые необходимо
                // подставить вместо некоторых лексем (имен формальных аргументов)
                // в результатной части.
                subst.clear();

                // В этом поле получим число лексем, которые нужно выбросить из
                // списка list, начиная с лексемы ifirst.
                int n_to_reduce;
                IR_Var_Table local_var_table(&global_var_table);

                if (
                    m->GetHead().DoesMatch(
                        ios,
                        list,
                        ifirst,
                        txtfile,
                        subst,
                        &n_to_reduce,
                        &local_var_table
                    )
                    )
                {
                    // Есть успешная унификация.

                    changed = true;

                    // Начинаем макроподстановку! Перепишем лексемы из list, которые
                    // стоят ПОСЛЕ отбрасываемого куска, в отдельный временный список.
                    tail.clear();

                    const int nlist = CastSizeToInt(list.size());
                    int itail;
                    for (itail = ifirst + n_to_reduce; itail < nlist; itail++)
                        tail.push_back(list[itail]);

                    // Теперь отбрасываем часть списка list, начиная с элемента ifirst.
                    list.resize(ifirst);

                    // Начинаем переносить тело макроса, используя полученные подстановки
                    // для имен формальных параметров.
                    m->GetBody().Perform(ios, list, subst, local_var_table, macro);

                    // Дописываем сохраненный хвост.
                    const int ntail = CastSizeToInt(tail.size());
                    for (itail = 0; itail < ntail; itail++)
                        list.push_back(tail[itail]);
                }
            }
        } // end for по всем макросам
    } while (changed);

    return;
}

/******************************************************************************
 Читаем pragma-директиву, которая может устанавливать некоторые специфические
 флаги чтения и лексического анализа. Если мы не сможем распознать информацию
 в директиве, то просто проигнорируем ее, то есть дойдем до конца текущей
 строки. Так же поступает лексический парсер трансляторов с языка C/C++.
******************************************************************************/
void Macro_Parser::Pragma(UTextParser &txtfile)
{
    const SourceState back = txtfile.tellp();
    const UToken t = txtfile.read();

    if (t.string() == "CodeConverter")
    {
        // Манипуляции с текущей кодовой таблицей. Если директива имеет формат:
        // #pragma CodeConverter=NNN, то устанавливается новая кодовая таблица,
        // а индекс прежней сохраняется в специальном стеке. Если же использован
        // формат: #pragma CodeConverter <EOL>, то текущая кодовая таблица сбрасывается
        // и восстанавливается прежняя, индекс которой запомнен в стеке. Второй
        // формат директивы не будет иметь силы, если до этого не была прочитана
        // хоть одна директива #pragma CodeConverter=NNN, то есть если стек индексов
        // кодовых таблиц пуст.
        if (txtfile.read().GetToken() == LEM_SOURCE_EOL)
        {
            // Второй формат - восстановление прежней кодовой таблицы.
            if (cp_stack.size())
            {
                const CodeConverter *old_cp = CodeConverter::getConverter(cp_stack.top());
                cp_stack.pop();
                if (old_cp)
                    code_page = old_cp;
            }
        }
        else
        {
            // Устанавливаем новую кодовую таблицу.
            const int code_page_index = txtfile.read_int();
            const CodeConverter *new_cp = CodeConverter::getConverter(code_page_index);
            if (new_cp)
            {
                if (code_page)
                    cp_stack.push(code_page->get_Index());

                code_page = new_cp;
            }
        }

        return;
    }

    if (t == t_Comment)
    {
        // Устанавливаем режим комментариев в исходном тексте. Другими
        // словами, определяем синтаксис участков, которые Транслятор
        // не видит в исходном текстовом файле.

        const UToken t = txtfile.read();
        const UToken mode = txtfile.read();
        const bool f = mode.string() == t_On ? true : false;

        if (t == t_C)
        {
            txtfile.SetFlag(SRC_SKIP_C_COMMENTARY, f);
            Reach_EOL(txtfile);
            return;
        }

        if (t == t_Cpp)
        {
            txtfile.SetFlag(SRC_SKIP_CPP_COMMENTARY, f);
            Reach_EOL(txtfile);
            return;
        }

        if (t == t_Prolog)
        {
            txtfile.SetFlag(SRC_SKIP_PROLOG_COMMENTARY, f);
            Reach_EOL(txtfile);
            return;
        }

        if (t == t_Pascal)
        {
            txtfile.SetFlag(SRC_SKIP_PASCAL_COMMENTARY, f);
            Reach_EOL(txtfile);
            return;
        }

        if (t == t_Lisp)
        {
            txtfile.SetFlag(SRC_SKIP_LISP_COMMENTARY, f);
            Reach_EOL(txtfile);
            return;
        }
    }

    if (t == t_Floating)
    {
        // Изменяем режим интерпретации чисел с плавающей запятой:
        // включаем либо блокируем формат типа AAA.BBB. Напоминаю,
        // что в продукционных правилах Алеф-Автомата возможны
        // записи типа "1.2", которые не есть числа, а являютс
        // на самом деле записями "1 . 2", то есть точка является разделителем.
        txtfile.SetFlag(SRC_READ_FLOATING, (txtfile.read() == t_On ? true : false));
        return;
    }

    if (t == t_LanguageMix)
    {
        do_check_mixage = txtfile.read() == t_On;
        return;
    }

    txtfile.seekp(back);
    Reach_EOL(txtfile);

    return;
}

/********************************************
 Читаем лексемы до конца текущей строки.
*********************************************/
void Macro_Parser::Reach_EOL(UTextParser &txtfile)
{
    while (!txtfile.eof() && txtfile.read().GetToken() != LEM_SOURCE_EOL) {}
    return;
}

/*************************************************************************
 Определение нового макроса операцией #define. Контролируем уникальность
 определяемого макроса. Если созданный макрос имеет вид
            #define NAME CONTENT
 или
            #define FLAG
 то создаётся глобальная переменная, доступная в парсере калькулятора.
*************************************************************************/
void Macro_Parser::AddMacro(UTextParser &txtfile)
{
    const UToken mbeg = txtfile.read();
    txtfile.seekp(mbeg.GetBegin());

    IR_Macro *m = new IR_Macro(ios, txtfile); // Загружаем макрос полностью.

    // Попробуем создать из него переменную...
    IR_Parser_Variable *var = m->GetVariable(ios);
    if (!!(var))
        // Удалось - обновляем глобальную таблицу переменных.
        global_var_table.push_back(var);

    // Такой макрос еще не был определен?
    const UCString& macro_name = m->GetHead().GetName();
    if (IsMacro(macro_name))
    {
        // Переопределение макроса не допускаем.
        Print_Error(ios, mbeg, txtfile);
        ios.merr().printf(
            "%vfDRedefinition of macro [%us]%vn\n"
            , macro_name.c_str()
        );
        delete m;
        throw E_ParserError();
    }
    else
        macro.push_back(m);

    return;
}

/*************************************************************************
 Уничтожает макрос по директиве #undef. Уничтожение неопределенного
 ранее макроса не контролируется и опасности не представляет, как
 и в стандарте препроцессора C/C++. Одновременно удаляем соответствующую
 переменную из глобальной таблицы.
*************************************************************************/
void Macro_Parser::DelMacro(UTextParser &txtfile)
{
    const UToken macro_name = txtfile.read(); // Считываем имя макроса

    // Такой макрос уже был определен?
    for (Container::size_type i = 0; i < macro.size(); i++)
        if (macro[i]->GetHead().GetName() == macro_name.string())
        {
            macro.Remove(i); // Удаляем определение макроса из списка
            global_var_table.Remove(macro_name.string());
            return;
        }

    return;
}

/**********************************************************************
 Препроцессорная операция помещения следующего токена
 в двойные апострофы: макровыражение #str(abc) помещает в текст "abc".
***********************************************************************/
const UToken Macro_Parser::CastString(UTextParser &txtfile)
{
    const UToken t = txtfile.read();
    const UCString lexem = UCString('"') + t.string() + UCString('"');
    const UToken ret(
        lexem,
        t.GetBegin(),
        false,
        txtfile.GetTokens()
    );
    return ret;
}

/*****************************************************************
 Объявление препроцессорной альтернативы #if. В данном случае мы
 интерпретирует конструкцию.
******************************************************************/
void Macro_Parser::DeclareIf(UTextParser &txtfile)
{
    IR_Parser_Stack parser(ios);

    // Передаём парсеру токены макровыражения до конца строки.
    parser.Parse(txtfile, global_var_table, macro);

    // Результат вычисления логического выражения справа от #if.
    const bool res = parser.get_bool_exp(global_var_table, macro);

    if (res)
    {
        // Необходимо будет читать весь текст в then-ветке и затем пропустить
        // else-ветку. Поэтому поместим на стек блоков соответствующую метку,
        // так что по встрече с закрывающей директивой #endif или #else можно
        // будет предпринять необходимые действия.
        block.push(SOL_IR_DO_IGNORE_ELSE);
    }
    else
    {
        // Пропускаем текст в then-ветке и приступим к транслированию текста
        // в else-ветке, если она есть. Могут встретится также #elif-ветки,
        // которые обрабатываются аналогично #else-веткам, с минимальным отличием.
        int n_open_if = 1; // Число открытых вложенных #if блоков.
        bool found = false;
        while (!found && n_open_if > 0)
        {
            if (txtfile.eof())
            {
                // Отсутствует #endif !
                Print_Error(ios, txtfile);
                ios.merr().printf("%vfDPreprocessor directive #if...#else...#endif syntax error%vn\n");
                throw E_ParserError();
            }

            if (txtfile.read() == t_Diez)
            {
                UToken t2 = txtfile.read();
                if (t2 == t_If)
                    n_open_if++;
                else if (t2 == t_Endif)
                    n_open_if--;
                else if (t2 == t_Else)
                {
                    if (n_open_if == 1)
                    {
                        // Мы нашли именно нашу else-ветку. Теперь ее надо транслировать до
                        // появления препроцессорного оператора #endif. На стек блоков помещаем
                        // специальную метку.
                        block.push(SOL_IR_DO_PROCESS_ELSE);
                        found = true;
                    }
                }
                else if (t2 == t_Elif)
                {
                    if (n_open_if == 1)
                    {
                        // Мы нашли нашу #elif-ветку. Теперь проверим логическое условие, котрое
                        // стоит справа, и если оно даст true, то ее надо транслировать до
                        // появления препроцессорного оператора #endif. На стек блоков помещаем
                        // специальную метку. Если логическое условие дает false, продолжаем
                        // поиск #else или #elif веток.
                        IR_Parser_Stack parser(ios);

                        // Передаём парсеру токены макровыражения до конца строки.
                        parser.Parse(txtfile, global_var_table, macro);

                        const bool res = parser.get_bool_exp(global_var_table, macro); // Логическое выражение стоит справа от #if

                        if (res)
                        {
                            block.push(SOL_IR_DO_IGNORE_ELSE);
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    return;
}

/******************************************************************
 Нам встретился препроцессорный оператор #else. На стеке блоков
 ОБЯЗАТЕЛЬНО должен находиться флаг IR_DO_IGNORE_ELSE, то есть нам
 должна соответствовать директива #if.
******************************************************************/
void Macro_Parser::ProcessElse(
    UTextParser &txtfile,
    const UToken& t
)
{
    int tos = UNKNOWN;

    if (!block.empty())
    {
        tos = block.top();
        block.pop();
    }

    if (tos != SOL_IR_DO_IGNORE_ELSE)
    {
        Print_Error(ios, t, txtfile);
        // Отсутствует #if
        ios.merr().printf("%vfD#else directive without mathing #if%vn\n");
        throw E_ParserError();
    }

    // Теперь пропускаем else-ветку (до оператора #endif).
    int n_open_if = 1; // Число открытых вложенных блоков #if
    while (n_open_if > 0)
    {
        if (txtfile.eof())
        {
            // Отсутствует #endif !
            Print_Error(ios, txtfile);
            ios.merr().printf("%vfDPreprocessor directive #if...#else...#endif syntax error%vn\n");
            throw E_ParserError();
        }

        if (txtfile.read() == t_Diez)
        {
            const UToken t = txtfile.read();
            if (t == t_If)
                n_open_if++;
            else if (t == t_Endif)
                n_open_if--;
        }
    }

    // if( !txtfile.eof() )
    //  block.pop();

    return;
}

/***********************************************************************
 Нам встретился препроцессорный оператор #endif. На стеке блоков
 ОБЯЗАТЕЛЬНО должен находиться IR_DO_PROCESS_ELSE или IR_DO_IGNORE_ELSE
************************************************************************/
void Macro_Parser::ProcessEndif(
    UTextParser &txtfile,
    const UToken &t
)
{
    int tos = UNKNOWN;

    if (!block.empty())
    {
        tos = block.top();
        block.pop();
    }

    if (tos != SOL_IR_DO_PROCESS_ELSE && tos != SOL_IR_DO_IGNORE_ELSE)
    {
        Print_Error(ios, t, txtfile);
        // Отсутствует #if
        ios.merr().printf("%vfD#endif directive without mathing #if%vn\n");
        throw E_ParserError();
    }

    return;
}

/******************************************************************
 Обработка директивы #error - вывод на терминал сообщения об ошибке,
 текст которого определен пользователем в исходном читаемом файле
 программы, и полная остановка трансляции.
******************************************************************/
void Macro_Parser::ErrorMessage(UTextParser &txtfile)
{
    ios.merr().printf(
        "%vfDError in file [%us] in line %d:%vn\n"
        , txtfile.GetName().GetUnicode().c_str()
        , to_ustr(txtfile.GetLine()).c_str()
    );

    txtfile.skip_white();
    txtfile.PrintLine((OFormatter&)ios.merr()); // Вывод содержимого остатка строки
    ios.merr().eol();
    StopReading(txtfile);
    return;
}

/********************************************************************
 Отработка директивы #print - вывод пользовательского сообщения на
 системный терминал без остановки трансляции.
*********************************************************************/
void Macro_Parser::PrintMessage(UTextParser &txtfile)
{
    txtfile.skip_white();
    txtfile.PrintLine(ios.merr()); // Вывод содержимого остатка строки
    ios.merr().eol();
    return;
}

/**********************************************************
 Директива #stop вызывает безусловную остановку трансляции.
***********************************************************/
void Macro_Parser::StopReading(UTextParser&)
{
    if (lem::LogFile::IsOpen())
        lem::LogFile::logfile->printf("%vfDTranslation cancelled%vn\n");

    throw E_ParserError(L"compilation cancelled by #stop directive");
}

void Macro_Parser::ToLineBegin()
{
    const BethToken &t = text[next];

    // Откроем файл, который содержал в себе текущий токен.
    UTextParser txtfile;

    // txtfile.set_Code_Page(code_page);
    // txtfile.Open( flist[t.GetFile()].c_str() );

    WideStreamPtr reader = Char_Stream::WideStream::GetReader(
        StreamPtr(new BinaryFile(lem::Path(flist[t.GetFile()]), true, false))
    );


    reader->SetEncoding(code_page);
    txtfile.Open(reader);
    txtfile.seekp(((const UToken&)t).GetBegin());
    txtfile.ToLineBegin();
    return;
}

/*****************************************************************
 Возвращает очередной токен из списка в оперативной памяти.
 Так как Транслятор активно использует откаты на несколько лексем,
 мы храним индекс последнего считанного токена и анализаруем
 необходимость печатать что-либо в эхо-потоке и в журнале ТОЛЬКО
 если новый считанный токен расположен ЗА последним считанным.
******************************************************************/
const BethToken& Macro_Parser::read(void)
{
    // Хранимый текст всегда содержит один специальный токен B_EOF_REACHED,
    // поэтому самый последний токен не должен участвовать в трассировке
    // транслируемого текста в журнал.

    if (options&SRC_BETH_JOURNALIZE && static_cast<int>(next) > i_last_tok && next < text.size() - 1)
    {
        i_last_tok = next;

        int prev_ifile = -1, prev_line = -1;
        if (next > 0)
        {
            const BethToken &prev_tok = text.at(next - 1);
            prev_ifile = prev_tok.GetFile();
            prev_line = static_cast<const UToken&>(prev_tok).GetBegin().GetLine();
        }

        const BethToken &curr_tok = text.at(next);
        const int ifile = curr_tok.GetFile();
        const int iline = static_cast<const UToken&>(curr_tok).GetBegin().GetLine();
        const int spos = static_cast<const UToken&>(curr_tok).GetBegin().GetSymbolPos();

        if (ifile != prev_ifile && ifile != UNKNOWN)
        {
            // Начали считывать токены из нового файла.
            if (options&SRC_BETH_PRINT_SOURCE && lem::LogFile::IsOpen())
                lem::LogFile::logfile->printf(
                    "\nLoading [%us]...\n",
                    GetFileName(ifile).GetUnicode().c_str()
                );
        }

        if (ifile != UNKNOWN && iline != prev_line && (options&SRC_BETH_PRINT_SOURCE) && lem::LogFile::IsOpen())
        {
            if (options&SRC_BETH_PRINT_LINE_NUM)
                // С печатью номеров строк.
                lem::LogFile::logfile->printf("\n%W5Ard%H ", iline, spos + 5);
            else
                lem::LogFile::logfile->printf("\n%H ", spos + 5);
        }

        if (ifile != UNKNOWN && options&SRC_BETH_PRINT_SOURCE && lem::LogFile::IsOpen())
            // Печатаем очередной прочитаный токен.
            lem::LogFile::logfile->printf("%Fs1us ", curr_tok.string().c_str());
    }

    if (next >= text.size())
        return text.back();

    return text[next++];
}


const BethToken& Macro_Parser::pick(void)
{
    if (next >= text.size())
        return text.back();

    return text[next];
}


/*********************************************************************
 Из текста должен быть считан токен с указанным кодом. Если этого не
 произойдет, то трансляция останавливается с выдачей диагностики.
*********************************************************************/
void Macro_Parser::read_it(int token)
{
    const BethToken& t = read();

    if (t.GetToken() != token)
    {
        Print_Error(t, *this);

        ios.merr().printf(
            "%vfDRequired token [%us] missing, got [%us]%vn\n"
            , tokens.at(token).c_str()
            , t.c_str()
        );

        throw E_ParserError(L"required token missing");
    }

    return;
}

void Macro_Parser::read_it(const UCString &token)
{
    const BethToken& t = read();

    const bool f = ProbeOption(BETH_NO_CASE) ? token.eqi(t.string()) : token == t.string();

    if (!f)
    {
        Print_Error(t, *this);
        ios.merr().printf(
            "%vfCRequired lexem %vfE%us%vfC missing, got [%us]%vn%vn\n"
            , token.c_str()
            , t.c_str()
        );
        throw E_ParserError();
    }

    return;
}

/********************************************************************
 UToken must be read from list of loaded tokens, and the lexical
 content of the retrieved token should be convertable to int number.
 If not, translation is stopped.
*********************************************************************/
int Macro_Parser::read_int(void)
{
    const BethToken & t = read();

    int res = 0;
    const bool correct = str_c_to_int(t.c_str(), &res);

    if (!correct)
    {
        Print_Error(t, *this);
        ios.merr().printf(
            "%vfCIncorrect format for INT integer field: %vfE%us%vn\n"
            , t.c_str()
        );
        throw E_ParserError();
    }

    return res;
}

int Macro_Parser::read_signed_int(void)
{
    if (probe(L"-"))
        return -read_int();
    else
        return read_int();
}


#if !defined LEM_NOREAL
double Macro_Parser::read_real(void)
{
    const BethToken &t = read();

    double res = 0;
    const bool correct = to_real(t.c_str(), &res);

    if (!correct)
    {
        Print_Error(t, *this);
        ios.merr().printf("%vfCError reading REAL field: %vfE%us%vn", t.c_str());
        throw E_ParserError();
    }

    return res;
}
#endif

/********************************************************************
 Возвращает положение в исходном текстовом файле, если бы мы читали
 токены оттуда, а не из списка в оперативной памяти.
********************************************************************/
const BSourceState Macro_Parser::tellp(void) const
{
    return next >= text.size() ?
        text.back().GetBegin()
        :
        text.at(next).GetBegin();
}

void Macro_Parser::seekp(const BethToken &bt)
{
    seekp(bt.GetBegin());
}

/*****************************************************************
 Возвращается к токену в оперативной памяти, который ходится в
 позиции в исходном текстовом файле, заданной как SourceState.
 Учитываем то факт, что обычно (99% случаев) производится откат
 на один токен назад.
*****************************************************************/
void Macro_Parser::seekp(const BSourceState &ss)
{
    if (ss.GetIndex() >= CastSizeToInt(text.size()) || ss.GetIndex() < 0)
        next = text.size() - 1;
    else
        next = ss.GetIndex();

    return;
}


// *****************************************************
// Обработка макрокоманды a ## b - слияние двух лексем.
// левая лексема 'a' уже помещена в итоговый список.
// *****************************************************
void Macro_Parser::Merge(UTS &txtfile)
{
    UToken b = txtfile.read();

    Collect<UFString> lst;
    Unroll(b, lst, txtfile);

    if (lst.size() != 1)
    {
        // Для операции слияния нужно, чтобы правая часть 'b' была единственной 
        // лексемой!
        txtfile.Error(b, b.length());
        throw E_ParserError(L"Incorrect right part of ## operation");
    }

    BethToken &a = text.back();

    a.string() += lst.front().c_str();

    return;
}


void Macro_Parser::Echo_Progress_Dot(int /*percent*/)
{
    ios.mecho().printf('.');
    return;
}


int Macro_Parser::iseq = 0;
void Macro_Parser::Sequence(UTS & /*txtfile*/)
{
    // В выходной список помещаем очередное число последовательности.
    text.push_back(BethToken(to_ustr(iseq++), CastSizeToInt(flist.size() - 1), text.size()));
}

// Аргумент функции одеваем в '"'
void Macro_Parser::Cast(UTS &txtfile)
{
    // В выходной список помещаем очередное число последовательности.
    txtfile.read_it(L"(");
    UToken b = txtfile.read();
    txtfile.read_it(L")");

    text.push_back(BethToken(UCString(L"\"") + b.string() + UCString(L"\""), flist.size() - 1, text.size()));

    return;
}


/***************************************************************
 Устанавливаем флаги, которые управляют печатью сопроводительной
 информации в Журнал при трансляции текстового файла Словаря.
 При on_off=true флаги устанавливаются, при false - сбрасываются
****************************************************************/
void Macro_Parser::SetOptions(lem::uint32_t opt, bool on_off)
{
    if (on_off)
        options = opt;
    else
        options &= ~opt;

    return;
}



void Macro_Parser::SetSrcOption(lem::uint32_t Options, bool flag)
{
    if (flag)
        src_set_flags |= Options;
    else
        src_clr_flags |= Options;

    return;
}

bool Macro_Parser::ProbeOption(lem::uint32_t Option) const
{
    return (options&Option) == Option;
}

// Два метода для чтения токена, если удалось - возвращается true и курсор
// передвигается, иначе курсор остается на прежнем месте и возвращается false;
bool Macro_Parser::probe(const int token)
{
    if (pick().GetToken() == token)
    {
        read();
        return true;
    }
    else
        return false;
}

bool Macro_Parser::probe(const UCString &token)
{
    if (ProbeOption(BETH_NO_CASE) ? pick().string() == token : pick().string().eqi(token))
    {
        read();
        return true;
    }
    else
        return false;
}
