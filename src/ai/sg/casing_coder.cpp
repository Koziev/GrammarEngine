// -----------------------------------------------------------------------------
// File CASING_CODER.CPP
//
// (c) by Elijah Koziev
//
// -----------------------------------------------------------------------------
//
// CD->06.04.2010
// LC->09.06.2011
// --------------

#include <lem/fstring.h>
#include <lem/Ucs4ToWideString.h>
#include <lem/WideStringUcs4.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/GG_CharOperations.h>
#include <lem/solarix/GG_CharOperation.h>
#include <lem/solarix/LanguageUsage.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/casing_coder.h>

using namespace lem;
using namespace Solarix;


CasingCoder::CasingCoder( SynGram &sg )
 : SG(sg)
{
 default_xlat = new XLAT();
 default_xlat->use_unicode = true;

 GraphGram &gg = sg.GetDict().GetGraphGram();
 LexicalAutomat &la = sg.GetDict().GetLexAuto();

 Lower=UNKNOWN; FirstCapitalized=UNKNOWN; Upper=UNKNOWN; EachLexemCapitalized=UNKNOWN;
 UnknownEntries_ekey=UNKNOWN;

 icoord_casing = sg.FindCoord( L"CharCasing" ).GetIndex();

 if( icoord_casing!=UNKNOWN )
 {
  const Solarix::GramCoord &c = sg.coords()[icoord_casing];
  Lower = c.FindState( L"Lower" );
  FirstCapitalized = c.FindState(L"FirstCapitalized");
  Upper = c.FindState(L"Upper");
  EachLexemCapitalized = c.FindState(L"EachLexemCapitalized");
  UnknownEntries_ekey = la.GetUnknownEntryKey();


// ------
//lem::FString msg = lem::format_str( "icoord_casing=%d Lower=%d FirstCapitalized=%d Upper=%d", icoord_casing, Lower, FirstCapitalized, Upper );
//MessageBox( NULL, msg.c_str(), "DEBUG-2", MB_OK );
// ------
 }

 // Определим языки вывода по-умолчанию
 sg.GetLanguageUsage().GetOutputLanguages(default_xlat->id_langs);
 
 // Для каждого языка смотрим имена таблиц для перевода в верхний и нижний регистры.
 for( lem::Container::size_type i=0; i<default_xlat->id_langs.size(); ++i )
  {
   const int id_lang = default_xlat->id_langs[i];
   const SG_Language &lang = sg.languages()[id_lang];

   const int iparam_l = lang.FindParam( L"LowerCase", 0 );
   if( iparam_l!=UNKNOWN )
    {
     const lem::UFString &xlat_name = lang.params[iparam_l]->values.front();
     const GG_CharOperation *xlat = gg.GetCharOperations()[xlat_name.c_str()];
     default_xlat->lower_xlat.push_back(xlat);
    }

   const int iparam_u = lang.FindParam( L"UpperCase", 0 );
   if( iparam_u!=UNKNOWN )
    {
     const lem::UFString &xlat_name = lang.params[iparam_u]->GetValue();
     const GG_CharOperation *xlat = gg.GetCharOperations()[xlat_name.c_str()];
     default_xlat->upper_xlat.push_back(xlat);
    }
  }

 if( !default_xlat->upper_xlat.empty() && !default_xlat->lower_xlat.empty() )
  default_xlat->use_unicode = false;

 for( lem::Container::size_type i=0; i<default_xlat->id_langs.size(); ++i )
  lang2xlat.insert( std::make_pair( default_xlat->id_langs[i], default_xlat ) );

 return;
}


CasingCoder::~CasingCoder(void)
{
 lem_rub_off(default_xlat);

 for( lem::Container::size_type i=0; i<xlats.size(); ++i )
  delete xlats[i];

 xlats.clear();
 lang2xlat.clear();

 return;
}


