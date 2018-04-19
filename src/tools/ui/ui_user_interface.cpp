// -----------------------------------------------------------------------------
// File UI_USER_INTERFACE.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс User_Interface - параметры взаимодействия с пользователем.
// -----------------------------------------------------------------------------
//
// CD->22.11.2004
// LC->21.06.2010
// --------------

#include <lem/config.h>

#if defined LEM_WINDOWS && !defined LEM_MFC
 #include <windows.h>
#endif 

#if defined LEM_MFC
 #include <afx.h>
#endif

#if defined LEM_ICU
 #include <icu/include/unicode/locid.h>
#endif

#if defined LEM_DOT_NET
 #using <mscorlib.dll>
 using namespace System;
 using namespace System::Text;
#endif 

#include <lem/smart_pointers.h>
#include <lem/console_streams.h>
#include <lem/user_interface.h>
#include <lem/unicode.h>

using namespace lem;
using namespace lem::UI;

const char lem::UI::RUSSIAN_NAME[3]    = "ru";
const char lem::UI::ENGLISH_NAME[3]    = "en";
const char lem::UI::FRENCH_NAME[3]     = "fr";
const char lem::UI::SPANISH_NAME[3]    = "es";
const char lem::UI::PORTUGUESE_NAME[3] = "pt";
const char lem::UI::ITALIAN_NAME[3]    = "it";
const char lem::UI::POLISH_NAME[3]     = "pl";
const char lem::UI::GERMAN_NAME[3]     = "de";


static const wchar_t* umonth_ru[12] = { L"\x044f\x043d\x0432", L"\x0444\x0435\x0432", L"\x043c\x0430\x0440", L"\x0430\x043f\x0440", L"\x043c\x0430\x0439", L"\x0438\x044e\x043d", L"\x0438\x044e\x043b", L"\x0430\x0432\x0433", L"\x0441\x0435\x043d", L"\x043e\x043a\x0442", L"\x043d\x043e\x044f", L"\x0434\x0435\x043a" };
static const wchar_t* umonth1_ru[12] = { L"\x044f\x043d\x0432\x0430\x0440\x044c",
                                         L"\x0444\x0435\x0432\x0440\x0430\x043b\x044c",
                                         L"\x043c\x0430\x0440\x0442",
                                         L"\x0430\x043f\x0440\x0435\x043b\x044c",
                                         L"\x043c\x0430\x0439",
                                         L"\x0438\x044e\x043d\x044c",
                                         L"\x0438\x044e\x043b\x044c",
                                         L"\x0430\x0432\x0433\x0443\x0441\x0442",
                                         L"\x0441\x0435\x043d\x0442\x044f\x0431\x0440\x044c",
                                         L"\x043e\x043a\x0442\x044f\x0431\x0440\x044c",
                                         L"\x043d\x043e\x044f\x0431\x0440\x044c",
                                         L"\x0434\x0435\x043a\x0430\x0431\x0440\x044c" };


static const wchar_t* umonth_en[12] = { L"jan", L"feb", L"mar", L"apr", L"may",
                                           L"jun", L"jul", L"aug", L"sep", L"oct",
                                           L"nov", L"dec" };

static const wchar_t* umonth1_en[12] = { L"january", L"february", L"march", L"april",
                                            L"may", L"june", L"july", L"august",
                                            L"september", L"october", L"november",
                                            L"december" };

static const wchar_t* umonth_fr[12] = { L"jan", L"fev", L"mar", L"avr", L"mai",
                                           L"jun", L"jul", L"aut", L"sep", L"oct",
                                           L"nov", L"dec" };

static const wchar_t* umonth1_fr[12] = { L"janvier", L"f\xe9vrier", L"mars", L"avril",
                                            L"mai", L"juin", L"juillet", L"ao\xfbt",
                                            L"septembre", L"octobre", L"novembre",
                                            L"d\xe9cembre" };


