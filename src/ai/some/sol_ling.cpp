// -----------------------------------------------------------------------------
// File SOL_LING.CPP
//
// (c) by Koziev Elijah
//
// Content:
// ������ ������ ���������� � ������������. ��������� ���������� �������.
// -----------------------------------------------------------------------------
//
// CD->07.10.1995
// LC->13.09.2011
// --------------

#include <string.h>
#include <ctype.h>

#include <lem/conversions.h>
#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/string_set.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/ref_name.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/coord_pair.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/WordEntry.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT
/*******************************************************************
  ��������� ������������� �� ���������� ����� ��������
  ���������� �������:

    ����1 ����2 ... ����N BREAKER


  ���������� ���������� �� ������� ������� �� ��������� �����������
  ���� breaker ������. ����� ���������� ������� ������� � ����� -
  ����� ������ BREAKER.

  ���� ������ breaker ��� ANY_STATE, �� ����� ������� ������ ���� �������.

  ������� ���������, ������� �� ��������, ����������.

  ������� ���������:

   Source - ��������� ����.
   breaker - ��� ������, ������������ ����������.
***********************************************************************/
const UCString Solarix::sol_read_multyname(
    const Sol_IO &io,
    Macro_Parser& txtfile,
    int breaker
)
{
    UCString mname; // ���������� �������������

    BethToken part;
    FOREVER
    {
     if (txtfile.eof())
      {
       lem::Iridium::Print_Error(txtfile);
       io.merr().printf("End of file has been reached before multilexem name completely read\n");
       throw E_ParserError();
      }

    // ��������� ������� � �������������
    part = txtfile.read();

    if (lem_strlen(part.GetFullStr()) >= lem::UCString::max_len)
     {
      lem::Iridium::Print_Error(txtfile);
      io.merr().printf("Lexem [%us] is too long\n", part.GetFullStr());
      throw E_ParserError();
     }

    // ���������, ��� ����������� ������� (������) ���� ����� ����
    // ������� ������.
    if (!mname.empty() && part.GetToken() == breaker)
     break;

    if (!mname.empty() && !lem::is_udelim(part.string()) && !lem::is_udelim(mname.back()))
     {
      if (mname.length() + 1 >= lem::UCString::max_len)
       {
        lem::Iridium::Print_Error(txtfile);
        io.merr().printf("Lexem [%us] is too long\n", mname.c_str());
        throw E_ParserError();
       }

      mname += L' ';
     }

    UCString as(strip_quotes(part.string()));

    if (mname.length() + as.length() >= lem::UCString::max_len)
     {
      lem::Iridium::Print_Error(txtfile);
      io.merr().printf("Lexem [%us %us] is too long\n", mname.c_str(), as.c_str());
      throw E_ParserError();
     }

    mname += as;

    if (breaker == ANY_STATE)
     break;
    }

        if (mname.back() == L' ')
        {
            // ������������ �������� - �����-�� ������� �� ����� ������ �������� ������.
            //mname.ShrinkTo( mname.length() );
            mname = mname.strip(L' ');
        }

    return mname;
}
#endif

#if defined SOL_LOADTXT
/****************************************************************************
 DESCRIPTION:
  ���������, ����� �� ��������� ��� ���������� ������� ���� ������ ����������,
  �������, ����������, �������, � �.�. ���������� � ����� - ����������� ���
  ����� C.

  ���� ������� �������� strict=true, �� ������������� ������������, ����� ��
  ���� ���������� � ��������� �������, ������������������ � �������.
*****************************************************************************/
void Solarix::sol_check_s_name(
    const Dictionary &dict,
    Macro_Parser& txtfile,
    const BethToken& s,
    bool strict
)
{
    if (
        !is_name(s.c_str()) ||
        (strict && sol_is_token(s.string().c_str()))
        )
    {
        lem::Iridium::Print_Error(s, txtfile);
        dict.GetIO().merr().printf("Lexem can not be a name\n");
        throw E_ParserError();
    }

    return;
}
#endif

#if defined SOL_LOADTXT
void Solarix::sol_check_coord_name(
    const Dictionary &dict,
    Macro_Parser& txtfile,
    const BethToken& s
)
{
    if (s.GetToken() == B_NET || s.GetToken() == B_RULE)
        return;

    sol_check_s_name(dict, txtfile, s, true);
    return;
}
#endif




#if defined SOL_LOADTXT && defined SOL_COMPILER
/*******************************************************************************
 ������ ����������� ����������� ��������� ������ � ���� ���_������:���_������{}
 � ���������� ���� ������ � ������ ������. ��� ������ ����� ���� ��������������,
 ����� ����� ����� ����������� ����������� �������� �������. �����, ��� ���
 ������ ����� ����������� �� ����� � ���������. ���� ���������� �������� do_search
 ��� false, �� ���������� ����� ���������, �� ������ � ������� �� �����, �
 ������������ �������� ����� ������ ������ �� �����.

 ���� do_check=false, �� ���� ��� �������� ������ ��������� ������ ���������
 ������ ������ UNKNOWN.
*******************************************************************************/

