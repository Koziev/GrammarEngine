// -----------------------------------------------------------------------------
// File VARIATOR.CPP
//
// (c) Koziev Elijah
//
// Content:
// �������� - ����� Variator: ������������� ������ ���������, �� ���� ������
// ��������-beth. �������� ��������� ������ ��� ResPack.
//
// 01.09.2007 - ������ ����������� ��������� ����� PrintRoot - �������� ��������
//              BEGIN � END �� ����������. 
// 11.10.2011 - ��������� ������������ � XML
// -----------------------------------------------------------------------------
//
// CD->14.11.1995
// LC->31.03.2018
// --------------

#if !defined SOL_NO_AA

#include <lem/io_tbs.h>

#include <lem/solarix/sg_autom.h>
#include <lem/solarix/variator.h>

#undef min
#undef max

using namespace std;
using namespace lem;
using namespace Solarix;


Variator::~Variator(void)
{
 Delete();
 return;
}


Variator::Variator( const Variator& t )
{
 Init(t);
 key = UNKNOWN;
 return;
}



void Variator::operator=( const Variator& t )
{
 if( &t==this )
  return;

 Delete();
 Clear();
 Init(t);
 key = UNKNOWN;
 return;
}



Variator::Variator(void)
{
 roots.reserve(16);
 Clear();
 key     = UNKNOWN;
 org_key = UNKNOWN;
 return;
}

/************************************************************************
 ��������������� ��������� �� ������ ��������� ������ �������� tree_list.
 �����, ��� ��������� �� ������ tree_list ������������ � ����� ������
 �����, ��� ���������� ����� ��������, ������� ��� ��������� �� ������
 ������������� �� ������� ���������. ��� ������� ���� �������� ������.
*************************************************************************/
Variator::Variator( const MCollect<Tree_Node*> &tree_list )
{
 Clear();
 key     = UNKNOWN;
 org_key = UNKNOWN;

 const int ntree=CastSizeToInt(tree_list.size());
 roots.reserve(ntree);

 val = Real1(100);

 for( int i=0; i<ntree; i++ )
  roots.push_back( tree_list[i] );

 return;
}

#if defined SOL_CAA
/*********************************************************************
 ������ ��������� �� ���������. ������ ���������� �� ������ slist
 ������ ������� ��� �������� ������. �� ������ ������ �������������
 ��������� ������ slist ����������� ����� ������������� ���������.
*********************************************************************/
Variator::Variator( const Word_Form *slist, int nsynt )
{
 Clear();
 key     = UNKNOWN;
 org_key = UNKNOWN;

 roots.reserve(nsynt);

 for( int i=0; i<nsynt; i++ )
  roots.push_back( new Tree_Node(slist[i]) );

 return;
}
#endif


#if defined SOL_LOADBIN
Variator::Variator( lem::Stream &bin )
{
 LoadBin(bin);
 key     = UNKNOWN;
 org_key = UNKNOWN;
 return;
}
#endif

void Variator::Clear(void)
{
 LEM_CHECKIT_Z( roots.empty() );
 roots.clear();

 val     = Real1(100);
 freq    = 0;
 key     =
 org_key = UNKNOWN;
 score = 0;

 marks.clear();

 return;
}


void Variator::Delete(void)
{
 for( lem::Container::size_type i=0; i<roots.size(); ++i )
  {
   delete roots[i];
  }

 roots.clear();
 marks.clear();

 return;
}

void Variator::Init( const Variator& t )
{
 LEM_CHECKIT_Z( &t!=NULL );

 freq     = t.freq;
 val      = t.val;
 org_key  = t.org_key;

 const int nroot=t.size();

 roots.resize(nroot);

 for( int i=0; i<nroot; i++ )
  roots[i] = new Tree_Node( t.get(i) );

 marks = t.marks;

 return;
}


Variator* Variator::DeepCopy(void) const
{
 Variator * res = new Variator();

 res->freq = freq;
 res->val      = val;
 res->org_key  = org_key;

 for( lem::Container::size_type i=0; i<roots.size(); ++i )
  res->roots.push_back( new Tree_Node( get(i) ) );

 res->marks = marks;

 return res;
}





void Variator::Add( Tree_Node *to_add )
{
 roots.push_back( to_add );
 return;
}


#if defined SOL_CAA
/*****************************************************************************
 ��������� ������ to_add � �������� ������� where_to, �������� ������. ����
 where_to=0, �� ������ to_add ����� ��������� � ����� ������ ������ � �������
 �������, � ���� ������ �������� ��������� ������, � ��� �����. ������� ���
 ������ �������� ��� ���������� to_add!
******************************************************************************/
void Variator::Insert( int where_to, Tree_Node *to_add )
{
 roots.Insert( where_to, to_add );
 return;
}
#endif



/***********************************************************************
 ��������� ���������� ����������� ���������, ������ - � �����������
 �������� �����. �������� ���������� ������, ��� ��� �� ��������
 ����� �������������� ��������, ������� ���������� ��������, � ����
 ������ �� �����������. � ��� ��� ������ ������ ����� ����� �����������
 ������� ���������, �� ���������� ��������� ���������� �������� -
 ������������� ������. ��� �� �����, ��� �������� ����� �������������
 ������������� ������� ���������� ��������� ��������.
************************************************************************/

