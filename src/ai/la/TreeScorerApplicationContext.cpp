#include <lem/solarix/word_form.h>
#include <lem/solarix/TreeScorerApplicationContext.h>

using namespace Solarix;

void TreeScorerApplicationContext::StoreMatchedPosition( const Word_Form & token, int relative_position )
{
 #if LEM_DEBUGGING==1
 if( matched_token.find(&token)!=UNKNOWN )
  {
   if( matched_relative_position[ matched_token.find(&token) ] != relative_position )
    {
     LEM_STOPIT;
    }
  }

 if( matched_relative_position.find(relative_position)!=UNKNOWN )
  {
   LEM_CHECKIT_Z( matched_token[matched_relative_position.find(relative_position)] == &token );
  }
 #endif

 if( matched_token.find(&token)==UNKNOWN )
  {
   matched_token.push_back(&token);
   matched_relative_position.push_back(relative_position);
  }

 return;
}

bool TreeScorerApplicationContext::CheckRelativePositions() const
{
 for( lem::Container::size_type i=0; i<matched_token.size(); ++i )
  {
   for( lem::Container::size_type j=i+1; j<matched_token.size(); ++j )
    {
/*
     #if LEM_DEBUGGING==1
     lem::mout->printf( "matched_relative_position[%d]=%d token[i]=", i, matched_relative_position[i] );
     matched_token[i]->Print(*lem::mout,NULL,false);
     lem::mout->printf( " token_pos[i]=%d", matched_token[i]->GetOriginPos() );
     lem::mout->eol();

     lem::mout->printf( "matched_relative_position[%d]=%d token[j]=", j, matched_relative_position[j] );
     matched_token[j]->Print(*lem::mout,NULL,false);
     lem::mout->printf( " token_pos[j]=%d", matched_token[j]->GetOriginPos() );
     lem::mout->eol();
     #endif
*/

     if( matched_relative_position[i]>matched_relative_position[j] )
      {
       if( matched_token[i]->GetOriginPos()<=matched_token[j]->GetOriginPos() )
        return false;
      }
     else if( matched_relative_position[i]<matched_relative_position[j] )
      {
       if( matched_token[i]->GetOriginPos()>=matched_token[j]->GetOriginPos() )
        return false;
      }
     else
      {
       LEM_STOPIT;
      }
    }
  }

 return true;
}


bool TreeScorerApplicationContext::CheckPosition( const Word_Form & token, int relative_position ) const
{
 if( !matched_token.empty() )
  {
   for( lem::Container::size_type i=0; i<matched_token.size(); ++i )
    {
     if( relative_position>matched_relative_position[i] )
      {
       if( token.GetOriginPos()<matched_token[i]->GetOriginPos() )
        return false;
      }
     else if( relative_position<matched_relative_position[i] )
      {
       if( token.GetOriginPos()>matched_token[i]->GetOriginPos() )
        return false;
      }
    }
  }

 if( parent!=NULL )
  return parent->CheckPosition( token, relative_position );
 else
  return true;
}

