// -----------------------------------------------------------------------------
// File WORD_FORM.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                https://github.com/Koziev/GrammarEngine
//
// Content:
// Word_Form класс - внутреннее представление словоформы. Является контейнером
// для хранения символьного представления лексемы и служебной информации для
// работы ЦАА. Является также составным элементом СИНТАКСЕМ. Используется для
// хранения описания НОВОЙ СИНТАКСЕМЫ результатной части трансформанты в
// грамматических правилах.
//
// 11.10.2011 - добавлена сериализация в XML
// -----------------------------------------------------------------------------
//
// CD->16.10.1995
// LC->02.04.2018
// --------------

#include <lem/conversions.h>
#include <lem/macro_parser.h>
#include <algorithm>

#include <lem/solarix/tokens.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordCoord.h>
#include <lem/solarix/CoordList.h>

using namespace lem;
using namespace Solarix;

lem::Process::InterlockedInt Word_Form::seq_iversion(0);


Word_Form::Word_Form(void)
{
    score = 0;
    entry_key = UNKNOWN;
    origin_pos = UNKNOWN;
    iversion = seq_iversion++;
    return;
}

Word_Form::Word_Form(const lem::MCollect<const Word_Form*> &variants)
{
    LEM_CHECKIT_Z(!variants.empty());

    // Первая версия становится основной, ее не копируем в альтернативы.
    for (auto variant : variants)
    {
        alt.push_back(new Word_Form(*variant));
    }

    name = variants[0]->name;
    normalized = variants[0]->normalized;
    pair = variants[0]->pair;
    entry_key = variants[0]->entry_key;
    //val = variants[0]->val;
    score = variants[0]->score;
    origin_pos = variants[0]->origin_pos;
    tokenizer_flags = variants[0]->tokenizer_flags;

    iversion = seq_iversion++;
    return;
}


Word_Form::Word_Form(const Lexem &s, int EntryKey)
{
    entry_key = EntryKey;
    name = RC_Lexem(new Lexem(s));
    normalized = name;
    //val = Real1(100);
    score = 0;
    origin_pos = UNKNOWN;
    iversion = seq_iversion++;

    return;
}

Word_Form::Word_Form(const Lexem &s, int EntryKey, const CP_Array &attrs)
{
    entry_key = EntryKey;
    name = RC_Lexem(new Lexem(s));
    normalized = name;
    //val = Real1(100);
    score = 0;
    origin_pos = UNKNOWN;
    iversion = seq_iversion++;

    const int npair = CastSizeToInt(attrs.size());
    pair.reserve(npair);

    for (int i = 0; i < npair; i++)
        pair.push_back(GramCoordEx(attrs[i]));

    return;
}


#if defined SOL_LOADBIN
Word_Form::Word_Form(lem::Stream &bin)
{
    origin_pos = UNKNOWN;
    LoadBin(bin);
    iversion = seq_iversion++;
    return;
}
#endif

Word_Form::Word_Form(
    const RC_Lexem &Name,
    const RC_Lexem &NormalizedName,
    int EntryKey,
    const CP_Array &Pair,
    float form_score //Real1 Val
)
    : name(Name), normalized(NormalizedName), /*val(Val),*/ score(form_score), entry_key(EntryKey)
{
    origin_pos = UNKNOWN;
    iversion = seq_iversion++;

    if (&Pair != nullptr)
    {
        const int npair = CastSizeToInt(Pair.size());
        pair.reserve(npair);
        for (int i = 0; i < npair; i++)
            pair.push_back(GramCoordEx(Pair[i]));
    }

    return;
}


Word_Form::Word_Form(
    const RC_Lexem &Name,
    const RC_Lexem &NormalizedName,
    int EntryKey,
    float form_score //Real1 Val
)
    : name(Name), normalized(NormalizedName), /*val(Val),*/ score(form_score), entry_key(EntryKey)
{
    origin_pos = UNKNOWN;
    iversion = seq_iversion++;
    return;
}



Word_Form::Word_Form(const Word_Form& fw, bool copy_versions)
{
    Init(fw, copy_versions);
    return;
}


Word_Form::~Word_Form(void)
{
    for (lem::Container::size_type i = 0; i < alt.size(); ++i)
        delete alt[i];

    return;
}

void Word_Form::operator=(const Word_Form& fw)
{
    if (&fw != this)
        Init(fw, true);

    return;
}


void Word_Form::Init(const Word_Form &fw, bool copy_versions)
{
    LEM_CHECKIT_Z(&fw != nullptr);

    name = fw.name;
    normalized = fw.normalized;
    pair = fw.pair;
    entry_key = fw.entry_key;
    // val         = fw.val;
    score = fw.score;
    origin_pos = fw.origin_pos;
    tokenizer_flags = fw.tokenizer_flags;

    if (copy_versions)
    {
        iversion = fw.iversion;

        for (auto a : alt)
        {
            delete a;
        }

        alt.clear();

        for (auto a : fw.alt)
        {
            alt.push_back(new Word_Form(*a));
        }
    }
    else
    {
        iversion = seq_iversion++;
    }

    return;
}


bool Word_Form::CanMatch(const Lexem &word) const
{
    return *name == word;
}




