#include <lem/solarix/sg_autom.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/coordinate.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/BackRefCorrel.h>
#include <lem/solarix/BackTraceItem.h>

using namespace lem;
using namespace Solarix;


BackTraceItem::BackTraceItem( const BackTraceItem &x )
 : wf(x.wf), use_export(x.use_export), export_coords(x.export_coords), export_nodes(x.export_nodes),
   beg_token(x.beg_token), end_token(x.end_token)
{
}


void BackTraceItem::operator=( const BackTraceItem &x )
{
 wf = x.wf;
 use_export = x.use_export;
 export_coords = x.export_coords;
 export_nodes = x.export_nodes;
 beg_token = x.beg_token;
 end_token = x.end_token;
 return;
}


BackTraceItem::BackTraceItem( const Solarix::Word_Form * _wordform )
 : wf(_wordform), beg_token(NULL), end_token(NULL)
{}


BackTraceItem::BackTraceItem( const Solarix::Word_Form * _wordform, const CP_Array & _exported )
 : wf(_wordform), use_export(true), export_coords(_exported), beg_token(NULL), end_token(NULL)
{}


BackTraceItem::BackTraceItem( const CP_Array & _exported )
 : wf(NULL), use_export(true), export_coords(_exported), beg_token(NULL), end_token(NULL)
{}



void BackTraceItem::SetExportedNodes( const lem::MCollect< std::pair<const lem::UCString*,const Word_Form*> > & nodes )
{
 export_nodes = nodes;
 return;
}



void BackTraceItem::SetRange( const LexerTextPos * _begin, const LexerTextPos * _end )
{
 LEM_CHECKIT_Z( _begin!=NULL );
 LEM_CHECKIT_Z( _end!=NULL );
 LEM_CHECKIT_Z( _begin->GetWordIndex()<=_end->GetWordIndex() );

 beg_token = _begin;
 end_token = _end;
 return;
}



void BackTraceItem::Print( lem::OFormatter &to, SynGram &sg, bool detailed ) const
{
 if( wf!=NULL )
  {
   Solarix::Word_Form dummy( *wf, false );
   wf->Print( to, &sg, detailed );
  }
 else
  {
   if( !export_coords.empty() )
    {
     to.printf( "%vf6(%vn" );
  
     for( lem::Container::size_type i=0; i<export_coords.size(); ++i )
      {
       const int id_coord = export_coords[i].GetCoord().GetIndex();
       const int id_state = export_coords[i].GetState();
  
       const GramCoord &c = sg.coords()[id_coord];
       if( c.IsBistable() )
        {
         if( id_state==1 )
          {
           to.printf( " %us", c.GetName().string().c_str() );
          }
         else
          {
           to.printf( " ~%us", c.GetName().string().c_str() );
          }
        }
       else
        {
         to.printf( " %us:%us", c.GetName().string().c_str(), c.GetStateName(id_state).c_str() );
        }
      }
  
     to.printf( " %vf6)%vn" );
    }
  }

 if( !export_nodes.empty() )
  {
   to.printf( " export_nodes: " );
   for( lem::Container::size_type i=0; i<export_nodes.size(); ++i )
    {
     to.printf( " %us=", export_nodes[i].first->c_str() );
     export_nodes[i].second->Print( to, &sg, true );
    }

   to.eol();
  }

 return;
}


int BackTraceItem::GetCoordState( int id_coord ) const
{
 if( use_export )
  {
   return export_coords.GetState(id_coord);
  }
 else
  {
   return GetWordform()->GetState( Solarix::GramCoordAdr(id_coord) );
  }
}


void BackTraceItem::GetCoordStates( int id_coord, lem::MCollect<int> & states ) const
{
 if( use_export )
  {
   for( lem::Container::size_type i=0; i<export_coords.size(); ++i )
    {
     if( export_coords[i].GetCoord().GetIndex()==id_coord )
      states.push_back( export_coords[i].GetState() );
    }
  }
 else
  {
   states = GetWordform()->GetStates( Solarix::GramCoordAdr(id_coord) );
  }

 return;
}



void BackTraceItem::GetCoorPairs( CP_Array &dst ) const
{
 if( use_export )
  {
   dst = export_coords;
  }
 else
  {
   const CPE_Array &src0 = GetWordform()->pairs();
   for( lem::Container::size_type i=0; i<src0.size(); ++i )
    dst.push_back( src0[i] );
  }

 return;
}