User_Interface::User_Interface(void)
 : curr_lang(ENGLISH_NAME)
 , tty_cp( cp1250, null_deleter() )
 , session_cp( cp1250, null_deleter() )
 , src_cp( cp1250, null_deleter() )
{
 #if defined LEM_WINDOWS

  // КОНСОЛЬ
  int itty_cp = GetConsoleCP();

  if( itty_cp==0 )
   // оконная программа   
   itty_cp = 1250; 

  try
   {   
    tty_cp = boost::shared_ptr<CodeConverter>( const_cast<CodeConverter*>(CodeConverter::getConverter(itty_cp)), null_deleter() );
   }
  catch(...)
   {
    // Не удалось установить такую кодовую таблицу, поэтому выставим умолчальную.
    tty_cp = boost::shared_ptr<CodeConverter>( cp1250, null_deleter() );
   }

  // Системная кодовая таблица
  int isys_cp = GetACP();
  
  try
   {   
    session_cp = boost::shared_ptr<CodeConverter>( const_cast<CodeConverter*>(CodeConverter::getConverter(isys_cp)), null_deleter() );
   }
  catch(...)
   {
    // Не удалось установить такую кодовую таблицу, поэтому выставим умолчальную.
    session_cp = boost::shared_ptr<CodeConverter>( cp1250, null_deleter() );
   }

  // Устанавливаем язык для текущего сеанса
  const int ilang = GetUserDefaultLangID();
  const int lid = ilang & 0x03ff;

  switch( lid )
  { 
   case LANG_RUSSIAN: 
    curr_lang = RUSSIAN_NAME;
    break;

   case LANG_ENGLISH: 
    curr_lang = ENGLISH_NAME;
    break;

   case LANG_FRENCH: 
    curr_lang = FRENCH_NAME;
    break;

   default:
    {
     bool found=false;

     #if defined LEM_ICU
     // Попробуем подобрать локаль ICU по LCID

     LCID lcid = GetUserDefaultLCID();

     int32_t count;
     const Locale* list = 0;
     UnicodeString result;
     list = Locale::getAvailableLocales(count);
     for( int i=0; i<count; i++ )
      {
       if( list[i].getLCID() == lcid )
        {
         // Нашли!
         curr_lang = list[i].getBaseName();
         found = true;
         break;
        }  
      }
    
     #endif

     if( !found )
      {
       // используем английский язык по умолчанию
//       curr_lang = boost::shared_ptr<Language>( (Language*)&English, null_deleter() );
       curr_lang = ENGLISH_NAME;     
      }

     break;
    }

/*
   case LANG_GERMAN:  
   case LANG_ITALIAN: 
  case LANG_DANISH Danish 
  case LANG_CZECH Czech 
  case LANG_GREEK Greek 
  case LANG_SPANISH Spanish  
  case LANG_FINNISH Finnish 
  case LANG_JAPANESE Japanese 
  case LANG_CHINESE
  case LANG_HEBREW Hebrew 
  case LANG_HUNGARIAN Hungarian 
  case LANG_ICELANDIC Icelandic 
  case LANG_KOREAN Korean 
  case LANG_DUTCH Dutch 
  case LANG_NORWEGIAN Norwegian 
  case LANG_POLISH Polish 
  case LANG_PORTUGUESE Portuguese 
  case LANG_ROMANIAN Romanian 
  case LANG_CROATIAN Croatian 
  case LANG_SERBIAN Serbian 
  case LANG_SLOVAK Slovak 
  case LANG_ALBANIAN Albanian 
  case LANG_SWEDISH Swedish  
  case LANG_THAI Thai 
  case LANG_TURKISH Turkish  
  case LANG_URDU Urdu 
  case LANG_INDONESIAN Indonesian 
  case LANG_UKRAINIAN Ukrainian 
  case LANG_BELARUSIAN Belarusian 
  case LANG_SLOVENIAN Slovenian 
  case LANG_ESTONIAN Estonian 
  case LANG_LATVIAN Latvian 
  case LANG_LITHUANIAN Lithuanian 
  case LANG_FARSI Farsi 
  case LANG_VIETNAMESE Vietnamese 
  case LANG_ARMENIAN Armenian 
  case LANG_AFRIKAANS Afrikaans 
  case LANG_GEORGIAN Georgian 
  case LANG_HINDI Hindi 
  case LANG_MALAY Malay 
  case LANG_KAZAK Kazak 
  case LANG_KYRGYZ Kyrgyz 
  case LANG_SWAHILI Swahili 
  case LANG_UZBEK Uzbek 
  case LANG_TATAR Tatar 
*/
  }

  // Получим локаль ICU
  

 #elif defined LEM_UNIX

 const char *LANG = getenv( "LANG" );

 // English locale is used by default 
 FString lang("en");

 if( LANG!=NULL )
  {  
   lang = LANG;    
   if( lang.length()>2 )
    lang = left( lang, 2 );
    
   lang = lem::to_lower(lang); 
  }
 
 curr_lang = lang.c_str();

 // Retrieve the session codepage from LANG (e.q. ru_RU.KOI8-R)

 const int dot = lem::lem_find( LANG, '.' );
 if( dot==UNKNOWN )
  {
   tty_cp     = boost::shared_ptr<CodeConverter>( cp847, null_deleter() );
   session_cp = boost::shared_ptr<CodeConverter>( cp847, null_deleter() );
  }
 else
  {
   FString encoding( LANG+dot+1 );

   const int cp_index = (encoding.eqi("utf-8") || encoding.eqi("utf8") )? 65001 : lem::CodeConverter::CP_Name_2_Index( encoding.c_str() );

   if( cp_index==65001 )
    {
     tty_cp     = boost::shared_ptr<CodeConverter>( cp_utf8, null_deleter() );
     session_cp = boost::shared_ptr<CodeConverter>( cp_utf8, null_deleter() );
    }
   else
    {
     const lem::CodeConverter *cp = lem::CodeConverter::getConverter(cp_index);
     tty_cp     = boost::shared_ptr<CodeConverter>( (CodeConverter*)cp, null_deleter() );
     session_cp = boost::shared_ptr<CodeConverter>( (CodeConverter*)cp, null_deleter() );
    }
  }
  
 #elif defined LEM_DOS

 curr_lang = "en";
 tty_cp     = boost::shared_ptr<CodeConverter>( cp1250, null_deleter() );
 session_cp = boost::shared_ptr<CodeConverter>( cp1250, null_deleter() );

 #else

 curr_lang = "en";
 tty_cp     = boost::shared_ptr<CodeConverter>( cp1250, null_deleter() );
 session_cp = boost::shared_ptr<CodeConverter>( cp1250, null_deleter() );
   
 #endif

/* 
 #elif defined LEM_DOT_NET
 // Кодовая страница Windows для текущей консоли.
 int win_cp = Console::get_Out()->get_Encoding()->get_WindowsCodeConverter();

 switch( win_cp )
 {
  case 866:  tty_cp = boost::shared_ptr<CodeConverter>( new CP_866, true );
  case 1251: tty_cp = boost::shared_ptr<CodeConverter>( new CP_1251, true );
 };
 #endif
*/

 PresetFormats();
 return;
}


