// -----------------------------------------------------------------------------
// File TREE_NODE.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс Tree_Node - узел сминтаксического графа. Используется для построения
// Синтаксических Деревьев, Результатных частей трансформант синтаксических
// правил. Общий случай ГРАММАТИЧЕСКИХ ДЕРЕВЬЕВ.
//
// 11.10.2011 - добавлена сериализация в XML
// -----------------------------------------------------------------------------
//
// CD->14.11.1995
// LC->11.10.2011
// --------------

#if !defined SOL_NO_AA

#include <lem/conversions.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/tree_node.h>

using namespace lem;
using namespace Solarix;


Tree_Node::Tree_Node(void)
{
 #if defined SOL_CAA
// label=UNKNOWN;
 #endif
}

Tree_Node::Tree_Node( const Tree_Node& tn )
{
 Init(tn);
 return;
}


#if defined SOL_LOADBIN
Tree_Node::Tree_Node( lem::Stream &bin )
{
 #if defined SOL_CAA
// label=UNKNOWN;
 #endif
 
 LoadBin(bin);
 return;
}
#endif


Tree_Node::Tree_Node( const Word_Form& s )
{
 node = new Word_Form(s);
// org_node = new Word_Form(s);
 #if defined SOL_CAA
// label=UNKNOWN;
 #endif
 return;
}

Tree_Node::Tree_Node( Word_Form *s, bool dummy )
 : node(s)
{
// org_node = new Word_Form(*s);
 #if defined SOL_CAA
// label=UNKNOWN;
 #endif
 return;
}


void Tree_Node::ForgetChild( int ichild )
{
 child.Forget(ichild);
 return;
}

void Tree_Node::ClearChildren(void)
{
 child.Clear();
 return;
}


void Tree_Node::operator=( const Tree_Node& tn )
{
 if( &tn==this )
  return;

 Init(tn);
 return;
}


void Tree_Node::Init( const Tree_Node& tn )
{
 LEM_CHECKIT_Z( &tn != NULL );

 node     = tn.node;
// org_node = tn.org_node;
 ilink    = tn.ilink;
 child    = tn.child;
 dims     = tn.dims;
 marks    = tn.marks;
 #if defined SOL_CAA
// label    = tn.label;
 #endif
 return;
}

Tree_Node* Tree_Node::DeepCopy(void) const
{
 Tree_Node *res = new Tree_Node();

 res->node = new Word_Form( GetNode(), true );

// if( org_node.NotNull() )
//  res->org_node = new Word_Form( *org_node, true );

 res->ilink    = ilink;

 for( lem::Container::size_type i=0; i<child.size(); ++i )
  res->child.Add( child[i].DeepCopy() );

 res->dims     = dims;
 res->marks    = marks;
 #if defined SOL_CAA
// res->label    = label;
 #endif

 return res;
}




#if defined SOL_CAA
/***********************************************************
 Отрезается ветка с индексом ichild, указатель на эту ветку
 освобождается и список указателей на ветки сжимается.
************************************************************/
void Tree_Node::Remove( int ichild )
{
 child.Remove(ichild);
 return;
}
#endif

/*
#if defined SOL_CAA
// Перемаркировывает дерево.
void Tree_Node::Label(void)
{
 // Это поле никак не может помешать мультипроцессорности Ядра
 // Солярис - оставляем.
 static int LABEL=0;

 if(++LABEL==UNKNOWN)
  LABEL=0;

 label=LABEL;

 for( Container::size_type i=0; i<child.size(); i++ )
  child[i].Label();

 return;
}
#endif
*/

bool Tree_Node::DoesMatch( SynGram &sg, const Tree_Node& tn, bool strict_position ) const
{
 if(
    child.size() != tn.child.size() ||
    !GetNode().DoesMatch( sg, tn.GetNode() )
   )
  return false;

 for( lem::Container::size_type i=0; i<child.size(); i++ )
  if( !child[i].DoesMatch( sg, tn.child[i], strict_position ) )
   {
    // Обнаружилось несоответствие. Если разрешено сравнение без учета порядка
    // веток strict_position=false, то придется входить в тяжелый алгоритм.
    if( strict_position )
     return false;

    lem::MCollect<const Tree_Node*> this_nodes;
    for( lem::Container::size_type j=i; j<child.size(); j++ )
     this_nodes.push_back( &child[j] );

    // Для каждой из оставшихся веток в tn надо искать соответствие в this_nodes.
    {
    for( lem::Container::size_type j=i; j<child.size(); j++ )
     {
      bool matched=false;
      for( lem::Container::size_type k=0; k<this_nodes.size(); ++k )
       {
        if( this_nodes[k]->DoesMatch( sg, tn.child[j], strict_position ) )
         {
          matched=true;
          this_nodes.Remove(k);
          break;
         }
       } 

      if( !matched )
       return false;
     }  
    }

    return true;
   } 

 return true;
}