const CasingCoder::XLAT * CasingCoder::GetXLAT( int ekey )
{
 if( ekey==UNKNOWN || ekey==UnknownEntries_ekey )
  {
   return default_xlat;
  }

 const Solarix::SG_Entry &e = SG.GetEntry(ekey);
 const int id_class = e.GetClass();
 if( id_class!=UNKNOWN )
  {
   const SG_Class &c = SG.GetClass(id_class);
   const int id_lang = c.GetLanguage();

   if( id_lang!=UNKNOWN )
    {
     #if defined LEM_THREADS
     lem::Process::RWU_ReaderGuard rlock(cs);
     #endif
  
     std::map<int,XLAT*>::const_iterator it = lang2xlat.find(id_lang);
     if( it==lang2xlat.end() )
      {
       #if defined LEM_THREADS
       lem::Process::RWU_WriterGuard wlock(rlock);
       #endif
  
       XLAT *xlat = new XLAT;
       xlat->id_langs.push_back(id_lang);
       xlat->use_unicode = true;
  
       xlats.push_back(xlat);
       lang2xlat.insert( std::make_pair(id_lang,xlat) );
  
       const SG_Language &lang = SG.languages()[id_lang];
  
       const int iparam_l = lang.FindParam( L"LowerCase", 0 );
       if( iparam_l!=UNKNOWN )
        {
         const lem::UFString &xlat_name = lang.params[iparam_l]->values.front();
         const GG_CharOperation *xlat_op = SG.GetDict().GetGraphGram().GetCharOperations()[xlat_name.c_str()];
         xlat->lower_xlat.push_back(xlat_op);
        }
  
       const int iparam_u = lang.FindParam( L"UpperCase", 0 );
       if( iparam_u!=UNKNOWN )
        {
         const lem::UFString &xlat_name = lang.params[iparam_u]->values.front();
         const GG_CharOperation *xlat_op = SG.GetDict().GetGraphGram().GetCharOperations()[xlat_name.c_str()];
         xlat->upper_xlat.push_back(xlat_op);
        }
  
       if( !xlat->upper_xlat.empty() && !xlat->lower_xlat.empty() )
        xlat->use_unicode = false;
  
       return xlat;
      }
     else 
      {
       return it->second;
      }
    }
  }

 return default_xlat;
}


int CasingCoder::x( int i ) const
{
 if( i==Lower ) return 0;
 if( i==FirstCapitalized ) return 1;
 if( i==Upper ) return 2;
 if( i==EachLexemCapitalized ) return 3;
 return 0;
}


void CasingCoder::AddLower( const CasingCoder::XLAT *xlat, lem::uint32_t src_ch, lem::UFString &res ) const
{
 for( lem::Container::size_type i=0; i<xlat->lower_xlat.size(); ++i )
  {
   lem::uint32_t res_ch = xlat->lower_xlat[i]->Apply(src_ch);
   if( res_ch!=src_ch )
    {
     lem::Ucs4ToUCString x;
     x.Add(res_ch);
     res.Add_Dirty( x.ToString().c_str() );
     return;
    }
  }

 lem::Ucs4ToUCString x;
 x.Add(src_ch);
 res.Add_Dirty( x.ToString().c_str() );

 return;
}


void CasingCoder::AddUpper( const CasingCoder::XLAT *xlat, lem::uint32_t src_ch, lem::UFString &res ) const
{
 for( lem::Container::size_type i=0; i<xlat->upper_xlat.size(); ++i )
  {
   lem::uint32_t res_ch = xlat->upper_xlat[i]->Apply(src_ch);
   if( res_ch!=src_ch )
    {
     Ucs4ToUCString x;
     x.Add(res_ch);
     res.Add_Dirty( x.ToString().c_str() );
     return;
    }
  }

 Ucs4ToUCString x;
 x.Add(src_ch);
 res.Add_Dirty( x.ToString().c_str() );

 return;
}