bool BackTraceItem::Check( SynGram &sg, const BackRefCorrel & condition, const Solarix::Word_Form & alt ) const
{
 const int id_coord0 = condition.id_coord0; // состо€ние этой координаты в alt
                                            // должно соответствовать
 const int id_coord1 = condition.id_coord1; // состо€нию этой координаты в нашем объекте

 const CPE_Array & alt_pairs = alt.pairs();
 const lem::Container::size_type n1 = alt_pairs.size();

 if( condition.affirmative )
  {
   bool alt_has_coord=false, b_has_coord=false;

   if( use_export )
    {
     for( lem::Container::size_type i=0; i<n1; ++i )
      {
       if( id_coord0 == alt_pairs[i].GetCoord().GetIndex() )
        {
         alt_has_coord=true;
         const int alt_state = alt_pairs[i].GetState();

         if( condition.for_group )
          {
           // проверим через сопоставление групп, например –ќƒ»“≈Ћ№Ќџ… и ѕј–“»“»¬ дл€ падежа дадут совпадение
           const GramCoord &c = sg.coords()[ id_coord0 ];
           const int alt_state_group = c.GetSubgroup(alt_state);

           const lem::Container::size_type n2 = this->export_coords.size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == this->export_coords[j].GetCoord().GetIndex() )
              {
               const int state2_group = c.GetSubgroup(this->export_coords[j].GetState());
               
               b_has_coord = true;

               if( alt_state_group==state2_group )
                {
                 // нашли соответствие подгрупп.
                 return true;
                }
              }
            }
          }
         else
          {
           // »щем такое состо€ние...
           const lem::Container::size_type n2 = this->export_coords.size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == this->export_coords[j].GetCoord().GetIndex() )
              {
               b_has_coord=true;
               if( this->export_coords[j].GetState()==alt_state )
                {
                 // нашли соответствие.
                 return true;
                }
              }
            }
          }
        }
      }
    }
   else
    {
     for( lem::Container::size_type i=0; i<n1; ++i )
      {
       if( id_coord0 == alt_pairs[i].GetCoord().GetIndex() )
        {
         alt_has_coord=true;
         const int alt_state = alt_pairs[i].GetState();

         if( condition.for_group )
          {
           const GramCoord &c = sg.coords()[ id_coord0 ];
           const int alt_state_group = c.GetSubgroup(alt_state);
           
           const lem::Container::size_type n2 = this->wf->pairs().size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
              {
               b_has_coord=true;

               const int state2_group = c.GetSubgroup(this->wf->pairs()[j].GetState());

               if( state2_group==alt_state_group )
                {
                 return true;
                }
              }
            }
          }
         else
          {
           // »щем такое состо€ние...
           const lem::Container::size_type n2 = this->wf->pairs().size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
              {
               b_has_coord=true;
               if( this->wf->pairs()[j].GetState()==alt_state )
                {
                 return true;
                }
              }
            }
          }
        }
      }
    }

   return !alt_has_coord || !b_has_coord;
  }
 else
  {
   if( use_export )
    {
     for( lem::Container::size_type i=0; i<n1; ++i )
      {
       if( id_coord0 == alt_pairs[i].GetCoord().GetIndex() )
        {
         const int alt_state = alt_pairs[i].GetState();
         
         if( condition.for_group )
          {
           const GramCoord &c = sg.coords()[ id_coord0 ];
           const int alt_state_group = c.GetSubgroup(alt_state);
           
           const lem::Container::size_type n2 = export_coords.size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == export_coords[j].GetCoord().GetIndex() )
              {
               const int state2_group = c.GetSubgroup(export_coords[j].GetState());

               if( state2_group==alt_state_group )
                {
                 return false;
                }
              }
            }
          }
         else
          {
           // »щем такое состо€ние...
           const lem::Container::size_type n2 = export_coords.size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == export_coords[j].GetCoord().GetIndex() )
              {
               if( export_coords[j].GetState()==alt_state )
                {
                 return false;
                }
              }
            }
          }
        }
      }
    }
   else
    {
     for( lem::Container::size_type i=0; i<n1; ++i )
      {
       if( id_coord0 == alt_pairs[i].GetCoord().GetIndex() )
        {
         const int alt_state = alt_pairs[i].GetState();
         
         if( condition.for_group )
          {
           const GramCoord &c = sg.coords()[ id_coord0 ];
           const int alt_state_group = c.GetSubgroup(alt_state);

           const lem::Container::size_type n2 = this->wf->pairs().size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
              {
               const int state2_group = c.GetSubgroup(this->wf->pairs()[j].GetCoord().GetIndex());

               if( state2_group==alt_state_group )
                {
                 return false;
                }
              }
            }
          }
         else
          {
           // »щем такое состо€ние...
           const lem::Container::size_type n2 = this->wf->pairs().size();
           for( lem::Container::size_type j=0; j<n2; ++j )
            {
             if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
              {
               if( this->wf->pairs()[j].GetState()==alt_state )
                {
                 return false;
                }
              }
            }
          }
        }
      }
    }

   return true;
  }

 return false;
}