#if defined SOL_SAVEBIN
void Tree_Node::SaveBin( lem::Stream &bin ) const
{
 bin.write( &ilink, sizeof(ilink) );
 node->SaveBin(bin);
 child.SaveBin(bin);
 dims.SaveBin(bin);
 return;
}
#endif


#if defined SOL_LOADBIN
void Tree_Node::LoadBin( lem::Stream &bin )
{
 bin.read( &ilink, sizeof(ilink) );

 Word_Form *wf = new Word_Form;
 wf->LoadBin(bin);
 node = boost::shared_ptr<Word_Form>(wf);

 child.LoadBin(bin);
 dims.LoadBin(bin);

 return;
}
#endif


// *********************************************************************
// Если такое измерение уже есть, то просто возвращает ссылку на него.
// Если нет - создает измерение и опять-таки возвращает ссылку на него.
// *********************************************************************
TreeDimension& Tree_Node::TouchDimension( const UCString &name )
{
 if( name.empty() )
  return child;

 for( lem::Container::size_type i=0; i<dims.size(); ++i )
  if( dims[i]->GetName()==name )
   return *dims[i];

 dims.push_back( new TreeDimension(name) );
 return *dims.back();
} 

const TreeDimension& Tree_Node::leafs( const UCString &name ) const
{
 if( name.empty() )
  return child;

 for( lem::Container::size_type i=0; i<dims.size(); ++i )
  if( dims[i]->GetName()==name )
   return *dims[i];

 throw E_BaseException();
}


TreeDimension& Tree_Node::leafs( const UCString &name )
{
 if( name.empty() )
  return child;

 for( lem::Container::size_type i=0; i<dims.size(); ++i )
  if( dims[i]->GetName()==name )
   return *dims[i];

 throw E_BaseException();
}


/***********************************************************************
 Поиск ветки, подключенной к данной посредством связки типа ilink.
 Процедура вернет UNKNOWN, если поиск безрезультатен. Обрати внимание,
 что ищется только ОДНА ветка.
************************************************************************/
int Tree_Node::FindLinkedBy( Tree_Link ilink ) const
{
 for( Container::size_type i=0; i<child.size(); i++ )
  if( ilink==GetLinkIndex(i) )
   return i;

 return UNKNOWN;
}


void Tree_Node::PrintXML( OFormatter &xml, SynGram &gram ) const
{
 xml.printf( "<node>" );

 xml.printf( "<wordform>" );
 if( !node.IsNull() )
  node->PrintXML( xml, gram );
 xml.printf( "</wordform>" );

 if( !child.Empty() )
  {
   xml.printf( "<leaves count=\"%d\">", CastSizeToInt(child.size()) );
   for( Container::size_type i=0; i<child.size(); i++ )
    {
     int link_type_id = child[i].GetLink().GetState();
     lem::UCString link_name = link_type_id==UNKNOWN ? L"" : gram.GetLink(link_type_id);
     xml.printf( "<leaf n=\"%d\" arc_type=\"%d\" arc_name=\"%us\">\n", CastSizeToInt(i), link_type_id, link_name.c_str() );
     child[i].PrintXML(xml,gram);
     xml.printf( "</leaf>\n" );
    }
   xml.printf( "</leaves>" );
  }

 if( !dims.empty() )
  {
   xml.printf( "<dims count=\"%d\">", CastSizeToInt(dims.size()) );
   for( lem::Container::size_type i=0; i<dims.size(); ++i )
    {
     const TreeDimension &d = *dims[i];
     xml.printf( "<dim n=\"%d\" name=\"%us\">\n", CastSizeToInt(i), d.GetName().c_str() );
     d.PrintXML( xml, gram.GetDict() );
     xml.printf( "</dim>\n" );
    }
   xml.printf( "</dims>" );
  }

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
 
 xml.printf( "</node>" );

 return;
}


