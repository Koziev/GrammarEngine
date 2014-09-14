#include <lem/solarix/sg_autom.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/ParadigmaMatcher.h>

using namespace Solarix;
using namespace lem;

ParadigmaMatcher::ParadigmaMatcher(void)
{
}

ParadigmaMatcher::ParadigmaMatcher( const lem::UFString & ConditionStr )
 : condition_str(ConditionStr)
{
 Init();
 return;
}

ParadigmaMatcher::ParadigmaMatcher( const ParadigmaMatcher &x )
 : condition_str(x.condition_str)
{
 Init();
 return;
}

void ParadigmaMatcher::operator=( const ParadigmaMatcher &x )
{
 condition_str = x.condition_str;
 Init();
 return;
}

void ParadigmaMatcher::Init(void)
{
 if( !condition_str.empty() )
  {
   condition = boost::wregex( condition_str.c_str(), boost::basic_regex<wchar_t>::icase );
  }

 return;
}


bool ParadigmaMatcher::Empty(void) const
{ return condition_str.empty(); }


bool ParadigmaMatcher::Match( const lem::UCString & entry_name ) const
{
 if( condition_str.empty() )
  return false;

 return regex_match( entry_name.c_str(), condition );
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void ParadigmaMatcher::LoadTxt( Macro_Parser &txtfile, int PartOfSpeech, SynGram& sg )
{
 lem::Iridium::BSourceState t = txtfile.tellp();

 condition_str = txtfile.read().GetFullStr();
 condition_str.strip_quotes();

 if( PartOfSpeech!=UNKNOWN )
  {
   const SG_Class &cls = sg.GetClass( PartOfSpeech );

   const int id_lang = cls.GetLanguage();
   if( id_lang!=UNKNOWN )
    {
     const SG_Language &lang = sg.languages()[id_lang];
     lang.SubstParadigmPattern(condition_str);
    }
  }

 try
  {
   condition = boost::wregex( condition_str.c_str(), boost::basic_regex<wchar_t>::icase );
  }
 catch(...)
  {
   lem::Iridium::Print_Error( t, txtfile );
   sg.GetIO().merr().printf( "Invalid syntax of regular expression %us", condition_str.c_str() );
   throw lem::E_ParserError();
  }
 
 return; 
}
#endif


lem::UFString ParadigmaMatcher::ToString(void) const
{
 return condition_str;
}