/**********************************************************************
 Проверяет равенство координатных пар, хранимых в списке pair здесь
 и в указанной словоформе wf, причем из процедуры сравнения исключаются
 переданные в списке excoord координаты. Также проверяется совпадение
 хранимой лексической информации.
***********************************************************************/
bool Word_Form::AreEqualExcept(
    const Word_Form &wf,
    const CA_Array &excoord
) const
{
    // Прежде всего должна совпасть хранимая лексическая информация.

    if (entry_key == UNKNOWN_STATE || wf.entry_key == UNKNOWN_STATE)
        return wf.GetName() == GetName();

    if (entry_key != wf.entry_key)
        return false;

    // Собираем координаты для нашей словоформы.
    const Container::size_type npair = pair.size();
    CA_Array pairs;
    pairs.reserve(npair + 1);

    for (Container::size_type i1 = 0; i1 < npair; i1++)
    {
        const GramCoordAdr pair_index = pair[i1].GetCoord();

        if (
            // Если координата уже попала в список, и она встречается второй раз,
            // то это AND-координата, мы ее второй раз в список не будем включать.
            pairs.find(pair_index) != UNKNOWN

            ||

            // Координаты из списка excoord не включаем в проверку.
            excoord.find(pair_index) != UNKNOWN
            )
            continue;

        pairs.push_back(pair_index);
    }

    // Добавляем координаты второй синтаксемы.
    const Container::size_type nwfpair = wf.GetnPair();
    for (Container::size_type i2 = 0; i2 < nwfpair; i2++)
    {
        const GramCoordAdr pair_index = wf.pair[i2].GetCoord();

        if (
            // Если координата уже попала в список, и она встречается второй раз,
            // то это AND-координата.

            pairs.find(pair_index) != UNKNOWN

            ||

            excoord.find(pair_index) != UNKNOWN
            )
            continue;

        pairs.push_back(pair_index);
    }

    // Проверяем совпадение координат из списка собранных нами.
    //
    // Требуем от обеих словоформ дать списки состояний по очередной
    // координате из приготовленного списка pairs. При этом мы учтем
    // И-координаты. Далее проверяем, чтобы у полученных списков
    // состояний совпали хотя бы по одному состоянию.

    for (Container::size_type i3 = 0; i3 < pairs.size(); i3++)
    {
        const IntCollect pair_states1 = GetStates(pairs[i3]);
        const IntCollect pair_states2 = wf.GetStates(pairs[i3]);

        if (!find_any(pair_states1, pair_states2))
            return false;
    }

    // Список координат для проверки оказался пуст - считаем, что все совпали.
    return true;
}

/***************************************************************************
 Частный случай предыдущей процедуры, но без списка исключаемых координат.
****************************************************************************/
bool Word_Form::DoesMatch(SynGram &sg, const Word_Form& wf) const
{
    CA_Array excoord;
    return AreEqualExcept(wf, excoord);
}

#if defined SOL_CAA
/***********************************************************
 Определим, присутствует ли в нашем внутреннем списке pair
 координатная пара Pair. Двойной поиск, поэтому обнаруживаем
 также случай координат-синонимов!
************************************************************/
bool Word_Form::Find(const GramCoordPair& Pair) const
{
    return pair.FindOnce(Pair) != UNKNOWN;
}
#endif


/***********************************************************************
 Возвращает состояние измерения pair_index, или UNKNOWN, если измерение
 в списке отсутствует. AT: если в списке словоформы есть несколько пар для
 координаты (AND-координата), то возвращается какое-то одно из состояний.
 Чтобы получить весь список, следует использовать метод ::GetStates.
************************************************************************/
int Word_Form::GetState(const GramCoordAdr& pair_index) const
{
    const int ipair = pair.FindTwice(pair_index);
    return ipair == UNKNOWN ? UNKNOWN : pair.get(ipair).GetState();
}


/************************************************************************
 Составляет список всех состояний у указанной координаты <Coord>.
 Процедура позволяет собрать список всех состояний одной AND-координаты.
*************************************************************************/
const IntCollect Word_Form::GetStates(const GramCoordAdr& Coord) const
{
    IntCollect res;

    // Первый проход - с точным учетом синонимов.
    const int npair = GetnPair();

    for (int i = 0; i < npair; i++)
    {
        if (pair[i].GetCoord() == Coord)
            res.push_back(pair[i].GetState());
    }

    // Если составленный список оказался пуст, то попробуем найти координаты
    // без учета синонимов.
    if (res.empty())
    {
        for (int i = 0; i < npair; i++)
        {
            if (pair[i].GetCoord().GetIndex() == Coord.GetIndex())
                res.push_back(pair[i].GetState());
        }
    }

    return res;
}


bool Word_Form::FindStateForCoord(
    const GramCoordAdr& pair_index,
    int istate
) const
{
    // Первый проход - с точным учетом синонимов.
    const int npair = GetnPair();

    for (int i1 = 0; i1 < npair; i1++)
    {
        if (pair[i1].GetCoord() == pair_index && pair[i1].GetState() == istate)
            return true;
    }

    // Если составленный список оказался пуст, то попробуем найти координаты
    // без учета синонимов.
    for (int i2 = 0; i2 < npair; i2++)
    {
        if (
            pair[i2].GetCoord().GetIndex() == pair_index.GetIndex() &&
            pair[i2].GetState() == istate
            )
            return true;
    }

    return false;
}

// *****************************************************************
// Проверяет, есть ли координатная пара с координатов icoord
// и в состоянии istate.
// *****************************************************************
bool Word_Form::FindStateForCoord(int icoord, int istate) const
{
    // Первый проход - с точным учетом синонимов.
    const int npair = GetnPair();

    for (int i1 = 0; i1 < npair; i1++)
    {
        if (
            pair[i1].GetCoord().GetIndex() == icoord  &&
            pair[i1].GetCoord().GetVar() == 0 &&
            (pair[i1].GetState() == istate || pair[i1].GetState() == ANY_STATE)
            )
            return true;
    }

    // Если составленный список оказался пуст, то попробуем найти координаты
    // без учета синонимов.
    for (int i2 = 0; i2 < npair; i2++)
    {
        if (
            pair[i2].GetCoord().GetIndex() == icoord &&
            (pair[i2].GetState() == istate || pair[i2].GetState() == ANY_STATE)
            )
            return true;
    }

    return false;
}