bool BackTraceItem::Check( SynGram &sg, const BackRefCorrel & condition, const std::multimap<int,int> & alt_coords ) const
{
 const int id_coord0 = condition.id_coord0; // состо€ние этой координаты в alt_coords
                                            // должно соответствовать
 const int id_coord1 = condition.id_coord1; // состо€нию этой координаты в нашем объекте

 typedef std::multimap<int,int>::const_iterator II4;

 if( condition.affirmative )
  {
   bool alt_has_coord=false, b_has_coord=false;

   if( use_export )
    {
     std::pair<II4,II4> p4 = alt_coords.equal_range(id_coord0);

     if( condition.for_group )
      {
       const GramCoord &co = sg.coords()[ id_coord0 ];

       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         alt_has_coord=true;
         const int alt_state = it4->second;
         const int alt_state_group = co.GetSubgroup(alt_state);
    
         // »щем такое состо€ние...
         const lem::Container::size_type n2 = this->export_coords.size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->export_coords[j].GetCoord().GetIndex() )
            {
             b_has_coord=true;

             const int export_state_group = co.GetSubgroup( this->export_coords[j].GetState() );

             if( export_state_group==alt_state_group )
              {
               // нашли соответствие.
               return true;
              }
            }
          }
        }
      }
     else
      {
       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         alt_has_coord=true;
         const int alt_state = it4->second;
    
         // »щем такое состо€ние...
         const lem::Container::size_type n2 = this->export_coords.size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->export_coords[j].GetCoord().GetIndex() )
            {
             b_has_coord=true;
             if( this->export_coords[j].GetState()==alt_state )
              {
               // нашли соответствие.
               return true;
              }
            }
          }
        }
      }
    }
   else
    {
     std::pair<II4,II4> p4 = alt_coords.equal_range(id_coord0);

     if( condition.for_group )
      {
       const GramCoord &co = sg.coords()[ id_coord0 ];

       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         alt_has_coord=true;
         const int alt_state = it4->second;
         const int alt_state_group = co.GetSubgroup( alt_state );
    
         // »щем такое состо€ние...
         const lem::Container::size_type n2 = this->wf->pairs().size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
            {
             b_has_coord=true;

             const int state2 = this->wf->pairs()[j].GetState();
             const int state2_grp = co.GetSubgroup(state2);

             if( state2_grp==alt_state_group )
              {
               return true;
              }
            }
          }
        }
      }
     else
      {
       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         alt_has_coord=true;
         const int alt_state = it4->second;
    
         // »щем такое состо€ние...
         const lem::Container::size_type n2 = this->wf->pairs().size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
            {
             b_has_coord=true;
             if( this->wf->pairs()[j].GetState()==alt_state )
              {
               return true;
              }
            }
          }
        }
      }
    }

   return !alt_has_coord || !b_has_coord;
  }
 else
  {
   if( use_export )
    {
     std::pair<II4,II4> p4 = alt_coords.equal_range(id_coord0);

     if( condition.for_group )
      {
       const GramCoord &c = sg.coords()[ id_coord0 ];

       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         const int alt_state = it4->second;
         const int alt_state_group = c.GetSubgroup(alt_state);
    
         const lem::Container::size_type n2 = this->export_coords.size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->export_coords[j].GetCoord().GetIndex() )
            {
             const int state2 = this->export_coords[j].GetState();
             const int state2_grp = c.GetSubgroup(state2);

             if( state2_grp==alt_state_group )
              {
               // нашли соответствие.
               return false;
              }
            }
          }
        }
      }
     else
      {
       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         const int alt_state = it4->second;
    
         // »щем такое состо€ние...
         const lem::Container::size_type n2 = this->export_coords.size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->export_coords[j].GetCoord().GetIndex() )
            {
             if( this->export_coords[j].GetState()==alt_state )
              {
               // нашли соответствие.
               return false;
              }
            }
          }
        }
      }
    }
   else
    {
     std::pair<II4,II4> p4 = alt_coords.equal_range(id_coord0);

     if( condition.for_group )
      {
       const GramCoord &c = sg.coords()[ id_coord0 ];

       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         const int alt_state = it4->second;
         const int alt_state_group = c.GetSubgroup(alt_state);
    
         const lem::Container::size_type n2 = this->wf->pairs().size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
            {
             const int state2_grp = c.GetSubgroup(this->wf->pairs()[j].GetState());
             if( state2_grp==alt_state_group )
              {
               return false;
              }
            }
          }
        }
      }
     else
      {
       for( II4 it4=p4.first; it4!=p4.second; ++it4 )
        {
         const int alt_state = it4->second;
    
         // »щем такое состо€ние...
         const lem::Container::size_type n2 = this->wf->pairs().size();
         for( lem::Container::size_type j=0; j<n2; ++j )
          {
           if( id_coord1 == this->wf->pairs()[j].GetCoord().GetIndex() )
            {
             if( this->wf->pairs()[j].GetState()==alt_state )
              {
               return false;
              }
            }
          }
        }
      }
    }

   return true;
  }

 return false;
}


const Solarix::Word_Form* BackTraceItem::FindNode( const lem::UCString & name ) const
{
 for( lem::Container::size_type i=0; i<export_nodes.size(); ++i )
  if( name == * export_nodes[i].first )
   return export_nodes[i].second;

 return NULL;
}


const Solarix::Word_Form* BackTraceItem::GetSingleRootNode() const
{
 LEM_CHECKIT_Z( beg_token==end_token );

 return wf==NULL ? beg_token->GetWordform() : wf;
}
