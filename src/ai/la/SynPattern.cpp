// CD->07.11.2014

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/SG_Coordinates.h>
#include <lem/solarix/PatternLinks.h>
#include <lem/solarix/PatternNGrams.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/PredicateTemplate.h>
#include <lem/solarix/PatternConstraints.h>
#include <lem/solarix/PatternOptionalPoints.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT && defined SOL_COMPILER
SynPattern::SynPattern() : id_src(UNKNOWN), id_language(UNKNOWN),
 incomplete(false), constraints(NULL)
{
 compilation_context = new SynPatternCompilation(this);
 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
SynPattern::~SynPattern()
{
 delete constraints;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPattern::LoadTxt(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         const SynPatterns &patterns,
                         WordEntrySet &wordentry_set,
                         TrFunctions &functions
                        )
{
 lem::Iridium::BSourceState pattern_beginning = txtfile.tellp();

 id_src = dict.GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );

 if( dict.GetDebugLevel_ir()>=3 )
  {
   dict.GetIO().mecho().printf( "pattern " );
  }

 // Опционально могут быть заданы целевой язык и опции.

 while( !txtfile.eof() )
 {
  if( txtfile.probe( B_OFIGPAREN ) )
   break;

  if( txtfile.probe( B_LANGUAGE ) )
   {
    txtfile.read_it( B_EQUAL );
   
    lem::Iridium::BethToken lang = txtfile.read();
    id_language = dict.GetSynGram().Find_Language(lang.string());
    if( id_language==UNKNOWN )
     {
      lem::Iridium::Print_Error(lang,txtfile);
      dict.GetIO().merr().printf( "Unknown language name %us\n", lang.c_str() );
      throw lem::E_BaseException();
     }     
   }
  else if( txtfile.probe( L"incomplete" ) )
   {
    incomplete=true;
   }
  else
   {
    lem::Iridium::BethToken tname = txtfile.read();
    name = tname.string();
  
    if( dict.GetDebugLevel_ir()>=3 )
     {
      dict.GetIO().mecho().printf( "%vfE%us%vn ", name.c_str() );
     }
  
    if( !patterns.IsPatternName(name) )
     {
      dict.GetIO().merr().printf( "Patterns group [%us] is not declared\n", name.c_str() );
      lem::Iridium::Print_Error(tname,txtfile);
      throw lem::E_BaseException();
     }
  
    const SynPatternOptions & group_options = patterns.GetOptions(name);
    id_language = group_options.GetLanguageId();
  
    // Секция export { ... } содержит объявления координат, которые паттерн выдает наружу
    // Сначала попробуем взять содержимое экспорта по умолчанию, зарегистрированное в объявлении
    // группы паттернов.
  
    if( txtfile.probe(L"export") )
     {
      export_info.LoadTxt( dict, txtfile );
     }
    else
     {
      const SynPatternOptions & p_options = patterns.GetOptions(name);
      export_info = p_options.GetExport();
     }
  
    export_info.RegisterExport( *compilation_context );
  
    if( txtfile.probe( B_LANGUAGE ) )
     {
      txtfile.read_it( B_EQUAL );
      
      lem::Iridium::BethToken lang = txtfile.read();
      id_language = dict.GetSynGram().Find_Language(lang.string());
      if( id_language==UNKNOWN )
       {
        lem::Iridium::Print_Error(lang,txtfile);
        dict.GetIO().merr().printf( "Unknown language name %us\n", lang.c_str() );
        throw lem::E_BaseException();
       }     
     }
  
    txtfile.read_it( B_OFIGPAREN );
    break;
   }
 }

 // Список опорных точек в фигурных скобочках
 lem::Iridium::BSourceState beg = txtfile.tellp();

 compilation_context->SetName( name );
 compilation_context->Set(&wordentry_set);

 while( !txtfile.eof() )
  {
   if( txtfile.pick().GetToken()==B_CFIGPAREN )
    {
     txtfile.read();
     break;
    }

   SlotProperties slot;
   slot.LoadTxt( dict, txtfile );

   SynPatternPoint *p = new SynPatternPoint;
   p->LoadTxt( dict, txtfile, patterns, *compilation_context, functions );

   points.push_back(p);
   slots.push_back(slot);
   compilation_context->BeforeNextPointCompilation();
  }

 if( points.empty() )
  {
   lem::Iridium::Print_Error(beg,txtfile);
   dict.GetIO().merr().printf("Pattern must not be empty\n" );
   throw E_Solarix();
  }

 if( !compilation_context->PatternHasBeenCompiled(dict.GetSynGram()) )
  {
   lem::Iridium::Print_Error(pattern_beginning,txtfile);
   dict.GetIO().merr().printf("Some export items are not actually exported\n" );
   throw E_Solarix();
  }

 points.back()->Terminator();

 bool links_loaded=false, ngrams_loaded=false, predicates_loaded=false, constraints_loaded=false;

 while( !txtfile.eof() )
  if( txtfile.probe(B_COLON) )
   {
    lem::Iridium::BSourceState section_beg = txtfile.tellp();

    if( txtfile.probe( L"links" ) )
     {
      if( links_loaded )
       {
        lem::Iridium::Print_Error(section_beg,txtfile);
        dict.GetIO().merr().printf("Redefinition of 'links'\n" );
        throw E_Solarix();
       }
 
      LoadLinks( dict, txtfile, *compilation_context );
      links_loaded=true;
     }
    else if( txtfile.probe( L"ngrams" ) )
     {
      if( ngrams_loaded )
       {
        lem::Iridium::Print_Error(section_beg,txtfile);
        dict.GetIO().merr().printf("Redefinition of 'ngrams'\n" );
        throw E_Solarix();
       }

      LoadNGrams( dict, txtfile, *compilation_context );
      ngrams_loaded=true;
     }
    else if( txtfile.probe( L"predicates" ) )
     {
      if( predicates_loaded )
       {
        lem::Iridium::Print_Error(section_beg,txtfile);
        dict.GetIO().merr().printf("Redefinition of 'predicates'\n" );
        throw E_Solarix();
       }

      LoadPredicates( dict, txtfile, *compilation_context );
      predicates_loaded=true;
     }
/*
    else if( sparse && txtfile.probe( L"constraints" ) )
     {
      if( constraints_loaded )
       {
        lem::Iridium::Print_Error(section_beg,txtfile);
        dict.GetIO().merr().printf("Redefinition of 'constraints'\n" );
        throw E_Solarix();
       }

      LoadConstraints( dict, txtfile, *compilation_context );
      constraints_loaded=true;
     }*/
    else
     {
      lem::Iridium::Print_Error(txtfile);
      dict.GetIO().merr().printf("Unexpected token\n" );
      throw E_Solarix();
     }
   }
  else
   {
    break;
   }


 // Опорные точки могут теперь выполнить внутренние оптимизации, в частности - учесть использование
 // маркировок и улучшить эффективность директивы @mark()
 for( lem::Container::size_type i=0; i<points.size(); ++i )
  points[i]->OptimizeAfterCompilation( *compilation_context );

 // Безымянные паттерны, то есть правила самого верхнего уровня, должны быть привязаны к языку с помощью директивы { language=XXX }
 if( id_language==UNKNOWN && name.empty() )
  {
   lem::Iridium::Print_Error(pattern_beginning,txtfile);
   dict.GetIO().merr().printf("Pattern must be bound to a language\n" );
   throw E_Solarix();
  }

 if( dict.GetDebugLevel_ir()>=3 )
  {
   dict.GetIO().mecho().printf( "%vfAOK%vn\n" );
  }
 
 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool SynPattern::Error(void) const
{
 for( lem::Container::size_type i=0; i<points.size(); ++i )
  if( points[i]->Error() )
   return true;

 return false;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPattern::Print( lem::OFormatter &to, SynGram &sg ) const
{
/*
 to.printf( "pattern %us {", name.c_str() );

 for( lem::Container::size_type i=0; i<points.size(); ++i )
  points[i]->Print( to, sg );

 to.printf( " }" );
*/

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPattern::CheckBeforeMerge( const SynPattern &x, SynGram &sg ) const
{
 try
  {
   compilation_context->CheckThatVariablesTheSame( * x.compilation_context );
  }
 catch( const E_BaseException &e )
  {
   lem::MemFormatter mem;

   mem.printf( "Error %us\n", e.what() );
   mem.printf( "Two contexts have different variables set:\nFirst: " );
   this->Print( mem, sg );
   mem.printf( "\nSecond: " );
   x.Print( mem, sg );
   throw lem::E_BaseException( mem.string() );
  }

 // проверим, что экспортируются одни и те же координаты
 lem::MCollect<int> mismatched_coords;
 for( lem::Container::size_type i=0; i<export_info.export_coords.size(); ++i )
  if( x.export_info.export_coords.find( export_info.export_coords[i] )==UNKNOWN )
   mismatched_coords.push_back( export_info.export_coords[i] );

 for( lem::Container::size_type i=0; i<x.export_info.export_coords.size(); ++i )
  if( export_info.export_coords.find( x.export_info.export_coords[i] )==UNKNOWN )
   mismatched_coords.push_back( x.export_info.export_coords[i] );

 if( !mismatched_coords.empty() )
  {
   lem::MemFormatter mem;

   mem.printf( "Mismatching coordinates in pattern %us:", name.c_str() );

   for( lem::Container::size_type i=0; i<mismatched_coords.size(); ++i )
    {
     const lem::UCString &cname = sg.coords()[ mismatched_coords[i] ].GetName()[0];
     mem.printf( " %us", cname.c_str() );
    }

   throw lem::E_BaseException( mem.string() );
  }

 lem::MCollect<lem::UCString> mismatched_nodes;
 for( lem::Container::size_type i=0; i<export_info.export_nodes.size(); ++i )
  if( x.export_info.export_nodes.find( export_info.export_nodes[i] )==UNKNOWN )
   mismatched_nodes.push_back( export_info.export_nodes[i] );

 for( lem::Container::size_type i=0; i<x.export_info.export_nodes.size(); ++i )
  if( export_info.export_nodes.find( x.export_info.export_nodes[i] )==UNKNOWN )
   mismatched_nodes.push_back( x.export_info.export_nodes[i] );


 if( !mismatched_nodes.empty() )
  {
   lem::MemFormatter mem;

   mem.printf( "Mismatching nodes in pattern %us:", name.c_str() );

   for( lem::Container::size_type i=0; i<mismatched_nodes.size(); ++i )
    {
     mem.printf( " %us", mismatched_nodes[i].c_str() );
    }

   throw lem::E_BaseException( mem.string() );
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPattern::LoadLinks( 
                           Dictionary &dict,
                           lem::Iridium::Macro_Parser & txtfile,
                           SynPatternCompilation & compilation_context
                          )
{
 PatternLinks * links = new PatternLinks();
 links->LoadTxt( dict, txtfile, compilation_context );
 points.back()->SetLinks( links );

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPattern::LoadNGrams( 
                            Dictionary &dict,
                            lem::Iridium::Macro_Parser & txtfile,
                            SynPatternCompilation & compilation_context
                           )
{
 PatternNGrams * ngrams = new PatternNGrams();
 ngrams->LoadTxt( dict, txtfile, compilation_context );
 points.back()->SetNGrams( ngrams );
 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SynPattern::LoadConstraints( 
                                 Dictionary &dict,
                                 lem::Iridium::Macro_Parser & txtfile,
                                 SynPatternCompilation & compilation_context
                                )
{
 constraints = new PatternConstraints();
 constraints->LoadTxt( dict, txtfile, compilation_context );
 return;
}
#endif




#if defined SOL_LOADTXT && defined SOL_COMPILER

namespace {

 class PredicateTemplateParams_PATTERN : public PredicateTemplateParams
 {
  private:
   SynPatternCompilation & ctx;

  public:
   PredicateTemplateParams_PATTERN( SynPatternCompilation & compilation_context ) : ctx(compilation_context) {}
   virtual bool IsParam( const lem::UCString & probe ) const
   {
    return ctx.Find(probe)!=UNKNOWN;
   }
 };
}


void SynPattern::LoadPredicates(
                                Dictionary &dict,
                                lem::Iridium::Macro_Parser & txtfile,
                                SynPatternCompilation & compilation_context
                               )
{
 PredicateTemplates * predicates = new PredicateTemplates();

 PredicateTemplateParams_PATTERN params(compilation_context);
 predicates->LoadTxt( dict, txtfile, params );

 points.back()->SetPredicates( predicates );
 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
const lem::PtrCollect<SynPatternPoint>& SynPattern::GetPointChain() const
{
 return points;
}
#endif