void Variator::Print(
                     OFormatter &s,
                     SynGram& gram,
                     bool detailed
                    ) const
{
 #if defined SOL_CAA

 s.printf( "%d item(s)", size() );

 // ������ �����. ������� ���������� ������� ��������� ���� �� ������
 // �� �����������. ��� ��������� �������� ����������� ��������� ���������.
 // -----------------------------------------------------------------------
 // ������� ������ ������ ��������� ��������������� � ��������� �����,
 // ����������� � ����������� ������.
 //
 // �������� ����� �������� � � �����������, � ������� ������ �������� ������
 // �� ��������� ���������:
 //    bunch0  bunch1  bunch2
 //      A1      B1      C1
 //      A2              C2
 //                      C3
 //
 //
 // ��������� �������-��������������� ����� ������ ��������������� ���� ���
 // ������ � ����� ���������� �������.

 PtrCollect< lem::Collect<UFString> > vstr;
 vstr.reserve(size());

 int nlines=0; // ������������ ����� ����� � �����������

 for( int itree=0; itree<size(); itree++ )
  {
   // ������� ��������� �������, � ������� �������� ��������� ������ ��������.
   lem::Char_Stream::UTF16_MemWriter mem;
   OUFormatter out(&mem);

   // �������������� ���������� � ������ ������.
   out.printf( "tree #%2d \n", itree );
   get(itree).Print( out, gram, 0, detailed );

   UFString *str = mem.Pick_String();

   lem::Collect<UFString> *ss = new lem::Collect<UFString>;
   lem::parse( *str, *ss, L"\n" );
   for( lem::Container::size_type k=0; k<ss->size(); ++k )
    ss->get(k).subst_all( L"\r", L"" );

   nlines = std::max( nlines, CastSizeToInt(ss->size()) );

   vstr.push_back(ss);
   delete str;
  }

 // ���������� nlines ������ �������� ����� ����� � ����������� �����������
 // ������.

 /*--------------------------------------------------------------------
  ������ ���������� ���������� ������������ ����������� ���, �����
  � ����� ������� �������������� ����� ����� �������� �, � ������, ��
  ��������� ���������� �������.

  ����� ��� ��������� ������ ����� ���:

    ������ ����       ������ ����      ��������� ���������
  |#########     |   |$$$$$$     | ==> #########     :$$$$$$
  |########      |   | $$$$$$$   | ==> ########      : $$$$$$$
  |  #######     |   | $$$$$$    | ==>   #######     : $$$$$$
  |   #######    |   |  $$$$$$$  | ==>     ######    :  $$$$$$$
  |   ###########|   |  $$$$$$$$$| ==>      #########:  $$$$$$$$$
  |              |   |           | ==>
  l0             r0  l1          r1

  ����������� ������ ����������� � ������� gap.
 -------------------------------------------------------------------*/
 IntCollect most_right;
 most_right.reserve(size());

 {
 for( int itree=0; itree<size(); itree++ )
  {
   const lem::Collect<UFString> &block = * vstr[itree];

   size_t max_right=0;
   for( lem::Container::size_type i=0; i<block.size(); i++ )
    max_right = std::max( max_right, block[i].length() );

   most_right.push_back( max_right );
  }
 }

 // ������ ��������� ������ �� �������, ��������� �� ������� ���������
 // � ������� vstr, � �������� �����-�������� s.
 s.printf( " val=%us\n", to_ustr( val ).c_str() );

 // ��������� ��������� ���������� ��������...
 for( int iline=0; iline<nlines; iline++ )
  {
   for( Container::size_type iblock=0; iblock<vstr.size(); iblock++ )
    {
     const lem::Collect<UFString> &block = *vstr[iblock];

     if( CastSizeToInt(block.size())<=iline )
      // ���������� ������ ������, ��� ��� � ���� ����� ����� ��������� ������,
      // ���  � ����� ������������� �����.
      s.printf( "%H ", most_right[iblock] );
     else
      {
       // ��� ������ ������ ����� ������ ����� ���� �����
       const int add = most_right[iblock]-block[iline].length();
       s.printf( "%us%H ", block[iline].c_str(), add );
      }

     // ������������ ����������� ������
     s.printf( " | " );
    }

   s.eol();
  }

 s.eol();
 #endif

 return;
}



#if defined SOL_LOADBIN
void Variator::LoadBin( lem::Stream &bin )
{
 bin.read( &key,          sizeof(key)          );
 bin.read( &org_key,      sizeof(org_key)      );
 bin.read( &val,          sizeof(val)          );
 bin.read( &freq,         sizeof(freq)         );
 bin.read( &score,        sizeof(score)        );
 
 Container::size_type n=0;
 bin.read( &n, sizeof(n) );
 roots.reserve(n);
 
 for( Container::size_type i=0; i<n; i++ )
  {
   Tree_Node *to_add = new Tree_Node();
   to_add->LoadBin(bin);
   roots.push_back(to_add);
  }

 return;
}
#endif


