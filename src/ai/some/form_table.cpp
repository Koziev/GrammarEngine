// -----------------------------------------------------------------------------
// File FORM_TABLE.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ����� Form_Table - ������� ��� ��������� ������ � ������ ���������.
//
// 20.05.2006 - ���������� �������� ������ �������������� ���������� ��� 
//              ������ ������ � ������� ����������������. ������� �������
//              �������������� ���������� - ����� :: 
//
// 21.11.2006 - ����������� ���� �������, ������� �������������.
// 12.12.2008 - ��������� ����� SaveTxt ��� AND-���������
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
  �������� �������� ������ �� ���������� �����
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

    if (iclass == UNKNOWN) // ���� � LoadName ��� �� ��������� ���������� � �������������� � ��������������� ������...
    {
        const BethToken class_name = txtfile.read();

        if ((iclass = gram.FindClass(class_name.string())) == UNKNOWN)
        {
            // �� ������ �����, ���������� ��� ������
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

    // *** ��������� �������� ������� ***
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
         // �������� ������� ���������.
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
                ); // ��������� ����������.

    } // ����� ����� ���������� �������� ������

    return;
}
#endif





#if defined SOL_LOADTXT && defined SOL_COMPILER
/**************************************************************************
     �������� ����� ���������� ������������ ����
             �� ���������� �����

  ����� ������:

     �����_��� : ���������

 ������ �������� ������� ������� ��������������� �������� AND-���������
 ��� ������������� ���������. ���� ����� �������� ������������, ��
 ������� ��������� ��� ���������, ��������� � ������ �������������, �
 ������� ��������:

           ����_��� : ( ��������� )

 ������������ ��������:

  true - �������������, �������� ������� ��� ���.
  false - ��� �� ����������� ��������� �������� ��� ����.
****************************************************************************/
bool Form_Table::LoadAttribute(
    Macro_Parser &txtfile,
    Grammar& gram
)
{
    const BSourceState back = txtfile.tellp();
    bool negative_state = txtfile.probe(B_NEGATIVE); // ��������� ������� � ~���������

    BethToken coord_name = txtfile.read();

    // ������ ���������� � ������ ����������.
    const GramCoordAdr iglob = gram.FindCoord(coord_name.string());

    // ������ ������� � ������ ��������������� ������.
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

    // ���� ���������� ����� ��� ������ ����������� ���������
    // TRUE/FALSE, �� ��������� ���� � ������ ������ �� ������ ����
    // �������.

    if (!gram.coords()[iglob.GetIndex()].IsBistable())
    {
        // ��������� ��������� � ����������.

        if (negative_state)
        {
            Print_Error(back, txtfile);
            gram.GetIO().merr().printf("~ is appliable to bistable coordinates only, whereas [%us] is not bistable\n", coord_name.c_str());
            throw E_ParserError();
        }

        txtfile.read_it(B_COLON);

        // �����, ��� ����� ����������� AND-�������. ����� ����������
        // ������������ ����� ����� ��������� ���������.

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

        // ������ ������� ���������(-�) ��� ����������� ��������.
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
              // ������ ���� ��������� ��� AND-���������� ������ ������� *.
              // �������������� ���������� ����� �����������, �����������
              // ��� ����������.

              const int ns = gram.coords()[iglob.GetIndex()].GetTotalStates();

              for (int i = 0; i < ns; i++)
               attr.push_back(GramCoordPair(iglob,i));

              // ���������� ������ ���������� �� ����� ������.
              break;
             }
           }

          if (!statei.empty())
           {
              // ���� ��� �������, �� ������ AND-��������� ������������.
              // � ��������� ������ ��������� �������� ���������.

              if (state_name.GetToken() != B_COMMA)
               {
                txtfile.seekp(back);
                break;
               }
              else
               state_name = txtfile.read();
             }

          // ���� ��� �������� ��������� � ������� ��������, ��
          // ��� ������������ ���� ��������� �������������� ��������.
          if (state_name.GetToken() == B_OROUNDPAREN)
           {
            state_name = txtfile.read();
            txtfile.read_it(B_CROUNDPAREN);
            letautoload = false;
           }

          // ���� ������ ��������� � ����������
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

          // ��������� ���������� ������ �������� � ������ ��� ���������
          // � ����� �������.
          statei.push_back(istate);
          doload.push_back(letautoload);
        }

            // ���������, ������� ��������� ��� ��������, ���������
            // � ������ ������������ ��� � ������� � ������ ������
            // ��������� ������.
        lem::Container::size_type ils;
        for (ils = 0; ils < statei.size(); ils++)
            attr.push_back(GramCoordPair(iglob, statei[ils]));

        // ������������� ��������� �� ���������, ������� �� ���������
        // ��� ����� �������������, �� ��������� � ������ � ���������.
        const GramCoord& c = gram.coords()[iglob.GetIndex()];
        IntCollect attaches; // ������������� ��������� � �������������� ���������

        for (ils = 0; ils < statei.size(); ils++)
            if (doload[ils])
            {
                int ibase = statei[ils];

                // ������ �� ��������� � ������ ������������� ��� �������?
                if (c.IsHeadState(ibase))
                {
                    // ��, ������.
                    // �������� ������ ���������, �������� � ������.
                    const IntCollect to_attach = c.GetSubgroupIndeces(c.GetSubgroup(ibase));

                    for (Container::size_type ia = 1; ia < to_attach.size(); ia++)
                    {
                        const int state_attach = to_attach.get(ia); // ��������� ��������� �� ������ �������������

                        // ���������, ����� �� ������������ ���������
                        // iglob:state_attach.
                        //
                        // ���������������� ����� ���� ���������.
                        //
                        // 1. ��������� ��� ������������ � ������ statei.
                        // 2. ��������� ��� ������������� ������� �
                        //    ��������� � ������ attaches.
                        //
                        // 3. ������������ ���� ��� ��������� � ������
                        //    ������.

                        bool already_loaded = false;

                        if (attr.FindOnce(GramCoordPair(iglob, state_attach)) != UNKNOWN)
                            already_loaded = true;

                        if (
                            !already_loaded                      &&
                            find(statei, state_attach) == UNKNOWN   &&
                            find(attaches, state_attach) == UNKNOWN
                            )
                            attaches.push_back(state_attach); // � ������ ��������������
                    }
                }
            }

        if (!attaches.empty()) // ���� ��������������?
        {
            // ���������� ������������ ������������ �� �������������
            // �������������� ����������.
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
        // ��������� ���������� ������ �������� � ������ ��� ���������
        // � ����� �������, ��������, ��� ��� ���� ��������� ��������
        // � �������� ����������� TRUE/FALSE �������� ��� ��������� TRUE.
        // ���� ��� ������� ~, �� ��������� ����������� FALSE.

        // ���� ���� ������ ������, ����� ��� ������������ ���������� ��������
        // ��������� - ��� �������������� ���������. � ���� ������ ��� ���������
        // ����������� ������� *
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
  ��������� ���� ��� ��������� ��������� ������.

  ������� ���� ����� ������������ ��� ���������, ����� - ���� ���
  ��������� ��������� � �������� ���������.

  ��������� � �������.

    1. ���������� ������������ ���� � ����:

                       ���_�����:*

       ������� �������������� �������� �������� ���������� ���������,
       ������� ��������� ���������� � ���������� ����������. ������ ����
       ��������� ����� ������������� ���������������.

    2. ��������� ������:

                  ���_����� { �����1 �����2 ... �����N }

       �������������, ��� � �������� ��������� ���������� ���������� ���
       ���������� ���� ������� ��������� ����������, � ������� �� ����������
       � �������� ����������. ����� ����� �������� ����� �����������
       "�������������� �����������".
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

    // ���� ���������� ���������� ��������� � ������� ����������
    // ��������� ���������.
    //
    // ����� �� ����� ����� ��������� ���������� ����� ������� ��
    // �������, �� ���� ����� ���� � ����������� �������, ��
    // ������ ����������� ��������� �� ��������� '}'.

    FOREVER
    {
     GramCoordAdr indexing = Indexing; // ��������� ��� ��������������� ��������������.
     int iindexing = iIndexing; // ������ � dim ��������� ��� ��������������

     int allquantor = AllQuantor; // ����� ������������ ���� � ������ ������ ���
                                 // ������������ ��������� ��������� �� �������� '*'

     CP_Array dim = common;        // ��������� ��������� ��� ����������� ������������ ���.

     GramCoordAdr do_autoload = Do_Autoload;
     int ido_autoload = iDoAutoload;
     bool load_forms = true;

     // ��������� ������ ������������ ���������.
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

       // ���� ����������� '|', �� ������ ����� ����� ���� � ���������
       // ����������� ������. �� ���� ���������� ������ ������ ������������
       // ���, ��� ����������� � ������ �������.
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
                 ); // ��� ��, ����������� �����!

         load_forms = false;
         break;
        }

       bool negation = false;
       if (dim_name.GetToken() == B_NEGATIVE)
        {
           // ������ ~���_���������� ����� �������������� ������
           // ��� ������������ ���������. ��������.
           negation = true;
           dim_name = txtfile.read();
          }

         const UCString& dim__name = dim_name.string();

         // �������� �� ��� ��������� �������� ��� ������?

         const GramCoordAdr dim_glob_index = gram.FindCoord(dim__name); // ������ ���������� � ������ ����������

         if (dim_glob_index.GetIndex() == UNKNOWN)
          {
           Print_Error(dim_name,txtfile);
           gram.GetIO().merr().printf(
                                      "Coordinate [%us] is not previously declared in grammar\n"
                                      , dim_name.c_str()
                                     );
           throw E_ParserError();
          }

         // ������ ���������� � ������ ������
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
             // ��� ������������ ����������.
             GramCoordPair p(dim_glob_index, !negation);
             if (dim.find(p) != UNKNOWN)
              {
               gram.GetIO().merr().printf("Dimension [%us] is already defined\n", dim_name.c_str());
               throw E_ParserError();
              }

             dim.push_back(p);
             continue;
            }

         // ������ ��������� ��� ��������� ���������.

         back = txtfile.tellp();
         state_name = txtfile.read();

         /*---------------------------------------------------------------------------
           ��� ��������� �������� ������ ���������, ������� ����������� ����������
           ������ ���������, ������ ����������� �����. ���� ��� ������ ���������
           �� ������ ���������, � ������ ���� ����������� �������� ��������,
           �� ������ ����� ���� ��������� ���������, ����� �� �������������
           ����� ������� � �������������� ���������. ��� ���� ��� ������ ������������
           ����� ������� ���������� ��������� �������������� ��������� ���������
           ��������������� ��� ��������.
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
           // ��� ��������� ����� ������������� ���������������
           indexing = dim_glob_index;
           iindexing = dim.size();

           // ������ ��������� ����� ����������������� �� ����� ��������������
           dim.push_back(GramCoordPair(dim_glob_index,UNKNOWN));
           continue;
          }

         state_name = txtfile.read();

         // ��� ���������, ����������� � ������� ������, ��������, ���
         // ��� ������� ��������� ����������� �������������� ��������
         // ��� ��������� �� ��������� �������������.

         if (state_name.GetToken() == B_OROUNDPAREN)
          {
           state_name = txtfile.read();
           txtfile.read_it(B_CROUNDPAREN);
          }
         else
          {
             // ���� ��������� �������� ������� � ��������� �������������,
             // � ������������ ���� �� ������� ������, �� ������� ��������
             // ������������.

             if (gram.coords()[dim_glob_index.GetIndex()].HasDefStates())
              {
               if (do_autoload.GetIndex() != UNKNOWN)
                {
                   // ��� - �����������!
                   Print_Error(state_name,txtfile);
                   gram.GetIO().merr().printf("Only one multycoordinate is allowed\n");
                   throw E_ParserError();
                  }

                 do_autoload = dim_glob_index;
                 ido_autoload = dim.size();
                }
              }

         // ��������! ���� ��� ��������� ��������� �������� ��� '*', ��
         // ���������������, ��� ����������, ������������ ������ ����������
         // ������� ��������� ��������� ����������.
         // ���� ������ ������ �������������: ��� ����������� �������������� ���������.
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
             // ���������� ������ ��������� � ������ ����������.
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
                // ������������� � { ... }
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

    // ������ �������� ����� ���� �����. ����� �����������
    // ���� ������������ ������ ��������� ��� ��������������
    // ���������.
    const int nform_before = CountForms();

    try
    {
        if (indexing.GetIndex() == UNKNOWN)
        {
            // ����� ���� ����� !
            WordFormName form_buf;
            LoadFormName(txtfile, gram, form_buf);

            // ��� �� ���������� ������� '*' ������ ����� ��������� � ������
            // �� ���������?
            if (allquantor != UNKNOWN)
            {
                // ��! ��������� � ������ ��������� ���������, �����������
                // ����������, �� ������������ ���������� ����������������
                // ���������.

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
                // ��������� � ����������� ������ ���� ����������.
                // ������� �� � ������.
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
            // ����� ��������� � �������������� ���������, ������ ������� ���������
            // ����� ��������� ������.
            const int nload = CastSizeToInt(gram.coords()[indexing.GetIndex()].states().size());

            // ��������� ��������� ����.
            WordFormName form_buf;
            for (int i = 0; i < nload; i++)
            {
                form_tellp = txtfile.tellp();

                LoadFormName(txtfile, gram, form_buf);

                dim[iindexing].SetState(i); // ������ ��������� �������������� ���������.

                if (allquantor != UNKNOWN)
                {
                    // ��! ��������� � ������ ��������� ���������, �����������
                    // ����������, �� ������������ ���������� ���������������
                    // ���������.

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
                    // ������� �� � ������
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

    // ���� ����� ����� :: �� ������ ����� ���� �������������� ����������, �������
    // ����� ��������� ������ ����������� �����.
    const BethToken cont = txtfile.read();
    if (cont.GetToken() == B_DCOLON)
    {
        // ������ �� ��������� ����������� ������ ������ �������� ����������� ���������
        // �������������� ����������
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
 ��������� ����������� ���������� � ������ ������, � ��� �������������
 ������������� ������� ��������� ��������� � ����������� �� �����
 ��������� �������������.
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

    // ��������� �������� ��������...
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
                              "��� ������ [%S] ������� ���������� ��� ��������� [%S]:\n",
                              GetName().s(), c.GetName()
                             );
                 #else
                  mlst.printf(
                              "For entry [%S] creating wordforms for dimention [%S]:\n",
                              GetName().s(), c.GetName()
                             );
                 #endif
            */
            // � ��! ������� ���������� ��� ��������� ��������� �� ����
            // �� ���������!

            const IntCollect tocreate = c.GetSubgroupIndeces(igroup);

            // �������� ��������� ��� ���������. ������� ����������
            // ������ tocreate �� ������� �������.

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
 ��� ��������� ����������� ����������� ������� �������� ����������
 ���������. ���� ����� ������� �� ��������� ��� ������, �� ����������
 UNKNOWN.
***********************************************************************/
int Form_Table::GetAttrState(const GramCoordAdr id_attr) const
{
    const int iattr = attr.FindTwice(id_attr);
    return iattr == UNKNOWN ? iattr : attr[iattr].GetState();
}




/*********************************************************************
 ���������� ������ ���� ��������� ��������� ����������. ������������
 ��� ������ � AND-�����������.
**********************************************************************/
const IntCollect Form_Table::GetAttrStates(const GramCoordAdr id_attr) const
{
    IntCollect res;
    res.reserve(attr.size());

    // ������ ������ - ������� ���������.
    for (Container::size_type i = 0; i < attr.size(); i++)
        if (attr[i].GetCoord() == id_attr)
            res.push_back(attr[i].GetState());

    // ������ ������ - ����������� ������ ������� ���������, ��������
    // ���������� �������.
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

    // ������ ��� ���������� ��������� ���� ����� ��� ����������� �����������
    // ������������ ��� � ����������� ����������� (AND-���������).
    // �� �������� ����� ���������� � ����
    //
    // �����:���,����
    //
    // ���� � ������ ������ �������� 2 ���� - �����:��� � �����:����, � �� ��
    // ������ ������ ������� �����:���,����
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

