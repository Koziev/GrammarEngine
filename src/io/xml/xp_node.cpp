// -----------------------------------------------------------------------------
// File XP_NODE.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Класс Node - узел XML-файла.
// -----------------------------------------------------------------------------
//
// CD->20.11.2004
// LC->29.01.2009
// --------------

#include <lem/conversions.h>
#include <lem/xml_parser.h>

using namespace lem;
using namespace lem::Xml;


Node::Node(void)
{
 closing=closed=false;
 node_type=OtherNode;
}


Node::~Node(void)
{
 ZAP_A( nodes );
}

// ***************************************************************
// Поиск вложенного узла по заданному имени. Если вложенных узлов
// с таким именем несколько, то будет найден первый.
// ***************************************************************
Node* Node::GetNode( const UFString &Name )
{
 for( Container::size_type i=0; i<nodes.size(); i++ )
  if( nodes[i]->GetName() == Name )
   return nodes[i];

 return NULL;
}



const Node* Node::GetNode( const UFString &Name ) const
{
 for( Container::size_type i=0; i<nodes.size(); i++ )
  if( nodes[i]->GetName() == Name )
   return nodes[i];

 return NULL;
}



// *************************************************************
// Делает поиск во всем дереве - находит первый узел с
// заданным именем. Если поиск безуспешен, то возвращает NULL.
// *************************************************************
Node* Node::Find_Everywhere( const UFString &Name )
{
 if( name == Name )
  return this;

 for( MCollect<Node*>::iterator i=nodes.begin(); i!=nodes.end(); i++ )
  {
   Node *res = (*i)->Find_Everywhere(Name);
   if( res )
    return res;
  }

 return NULL;
}



const Node* Node::Find_Everywhere( const UFString &Name ) const
{
 if( name == Name )
  return this;

 for( MCollect<Node*>::const_iterator i=nodes.begin(); i!=nodes.end(); i++ )
  {
   const Node *res = (*i)->Find_Everywhere(Name);
   if( res )
    return res;
  }

 return NULL;
}




const Node* Node::Find_By_Path( const UFString &Path ) const
{
 LEM_CHECKIT_Z(Path.empty()==false);

 lem::Collect<lem::UFString> steps;
 steps.reserve(16);

 Parser::Split_Path( Path, steps );

 return Find_By_Path(steps);
}




const Node* Node::Find_By_Path( const Collect<UFString> &Steps ) const
{
 if( Steps.empty() )
  return NULL;

 const Node *cur = this;

 for( Container::size_type i=0; i<Steps.size(); i++ )
  {
   cur = cur->GetNode(Steps[i]);
   if( !cur )
    return NULL;
  }

 return cur; 
}

lem::UFString Node::Get_By_Path( const UFString &Path ) const
{
 const Node *n = Find_By_Path(Path);
 return n==NULL ? UFString() : n->GetBody();
}




// ***********************************************************************
// Return the list of all nodes with given name
// ***********************************************************************
lem::MCollect<const Node*> Node::GetNodes( const UFString &Name ) const
{
 lem::Collect<lem::UFString> steps;
 steps.reserve(16);

 lem::MCollect<const Node*> nodes_list;
 nodes_list.reserve(128); 

 for( Container::size_type i=0; i<nodes.size(); i++ )
  if( nodes[i]->GetName() == Name )
   nodes_list.push_back(nodes[i]);
  
 return nodes_list;
}




int Node::GetInt(void) const
{
 const UFString &b = GetBody();
 int res=0;
 if( !lem::to_int( b.c_str(), &res, 10 ) )
  {
   throw E_BaseException( lem::format_str(L"XML node: can not convert [%us] to int", b.c_str() ).c_str() );
  }

 return res;
}


int Node::FindAttr( const lem::UFString &attr ) const
{
 for( lem::Container::size_type i=0; i<attrs.size(); ++i )
  if( attrs[i].first.eqi(attr) )
   return CastSizeToInt(i);

 return UNKNOWN;
}



const UFString& Node::GetAttr( const lem::UFString &attr, bool exception_if_missing ) const
{
 for( lem::Container::size_type i=0; i<attrs.size(); ++i )
  if( attrs[i].first.eqi(attr) )
   return attrs[i].second;

 if( exception_if_missing )
  {
   lem::UFString msg = lem::UFString(L"Attribute ")+attr+lem::UFString(L" not found in node ")+
    GetName();

   throw Attribute_Not_Found(msg);
  }

 static UFString z;
 return z;
}




/// \brief Поиск среди ветвей узла с указанным именем тэга
///        и значением указанного атрибута.
const lem::Xml::Node* Node::FindTagWithAttr( 
                                            const lem::UFString &tag,
                                            const lem::UFString &attr_name,
                                            const lem::UFString &attr_value
                                           )
{
 for( lem::Container::size_type i=0; i<nodes.size(); ++i )
  {
   #if LEM_DEBUGGING==1
   const lem::UFString &node = nodes[i]->GetName();
   #endif

   if(
      nodes[i]->MatchNameNoCase(tag) &&
      nodes[i]->MatchAttrNoCase(attr_name,attr_value)
     )
    return nodes[i];
  }

 {
 for( lem::Container::size_type i=0; i<nodes.size(); ++i )
  {
   const lem::Xml::Node *n = nodes[i]->FindTagWithAttr(tag,attr_name,attr_value);
   if( n!=NULL )
    return n;
  }
 }

 return NULL;
}
 

bool Node::MatchNameNoCase( const lem::UFString &x ) const
{ return name.eqi(x); }


/// Возвращает список подчиненных узлов, чьи имена совпадают с заданным без учета регистра.
void Node::FindMatchNameNoCase(
                               const lem::UFString &tag_name,
                               lem::MCollect<const lem::Xml::Node*> &retnodes
                              ) const
{
 for( lem::Container::size_type i=0; i<nodes.size(); ++i )
  { 
   if( nodes[i]->MatchNameNoCase(tag_name) )
    retnodes.push_back( nodes[i] );

   nodes[i]->FindMatchNameNoCase(tag_name,retnodes);
  }

 return;
}


/// \brief Есть ли среди атрибутов тэга заданное значение.                                            
bool Node::MatchAttrNoCase( const lem::UFString &attr, const lem::UFString &value ) const
{
 for( lem::Container::size_type i=0; i<attrs.size(); ++i )
  if( attrs[i].first.eqi(attr) && attrs[i].second.eqi(value) )
   return true;

 return false;
}

void Node::Walk( NodeVisitor *v ) const
{
 (*v)(this);

 for( lem::Container::size_type i=0; i<nodes.size(); ++i )
  (*v)(nodes[i]);

 return;
}

