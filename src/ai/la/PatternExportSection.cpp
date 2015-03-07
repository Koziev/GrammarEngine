#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;


PatternExportSection::PatternExportSection()
{}


PatternExportSection::PatternExportSection( const PatternExportSection & src )
: export_coords(src.export_coords), export_pairs(src.export_pairs), export_nodes(src.export_nodes)
{
 for( lem::Container::size_type i=0; i<src.export_functions.size(); ++i )
  {
   ExportCoordFunction * x = src.export_functions[i]->Clone();
   export_functions.push_back(x);
  }
}



PatternExportSection::~PatternExportSection()
{
 for( lem::Container::size_type i=0; i<export_functions.size(); ++i )
  delete export_functions[i];

 return;
}

void PatternExportSection::SaveBin( lem::Stream & bin ) const
{
 export_coords.SaveBin(bin);
 export_pairs.SaveBin(bin);
 export_nodes.SaveBin(bin);

 bin.write_int( CastSizeToInt(export_functions.size()) );
 for( lem::Container::size_type i=0; i<export_functions.size(); ++i )
  export_functions[i]->SaveBin(bin);

 return;
}


void PatternExportSection::LoadBin( lem::Stream & bin )
{
 export_coords.LoadBin(bin);
 export_pairs.LoadBin(bin);
 export_nodes.LoadBin(bin);

 const int n = bin.read_int();
 for( int i=0; i<n; ++i )
  {
   ExportCoordFunction * e = ExportCoordFunction::load_bin(bin);
   export_functions.push_back(e);
  }

 return;
}

bool PatternExportSection::operator==( const PatternExportSection & y ) const
{
 if( export_coords!=y.export_coords )
  return false;

 if( export_pairs!=y.export_pairs )
  return false;

 if( export_nodes!=y.export_nodes )
  return false;

 if( export_functions.size()!=y.export_functions.size() )
  return false;

 for( lem::Container::size_type i=0; i<export_functions.size(); ++i )
  if( ! export_functions[i]->Equals( *y.export_functions[i] ) )
   return false;

 return true;
}

bool PatternExportSection::operator!=( const PatternExportSection & y ) const
{
 return operator==(y);
}