void Tree_Node::Print( OFormatter &txtfile, SynGram &gram, int offset, bool detailed ) const
{
 int Offset=offset;

 if( offset>0 )
  txtfile.printf( "%H ", offset );

 ilink.Print( txtfile, gram );

 if( node.IsNull() )
  txtfile.printf( "%vfC(null)%vn" );
 else
  node->Print( txtfile, &gram, detailed );

 if( !child.Empty() )
  {
   if( detailed )
    {
     txtfile.printf( '.' );

     if( child.size()!=1 )
      txtfile.printf( '{' );
    }

   if( Offset!=-1 )
    {
     txtfile.eol();
     Offset++;
    }

   for( Container::size_type i=0; i<child.size(); i++ )
    {
     if( Offset==-1 && i )
      txtfile.printf(' ');

     if( Offset!=-1 )
      txtfile.printf( "%H ", Offset );

     child[i].Print(txtfile,gram,Offset,detailed);
    }

   if( detailed )
    {
     if( offset!=-1 )
      txtfile.printf( "%H ", Offset-1 );

     if( child.size()!=1 )
      txtfile.printf( '}' );
    }
  }

 if( !dims.empty() )
  {
   for( lem::Container::size_type i=0; i<dims.size(); ++i )
    {
     const TreeDimension &d = *dims[i];
     txtfile.printf( ' ' );
     d.Print( gram.GetDict(), txtfile, detailed );
    }
  }

 if( detailed && !marks.empty() )
  {
   txtfile.printf( " %vf6marks={%vn" );
   
   for( lem::Container::size_type i=0; i<marks.size(); ++i )
    {
     txtfile.printf( ' ' );
     marks[i]->Print( gram.GetDict(),txtfile);
    }

   txtfile.printf( " %vf6}%vn" );
  }

 if( Offset!=-1 )
  txtfile.eol();

 return;
}


#if defined SOL_CAA
/***********************************************
 Вычисление общей оценки достоверности дерева.
 Получается как суперпозиция достоверности корня
 и подключенных веток.
************************************************/
Real1 Tree_Node::ComputeValue(void) const
{
 Real1 v = GetNode().GetVal();
 for( Container::size_type i=0; i<child.size(); i++ )
  v *= child[i].ComputeValue();

 return v;
}
#endif


void Tree_Node::PrintPlain( OFormatter &s, bool EntryKey ) const
{
 GetNode().PrintPlain(s,EntryKey);

 if( !child.Empty() )
  {
   s.printf( " ( " );
   for( Container::size_type i=0; i<child.size(); i++ )
    {
     if( i )
      s.printf( ", " );

     child[i].PrintPlain( s, EntryKey );
    }

   s.printf( " ) " );
  }

 return;
}


/*
void Tree_Node::Assemble_Entries_List( BaseSet<int> &entries ) const
{
 for( Container::size_type i=0; i<child.size(); i++ )
  child[i].Assemble_Entries_List(entries);
  
 entries.insert( node->GetEntryKey() );

 {
 for( lem::Container::size_type i=0; i<node->GetAlts().size(); ++i )
  entries.insert( node->GetAlts()[i]->GetEntryKey() );
 }

 return;
}
*/

#if defined SOL_SAVETXT
void Tree_Node::SaveTxt(
                        OFormatter &txtfile,
                        SynGram &gram,
                        int Offset,
                        bool detailed
                       ) const
{
 int offset=Offset;

 ilink.SaveTxt(txtfile,gram);
 GetNode().SaveTxt( txtfile, gram, detailed );

 if( !child.Empty() )
  {
   if( detailed )
    {
     txtfile << sol_get_token(B_DOT);

     if( child.size()!=1 )
      txtfile<<sol_get_token(B_OFIGPAREN);
    }

   if( offset!=-1 )
    {
     offset = txtfile.GetPos();
     txtfile.eol();
    }

   for( Container::size_type i=0; i<child.size(); i++ )
    {
     int of=offset;

     if( of==-1 && i )
      txtfile.printf( ' ' );

     if( of!=-1 )
      txtfile.printf( "%H ", of );

     child[i].SaveTxt(txtfile,gram,of,detailed);
    }

   if( detailed )
    {
     if( offset!=-1 )
      txtfile.printf( "%H ", offset-1 );

     if( child.size()!=1 )
      txtfile<<sol_get_token(B_CFIGPAREN);
    }
  }

 if( offset!=-1 )
  txtfile.eol();

 return;
}
#endif


/*
bool Tree_Node::Does_Contain_Class( int iClass, SynGram &sg ) const
{
 if( GetNode().GetEntryKey()==ANY_STATE )
  return true;
 
 if( sg.GetEntry( GetNode().GetEntryKey() ).GetClass()==iClass )
  return true;
  
 for( Container::size_type i=0; i<child.size(); i++ )
  if( child[i].Does_Contain_Class( iClass, sg ) )
   return true;

 return false;
}
*/




// Проверяет полное владение указателем и если указатель разделяемый,
// то создает свою копию.
Word_Form& Tree_Node::GetUnique(void)
{
 if( !node.unique() )
  node = lem::Ptr<Word_Form>( new Word_Form( *node ) );

 return *node;
}



void Tree_Node::Add( Tree_Node *to_add )
{
 LEM_CHECKIT_Z(to_add!=NULL);
 child.Add(to_add);
}


void Tree_Node::Add( const Tree_Node& to_add )
{ child.Add( new Tree_Node(to_add) ); }