int Solarix::sol_load_omonym(
    Macro_Parser &txtfile,
    SynGram &gram,
    bool do_check
)
{
    int entry_key = UNKNOWN;

    const BethToken class_name = txtfile.read();
    int iclass = gram.FindClass(class_name.string());
    if (iclass == UNKNOWN)
    {
        lem::Iridium::Print_Error(class_name, txtfile);
        gram.GetIO().merr().printf(
            "The class [%us] is not previously declared in grammar\n"
            , class_name.c_str()
        );
        throw E_ParserError();
    }

    txtfile.read_it(B_COLON);
    UCString entry_name = sol_read_multyname(gram.GetIO(), txtfile, B_OFIGPAREN);
    entry_name.to_upper();

    // �������� ������ �������������� ������������ ���
    Solarix::CP_Array coords;
    coords.LoadTxt(txtfile, gram);
    LEM_CHECKIT_Z(coords.size() < 2);

    int ientry = coords.empty() ? gram.FindEntry(entry_name, iclass, false) : gram.FindEntryOmonym(entry_name, iclass, coords.front());
    if (ientry == UNKNOWN)
    {
        if (do_check)
        {
            lem::Iridium::Print_Error(class_name, txtfile);
            gram.GetIO().merr().printf(
                "The entry [%us] is not previously declared in grammar\n"
                , entry_name.c_str()
            );
            throw E_ParserError();
        }

        entry_key = UNKNOWN;
    }
    else
    {
        entry_key = gram.GetEntry(ientry).GetKey();
    }

    return entry_key;
}



int Solarix::sol_load_class_entry(
    Macro_Parser &txtfile,
    SynGram &gram,
    bool do_search,
    bool do_check
)
{
    int entry_key = UNKNOWN;

    const BethToken class_name = txtfile.read();
    int iclass = UNKNOWN;
    if (do_search)
        if ((iclass = gram.FindClass(class_name.string())) == UNKNOWN)
        {
            lem::Iridium::Print_Error(class_name, txtfile);
            gram.GetIO().merr().printf(
                "The class [%us] is not previously declared in grammar\n"
                , class_name.c_str()
            );
            throw E_ParserError();
        }

    txtfile.read_it(B_COLON);
    UCString entry_name = sol_read_multyname(gram.GetIO(), txtfile, B_OFIGPAREN);

    entry_name.to_upper();

    if (do_search)
    {
        int ientry = UNKNOWN;

        ientry = gram.FindEntry(entry_name, iclass, false);

        if (ientry == UNKNOWN)
        {
            if (do_check)
            {
                lem::Iridium::Print_Error(class_name, txtfile);
                gram.GetIO().merr().printf(
                    "The entry [%us] is not previously declared in grammar\n"
                    , entry_name.c_str()
                );
                throw E_ParserError();
            }

            entry_key = UNKNOWN;
        }
        else
            entry_key = gram.GetEntry(ientry).GetKey();
    }

    return entry_key;
}
#endif

/**********************************************************
 ������ ���������� � ������ "�����:���_������"
***********************************************************/
void Solarix::sol_print_class_entry(
    OFormatter &txtfile,
    SynGram &gram,
    int entry_key
)
{
    /*
    { for( int i=0; i<gram.entries().size(); i++ )
      {
       int k = gram.entries().at(i)->GetKey();
       int ii = gram.FindEntryIndexByKey(k);
       int k2 = gram.entries().at(ii)->GetKey();
       if( k!=k2 )
        mout.printf( "error\n" );

       const SG_Entry &e = gram.GetEntryByKey(k);
       if( e.GetKey()!=k )
        mout.printf( "error\n" );

       if( k==entry_key )
            mout.printf( "i=%d\n", i );
      }

    int ii3 = gram.FindEntryIndexByKey(entry_key);
    const SG_Entry &e2 = *gram.entries()[ii3];
    */

    const SG_Entry &e = gram.GetEntry(entry_key);
    const int iclass = e.GetClass();

    const UCString& class_name = iclass == UNKNOWN_STATE ?
        UCString(SOL_UNKNOWN_ENTRY_NAME)
        :
        gram.classes()[iclass].GetName();

    txtfile.printf("%us%us", class_name.c_str(), sol_get_token(B_COLON).c_str());
    txtfile.printf("%us", e.GetName().c_str());

    return;
}


// *************************************************************************
// �������� ������� ����: ����������� ���������� ������ ���, ��������������
// � ����� ������� A � B.
//
// ������� ������ ��������� ����� �� ����������� ������������ ������������
// ���� � ����� � ��� �� ����������� � �������.
// *************************************************************************
bool Solarix::sol_do_them_match(const CPE_Array &A, const CPE_Array &B)
{
    for (Container::size_type ia = 0; ia < A.size(); ia++)
    {
        const int b = B.FindOnce(A[ia].GetCoord());
        if (b != UNKNOWN && B[b].GetState() != A[ia].GetState())
            return false;
    }

    return true;
}