void User_Interface::PresetFormats(void)
{
 date_fmt = "dd-mmm-yyyy";
 ldate_fmt = "dd-Month-yyyy";
 time_fmt = "hh:mm:ss"; 


 #if defined LEM_WINDOWS

  // текущие параметры локали

  wchar_t lbuf[256];

  // разделитель полей в датах
  *lbuf=0;
  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SDATE, lbuf, sizeof(lbuf)/2 );
  wchar_t ds = *lbuf;
  if( !ds || ds==L'%' ) ds=L'.';
 

  // Краткое обозначение даты
  *lbuf=0;
  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_IDATE, lbuf, sizeof(lbuf)/2 );
  switch( *lbuf )
  {
   case L'0': date_fmt = "mm#dd#yyyy"; break;
   case L'1': date_fmt = "dd#mm#yyyy"; break;
   case L'2': date_fmt = "yyyy#mm#dd"; break;
  }

  // Длинное обозначение даты
  *lbuf=0;
  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_ILDATE, lbuf, sizeof(lbuf)/2 );
  switch( *lbuf )
  {
   case L'0': ldate_fmt = "Month#dd#yyyy"; break;
   case L'1': ldate_fmt = "dd#Month#yyyy"; break;
   case L'2': ldate_fmt = "yyyy#Month#dd"; break;
  }

  date_fmt.subst_all( '#', (char)ds );
  ldate_fmt.subst_all( '#', (char)ds );

  // Обозначение месяцев
  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME1,  lbuf, sizeof(lbuf)/2 );
  umonth[0] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME2,  lbuf, sizeof(lbuf)/2 ); 
  umonth[1] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME3,  lbuf, sizeof(lbuf)/2 ); 
  umonth[2] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME4,  lbuf, sizeof(lbuf)/2 ); 
  umonth[3] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME5,  lbuf, sizeof(lbuf)/2 ); 
  umonth[4] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME6,  lbuf, sizeof(lbuf)/2 ); 
  umonth[5] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME7,  lbuf, sizeof(lbuf)/2 ); 
  umonth[6] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME8,  lbuf, sizeof(lbuf)/2 ); 
  umonth[7] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME9,  lbuf, sizeof(lbuf)/2 ); 
  umonth[8] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME10, lbuf, sizeof(lbuf)/2 ); 
  umonth[9] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME11, lbuf, sizeof(lbuf)/2 ); 
  umonth[10] = lbuf;

  GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME12, lbuf, sizeof(lbuf)/2 ); 
  umonth[11] = lbuf;

 #else

  PresetMonthNames();  
 
 #endif


 return;
}


void User_Interface::PresetMonthNames(void)
{
 if( IsRussian() )
  {
   for( int i=0; i<12; i++ )
    {
     umonth[i] = umonth_ru[i];
     umonth1[i] = umonth1_ru[i];
    }
  }
 else if( IsFrench() )
  {
   for( int i=0; i<12; i++ )
    {
     umonth[i] = umonth_fr[i];
     umonth1[i] = umonth1_fr[i];
    }
  }
 else
  {
   for( int i=0; i<12; i++ )
    {
     umonth[i] = umonth_en[i];
     umonth1[i] = umonth1_en[i];
    }
  }

 return;
}

void User_Interface::AllCodeConvertersInitialized(void)
{
 PresetAsciiMonthNames();
}