/*
int Tree_Node::CountClass( int iclass, SynGram &sg ) const
{
 LEM_CHECKIT_Z( iclass!=UNKNOWN );

 int n=0;

 if( GetNode().GetEntryKey()!=ANY_STATE )
  { 
   if( sg.GetEntry( GetNode().GetEntryKey() ).GetClass()==iclass )
    n++;

   for( lem::Container::size_type i=0; i<GetNode().GetAlts().size(); ++i )
    if( sg.GetEntry( GetNode().GetAlts()[i]->GetEntryKey() ).GetClass()==iclass )
     n++;

   {  
   for( Container::size_type i=0; i<child.size(); i++ )
    n+=child[i].CountClass( iclass, sg );
   }
  }

 return n;
}


int Tree_Node::CountEntry( int ekey ) const
{
 LEM_CHECKIT_Z( ekey!=UNKNOWN );

 int n=0;

 if( GetNode().GetEntryKey()==ekey )
  n++;

 for( lem::Container::size_type i=0; i<GetNode().GetAlts().size(); ++i )
  if( GetNode().GetAlts()[i]->GetEntryKey()==ekey )
   n++;

 {  
 for( Container::size_type i=0; i<child.size(); i++ )
  n+=child[i].CountEntry( ekey );
 }

 return n;
}
*/

/*
#if defined SOL_CAA
Tree_Node* Tree_Node::CreateVersionedTree( const PM_Yield &yield ) const
{
 const Word_Form &src_wf = GetNode();

 // В новой словоформе оставим только прошедшие отбор версии.
 Word_Form *new_wf = src_wf.CreateNewVersioned( yield );
 Tree_Node *tn = new Tree_Node( new_wf, true );

 tn->ilink = ilink;
 tn->org_node = org_node;
 tn->dims = dims;

 // Версионность проверяем ТОЛЬКО для корневого узла.
 for( lem::Container::size_type i=0; i<leafs().size(); ++i )
  {
   Tree_Node *c = new Tree_Node( leafs()[i] );
   tn->Add(c);
  }

 return tn;
}
#endif
*/

bool Tree_Node::operator!=( const Tree_Node& tn ) const
{
 return !operator==(tn);
}

bool Tree_Node::operator==( const Tree_Node& tn ) const
{
 if( child.size()!=tn.child.size() ||
     GetNode().GetEntryKey()!=tn.GetNode().GetEntryKey() ||
     dims.size()!=tn.dims.size()
   )
  return false;

 if( GetNode().CanMatch(tn.GetNode()) )
  return false;

 if( ilink!=tn.ilink )
  return false;

 for( lem::Container::size_type i=0; i<child.size(); ++i )
  {
   if( !( child[i]==tn.child[i] ) )
    return false;
  }

 return true;
}

// ****************************************************************************
// Поиск измерения с указанным именем. Если не найдется, то возвращается NULL;
// ****************************************************************************
TreeDimension* Tree_Node::FindDimension( const UCString &name )
{
 if( name.empty() )
  return &child;

 for( lem::Container::size_type i=0; i<dims.size(); ++i )
  if( dims[i]->GetName().eqi(name) )
   return dims[i];

 return NULL;
}

const TreeDimension* Tree_Node::FindDimension( const UCString &name ) const
{
 if( name.empty() )
  return &child;

 for( lem::Container::size_type i=0; i<dims.size(); ++i )
  if( dims[i]->GetName().eqi(name) )
   return dims[i];

 return NULL;
}


TreeMarks& Tree_Node::TouchMarks( const UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 for( lem::Container::size_type i=0; i<marks.size(); ++i )
  if( marks[i]->GetName().eqi(name) )
   return * marks[i];

 marks.push_back( new TreeMarks(name) );
 return *marks.back();
}


TreeMarks* Tree_Node::FindMarks( const UCString &name )
{
 LEM_CHECKIT_Z( !name.empty() );

 for( lem::Container::size_type i=0; i<marks.size(); ++i )
  if( marks[i]->GetName().eqi(name) )
   return marks[i];

 return NULL;
}

const TreeMarks* Tree_Node::FindMarks( const UCString &name ) const
{
 LEM_CHECKIT_Z( !name.empty() );

 for( lem::Container::size_type i=0; i<marks.size(); ++i )
  if( marks[i]->GetName().eqi(name) )
   return marks[i];

 return NULL;
}


void Tree_Node::SetNode( Solarix::Word_Form *new_node )
{
 node = new_node;
 return;
}


Predef_Tree_Node::Predef_Tree_Node(
                                   int ientry_key,
                                   SynGram &gram,
                                   int FakePosition
                                  )
:Tree_Node()
{
 node = boost::shared_ptr<Word_Form>( new Predef_Word_Form(ientry_key,gram) );
 #if defined SOL_CAA
 node->SetOriginPos(FakePosition);
 #endif
 return;
}
 
#endif