#if defined SOL_CAA
/****************************************************************************
 Устанавливает или добавляет указанную координатную пару.

 Если координатная пара с таким же, как у toset, индексом координаты,
 присутствует в списке измерений, то просто изменяем ее состояние на
 переданное в toset. В противном случае добавляем координатную пару
 к списку.

 NB: Если кординат типа toset несколько в нашем списке, то будем добавлять.
*****************************************************************************/
void Word_Form::SetState(const GramCoordPair& toset, bool do_add, bool apply_versions)
{
    iversion = seq_iversion++;

    const int ipair = pair.FindOnce(toset.GetCoord());

    if (ipair == UNKNOWN)
    {
        // Так как такой координаты еще нет, то однозначно добавляем.
        pair.push_back(GramCoordEx(toset));
    }
    else
    {
        int ncount = 0;
        for (Container::size_type i = 0; i < pair.size(); i++)
        {
            if (pair[i].GetCoord() == toset.GetCoord())
                ncount++;
        }

        if (ncount > 1 || do_add)
            pair.push_back(GramCoordEx(toset));
        else
            pair[ipair].SetState(toset.GetState());
    }

    if (apply_versions)
    {
        for (lem::Container::size_type i = 0; i < alt.size(); ++i)
            alt[i]->SetState(toset, do_add);
    }

    return;
}
#endif

#if defined SOL_CAA
/*******************************************************
 Возвращает список неповторяющихся индексов координат,
 присутствующих в списке словоформы.
*******************************************************/
const CA_Array Word_Form::GetIndeces(void) const
{
    CA_Array res;
    res.reserve(pair.size());

    GramCoordAdr pair_index;
    for (int i = 0; i < GetnPair(); i++)
    {
        if (res.find(pair_index = pair[i].GetCoord()) != UNKNOWN)
        {
            res.push_back(pair_index);
        }
    }

    return res;
}
#endif

#if defined SOL_CAA
/**********************************************************
 Процедура используется для определения, присутствует ли
 измерение в списке словоформы.
**********************************************************/
bool Word_Form::DoesPresent(const GramCoordAdr& pair_index) const
{
    return pair.FindOnce(pair_index) != UNKNOWN;
}
#endif