void Variator::SaveBin( lem::Stream &bin ) const
{
 #if defined SOL_SAVEBIN
 bin.write( &key,      sizeof(key)      );
 bin.write( &org_key,  sizeof(org_key)  );
 bin.write( &val,      sizeof(val)      );
 bin.write( &freq,     sizeof(freq)     );
 bin.write( &score,        sizeof(score)        );

 const Container::size_type n=size();
 bin.write( &n, sizeof(n) );
 for( Container::size_type i=0; i<n; i++ )
  roots[i]->SaveBin(bin);

 return;
 #endif
}

#if defined SOL_CAA
/************************************************************************
 ������� ������ ���������� �� ������� � �������� itree ���������
 �� t, ������ ������ ��������� � ���� ������ ������ �� �������������.
 ����� ������� t=NULL, ����� ������ ����� ������� ������ ������ ��������
 � ��������� �������.
*************************************************************************/
void Variator::SetPtr( int itree, Tree_Node *t )
{
 LEM_CHECKIT_Z( roots[itree]==NULL );

 if( t==NULL )
  {
   roots[itree] = new Tree_Node();
  }
 else
  {
   roots[itree] = t;
  }

 return;
}
#endif





#if defined SOL_CAA
// ********************************************************
// ������� ���������� ����������� ��������� - � ���� �����
// ������ ������.
// ********************************************************
void Variator::PrintRoots(
                          OFormatter &s,
                          bool Decoration, // ���������� ��������������
                          bool EntryKeys   // �������� ���� ��������� ������
                         ) const
{
 if( Decoration )
  s.printf( "%W2d roots: ", roots.size() );

 for( Container::size_type i=0; i<roots.size(); i++ )
  {
   if(i)
    s.printf( "  " );

   roots[i]->PrintPlain( s, EntryKeys );
  }

 if( score!=0 )
  s.printf( " score=%vfA%d%vn", GetScore() );

 s.eol();

 return;
}
#endif

#if defined SOL_CAA
void Variator::PrintV( OFormatter &out, SynGram &gram, bool detailed ) const
{
 for( int itree=0; itree<size(); itree++ )
  {
   roots[itree]->Print( out, gram, detailed );
  }

 return;
}
#endif


#if defined SOL_CAA
void Variator::DeleteRoots(void)
{
 for( Container::size_type i=0; i<roots.size(); i++ )
  delete roots[i]; 

 roots.clear();

 return;
}
#endif

bool Variator::operator==( const Variator &x ) const
{
 for( Container::size_type i=0; i<roots.size(); i++ )
  if( !((*roots[i])==(*x.roots[i])) )
   return false;

 return true;
}



TreeMarks& Variator::TouchMarks( const UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 for( lem::Container::size_type i=0; i<marks.size(); ++i )
  if( marks[i]->GetName().eqi(name) )
   return * marks[i];

 marks.push_back( new TreeMarks(name) );
 return *marks.back();
}


TreeMarks* Variator::FindMarks( const UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 for( lem::Container::size_type i=0; i<marks.size(); ++i )
  if( marks[i]->GetName().eqi(name) )
   return marks[i];

 return NULL;
}

const TreeMarks* Variator::FindMarks( const UCString &name ) const
{
 LEM_CHECKIT_Z( !name.empty() );

 for( lem::Container::size_type i=0; i<marks.size(); ++i )
  if( marks[i]->GetName().eqi(name) )
   return marks[i];

 return NULL;
}


void Variator::RemoveRoot( int index )
{
 delete roots[index];
 roots.Remove(index);
 return;
}


/*
void Variator::DeleteBunch( int ibunch )
{
 delete roots[ibunch];
 roots[ibunch]=NULL;
 return;
}
*/


void Variator::DeleteTree( int index )
{
 delete roots[index];
 roots[index]=NULL;
 return;
}




void Variator::PrintXML( OFormatter &xml, SynGram &gram ) const
{
 xml.printf( "<rootset>\n" );

 xml.printf( "<trees count=\"%d\">\n", CastSizeToInt(roots.size()) );
 for( Container::size_type i=0; i<roots.size(); i++ )
  {
   xml.printf( "<tree n=\"%d\">\n", CastSizeToInt(i) );
   get(i).PrintXML( xml, gram );
   xml.printf( "</tree>\n" );
  }
 xml.printf( "</trees>\n" );

 if( !marks.empty() )
  {
   xml.printf( "<marks count=\"%d\">", CastSizeToInt(marks.size()) );
   for( lem::Container::size_type i=0; i<marks.size(); ++i )
    {
     xml.printf( "<mark n=\"%d\">\n", CastSizeToInt(i) );
     marks[i]->PrintXML( xml, gram.GetDict() );
     xml.printf( "</mark>\n" );
    }
   xml.printf( "</marks>" );
  }

 xml.printf( "</rootset>\n" );

 return;
}



#endif