void User_Interface::PresetAsciiMonthNames(void)
{
 for( size_t i=0; i<DIM_A(umonth); i++ )
  {
   month[i]  = to_ascii( umonth[i],  &*session_cp );
   month1[i] = to_ascii( umonth1[i], &*session_cp );
  }

 return;
}



int User_Interface::FindMonth( const FString &m ) const
{
 return FindMonth( to_unicode(m) );
}


int User_Interface::FindMonth( const char *m ) const
{
 return FindMonth(FString(m));
}

int User_Interface::FindMonth( const UFString &m ) const
{
 for( size_t i=0; i<DIM_A(umonth); i++ )
  if( umonth_ru[i]==m || umonth_en[i]==m || umonth_fr[i]==m )
   return i;

 return UNKNOWN;
}

int User_Interface::FindMonth( const wchar_t *m ) const
{
 for( size_t i=0; i<DIM_A(umonth); i++ )
  if( umonth_ru[i]==m || umonth_en[i]==m || umonth_fr[i]==m)
   return i;

 return UNKNOWN;
}


void User_Interface::SetCurrLang( const char* Lang )
{
//lem::Shell::Message( Lang ); 

 curr_lang = Lang;

 // Устанавливаем запрошенную кодировку для консольного потока.
 //mout.SetOutCP( &(Lang.get_Code_Page()) );

 PresetMonthNames(); 
 PresetAsciiMonthNames();

 return;
}

void User_Interface::SetTtyCp( const boost::shared_ptr<CodeConverter> &cp )
{
 tty_cp = cp;
 mout->SetOutCP( &*cp );
}

void User_Interface::SetSessionCp( const boost::shared_ptr<CodeConverter> &cp )
{
 session_cp = cp;
}


void User_Interface::SetSrcCp( const boost::shared_ptr<CodeConverter> &cp )
{
 src_cp = cp;
}


void User_Interface::AvailableLocales( OFormatter &out )
{
 #if defined LEM_ICU
 /*
   int32_t count;
   const Locale* list = 0;
   UnicodeString result;
   list = Locale::getAvailableLocales(count);

   if( get_UI().Is_Russian() )
    mout->printf( "\nДопустимые локали - %d шт.:", count );
   else
    mout->printf( "\nAvailable locales - %d total:\n", count );

   for (int i = 0; i < count; i++)
    {
     out.printf( "%vfE%W20s%vn", list[i].getBaseName() );
//   out.printf( "lang=%vfE%s%vn ",    list[i].getLanguage() );
//   out.printf( "country=%vfE%s%vn ", list[i].getCountry() );
//   out.printf( "script=%vfE%s%vn ",  list[i].getScript() );
//   out.eol();
    }

  out.printf( "%vn\n\n" );  
 */
 #endif

 out.printf( "\nAvailable locales - %vfEen ru fr%vn\n" );

 return;
}


bool User_Interface::Eq( const char *Code ) const
{
 return memcmp( curr_lang.c_str(), Code, strlen(Code) )==0;
}

// ************************************************************
// Show some brief info about current UI settings, eg. locale.
// ************************************************************
void User_Interface::PrintInfo( OFormatter &dst ) const
{
 #if defined LEM_CONSOLE
 const char type[]="console";
 #elif defined LEM_GUI
 const char type[]="GUI";
 #else
 const char type[]="unknown";
 #endif

 dst.printf(
            "UI settings: type=%s lang=%s session_cp=%s tty_cp=%s date_fmt=%s time_fmt=%s\n"
            , type
            , GetCurrLang().c_str()
            , GetSessionCp().getEncodingName().c_str()
            , GetTtyCp().getEncodingName().c_str()
            , GetDateFmt().c_str()
            , GetTimeFmt().c_str()
           );

 return;  
}


lem::FString User_Interface::GetEncodingNameForLang( int langid )
{
 #if defined LEM_WINDOWS
 char buf[64]="";
 if( GetLocaleInfoA( MAKELCID( langid, SORT_DEFAULT ), LOCALE_IDEFAULTANSICODEPAGE, buf, sizeof(buf)/sizeof(*buf) )!=0 )
  {
   return lem::FString(buf);
  } 
 #endif

 const int lid = langid & 0x03ff;

 lem::FString encoding;
 switch( lid )
 { 
  case 0x19 /*LANG_RUSSIAN*/: encoding="cp1251"; break;
//  case LANG_ENGLISH: encoding=L"cp1250"; break;
//  case LANG_FRENCH:  encoding=L"cp1250"; break;
  default:           encoding="cp1250"; break;
 }

 return encoding;
}

const lem::CodeConverter* User_Interface::GetEncodingForLang( int langid )
{
 return lem::CodeConverter::getConverter( GetEncodingNameForLang(langid).c_str() );
}