#if defined SOL_LOADTXT
/******************************************************************
 Считывание описание узла синтаксического дерева из текстового файла
*******************************************************************/
void Word_Form::LoadTxt(
    CompilationContext &context,
    Macro_Parser &txtfile,
    SynGram &gram
)
{
    //val=Real1(100);
    score = 0;
    iversion = seq_iversion++;

    // Сначала считываем определение класса и имя словарной статьи.
    const BethToken class_name = txtfile.read();
    entry_key = UNKNOWN_STATE;
    int iclass;

    // Если считанная лексема заключена в апострофы, то имеем дело
    // с сокращенным форматом: ?:строка. Этот формат применяется дл
    // описания лексемы, принадлежность которой к какому-либо классу
    // не очевидна или не важна, а важно лексическое представление.
    if (in_apostrophes(class_name.string()))
    {
        name = RC_Lexem(new Lexem(strip_quotes(class_name.string())));
        return;
    }

    if (class_name.string() == SOL_UNKNOWN_ENTRY_NAME)
    {
        // Только одна статья принадлежит особому классу UNKNOWN!
        // Эта статья может быть описана только как "?:?"

        if (
            txtfile.read().string() == sol_get_token(B_COLON) &&
            txtfile.read().string() == sol_get_token(B_UNKNOWN)
            )
        {
            const Word_Coord iuu = gram.FindEntryForm(class_name.string());
            const SG_Entry& euu = gram.GetEntry(iuu.GetEntry());

            iclass = UNKNOWN_STATE;
            entry_key = euu.GetKey();
            return;
        }
    }

    // Пытаемся найти имя синтаксического класса в списке
    // уже загруженных в Словаре для синтаксической грамматики.
    if ((iclass = gram.FindClass(class_name.string())) == UNKNOWN)
    {
        // Класс не определен.
        //
        // Предполагаем, что задано лексическое содержимое некоторой
        // словоформы. Если такая словоформа лексически уникальна,
        // то мы сами можем восстановить пару класс:статья. В случае
        // множественности вариантов тяжесть ответственности ложитс
        // на пользователя.
        Word_Coord ie = gram.FindEntryForm(class_name.string());

        if (ie.GetEntry() == UNKNOWN)
        {
            // Выводим сообщение о неверном имени синтаксического класса или
            // ненайденной словоформе.
            lem::Iridium::Print_Error(class_name, txtfile);
            gram.GetIO().merr().printf("Neither a class previously declared in grammar, nor an entry form\n");
            throw E_ParserError();
        }

        if (ie.GetEntry() != UNKNOWN)
        {
            // Словоформа найдена!
            const SG_Entry& ef = gram.GetEntry(ie.GetEntry());
            entry_key = ef.GetKey();

            // Вероятно, следует также переслать координатные пары.
            const SG_EntryForm& eef = ef.forms()[ie.GetForm()];
            const CP_Array& dims = eef.coords();

            for (Container::size_type ii = 0; ii < dims.size(); ii++)
            {
                // Здесь немного наворочено - прямо использовать конструктор без
                // копирования в промежуточные поля нельзя из-за ошибки в
                // кодогенераторе Symantec C++ (появляется General Protection Fault).
                const GramCoordAdr ca = dims[ii].GetCoord();
                const int cs = dims[ii].GetState();
                pair.push_back(GramCoordEx(ca, cs, true));
            }

            // И наконец, пересылаем полное имя (лексическое содержимое) статьи.
       //     icenter=0;
       //     e_list.push_back( entry_key );
            name = RC_Lexem(const_cast<Lexem*>(&ef.GetName()), null_deleter());
        }

        return;
    }

    const BSourceState back = txtfile.tellp();
    const BethToken t = txtfile.read();

    bool read_ofigparen = true;
    if (t.GetToken() == B_COLON)
    {
        // Считываем имя статьи, которое может в общем случае состоять
        // из нескольких лексем. Признаком окончания имени служит
        // открывающая фигурная скобка '{'.

        Lexem *mname = new Lexem(sol_read_multyname(gram.GetIO(), txtfile, B_OFIGPAREN));

        // Преобразуем в мультилексему так, чтобы правильно распознавались
        // объявления имен типа "ЕЩ^Ё".
        gram.GetDict().GetLexAuto().TranslateLexem(*mname, false);
        mname->Translate(gram.GetDict().GetGraphGram(), 2);

        //(*name) = mname;
        name = RC_Lexem(mname);

        //   lexem_owner.resize(1);
        //   lexem_owner.Nullify();

        read_ofigparen = false;

        // Пытаемся найти статью.
        if (*mname != sol_get_token(B_ANY))
        {
            // Считан НЕ квантор всеобщности, так что это должно быть имя статьи.
            // Попытаемся найти статью среди уже загруженных, причем ищем с
            // критерием принадлежности определенному синтаксическому классу.

            const int ientry = gram.FindEntry2(*mname, iclass);

            // Нашли ?
            if (ientry == UNKNOWN)
            {
                // Нет! Выводим сообщение об неверном имени словарной статьи.
                lem::Iridium::Print_Error(txtfile);
                gram.GetIO().merr().printf(
                    "The entry [%us:%us] is not previously declared in grammar\n"
                    , gram.classes()[iclass].GetName().c_str()
                    , mname->ToString().c_str()
                );
                throw E_ParserError();
            }

            // Запомним КЛЮЧ словарной статьи.
            entry_key = gram.GetEntry(ientry).GetKey();
        }
        else
            entry_key = ANY_STATE;
    }
    else
    {
        txtfile.seekp(back);
        entry_key = ANY_STATE;
    }

    bool load_precise = true;
    if (read_ofigparen)
    {
        const BSourceState back = txtfile.tellp();
        if (txtfile.read().GetToken() != B_OFIGPAREN)
        {
            // Секции уточнения координат нет.
            txtfile.seekp(back);
            load_precise = false;
        }
    }

    if (load_precise)
        LoadPreciser(context, txtfile, gram, iclass);

    return;
}
#endif