void CasingCoder::RestoreCasing( lem::UFString &res, int ekey )
{
 if( (ekey!=UNKNOWN && ekey==UnknownEntries_ekey ) )
  return;

 const Solarix::SG_Entry &e = SG.GetEntry(ekey);
 const int icasing_state = e.GetAttrState(icoord_casing);
 if( icasing_state==UNKNOWN )
  {
   // если для языка, к которому относится словарная статья, есть пометка, что
   // по умолчанию слова пишутся маленькими, то преобразуем соответственно.
   
   const int id_class = e.GetClass();

   if( id_class!=UNKNOWN )
    {   
     #if defined LEM_THREADS
     lem::Process::RWU_ReaderGuard rlock(cs_class_default_casing);
     #endif
  
     std::map<int,int>::const_iterator it = class2casing.find(id_class);
     if( it==class2casing.end() )
      {
       #if defined LEM_THREADS
       lem::Process::RWU_WriterGuard wlock(rlock);
       #endif
  
       // К какому языку относится часть речи.
       const SG_Class & c = SG.GetClass(id_class);

       const int id_language = c.GetLanguage();

       if( id_language!=UNKNOWN )
        {
         const SG_Language & lang = SG.languages()[id_language];
      
         const int iparam = lang.FindParam( L"DefaultCasing" );
         if( iparam==UNKNOWN )
          {
           class2casing.insert( std::make_pair( id_class, UNKNOWN ) );
          }
         else
          {
           const SG_LanguageParam & p = lang.GetParam(iparam);
           lem::UCString pval = p.GetValue().c_str();
      
           if( icoord_casing!=UNKNOWN )
            {
             const Solarix::GramCoord &c = SG.coords()[icoord_casing];
             const int id_state = c.FindState(pval);
             class2casing.insert( std::make_pair( id_class, id_state ) );
      
             if( id_state!=UNKNOWN )
              RestoreCasing( id_state, res, ekey );
            }
           else
            {
             class2casing.insert( std::make_pair( id_class, UNKNOWN ) );
            }
          }
        }
      }
     else
      {
       const int default_casing = it->second;
       if( default_casing!=UNKNOWN )
        RestoreCasing( default_casing, res, ekey );
      }
    }
  }
 else
  {
   RestoreCasing( icasing_state, res, ekey );
  }

 return;
}

void CasingCoder::RestoreCasing( int external_casing_state, lem::UFString &res, int ekey )
{
 if( (ekey!=UNKNOWN && ekey==UnknownEntries_ekey ) )
  return;

 const XLAT *xlat = GetXLAT(ekey);

 switch( x(external_casing_state) )
 {
  case 1:
   {
    if( xlat->use_unicode )
     {
      res.to_Aa();
     }
    else
     {
      WideStringUcs4 src_enum( res.c_str() );
      lem::UFString out;
      out.reserve(res.length()+1);
      for( int i=0; ; ++i )
       {
        const lem::uint32_t src_ucs4 = src_enum.Fetch();
        if(!src_ucs4)
         break;

        if(i==0)
         AddUpper( xlat, src_ucs4, out );
        else
         AddLower( xlat, src_ucs4, out );
       }
      
      res = out;
     }

    break;
   }

  case 2:
   {
    if( xlat->use_unicode )
     {
      res.to_upper();
     }
    else
     {
      WideStringUcs4 src_enum( res.c_str() );
      lem::UFString out;
      out.reserve(res.length()+1);
      for(;;)
       {
        const lem::uint32_t src_ucs4 = src_enum.Fetch();
        if(!src_ucs4)
         break;

        AddUpper( xlat, src_ucs4, out );
       }
      
      res = out;
     }
 
    break;
   }

  case 3:
   {
    if( xlat->use_unicode )
     {
      Solarix::MakeEachLexemAa(res);
     }
    else
     {
      bool capitalize=true;
      
      WideStringUcs4 src_enum( res.c_str() );
      lem::UFString out;
      out.reserve(res.length()+1);
      for(;;)
       {
        const lem::uint32_t src_ucs4 = src_enum.Fetch();
        if(!src_ucs4)
         break;

        if( capitalize )
         {
          AddUpper( xlat, src_ucs4, out );
          capitalize=false;
         }
        else
         {
          AddLower( xlat, src_ucs4, out );

          if( src_ucs4==L' ' || src_ucs4==L'-' )
           capitalize=true;
         }
       }
      
      res = out;
     }

    break;
   }

  case 0:
  default:
   {
    if( xlat->use_unicode )
     {
      res.to_lower();
     }
    else
     {
      WideStringUcs4 src_enum( res.c_str() );
      lem::UFString out;
      out.reserve(res.length()+1);
      for(;;)
       {
        const lem::uint32_t src_ucs4 = src_enum.Fetch();
        if(!src_ucs4)
         break;

        AddLower( xlat, src_ucs4, out );
       }
      
      res = out;
     }

    break;
   }
 }

// res.subst_all( L" - ", L"-" );
// res.subst_all( L" ' ", L"'" );

 return;
}