#if defined SOL_COMPILER && defined SOL_LOADTXT
void PatternExportSection::LoadTxt(
                                   Dictionary &dict,
                                   lem::Iridium::Macro_Parser & txtfile,
                                   const SynPatterns & pattern_declarations,
                                   SynPatternCompilation & compilation_context,
                                   TrFunctions & functions,
                                   const SynPatternPoint & point
                                  )
{
 txtfile.read_it( B_OFIGPAREN );
 while( !txtfile.eof() )
  {
   lem::Iridium::BethToken coord_name = txtfile.read();
   bool force_export_dublicate=false;
   if( coord_name.GetToken()==B_PLUS )
    {
     force_export_dublicate = true;
     coord_name = txtfile.read();
    }

   if( coord_name.GetToken()==B_CFIGPAREN )
    break;

   if( coord_name.eqi(L"node") )
    {
     txtfile.read_it( B_COLON );

     ExportNode x;

     lem::Iridium::BethToken t_str1 = txtfile.read();
     UCString str1 = t_str1.string();

     if( txtfile.probe( L"->" ) )
      {
       // export { node:a->b }
       x.node_name = str1;
       x.as_name = txtfile.read().string();
      }
     else
      {
       // export { node:a }
       x.node_name = str1;
       x.as_name = str1;
      }

     // проверим, что наше правило может экспортировать такое им€
     if( !compilation_context.IsExportNode(x.as_name) )
      {
       dict.GetIO().merr().printf( "Name '%us' is not declared as exportable\n", str1.c_str() );
       lem::Iridium::Print_Error(t_str1,txtfile);
       throw lem::E_BaseException();
      }

     if( !compilation_context.NodeIsExported( x.as_name ) )
      {
       dict.GetIO().merr().printf( "The node [%us] is already exported by a previous pattern term\n", x.as_name.c_str() );
       lem::Iridium::Print_Error(t_str1,txtfile);
       throw E_BaseException();
      }

     x.NormalizeCharCase();
     export_nodes.push_back(x);

     continue;
    }

   if( coord_name.string()==L"@" )
    {
     lem::Iridium::BSourceState t1 = txtfile.tellp();

     ExportCoordFunction * fun = ExportCoordFunction::load_txt( dict, txtfile, pattern_declarations, compilation_context, point );
     export_functions.push_back(fun);

     const int fun_coord_id = fun->GetExportCoord();
     const lem::UFString & coord_name = dict.GetSynGram().coords()[fun_coord_id].GetName().string();

     if( !compilation_context.IsExportCoord(fun_coord_id) )
      {
       dict.GetIO().merr().printf( "Coordinate %us is not declared as export in pattern\n", coord_name.c_str() );
       lem::Iridium::Print_Error(t1,txtfile);
       throw lem::E_BaseException();
      }
  
     if( !fun->IsAdder() && !compilation_context.CoordIsExported( dict.GetSynGram(), fun_coord_id ) )
      {
       dict.GetIO().merr().printf( "The coordinate [%us] is already exported by a previous pattern term\n", coord_name.c_str() );
       lem::Iridium::Print_Error(t1,txtfile);                                                                                                         
       throw E_BaseException();                                                                                                                               
      }                                                                                                                                                       
                                                                                                                                                              
     continue;                                                                                                                                                
    }                                                                                                                                                        
                                                                                                                                                              
   const GramCoordAdr iglob_coord = dict.GetSynGram().FindCoord(coord_name.string());                                                                         
                                                                                                                                                              
   if( !iglob_coord.IsDefined() )                                                                                                                             
    {                                                                                                                                                         
     dict.GetIO().merr().printf( "Unknown coordinate %us\n", coord_name.c_str() );                                                                            
     lem::Iridium::Print_Error(coord_name,txtfile);
     throw lem::E_BaseException();
    }

   if( !compilation_context.IsExportCoord(iglob_coord.GetIndex()) )
    {
     dict.GetIO().merr().printf( "Coordinate %us is not declared as export in pattern\n", coord_name.c_str() );
     lem::Iridium::Print_Error(coord_name,txtfile);
     throw lem::E_BaseException();
    }

   if( !force_export_dublicate && !compilation_context.CoordIsExported( dict.GetSynGram(), iglob_coord.GetIndex() ) )
    {
     dict.GetIO().merr().printf( "The coordinate [%us] is already exported by a previous pattern term\n", dict.GetSynGram().coords()[iglob_coord.GetIndex()].GetName().string().c_str() );
     lem::Iridium::Print_Error(coord_name,txtfile);
     throw E_BaseException();
    }

   if( txtfile.probe(B_COLON) )
    {
     // задана координатна€ пара.
     lem::Iridium::BethToken state_name = txtfile.read();
     const Solarix::GramCoord &c = dict.GetSynGram().coords()[ iglob_coord.GetIndex() ];

     if( c.IsBistable() && (state_name.string()==L"0" || state_name.string()==L"1") )
      {
       const int istate = state_name.string()==L"1" ? 1 : 0;

       Solarix::GramCoordPair p( iglob_coord, istate );

       if( !force_export_dublicate && export_pairs.find(p)!=UNKNOWN )
        {
         dict.GetIO().merr().printf( "Coordinate pair %us:%us is already defined in export list\n", coord_name.c_str(), state_name.c_str() );
         lem::Iridium::Print_Error(coord_name,txtfile);
         throw lem::E_BaseException();
        }         

       export_pairs.push_back( p );
      }
     else
      {
       const int istate = c.FindState(state_name.string());
       if( istate==UNKNOWN )
        {
         dict.GetIO().merr().printf( "Coordinate %us does not have state %us\n", coord_name.c_str(), state_name.c_str() );
         lem::Iridium::Print_Error(coord_name,txtfile);
         throw lem::E_BaseException();
        }
    
       Solarix::GramCoordPair p( iglob_coord, istate );

       if( export_pairs.find(p)!=UNKNOWN )
        {
         dict.GetIO().merr().printf( "Coordinate pair %us:%us is already defined in export list\n", coord_name.c_str(), state_name.c_str() );
         lem::Iridium::Print_Error(coord_name,txtfile);
         throw lem::E_BaseException();
        }         

       export_pairs.push_back( p );
      }
    }
   else
    {
     if( export_coords.find(iglob_coord.GetIndex())!=UNKNOWN )
      {
       dict.GetIO().merr().printf( "Coordinate %us is already defined in export list\n", coord_name.c_str() );
       lem::Iridium::Print_Error(coord_name,txtfile);
       throw lem::E_BaseException();
      }         

     export_coords.push_back( iglob_coord.GetIndex() );
    }
  }

 return;
}
#endif


// ƒобавл€ем в результаты заданные €вно координатные пары.
void PatternExportSection::ExportPairs_Unconditional( SynPatternResult & dest ) const
{
 for( lem::Container::size_type j=0; j<export_pairs.size(); ++j )
  dest.exported_coords.insert( std::make_pair( export_pairs[j].GetCoord().GetIndex(), export_pairs[j].GetState() ) );

 return;
}

void PatternExportSection::ExportCoords_Unconditional( SynPatternResult & dest, const Word_Form * alt ) const
{
 for( lem::Container::size_type k=0; k<export_coords.size(); ++k )
  {
   const int id_coord = export_coords[k];
   lem::MCollect<int> bstates = alt->GetStates(id_coord);
   for( lem::Container::size_type l=0; l<bstates.size(); ++l )
    dest.exported_coords.insert( std::make_pair( id_coord, bstates[l] ) );
  }

 return;
}



bool PatternExportSection::HasRootNode() const
{
 for( lem::Container::size_type i=0; i<export_nodes.size(); ++i )
  if( export_nodes[i].as_name.eqi(L"ROOT_NODE") )
   {
    return true;
   }

 return false;
}


void PatternExportSection::ExportNodes( SynPatternResult & dest, const Word_Form * wf ) const
{
 for( lem::Container::size_type j=0; j<export_nodes.size(); ++j )
  dest.AddExportedNode( & export_nodes[j].as_name, wf );

 return;
}


#if defined SOL_CAA
void PatternExportSection::ExportByFunctions( SynPatternResult & dest, const PatternExportFuncContext & context ) const
{
 for( lem::Container::size_type i=0; i<export_functions.size(); ++i )
  export_functions[i]->Run( dest, context );

 return;
}
#endif