#if defined SOL_LOADTXT
void Word_Form::LoadPreciser(
    CompilationContext &context,
    Macro_Parser& txtfile,
    SynGram& gram,
    int iclass
)
{
    // Тапереча в {} могет быть идти список уточняющих координат.
    //
    // Каждая уточняющая координата должна следовать такому формату:
    //
    //  [~]имя_координаты:имя_состояния
    //
    // Причем, только если вместо имени статьи указан квантор всеобщности,
    // то разрешается задавать АТРИБУТЫ как координаты.
    //
    // Особо обрабатываются координаты с неявно объявленными состояниями
    // TRUE/FALSE. Следует учесть, что само упоминание имени такой координаты
    // равносильно упоминанию также и имени состояния TRUE, а для объявлени
    // состояния FALSE необходимо использовать конструкцию с оператором
    // отрицания НЕ.

    while (!txtfile.eof())
    {
        // Считываем имя координаты.
        BethToken coord_name = txtfile.read();

        // Может, список закончился, то есть встретилась '{' ?
        if (coord_name.GetToken() == B_CFIGPAREN)
            break;


        // В двойных апострофах может идти имя формы, которую надо использовать вместо
        // имени словарной статьи.
        if (lem::in_quotes(coord_name.string()))
        {
            Lexem *mname = new Lexem(strip_quotes(coord_name));

            gram.GetDict().GetLexAuto().TranslateLexem(*mname, false);
            mname->Translate(gram.GetDict().GetGraphGram(), 2);
            name = RC_Lexem(mname);
        }
        else
        {
            bool AFFIRM = true;

            if (coord_name.GetToken() == B_NEGATIVE)
            {
                // Оператор отрицания перед определением координаты!
                AFFIRM = false;
                coord_name = txtfile.read();
            }

            const GramCoordAdr iglob_coord = gram.FindCoord(coord_name.string());

            // Попытаемся найти координату среди списка атрибутов и тэгов.
            int iloc_coord = gram.classes()[iclass].attrs().find(iglob_coord);

            // Нашли?
            if (iloc_coord != UNKNOWN)
            {
                // Да! Примем к сведению, что если для опорной точки задано
                // имя словарной статьи, то мы не имеем право по логике вещей
                // определять также и атрибуты, так как само определение словарной
                // статьи определяет необходимые атрибуты.
                if (entry_key != ANY_STATE)
                {
                    lem::Iridium::Print_Error(coord_name, txtfile);
                    gram.GetIO().merr().printf(
                        "The attribute can not be declared here, because entry is already declared\n"
                    );
                    throw E_ParserError();
                }
            }
            else
            {
                // Попробуем найти координату среди списка измерений.
                iloc_coord = gram.classes()[iclass].dims().find(iglob_coord);

                if (iloc_coord == UNKNOWN)
                    iloc_coord = gram.classes()[iclass].tags().find(iglob_coord);

                // Нашли?
                if (iloc_coord == UNKNOWN && iclass != SOL_EQUIL_INDEX)
                {
                    // Нет. Таким образом, имя координаты не определяет
                    // ни тэг, ни измерение. Генерируем сообщение
                    // об ошибке.

                    lem::Iridium::Print_Error(coord_name, txtfile);
                    gram.GetIO().merr()
                        .printf(
                            "Coordinate [%us] is neither tag"
                            " nor dimention for the class [%us]\n"
                            , coord_name.string().c_str()
                            , gram.classes()[iclass].GetName().c_str()
                        );

                    throw E_ParserError();
                }
            }

            /*-------------------------------------------------------------------------

            Теперь считываем определение состояния.

            В некоторых случаях допускается такой формат записи:

                                 имя_координаты:=индекс

            Обычно так указываются те состояния, которые имеет данная координата
            у заданной индексом опорной точки контекста. Внутреннее описание в этом
            случае отличается от обычного лишь тем, что состояние имеет знак минус
            и хранит на самом деле числовое значение индекса минус единица, так
            что состояние -1 означает опорную точку 0, и так далее. Это сделано,
            чтобы корректно отличать случай состояния с нулевым индексом.

            -------------------------------------------------------------------------*/

            int istate;

            const BSourceState back = txtfile.tellp();
            if (
                txtfile.read().GetToken() == B_COLON &&
                txtfile.read().GetToken() == B_EQUAL
                )
                istate = -txtfile.read_int() - 1; // Да, это формат ИМЯ_КООРД:=ИНДЕКС
            else
            {
                txtfile.seekp(back);

                // Является ли она бистабильной?
                if (gram.coords()[iglob_coord.GetIndex()].states().empty())
                {
                    // Да - считывать имя состояния не надо.
                    istate = AFFIRM;
                }
                else
                {
                    // Индекс состояния у найденной координаты.
                    txtfile.read_it(B_COLON);
                    const BethToken state_name = txtfile.read();
                    istate = gram.coords()[iglob_coord.GetIndex()].FindState(state_name.string());

                    if (istate == UNKNOWN)
                    {
                        lem::Iridium::Print_Error(state_name, txtfile);
                        gram.GetIO().merr().printf(
                            "State [%us] is not declared for coordinate [%us]\n"
                            , state_name.c_str(), coord_name.c_str()
                        );
                        throw E_ParserError();
                    }
                }
            }

            pair.push_back(GramCoordEx(iglob_coord, istate, AFFIRM));

        }

    } // конец цикла считывания уточненных координат

    return;
}
#endif


void Word_Form::PrintXML(OFormatter &xml, SynGram &gram) const
{
    xml.printf("<wordform>\n");

    lem::UFString sword(lem::encode_chars_to_xml(GetName()->c_str()));
    xml.printf("<word>%us</word>\n", sword.c_str());

    xml.printf("<origin_pos>%d</origin_pos>\n", GetOriginPos());
    xml.printf("<id_entry>%d</id_entry>\n", entry_key);
    // xml.printf( "<val>%4.2f</val>\n", val.GetFloat() );
    xml.printf("<score>%g</score>\n", score);

    if (!pair.empty())
    {
        xml.printf("<coord_pairs count=\"%d\">\n", CastSizeToInt(pair.size()));
        for (lem::Container::size_type i = 0; i < pair.size(); ++i)
        {
            xml.printf("<coord_pair n=\"%d\" id_coord=\"%d\" id_state=\"%d\">", pair[i].GetCoord().GetIndex(), pair[i].GetState());
            pair[i].SaveTxt(xml, gram);
            xml.printf("</coord_pair>\n");
        }
        xml.printf("</coord_pairs>\n");
    }

    if (HasAlt())
    {
        xml.printf("<versions count=\"%d\">\n", CastSizeToInt(GetAlts().size()));
        for (lem::Container::size_type i = 0; i < GetAlts().size(); ++i)
        {
            xml.printf("<version n=\"%d\">\n", CastSizeToInt(i));
            GetAlts()[i]->PrintXML(xml, gram);
            xml.printf("</version>\n");
        }

        xml.printf("</versions>\n");
    }

    xml.printf("</wordform>\n");

    return;
}


void Word_Form::Print(OFormatter &s, SynGram *gram, bool detailed) const
{
    const int nver = 1 + CastSizeToInt(GetAlts().size());
    if (nver > 1)
        s.printf("%vf6((%vn");

    for (int iver = 0; iver < nver; ++iver)
    {
        if (iver > 0)
            s.printf(" ");

        const Word_Form &alt = iver == 0 ? *this : *GetAlts()[iver - 1];

        if (nver > 1)
            s.printf("%vf6version=%d%vn ", alt.iversion);

        if (detailed && !is_quantor(alt.GetEntryKey()) && gram != nullptr)
        {
            // Можем напечатать имя грамматического класса.
            const GramClass &c = gram->classes()[gram->GetEntry(alt.GetEntryKey()).GetClass()];

            s.printf("%vfA%us%vn%us", c.GetName().c_str(), sol_get_token(B_COLON).c_str());
        }

        // Мультилексемные имена - в квадратных скобках.
        int npart = alt.name->Count_Lexems();

        if (npart > 1)
            s.printf("%vf6[%vn");

        s.printf("%vfE%us%vn", alt.name->c_str());

        if (npart > 1)
            s.printf("%vf6]%vn");

        if (alt.GetScore() != 0)
            s.printf("|%g|", alt.GetScore());

        if (detailed)
        {
            s.printf("%vf6%us%vn", sol_get_token(B_OFIGPAREN).c_str());
            alt.SaveTxtPreciser(s, gram);

            if (tokenizer_flags.NotNull() && !tokenizer_flags->empty())
            {
                s.printf(" tokenizer_flag:%us", tokenizer_flags->c_str());
            }

            s.printf("%vf6%us%vn", sol_get_token(B_CFIGPAREN).c_str());
        }
    }

    if (nver > 1)
        s.printf("%vf6))%vn");

    return;
}

