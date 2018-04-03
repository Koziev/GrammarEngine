// -----------------------------------------------------------------------------
// File FORM_TABLE.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// Класс Form_Table - базовый для Словарных Статей и Таблиц Склонений.
//
// 20.05.2006 - реализован механизм чтения дополнительной информации для 
//              каждой записи в таблице формообразования. Признак наличия
//              дополнительной информации - токен :: 
//
// 21.11.2006 - рефакторинг имен методов, убираем подчеркивания.
// 12.12.2008 - поправлен метод SaveTxt для AND-координат
// -----------------------------------------------------------------------------
//
// CD->10.03.1997
// LC->02.04.2018
// --------------

#include <lem/macro_parser.h>
#include <lem/logfile.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/grammar.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/form_table.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;

Form_Table::Form_Table()
{
    iclass = UNKNOWN;
    key = UNKNOWN;
#if defined SOL_LOADTXT && defined SOL_COMPILER
    is_realized = false;
#endif
    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
Form_Table::Form_Table(
    Macro_Parser& txtfile,
    Grammar& gram,
    bool IsRealized
)
{
    LoadTxt(txtfile, gram, IsRealized);
    return;
}
#endif


Form_Table::Form_Table(Stream& bin)
{
    LoadBin(bin);
    return;
}


Form_Table::Form_Table(const Form_Table& e)
{
    Init(e);
    return;
}

void Form_Table::operator=(const Form_Table& e)
{
    Init(e);
}


void Form_Table::Init(const Form_Table& e)
{
    LEM_CHECKIT_Z(&e != NULL);

    key = e.key;
    iclass = e.iclass;
    attr = e.attr;
#if defined SOL_LOADTXT && defined SOL_COMPILER
    is_realized = e.is_realized;
#endif
    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
/********************************************************************
  Загрузка описания Статьи из текстового файла
*********************************************************************/
void Form_Table::LoadTxt(
    Macro_Parser &txtfile,
    Grammar& gram,
    bool IsRealized
)
{
    is_realized = IsRealized;
    iclass = UNKNOWN;

    LoadName(txtfile, gram.GetDict());

    if (iclass == UNKNOWN) // если в LoadName еще не прочитали информацию о принадлежности к грамматическому классу...
    {
        const BethToken class_name = txtfile.read();

        if ((iclass = gram.FindClass(class_name.string())) == UNKNOWN)
        {
            // Не найден класс, заявленный для статьи
            Print_Error(class_name, txtfile);
            gram.GetIO().merr().printf(
                "The class [%us] is not previously declared in grammar\n"
                , class_name.c_str()
            );
            throw E_ParserError();
        }
    }

    LoadBody(txtfile, gram);
    Loaded(gram.GetDict());
    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Form_Table::Loaded(const Dictionary &dict)
{
    if (dict.GetDebugLevel_ir() >= 3)
        dict.GetIO().mecho().printf("%vfAOK%vn\n");

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void Form_Table::LoadBody(Macro_Parser &txtfile, Grammar& gram)
{
    txtfile.read_it(B_OFIGPAREN);

    // *** Считываем описание Таблицы ***
    BethToken token;
    CP_Array common;

    FOREVER
    {
     if (txtfile.eof())
      {
       Print_Error(txtfile);
       gram.GetIO().merr().printf("End of file has been reached before entry body completely loaded\n");
       throw E_ParserError();
      }

     const BSourceState back = txtfile.tellp();
     token = txtfile.read();

     if (token.GetToken() == B_CFIGPAREN)
      {
         // Описание Таблицы закончено.
         break;
        }

       if (ProcessSection(txtfile,gram,token))
        continue;

       txtfile.seekp(back);

       if (LoadAttribute(txtfile,gram))
        continue;

       LoadForm(
                txtfile,
                gram,
                common,
                GramCoordAdr(UNKNOWN,UNKNOWN),
                UNKNOWN,
                GramCoordAdr(UNKNOWN,UNKNOWN),
                UNKNOWN,
                UNKNOWN
                ); // Загружаем словоформу.

    } // конец цикла считывания описания статьи

    return;
}
#endif





#if defined SOL_LOADTXT && defined SOL_COMPILER
/**************************************************************************
     ЗАГРУЗКА ОДНОЙ АТРИБУТНОЙ КООРДИНАТНОЙ ПАРЫ
             из текстового файла

  Общий формат:

     коорд_имя : состояние

 Особое внимание следует уделять автоматическому созданию AND-атрибутов
 для многоохватных состояний. Если такое создание нежелательно, то
 следует заключить имя состояния, входящего в группу многоохватных, в
 круглые скобочки:

           коор_имя : ( состояние )

 ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:

  true - действительно, загружен атрибут или тэг.
  false - это не определение состояния атрибута или тэга.
****************************************************************************/
bool Form_Table::LoadAttribute(
    Macro_Parser &txtfile,
    Grammar& gram
)
{
    const BSourceState back = txtfile.tellp();
    bool negative_state = txtfile.probe(B_NEGATIVE); // считываем префикс в ~ПРИЧАСТИЕ

    BethToken coord_name = txtfile.read();

    // Индекс координаты в списке грамматики.
    const GramCoordAdr iglob = gram.FindCoord(coord_name.string());

    // Найдем атрибут в списке грамматического класса.
    const int iattr = gram.classes()[iclass].attrs().FindTwice(iglob);

    if (iattr == UNKNOWN)
    {
        const int itag = gram.classes()[iclass].tags().FindTwice(iglob);

        if (itag == UNKNOWN)
        {
            txtfile.seekp(back);
            return false;
        }
    }

    // Если координата имеет два неявно объявленных состояния
    // TRUE/FALSE, то состояние явно в данной секции не должно быть
    // указано.

    if (!gram.coords()[iglob.GetIndex()].IsBistable())
    {
        // Несколько состояний у координаты.

        if (negative_state)
        {
            Print_Error(back, txtfile);
            gram.GetIO().merr().printf("~ is appliable to bistable coordinates only, whereas [%us] is not bistable\n", coord_name.c_str());
            throw E_ParserError();
        }

        txtfile.read_it(B_COLON);

        // Учтем, что может встретиться AND-атрибут. Такая координата
        // одновременно может иметь несколько состояний.

        IntCollect statei;
        IntCollect doload;

        FOREVER
        {
         if (txtfile.eof())
          {
           Print_Error(txtfile);
           gram.GetIO().merr().printf("End of file has been reached before list of attribute states in entry completely loaded\n");
           throw E_ParserError();
          }

        // Теперь считаем состояние(-я) для заявленного атрибута.
        const BSourceState back = txtfile.tellp();
        BethToken state_name = txtfile.read();

        bool letautoload = true;

        if (state_name.GetToken() == B_ANY)
         {
          if (StoreQuantors())
           {
            attr.push_back(GramCoordPair(iglob,ANY_STATE));
            break;
           }
          else if (statei.empty())
           {
              // Вместо имен состояний для AND-координаты указан квантор *.
              // Инициализируем координату ВСЕМИ состояниями, заявленными
              // для координаты.

              const int ns = gram.coords()[iglob.GetIndex()].GetTotalStates();

              for (int i = 0; i < ns; i++)
               attr.push_back(GramCoordPair(iglob,i));

              // Продолжать дальше считывание не имеет смысла.
              break;
             }
           }

          if (!statei.empty())
           {
              // Если это запятая, то список AND-состояний продолжается.
              // в противном случае прерываем загрузку состояний.

              if (state_name.GetToken() != B_COMMA)
               {
                txtfile.seekp(back);
                break;
               }
              else
               state_name = txtfile.read();
             }

          // Если имя атрибута заключено в круглые скобочки, то
          // для координатной пары запрещено автоматическое создание.
          if (state_name.GetToken() == B_OROUNDPAREN)
           {
            state_name = txtfile.read();
            txtfile.read_it(B_CROUNDPAREN);
            letautoload = false;
           }

          // Ищем индекс состояния в координате
          const int istate = gram.coords()[iglob.GetIndex()].FindState(state_name.string());
          if (istate == UNKNOWN)
           {
            Print_Error(state_name,txtfile);
            gram.GetIO().merr().printf(
                                       "State [%us] is not declared for coordinate [%us]\n"
                                       , state_name.c_str(), coord_name.c_str()
                                      );
            throw E_ParserError();
           }

          // Добавляем глобальный индекс атрибута и индекс его состояния
          // к нашим спискам.
          statei.push_back(istate);
          doload.push_back(letautoload);
        }

            // Состояния, которые объявлены для атрибута, превратим
            // в список координатных пар и добавим к своему списку
            // атрибутов статьи.
        lem::Container::size_type ils;
        for (ils = 0; ils < statei.size(); ils++)
            attr.push_back(GramCoordPair(iglob, statei[ils]));

        // Автоматически подключим те состояния, которые не запрещены
        // для этого пользователем, не объявлены и входят в подгруппу.
        const GramCoord& c = gram.coords()[iglob.GetIndex()];
        IntCollect attaches; // Автоматически созданные и присоединяемые состояния

        for (ils = 0; ils < statei.size(); ils++)
            if (doload[ils])
            {
                int ibase = statei[ils];

                // Входит ли состояние в группу многоохватных как главное?
                if (c.IsHeadState(ibase))
                {
                    // Да, входит.
                    // Получаем список состояний, входящих в группу.
                    const IntCollect to_attach = c.GetSubgroupIndeces(c.GetSubgroup(ibase));

                    for (Container::size_type ia = 1; ia < to_attach.size(); ia++)
                    {
                        const int state_attach = to_attach.get(ia); // Очередное состояние из группы многоохватных

                        // Посмотрим, можно ли присоединять состояние
                        // iglob:state_attach.
                        //
                        // Противопоказания могут быть следующие.
                        //
                        // 1. Состояние уже присутствует в списке statei.
                        // 2. Состояние уже автоматически создано и
                        //    добавлено в список attaches.
                        //
                        // 3. Координатная пара уже загружена в списки
                        //    статьи.

                        bool already_loaded = false;

                        if (attr.FindOnce(GramCoordPair(iglob, state_attach)) != UNKNOWN)
                            already_loaded = true;

                        if (
                            !already_loaded                      &&
                            find(statei, state_attach) == UNKNOWN   &&
                            find(attaches, state_attach) == UNKNOWN
                            )
                            attaches.push_back(state_attach); // К списку присоединяемых
                    }
                }
            }

        if (!attaches.empty()) // Есть присоединяемые?
        {
            // Необходимо предупредить пользователя об автоматически
            // присоединяемых состояниях.
            lem::LogFile::logfile->printf("\nCoordinate pairs were autocreated for a form table:");

            PrintName(*lem::LogFile::logfile);
            lem::LogFile::logfile->printf(" ->");

            for (Container::size_type ils = 0; ils < attaches.size(); ils++)
            {
                if (ils)
                    lem::LogFile::logfile->printf(",");

                lem::LogFile::logfile->printf(
                    " %us%us%us ",
                    c.GetName().string().c_str(),
                    sol_get_token(B_COLON).c_str(),
                    c.GetStateName(attaches[ils]).c_str()
                );
                attr.push_back(GramCoordPair(iglob, attaches[ils]));
            }

            lem::LogFile::logfile->eol();
        }
    }
    else
    {
        // Добавляем глобальный индекс атрибута и индекс его состояния
        // к нашим спискам, учитывая, что сам факт появления атрибута
        // с неявными состояниями TRUE/FALSE означает его состояние TRUE.
        // Если был префикс ~, то состояние присваиваем FALSE.

        // Есть один особый случай, когда для бистабильной координаты задается
        // состояние - для грамматических кванторов. В этом случае имя состояния
        // обязательно квантор *
        if (StoreQuantors())
        {
            const BSourceState back = txtfile.tellp();

            if (txtfile.read().GetToken() == B_COLON && txtfile.read().GetToken() == B_ANY)
            {
                attr.push_back(GramCoordPair(iglob, ANY_STATE));
            }
            else
            {
                txtfile.seekp(back);
                attr.push_back(GramCoordPair(iglob, !negative_state));
            }
        }
        else
        {
            attr.push_back(GramCoordPair(iglob, !negative_state));
        }
    }

    return true;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/***************************************************************************
  Загружаем одну или несколько словоформ статьи.

  Сначала идет набор координатных пар измерений, далее - одна или
  несколько словоформ в фигурных скобочках.

  ЗАМЕЧАНИЯ О ФОРМАТЕ.

    1. Объявление координатной пары в виде:

                       имя_коорд:*

       вызовет автоматическое создание стольких одинаковых словоформ,
       сколько состояний содержится в объявлении координаты. Только одно
       измерение может автоматически индексироваться.

    2. Следующая запись:

                  имя_коорд { форма1 форма2 ... формаN }

       подразумевает, что в фигурных скобочках содержатся словоформы для
       поочередно всех ГЛАВНЫХ состояний координаты, в порядке их следования
       в описании координаты. Далее такая операция будет именоваться
       "автоматической индексацией".
*****************************************************************************/
void Form_Table::LoadForm(
    Macro_Parser& txtfile,
    Grammar& gram,
    CP_Array &common,
    const GramCoordAdr Do_Autoload,
    int iDoAutoload,
    const GramCoordAdr Indexing,
    int iIndexing,
    int AllQuantor
)
{
    const GramClass &c = gram.classes()[GetClass()];
    BethToken state_name, dim_name;
    BSourceState back;

    // Цикл считывания нескольких словоформ с набором одинаковых
    // состояний измерения.
    //
    // Выход из этого цикла нормально происходит после первого же
    // прохода, но если имеем дело с рекурсивным вызовом, то
    // читаем определения словоформ до появления '}'.

    FOREVER
    {
     GramCoordAdr indexing = Indexing; // Измерение для автоматического индексирования.
     int iindexing = iIndexing; // Индекс в dim измерения для индексирования

     int allquantor = AllQuantor; // Номер координатной пары в списке статьи для
                                 // формирования множества словоформ по квантору '*'

     CP_Array dim = common;        // Временное хранилище для загружаемых координатных пар.

     GramCoordAdr do_autoload = Do_Autoload;
     int ido_autoload = iDoAutoload;
     bool load_forms = true;

     // Загружаем список определенных измерений.
     FOREVER
      {
       if (txtfile.eof())
        {
         Print_Error(txtfile);
         gram.GetIO().merr().printf("End of file has been reached before list of dimension pairs in entry form completely loaded\n");
         throw E_ParserError();
        }

       dim_name = txtfile.read();

       if (dim_name.GetToken() == B_OFIGPAREN)
        break;

       // Если встречается '|', то значит будем иметь дело с вложенным
       // рекурсивным блоком. На вход считывания подаем список координатных
       // пар, уже загруженных в данном проходе.
       if (dim_name.GetToken() == B_ORSIGN)
        {
         txtfile.read_it(B_OFIGPAREN);
         LoadForm(
                  txtfile,
                  gram,
                  dim,
                  do_autoload,
                  ido_autoload,
                  indexing,
                  iindexing,
                  allquantor
                 ); // Вот он, рекурсивный вызов!

         load_forms = false;
         break;
        }

       bool negation = false;
       if (dim_name.GetToken() == B_NEGATIVE)
        {
           // Формат ~имя_координаты может использоваться только
           // для бистабильных измерений. Проверим.
           negation = true;
           dim_name = txtfile.read();
          }

         const UCString& dim__name = dim_name.string();

         // Является ли это измерение законным для статьи?

         const GramCoordAdr dim_glob_index = gram.FindCoord(dim__name); // Индекс координаты в списке грамматики

         if (dim_glob_index.GetIndex() == UNKNOWN)
          {
           Print_Error(dim_name,txtfile);
           gram.GetIO().merr().printf(
                                      "Coordinate [%us] is not previously declared in grammar\n"
                                      , dim_name.c_str()
                                     );
           throw E_ParserError();
          }

         // Индекс координаты в списке класса
         const int dim_loc_index = c.dims().FindTwice(dim_glob_index);
         if (dim_loc_index == UNKNOWN)
          {
           Print_Error(dim_name,txtfile);
           gram.GetIO().merr().printf(
                                      "Coordinate [%us] is not declared as a dimension for class [%us]\n"
                                      , dim_name.c_str(), c.GetName().c_str()
                                     );
           throw E_ParserError();
          }

         if (gram.coords()[dim_glob_index.GetIndex()].IsBistable())
          {
             // Это бистабильная координата.
             GramCoordPair p(dim_glob_index, !negation);
             if (dim.find(p) != UNKNOWN)
              {
               gram.GetIO().merr().printf("Dimension [%us] is already defined\n", dim_name.c_str());
               throw E_ParserError();
              }

             dim.push_back(p);
             continue;
            }

         // Теперь считываем имя состояния измерения.

         back = txtfile.tellp();
         state_name = txtfile.read();

         /*---------------------------------------------------------------------------
           Для упрощения описания группы словоформ, которые различаются состоянием
           одного измерения, введен специальный прием. Если для одного измерения
           не задано состояния, а следом идет открывающая фигурная скобочка,
           то значит далее идет несколько словоформ, число их соответствует
           числу стояний у индексируемого измерения. При этом для каждой определяемой
           таким образом словоформы состояние индексируемого измерения пробегает
           последовательно все значения.
         ----------------------------------------------------------------------------*/
         if (state_name.GetToken() != B_COLON)
          {
           if (iindexing != UNKNOWN)
            {
             Print_Error(state_name,txtfile);
             gram.GetIO().merr().printf(
            "Second use of the coordinate autoindexing mode : define a state for "
            "coordinate\n"
                                       );
             throw E_ParserError();
            }

           txtfile.seekp(back);
           // Это измерение будет автоматически индексироваться
           indexing = dim_glob_index;
           iindexing = dim.size();

           // Индекс состояния будем переустанавливать во время индексирования
           dim.push_back(GramCoordPair(dim_glob_index,UNKNOWN));
           continue;
          }

         state_name = txtfile.read();

         // Имя состояния, заключенное в круглые скобки, означает, что
         // для данного измерения отключается автоматическое создание
         // для состояний из подгруппы многоохватных.

         if (state_name.GetToken() == B_OROUNDPAREN)
          {
           state_name = txtfile.read();
           txtfile.read_it(B_CROUNDPAREN);
          }
         else
          {
             // Если состояние является главным в подгруппе многоохватных,
             // и пользователь явно не наложил запрет, то включим механизм
             // автосоздания.

             if (gram.coords()[dim_glob_index.GetIndex()].HasDefStates())
              {
               if (do_autoload.GetIndex() != UNKNOWN)
                {
                   // Два - недопустимо!
                   Print_Error(state_name,txtfile);
                   gram.GetIO().merr().printf("Only one multycoordinate is allowed\n");
                   throw E_ParserError();
                  }

                 do_autoload = dim_glob_index;
                 ido_autoload = dim.size();
                }
              }

         // Внимание! Если имя состояния измерения заявлено как '*', то
         // подразумевается, что словоформы, отличающиеся только состоянием
         // данного измерения совпадают лексически.
         // Есть особый случай интерпретации: для определений грамматических кванторов.
         if (state_name.GetToken() == B_ANY)
          {
           if (StoreQuantors())
            {
             dim.push_back(GramCoordPair(dim_glob_index,ANY_STATE));
            }
           else
            {
             if (allquantor != UNKNOWN)
              {
               Print_Error(state_name,txtfile);
               gram.GetIO().merr().printf(
                    "Second use of ALL quantor in entry form group description is not "
                    "allowed. Only one quantor must remain\n"
                                         );
               throw E_ParserError();
              }

             allquantor = dim.size();
             dim.push_back(GramCoordPair(dim_glob_index,UNKNOWN));
            }
          }
         else
          {
             // Определяем индекс состояния в списке координаты.
             const int istate = gram.coords()[dim_glob_index.GetIndex()].FindState(state_name.string());

             if (istate == UNKNOWN)
              {
               Print_Error(state_name,txtfile);
               gram.GetIO().merr().printf(
                                          "State [%us] is not declared for coordinate [%us]\n"
                                          , state_name.c_str(), dim_name.c_str()
                                         );
               throw E_ParserError();
              }


             GramCoordPair p(dim_glob_index, istate);
             if (dim.find(p) != UNKNOWN)
              {
               gram.GetIO().merr().printf(
                                          "Dimension [%us:%us] is already defined\n"
                                          , dim_name.c_str(), state_name.c_str()
                                         );
               throw E_ParserError();
              }

             dim.push_back(p);
            }
          }

         if (load_forms)
          LoadFormsGroup(
                         txtfile,
                         gram,
                         dim,
                         do_autoload,
                         ido_autoload,
                         indexing,
                         iindexing,
                         allquantor
                        );

         if (common.empty())
          break;

         const BSourceState back = txtfile.tellp();
         if (txtfile.read().GetToken() == B_CFIGPAREN)
          break;
         else
          txtfile.seekp(back);
    }

    return;
}
#endif


void WordFormName::AddAux(const lem::UCString &aux_type, const lem::UFString &aux_data)
{
    /*
    for( lem::Container::size_type i=0; i<aux.size(); ++i )
     if( aux[i].first.eqi(aux_type) )
      {
       lem::UFString msg( lem::format_str( L"Redefinition of aux_type='%s'", aux_type.c_str() ) );
       throw E_BaseException( msg );
      }
   */

    aux.push_back(std::make_pair(aux_type, aux_data));

    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Form_Table::LoadFormName(
    Macro_Parser & txtfile,
    Grammar & gram,
    WordFormName & form_name
) const
{
    form_name.clear();

    bool has_aux = txtfile.probe(B_OSPAREN);

    int counter = 0;
    while (!txtfile.eof())
    {
        if (txtfile.probe(B_CSPAREN))
        {
            break;
        }

        if (counter == 0)
        {
            BethToken tform_buf = txtfile.read();
            Lexem form_buf = tform_buf;

            if (tform_buf == B_OFIGPAREN)
            {
                form_buf.clear();
                // Мультилексема в { ... }
                while (!txtfile.eof())
                {
                    tform_buf = txtfile.read();
                    if (tform_buf == B_CFIGPAREN)
                        break;

                    form_buf.Add(tform_buf);
                }
            }

            form_buf.strip(L'"');
            if (form_buf.length() > 1 && (lem::is_uspace(form_buf.back()) || lem::is_uspace(form_buf.front())))
                form_buf.trim();

            form_name.form_name = form_buf;
        }
        else
        {
            lem::UCString aux_type = txtfile.read().string();
            txtfile.read_it(B_EQUAL);
            lem::UFString aux_data = txtfile.read().GetFullStr();
            aux_data.strip(L'"');

            if (aux_data.length() > 1 && (lem::is_uspace(aux_data.back()) || lem::is_uspace(aux_data.front())))
                aux_data.trim();

            form_name.AddAux(aux_type, aux_data);
        }

        counter++;

        if (!has_aux)
            break;
    }

    return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void Form_Table::LoadFormsGroup(
    Macro_Parser& txtfile,
    Grammar& gram,
    CP_Array &dim,
    const GramCoordAdr do_autoload,
    int ido_autoload,
    const GramCoordAdr indexing,
    int iindexing,
    int allquantor
)
{
    BSourceState form_tellp = txtfile.tellp();

    // Теперь загрузим часть форм слова. Число загружаемых
    // форм определяется числом состояний для индексируемого
    // измерения.
    const int nform_before = CountForms();

    try
    {
        if (indexing.GetIndex() == UNKNOWN)
        {
            // Всего одна форма !
            WordFormName form_buf;
            LoadFormName(txtfile, gram, form_buf);

            // Был ли употреблен квантор '*' вместо имени состояния у одного
            // из измерений?
            if (allquantor != UNKNOWN)
            {
                // Да! Добавляем к списку несколько словоформ, совпадающих
                // лексически, но отличающихся состоянием соответствующего
                // измерения.

                const GramCoordAdr iqua = dim[allquantor].GetCoord();
                const int nstates = CastSizeToInt(gram.coords()[iqua.GetIndex()].states().size());

                for (int i = 0; i < nstates; i++)
                {
                    dim[allquantor].SetState(gram.coords()[iqua.GetIndex()].GetIndexOfState(i));

                    AddForms(
                        dim,
                        form_buf,
                        do_autoload,
                        ido_autoload,
                        gram
                    );
                }
            }
            else
            {
                // Загружена и добавляется только одна словоформа.
                // Добавим ее к списку.
                AddForms(
                    dim,
                    form_buf,
                    do_autoload,
                    ido_autoload,
                    gram
                );
            }
        }
        else
        {
            // Число состояний у индексируемого измерения, именно столько словоформ
            // будет загружено сейчас.
            const int nload = CastSizeToInt(gram.coords()[indexing.GetIndex()].states().size());

            // Загружаем несколько форм.
            WordFormName form_buf;
            for (int i = 0; i < nload; i++)
            {
                form_tellp = txtfile.tellp();

                LoadFormName(txtfile, gram, form_buf);

                dim[iindexing].SetState(i); // Меняем состояние индексируемого измерения.

                if (allquantor != UNKNOWN)
                {
                    // Да! Добавляем к списку несколько словоформ, совпадающих
                    // лексически, но отличающихся состоянием соответсвующего
                    // измерения.

                    const GramCoordAdr iqua = dim[allquantor].GetCoord();
                    const int nstates = CastSizeToInt(gram.coords()[iqua.GetIndex()].states().size());

                    for (int j = 0; j < nstates; j++)
                    {
                        dim[allquantor].SetState(gram.coords()[iqua.GetIndex()].GetIndexOfState(j));

                        AddForms(
                            dim,
                            form_buf,
                            do_autoload,
                            ido_autoload,
                            gram
                        );
                    }
                }
                else
                {
                    // Добавим ее к списку
                    AddForms(
                        dim,
                        form_buf,
                        do_autoload,
                        ido_autoload,
                        gram
                    );
                }
            }
        }
    }
    catch (...)
    {
        lem::Iridium::Print_Error(form_tellp, txtfile);
        throw;
    }

    txtfile.read_it(B_CFIGPAREN);

    // Если будет токен :: то значит далее идет дополнительная информация, которую
    // умеет считывать только производный класс.
    const BethToken cont = txtfile.read();
    if (cont.GetToken() == B_DCOLON)
    {
        // КАЖДАЯ из последних добавленных статей должна получить возможность прочитать
        // дополнительную информацию
        const BSourceState add_begin = txtfile.tellp();

        for (int iform = nform_before; iform < CountForms(); iform++)
        {
            txtfile.seekp(add_begin);
            ReadAdditionalInfo(gram, iform, txtfile);
        }
    }
    else
        txtfile.seekp(cont);

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
 Добавляем загруженную словоформу к своему списку, и при необходимости
 автоматически создаем несколько словоформ с состояниями из одной
 подгруппы многоохватных.
*************************************************************************/
void Form_Table::AddForms(
    CP_Array &dim,
    const WordFormName &form_name,
    const GramCoordAdr do_autoload,
    int ido_autoload,
    Grammar &gram
)
{
    AddForm(dim, form_name, gram.GetDict());

    // Запускаем механизм создания...
    if (do_autoload.GetIndex() != UNKNOWN)
    {
        const GramCoord &c = gram.coords()[do_autoload.GetIndex()];

        const int idim = dim.FindTwice(do_autoload);
        const int statei = dim[idim].GetState();

        const int igroup = c.GetSubgroup(statei);

        if (c.GetTopState(igroup).size() > 1 && c.IsHeadState(statei))
        {
            /*
                 #if defined RUSSIAN
                  mlst.printf(
                              "Для статьи [%S] создаем словоформы для измерения [%S]:\n",
                              GetName().s(), c.GetName()
                             );
                 #else
                  mlst.printf(
                              "For entry [%S] creating wordforms for dimention [%S]:\n",
                              GetName().s(), c.GetName()
                             );
                 #endif
            */
            // О да! Создаем словоформы для остальных состояний из этой
            // же подгруппы!

            const IntCollect tocreate = c.GetSubgroupIndeces(igroup);

            // Головное состояние уже загружено. Поэтому перебираем
            // список tocreate со второго индекса.

            for (Container::size_type i = 1; i < tocreate.size(); i++)
            {
                dim[ido_autoload].SetState(tocreate.get(i));
                AddForm(dim, form_name, gram.GetDict());
            }
        }
    }

    return;
}
#endif




#if defined SOL_SAVEBIN
void Form_Table::SaveBin(lem::Stream &bin) const
{
    bin.write(&key, sizeof(key));
    bin.write(&iclass, sizeof(iclass));
    attr.SaveBin(bin);
    return;
}
#endif

void Form_Table::LoadBin(lem::Stream &bin)
{
    bin.read(&key, sizeof(key));
    bin.read(&iclass, sizeof(iclass));
    attr.LoadBin(bin);

#if defined SOL_LOADTXT && defined SOL_COMPILER
    is_realized = true;
#endif

    return;
}

/***********************************************************************
 Для заданного посредством глобального индекса атрибута возвращаем
 состояние. Если такой атрибут не определен для статьи, то возвращаем
 UNKNOWN.
***********************************************************************/
int Form_Table::GetAttrState(const GramCoordAdr id_attr) const
{
    const int iattr = attr.FindTwice(id_attr);
    return iattr == UNKNOWN ? iattr : attr[iattr].GetState();
}




/*********************************************************************
 Возвращает список всех состояний указанной координаты. Используется
 для работы с AND-состояниями.
**********************************************************************/
const IntCollect Form_Table::GetAttrStates(const GramCoordAdr id_attr) const
{
    IntCollect res;
    res.reserve(attr.size());

    // Первый проход - строгое сравнение.
    for (Container::size_type i = 0; i < attr.size(); i++)
        if (attr[i].GetCoord() == id_attr)
            res.push_back(attr[i].GetState());

    // Второй проход - учитываются только индексы координат, синонимы
    // признаются равными.
    if (res.empty())
    {
        for (Container::size_type i = 0; i < attr.size(); i++)
            if (attr[i].GetCoord().GetIndex() == id_attr.GetIndex())
                res.push_back(attr[i].GetState());
    }

    return res;
}


#if defined SOL_SAVETXT
bool Form_Table::DoSaveAttrTxt(
    int iattr,
    const Grammar &gram
) const
{
    return true;
}
#endif


#if defined SOL_SAVETXT
void Form_Table::SaveCoordinatesTxt(
    OFormatter& txtfile,
    const Grammar& gram
) const
{
    if (attr.empty())
        return;

    // Список уже выведенных координат надо вести для корректного отображения
    // координатных пар с несколькими состояниями (AND-координат).
    // Мы печатаем такие координаты в виде
    //
    // ПАДЕЖ:ВИН,ТВОР
    //
    // хотя в списке статьи хранится 2 пары - ПАДЕЖ:ВИН и ПАДЕЖ:ТВОР, и мы не
    // должны дважды вывести ПАДЕЖ:ВИН,ТВОР
    lem::MCollect<GramCoordAdr> already_printed;

    for (Container::size_type i = 0; i < attr.size(); i++)
        if (DoSaveAttrTxt(i, gram))
        {
            const GramCoordAdr iattr = attr[i].GetCoord();

            if (already_printed.find(iattr) != UNKNOWN)
                continue;

            already_printed.push_back(iattr);

            const GramCoord& c = gram.coords()[iattr.GetIndex()];

            if (c.states().empty())
            {
                if (attr[i].GetState() == ANY_STATE)
                {
                    txtfile.printf(
                        "  %us%us%us\n"
                        , c.GetName()[iattr.GetVar()].c_str()
                        , sol_get_token(B_COLON).c_str()
                        , sol_get_token(B_ANY).c_str()
                    );
                }
                else if (attr[i].GetState() == 1)
                    txtfile.printf("  %us\n", c.GetName()[iattr.GetVar()].c_str());
                else
                    txtfile.printf(
                        "  //%us %us\n",
                        sol_get_token(B_NEGATIVE).c_str(),
                        c.GetName().front().c_str()
                    );
            }
            else
            {
                const IntCollect istate = GetAttrStates(iattr);

                txtfile.printf(
                    "  %us%us",
                    c.GetName()[iattr.GetVar()].c_str(),
                    sol_get_token(B_COLON).c_str()
                );

                const int n_in_coord = c.GetTotalStates();
                bool use_quantor = true;

                for (int is = 0; is < n_in_coord; is++)
                    if (find(istate, is) == UNKNOWN)
                    {
                        use_quantor = false;
                        break;
                    }

                if (use_quantor)
                    txtfile << sol_get_token(B_ANY);
                else
                    for (Container::size_type j = 0; j < istate.size(); j++)
                    {
                        if (j)
                            txtfile.printf(',');

                        const int state_index = istate[j];

                        if (c.IsDefState(state_index) && c.IsHeadState(state_index))
                            txtfile << sol_get_token(B_OROUNDPAREN)
                            << c.GetStateName(state_index)
                            << sol_get_token(B_CROUNDPAREN);
                        else if (state_index == ANY_STATE)
                            txtfile << sol_get_token(B_ANY);
                        else
                            txtfile << c.GetStateName(state_index);
                    }

                txtfile.eol();
            }
        }

    return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void Form_Table::AddForm(
    const CP_Array& dim,
    const WordFormName& form_name,
    Dictionary &dict
)
{
    if (CountForms() == 0)
        BeforeFirstForm(GetGrammar(dict));

    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Form_Table::BeforeFirstForm(Grammar& gram)
{
}
#endif


void Form_Table::SetAttr(const Solarix::GramCoordPair &p)
{
    if (attr.find(p) == UNKNOWN)
        attr.push_back(p);

    return;
}