void Word_Form::PrintPlain(OFormatter &s, bool EntryKey) const
{
    if (EntryKey)
        s.printf("(");

    const int nver = 1 + CastSizeToInt(GetAlts().size());
    if (nver > 1)
        s.printf("%vf6((%vn");

    for (int iver = 0; iver < nver; ++iver)
    {
        if (iver > 0)
            s.printf(" ");

        const Word_Form &alt = iver == 0 ? *this : *GetAlts()[iver - 1];

        if (name->Count_Lexems() == 1)
            s.printf("%vfE%us%vn", alt.name->c_str());
        else
            s.printf("[%vfE%us%vn]", alt.name->c_str());

        if (EntryKey)
            s.printf(" key=%d)", alt.GetEntryKey());
    }

    if (nver > 1)
        s.printf("%vf6))%vn");

    return;
}





void Word_Form::SaveTxtPreciser(
    OFormatter &txtfile,
    const SynGram *gram
) const
{
    if (!gram)
        return;

    const int npair = GetnPair();
    for (int ipair = 0; ipair < npair; ipair++)
    {
        if (ipair) txtfile.uprintf(L' ');

        const GramCoordAdr icoord = GetPair(ipair).GetCoord();
        const int istate = GetPair(ipair).GetState();
        const UCString dim_name = gram->coords()[icoord.GetIndex()].GetName().front();

        if (gram->coords()[icoord.GetIndex()].states().empty())
        {
            if (istate == ANY_STATE)
                txtfile.printf(
                    "%us%us%us"
                    , dim_name.c_str()
                    , sol_get_token(B_COLON).c_str()
                    , sol_get_token(B_ANY).c_str()
                );
            else
            {
                // Бистабильные координаты выводим особым образом
                const UCString prefix = istate ?
                    UCString("") :
                    sol_get_token(B_NEGATIVE);
                txtfile.printf("%us%us", prefix.c_str(), dim_name.c_str());
            }
        }
        else
        {
            UCString state_name;

            if (istate != ANY_STATE)
                state_name = gram->coords()[icoord.GetIndex()].GetStateName(istate);
            else
                state_name = sol_get_token(B_ANY);

            txtfile.printf(
                "%us%us%us"
                , dim_name.c_str()
                , sol_get_token(B_COLON).c_str()
                , state_name.c_str()
            );
        }
    }

    return;
}


#if defined SOL_SAVEBIN
/**************************************************
 Сохраняет содержимое в указанном бинарном потоке.
***************************************************/
void Word_Form::SaveBin(lem::Stream &bin) const
{
    bool p = !!name;
    bin.write_bool(p);
    if (p)
        name->SaveBin(bin);

    p = !!normalized;
    bin.write_bool(p);
    if (p)
        normalized->SaveBin(bin);

    // lexem_owner.SaveBin(bin);
    // e_list.SaveBin(bin);
    pair.SaveBin(bin);
    // bin.write( &tfield,     sizeof(tfield)     );
    bin.write(&entry_key, sizeof(entry_key));
    // bin.write( &val,        sizeof(val)        );
    bin.write(&score, sizeof(score));
    // bin.write( &icenter,    sizeof(icenter)    );
    bin.write(&origin_pos, sizeof(origin_pos));

    bin.write_int(CastSizeToInt(alt.size()));
    for (lem::Container::size_type i = 0; i < alt.size(); ++i)
        alt[i]->SaveBin(bin);

    return;
}
#endif


#if defined SOL_LOADBIN
/*****************************************************
 Загружает содержимое из указанного бинарного потока.
******************************************************/
void Word_Form::LoadBin(lem::Stream &bin)
{
    bool p = bin.read_bool();

    if (p)
    {
        Lexem *m = new Lexem;
        m->LoadBin(bin);
        name = RC_Lexem(m);
    }

    p = bin.read_bool();
    if (p)
    {
        Lexem *m2 = new Lexem;
        m2->LoadBin(bin);
        normalized = RC_Lexem(m2);
    }

    // lexem_owner.LoadBin(bin);
    // e_list.LoadBin(bin);
    pair.LoadBin(bin);

    // bin.read( &tfield,     sizeof(tfield)     );
    bin.read(&entry_key, sizeof(entry_key));
    // bin.read( &val,        sizeof(val)        );
    bin.read(&score, sizeof(score));
    // bin.read( &icenter,    sizeof(icenter)    );
    bin.read(&origin_pos, sizeof(origin_pos));

    const int n = bin.read_int();
    alt.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        alt.push_back(new Word_Form);
        alt.back()->LoadBin(bin);
    }

    return;
}
#endif

#if defined SOL_CAA
/********************************************************************
 Из внутреннего списка координатных пар удаляется элемент с индексом
 Internal_Pair_Index. Список сдвигается.
*********************************************************************/
void Word_Form::RemoveCoord(int Internal_Pair_Index)
{
    pair.Remove(Internal_Pair_Index);
    iversion = seq_iversion++;
    return;
}
#endif


#if defined SOL_CAA
// Удаляем все пары, относящиеся к заданной координате.
void Word_Form::Remove_Coord_States(const GramCoordAdr &coord)
{
    for (int i = CastSizeToInt(pair.size()) - 1; i >= 0; i--)
        if (pair[i].GetCoord() == coord)
            pair.Remove(i);

    iversion = seq_iversion++;

    return;
}
#endif


/*
int Word_Form::GetMaxContextLen(void) const
{
 int l = tfield.IsInt() ? tfield.GetData() : 0;

 for( lem::Container::size_type i=0; i<pair.size(); i++ )
  if( pair[i].GetState()<0 )
   {
    const int index = -pair[i].GetState()-1;
    l = max( l, index+1 );
   }

 return l;
}
*/


#if defined SOL_CAA
void Word_Form::AddAlt(Word_Form *new_alt)
{
    alt.push_back(new_alt);
    iversion = seq_iversion++;
    return;
}
#endif




#if defined SOL_CAA
Word_Form* Word_Form::CreateNewVersioned(const std::set<int> & ialt) const
{
    lem::MCollect<Word_Form*> cluster;

    const int nver = 1 + CastSizeToInt(GetAlts().size());

    for (std::set<int>::const_iterator iver = ialt.begin(); iver != ialt.end(); ++iver)
    {
        const int iiver = *iver;
        const Word_Form &wf = iiver == 0 ? *this : *GetAlts()[iiver - 1];
        Word_Form * new_wf = new Word_Form(wf, false);
        new_wf->SetOriginPos(GetOriginPos());
        cluster.push_back(new_wf);
    }

    if (cluster.empty())
    {
        // Это странная ситуация.
        return new Word_Form(*this);
    }

    if (cluster.size() == 1)
        return cluster.front();

    // Словоформы кластера надо объединить.
    Word_Form *head = cluster.front();

#if !defined SOL_NO_AA
    for (lem::Container::size_type i = 1; i < cluster.size(); ++i)
        head->AddAlt(cluster[i]);
#endif

    return head;
}
#endif





#if defined SOL_CAA
// Создает полную глубокую копию, причем перечисленные в ialt варианты становятся в начале списка.
Word_Form* Word_Form::CreateNewVersionedSorted(const std::set<int> & ialt) const
{
    lem::MCollect<Word_Form*> cluster;

    const int nver = 1 + CastSizeToInt(GetAlts().size());

    for (std::set<int>::const_iterator iver = ialt.begin(); iver != ialt.end(); ++iver)
    {
        const int iiver = *iver;
        const Word_Form &wf = iiver == 0 ? *this : *GetAlts()[iiver - 1];
        Word_Form * new_wf = new Word_Form(wf, false);
        new_wf->SetOriginPos(GetOriginPos());
        cluster.push_back(new_wf);
    }

    // добавляем в хвост остальные альтернативы
    for (int iiver = 0; iiver < nver; ++iiver)
        if (ialt.find(iiver) == ialt.end())
        {
            const Word_Form &wf = iiver == 0 ? *this : *GetAlts()[iiver - 1];
            Word_Form * new_wf = new Word_Form(wf, false);
            new_wf->SetOriginPos(GetOriginPos());
            cluster.push_back(new_wf);
        }

    if (cluster.empty())
    {
        // Это странная ситуация.
        return new Word_Form(*this);
    }

    if (cluster.size() == 1)
        return cluster.front();

    // Словоформы кластера надо объединить.
    Word_Form *head = cluster.front();

    for (lem::Container::size_type i = 1; i < cluster.size(); ++i)
        head->AddAlt(cluster[i]);

    return head;
}
#endif





#if defined SOL_CAA
/*********************************************************************
 Возвращает состояние координатной пары, хранимой в ячейке с индексом
 Internal_Pair_Index в списке pair.
**********************************************************************/
int Word_Form::GetState(int Internal_Pair_Index) const
{
    return pair[Internal_Pair_Index].GetState();
}
#endif

#if defined SOL_CAA
/**********************************************************************
 Состояние координатной пары, располагающейся в списке pair в ячейке
 с индексом Internal_Pair_Index, принудительно заменяется на New_State.
************************************************************************/
void Word_Form::SetState(
    int Internal_Pair_Index,
    int New_State
)
{
    pair[Internal_Pair_Index].SetState(New_State);
    iversion = seq_iversion++;
    return;
}
#endif


Predef_Word_Form::Predef_Word_Form(int ientry_key, SynGram &gram)
    :Word_Form(
        RC_Lexem(const_cast<Lexem*>(&gram.GetEntry(ientry_key).GetName()), null_deleter()),
        RC_Lexem(const_cast<Lexem*>(&gram.GetEntry(ientry_key).GetName()), null_deleter()),
        ientry_key,
        0 //Real1(100)
    )
{}


#if defined SOL_SAVETXT
void Word_Form::SaveTxt(
    OFormatter &txtfile,
    SynGram &gram,
    bool detailed
) const
{
    switch (GetEntryKey())
    {
    case ANY_STATE:
        txtfile.printf("\"%us\"", sol_get_token(B_ANY).c_str());
        break;

    case UNKNOWN_STATE:
    {
        txtfile.printf("\"%us\"", name->ToString().c_str());
        break;
    }

    default:
    {
        sol_print_class_entry(txtfile, gram, GetEntryKey());

        txtfile << " ";
        break;
    }
    }

    txtfile << sol_get_token(B_OFIGPAREN);

    if (detailed)
        SaveTxtPreciser(txtfile, &gram);

    txtfile << sol_get_token(B_CFIGPAREN) << " ";
    return;
}
#endif




#if defined SOL_CAA
// ***************************************************************
// Лексическое содержимое словоформы приводим в соответствие с
// координатами.
// ***************************************************************
void Word_Form::Rename_By_States(SynGram &sg, bool apply_versions)
{
    iversion = seq_iversion++;

    if (entry_key != UNKNOWN)
    {
        try
        {
            const SG_Entry &E = sg.GetEntry(entry_key);
            const int iclass = E.GetClass();

            const GramClass &C = sg.classes()[iclass];

            // Имеем список всех координатных пар. Из него надо выделить только
            // измерения.
            CP_Array dims;
            dims.reserve(16);

            for (Container::size_type ic = 0; ic < pair.size(); ic++)
            {
                if (C.dims().find(pair[ic].GetCoord()) != UNKNOWN)
                    dims.push_back(pair[ic]);
            }

            // Собрали в список dims только измерения.

            // Ищем подходящую по координатам форму.
            const SG_EntryForm &F = E.FindFormAny(dims);

            // Перекачаем ее координаты себе.
            const CP_Array& c = F.coords();

            for (Container::size_type i2 = 0; i2 < c.size(); i2++)
                SetState(c[i2], false, false);

#if LEM_DEBUGGING==1
            const int npairs2 = CastSizeToInt(pair.size());
#endif

            // Нашли наиболее подходящую форму - берем ее лексическое содержание.
            const Lexem &new_name = F.name();

            name = RC_Lexem(new Lexem(new_name));

            /*
                 // Просто поменять имя словоформы нельзя, так как мы можем быть результатом
                 // свертки. Надо вычленить из списка name те лексемы, которые относятся к
                 // обновленной форме (грамматическому центру), и заменить их на новое
                 // значение.

                 // Начальная позиция в цепочке лексем

                 int i_from = lem::find( lexem_owner, icenter );
                 int n = std::count( lexem_owner.begin(), lexem_owner.end(), icenter );

                 UCStringSet parts;
                 new_name.Split(parts);

                 if( n == parts.size() )
                  {
                   // Число лексем в имени не поменялось
                   UCStringSet old_parts;
                   name->Split( old_parts );

                   for( int i=0; i<n; i++ )
                    old_parts[i_from+i] = parts[i];

                   name = RC_Lexem( new Lexem(old_parts) );
                  }
                 else
                  {
                   // Вряд ли возможная ситуация: у найденной формы имя имеет иное
                   // число лексем, чем у прежней формы.
                   //LEM_STOPIT;
            //       throw E_BaseException( L"Internal syntax engine error" );
                  }
            */
        }
        catch (const E_SG_NoForm&)
        {
        }
    }

    if (apply_versions)
    {
        for (auto a : alt)
        {
            a->Rename_By_States(sg, true);
        }
    }

    return;
}
#endif


bool Solarix::eq_states(
    const Word_Form &Node1,
    const GramCoordAdr &Coord1,
    const Word_Form &Node2,
    const GramCoordAdr &Coord2
)
{
    for (Container::size_type i1 = 0; i1 < Node1.pairs().size(); i1++)
    {
        if (Node1.pairs()[i1].GetCoord() == Coord1)
        {
            for (Container::size_type i2 = 0; i2 < Node2.pairs().size(); i2++)
            {
                if (
                    Node2.pairs()[i2].GetCoord() == Coord2 &&
                    (
                        Node1.pairs()[i1].GetState() == Node2.pairs()[i2].GetState() ||
                        Node1.pairs()[i1].GetState() == ANY_STATE ||
                        Node2.pairs()[i2].GetState() == ANY_STATE
                        )
                    )
                    return true;
            }
        }
    }

    return false;
}


void Word_Form::SelectAlt(int i)
{
    iversion = seq_iversion++;

    if (i > 0)
    {
        name = alt[i]->name;
        pair = alt[i]->pair;
        entry_key = alt[i]->entry_key;
        //   e_list = alt[i]->e_list;
        //   lexem_owner = alt[i]->lexem_owner;
        //   tfield = alt[i]->tfield;
        //   val = alt[i]->val;
        score = alt[i]->score;
        //   icenter = alt[i]->icenter;
        origin_pos = alt[i]->origin_pos;
        //   mark = alt[i]->mark;
    }

    return;
}

void Word_Form::SetOriginPos(int p)
{
    origin_pos = p;
    iversion = seq_iversion++;
    return;
}


void Word_Form::SetName(const RC_Lexem& Name)
{
    name = Name;
    iversion = seq_iversion++;
    return;
}


void Word_Form::SetName(const lem::UCString &x)
{
    Lexem *y = new Lexem(x);
    name.reset(y);
    Lexem *z = new Lexem(x);
    normalized.reset(z);
    return;
}


void Word_Form::SetTokenizerFlag(const lem::UFString &str)
{
    tokenizer_flags = new UFString(str);
    return;
}


bool Word_Form::MatchTokenizerFlag(const lem::UFString &str) const
{
    if (tokenizer_flags.NotNull())
        return str == *tokenizer_flags;
    else
        return false;
}


// максимальное значение оценки среди всех версий 
float Word_Form::GetMaxScore() const
{
    float s = score;
    for (auto a : alt)
    {
        s = std::max(s, a->score);
    }

    return s;
}
