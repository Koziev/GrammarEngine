// -----------------------------------------------------------------------------
// File CP_CODE_PAGE.CPP
//
// (c) Elijah Koziev
//     Solarix Intellectronix project - http://www.solarix.ru
//
// Content:
// Класс CodeConverter - работа с кодовыми таблицами.
// Класс обеспечивает некоторый минимальный уровень сервиса - выполняет
// перекодировки символов ASCII<-->UNICODE и тому подобные атомарные действия.
//
// 27.04.2007 - UTF-8 console is initialized for Linux (if "LANG=xxx.UTF-8")
// 17.06.2007 - исправлен Memory Leak при переинициализации форматтера консоли.
// 13.07.2007 - в версии без LEM_UNICODE_EX сделана упрощенная реализация
//              процедуры Strip_Diactrices.
// 04.08.2008 - добавлен вызов u_cleanup() для чистки памяти в ICU.
// 02.12.2007 - макрос LEM_UNICODE_EX подключает только основные европейские 
//              кодировки, LEM_UNICODE_EX2 подключает все имеющиеся.
// -----------------------------------------------------------------------------
//
// CD->29.09.1997
// LC->14.06.2011
// --------------

#include <lem/config.h>

#include <lem/user_interface.h>
#include <lem/conversions.h>
#include <lem/console_streams.h>
#include <lem/system_config.h>
#include <lem/keyboard.h>

#if defined LEM_ICU
#include <icu/include/unicode/utypes.h>
#include <icu/include/unicode/ucnv.h>
#include <icu/include/unicode/uclean.h>
#endif

#include <lem/unicode.h>

#undef assert

using namespace std;
using namespace lem;


#if defined LEM_ICU && defined LEM_UNICODE_EX
#if defined(LEM_MSC) && defined(LEM_WINDOWS)
#if LEM_DEBUGGING==1
# pragma comment ( lib, "icuucd.lib" )
# pragma comment ( lib, "icuind.lib" )
# pragma comment ( lib, "icutud.lib" )
# pragma comment ( lib, "icudt.lib" )
# pragma comment ( lib, "icuiod.lib" )
//   # pragma comment ( lib, "iculed.lib" )
#else
# pragma comment ( lib, "icuuc.lib" )
# pragma comment ( lib, "icuin.lib" )
# pragma comment ( lib, "icutu.lib" )
# pragma comment ( lib, "icudt.lib" )
# pragma comment ( lib, "icuio.lib" )
//   # pragma comment ( lib, "icule.lib" )
#endif
#endif
#endif



static std::map< lem::CString /*name*/, int /*index*/ > cpname_2_index;

#define DECL_CP(Name) static CP_##Name * cp##Name=NULL;
#define DEL_CP(Name)  delete lem::cp##Name; lem::cp##Name=NULL;

// Глобальные переменные - для общего доступа к перекодировщикам.
CP_866    *lem::cp866 = NULL;
CP_847    *lem::cp847 = NULL;
CP_1250   *lem::cp1250 = NULL;
CP_1251   *lem::cp1251 = NULL;
CP_1252   *lem::cp1252 = NULL;
CP_8859_1 *lem::cp28591 = NULL;
Utf8CodeConverter *lem::cp_utf8 = NULL;

namespace lem {
    DECL_CP(437);
}

#if defined LEM_UNICODE_EX2
// Расширенная поддержка Юникода
namespace lem {
    DECL_CP(037);
    DECL_CP(424);
    DECL_CP(1006);
    DECL_CP(1026);
    DECL_CP(500);
    DECL_CP(737);
    DECL_CP(775);
    DECL_CP(850);
    DECL_CP(852);
    DECL_CP(855);
    DECL_CP(856);
    DECL_CP(857);
    DECL_CP(860);
    DECL_CP(861);
    DECL_CP(862);
    DECL_CP(863);
    DECL_CP(864);
    DECL_CP(865);
    DECL_CP(869);
    DECL_CP(874);
    DECL_CP(875);
    DECL_CP(1253);
    DECL_CP(1254);
    DECL_CP(1255);
    DECL_CP(1256);
    DECL_CP(1257);
    DECL_CP(1258);

    //DECL_CP(8859_1);
    DECL_CP(8859_2);
    DECL_CP(8859_3);
    DECL_CP(8859_4);
    DECL_CP(8859_5);
    DECL_CP(8859_6);
    DECL_CP(8859_7);
    DECL_CP(8859_8);
    DECL_CP(8859_9);
    DECL_CP(8859_10);
    DECL_CP(8859_11);
    DECL_CP(8859_13);
    DECL_CP(8859_14);
    DECL_CP(8859_15);
    DECL_CP(8859_16);

    static std::vector< CodeConverter* > encodings;
}
#elif defined LEM_UNICODE_EX
// Расширенная поддержка Юникода (европейские кодировки)
namespace lem {
    DECL_CP(852);
    DECL_CP(8859_2);
    DECL_CP(8859_3);
    DECL_CP(8859_5);
    DECL_CP(8859_10);
    DECL_CP(8859_13);
    DECL_CP(8859_15);

    static std::vector< CodeConverter* > encodings;
}
#endif


static lem::UI::User_Interface *curr_ui = NULL;

namespace lem
{
    struct CP_Initialized
    {
        CP_Initialized(void);
        ~CP_Initialized(void);
    };
}

CP_Initialized::CP_Initialized(void)
{
    lem::cp866 = new CP_866;
    lem::cp847 = new CP_847;
    lem::cp1250 = new CP_1250;
    lem::cp1251 = new CP_1251;
    lem::cp1252 = new CP_1252;
    lem::cp437 = new CP_437;
    lem::cp28591 = new CP_8859_1;
    lem::cp_utf8 = new Utf8CodeConverter;

    curr_ui = new lem::UI::User_Interface;

#if defined LEM_ICU
    UErrorCode status = U_ZERO_ERROR;

    /* Initialize ICU */
    u_init(&status);
    if (U_FAILURE(status))
    {
        fprintf(stderr, "Can not initialize ICU.  status = %s\n", u_errorName(status));
        exit(1);
    }

#endif

    lem::UI::get_UI().AllCodeConvertersInitialized();


#if defined LEM_WINDOWS && defined LEM_GUI && !defined LEM_FORMS

    mout = new lem::OFormatter(new StdTtyStream(&std::cout), true); // Поток вывода на консоль по умолчанию.
    merr = new lem::OFormatter(stderr); // Поток вывода на консоль сообщений об ошибках.

#else


#if defined LEM_CONSOLE
    // Консоль поддерживает прямой вывод UNICODE, без кодовых страниц
    // Однако в Win98 поддержка UNICODE ограничена.
    // В Linux поддержка юникодной консоли определяется по локали типа "en_US.UTF-8"
    if (lem::System_Config::SupportUnicodeConsole())
    {
#if defined LEM_WINDOWS && defined LEM_UNICODE_CONSOLE
        mout = new lem::OUFormatter(new TtyUcs2Stream(), true); // Поток вывода на консоль по умолчанию.
        merr = new lem::OUFormatter(new TtyUcs2Stream(), true); // Поток вывода на консоль сообщений об ошибках
#elif (defined LEM_LINUX || defined LEM_DARWIN) && defined LEM_UNICODE_CONSOLE
        mout = new lem::OUFormatter(new TtyUtf8Stream(), true); // Поток вывода на консоль по умолчанию.
        merr = new lem::OUFormatter(new TtyUtf8Stream(), true); // Поток вывода на консоль сообщений об ошибках
#else
        mout = new lem::OFormatter(new TtyStream(), true);
        merr = new OFormatter(new TtyStream(), true);
#endif
    }
    else
    {
        mout = new lem::OFormatter(new TtyStream(), true);
        merr = new lem::OFormatter(new TtyStream(), true);
    }
#else
    // Консоль невидима
#if defined LEM_WINDOWS
    lem::mout = new OFormatter(new BinaryFile(lem::Path(L"NUL"), false, true), true);
    lem::merr = new OFormatter(new BinaryFile(lem::Path(L"NUL"), false, true), true);
#else
    lem::mout = new OFormatter(new BinaryFile(lem::Path(NULL_DEVICE), false, true), true);
    lem::merr = new OFormatter(new BinaryFile(lem::Path(NULL_DEVICE), false, true), true);
#endif
#endif

#endif

#if defined LEM_CONSOLE
    lem::mkey = new lem::IKbdFormatter(lem::Ptr<KbdStream>(new KbdStream));
#endif

    mout->SetLocalCP(cp1251);
    merr->SetLocalCP(cp1251);

    mout->SetOutCP(&UI::get_UI().GetTtyCp());
    merr->SetOutCP(&UI::get_UI().GetTtyCp());

    lem::CodeConverter::Prepare_Factory();

    return;
}


CP_Initialized::~CP_Initialized(void)
{
    lem_rub_off(mout);
    lem_rub_off(merr);
    lem_rub_off(curr_ui);
#if defined LEM_CONSOLE
    lem_rub_off(lem::mkey);
#endif

    lem::CodeConverter::Delete_Static_Data();

    lem_rub_off(cp866);
    lem_rub_off(cp847);
    lem_rub_off(cp1250);
    lem_rub_off(cp1251);
    lem_rub_off(cp1252);
    lem_rub_off(cp437);
    lem_rub_off(cp28591);
    lem_rub_off(cp_utf8);

    //Transliterator::DeleteInstances();

#if defined LEM_UNICODE_EX
    DEL_CP(852);
    DEL_CP(8859_2);
    DEL_CP(8859_3);
    DEL_CP(8859_5);
    DEL_CP(8859_10);
    DEL_CP(8859_13);
    DEL_CP(8859_15);
#endif

#if defined LEM_UNICODE_EX2
    DEL_CP(037);
    DEL_CP(424);
    DEL_CP(1006);
    DEL_CP(1026);
    DEL_CP(500);
    DEL_CP(737);
    DEL_CP(775);
    DEL_CP(850);
    DEL_CP(855);
    DEL_CP(856);
    DEL_CP(857);
    DEL_CP(860);
    DEL_CP(861);
    DEL_CP(862);
    DEL_CP(863);
    DEL_CP(864);
    DEL_CP(865);
    DEL_CP(869);
    DEL_CP(874);
    DEL_CP(875);
    DEL_CP(1250);
    DEL_CP(1253);
    DEL_CP(1254);
    DEL_CP(1255);
    DEL_CP(1256);
    DEL_CP(1257);
    DEL_CP(1258);

    //DEL_CP(8859_1);
    DEL_CP(8859_4);
    DEL_CP(8859_6);
    DEL_CP(8859_7);
    DEL_CP(8859_8);
    DEL_CP(8859_9);
    DEL_CP(8859_11);
    DEL_CP(8859_14);
    DEL_CP(8859_16);
#endif

#if defined LEM_UNICODE_EX2
    for (Container::size_type i = 0; i < encodings.size(); i++)
        delete encodings[i];

    encodings.clear();
#endif

#if defined LEM_ICU
    u_cleanup();
#endif

    return;
}



#if defined LEM_WINDOWS
//static CP_Initialized cp_initialized;
#endif

lem::UI::User_Interface& lem::UI::get_UI(void) { return *curr_ui; }


/*
 ISO-8859-1  (Latin 1)     win CodeConverter: 28591
 ISO-8859-2  (Latin 2)     28592
 ISO-8859-3  (Latin 3)     28593
 ISO-8859-4  (Baltic)      28594
 ISO-8859-5  (Cyrillic)    28595
 ISO-8859-6  (Arabic)      28596
 ISO-8859-7  (Greek)       28597
 ISO-8859-8  (Hebrew)      28598
 ISO-8859-9  (Turkish)     28599
 ISO-8859-15 (Latin 9)     28605

*/



CodeConverter::CodeConverter(void)
{
    index = UNKNOWN;
}



CodeConverter::CodeConverter(const char *Encoding)
    : encoding(Encoding)
{
    LEM_CHECKIT_Z(Encoding);
    index = UNKNOWN;
    IFDEBUG(assert());
}



/************************************************************************
 Процедура создает и возвращает указатель на кодовую
 таблицу с указанным индексом. Реализованы только самые распространенные
 кодовые таблицы, в противном случае будет возвращен NULL.
*************************************************************************/

#define RET_CP(Name) if(!(cp##Name)) return (cp##Name=new CP_##Name()); else return cp##Name;

const CodeConverter* CodeConverter::getConverter(int index)
{
    switch (index)
    {
    case 847:   return cp847;
    case 866:   return cp866;
    case 1250:  return cp1250;
    case 1251:  return cp1251;
    case 1252:  return cp1252;
    case 437:   return cp437;
    case 28591: return cp28591;
    case 65000: return cp_utf8;

#if defined LEM_UNICODE_EX2

    case 37:   RET_CP(037);
    case 424:  RET_CP(424);
    case 1006: RET_CP(1006);
    case 1026: RET_CP(1026);
    case 500:  RET_CP(500);
    case 737:  RET_CP(737);
    case 775:  RET_CP(775);
    case 850:  RET_CP(850);
    case 852:  RET_CP(852);
    case 855:  RET_CP(855);
    case 856:  RET_CP(856);
    case 857:  RET_CP(857);
    case 860:  RET_CP(860);
    case 861:  RET_CP(861);
    case 862:  RET_CP(862);
    case 863:  RET_CP(863);
    case 864:  RET_CP(864);
    case 865:  RET_CP(865);
    case 869:  RET_CP(869);
    case 874:  RET_CP(874);
    case 875:  RET_CP(875);

    case 1253: RET_CP(1253);
    case 1254: RET_CP(1254);
    case 1255: RET_CP(1255);
    case 1256: RET_CP(1256);
    case 1257: RET_CP(1257);
    case 1258: RET_CP(1258);

    case 28592: RET_CP(8859_2);
    case 28593: RET_CP(8859_3);
    case 28594: RET_CP(8859_4);
    case 28595: RET_CP(8859_5);
    case 28596: RET_CP(8859_6);
    case 28597: RET_CP(8859_7);
    case 28598: RET_CP(8859_8);
    case 28599: RET_CP(8859_9);
    case 28600: RET_CP(8859_10);
    case 28601: RET_CP(8859_11);
        //  case 28602: RET_CP(8859_12);
    case 28603: RET_CP(8859_13);
    case 28604: RET_CP(8859_14);
    case 28605: RET_CP(8859_15);
    case 28606: RET_CP(8859_16);

#elif defined LEM_UNICODE_EX

    case 852:   RET_CP(852);
    case 28592: RET_CP(8859_2);
    case 28593: RET_CP(8859_3);
    case 28600: RET_CP(8859_10);
    case 28603: RET_CP(8859_13);
    case 28605: RET_CP(8859_15);

#endif
    }

    // Неизвестная кодовая страница
    throw E_UnknownCodepage(
        wstring(L"Unknown code page '") +
        to_wstr(index) +
        wstring(L"' in CodeConverter::getConverter")
    );
}


const CodeConverter* CodeConverter::getConverter(const char *Encoding)
{
    LEM_CHECKIT_Z(Encoding != NULL);

    int idx = UNKNOWN;

    if (Encoding && !!*Encoding)
    {
        try
        {
            idx = CP_Name_2_Index(Encoding);
            if (idx != UNKNOWN)
                return getConverter(idx);
        }
        catch (...)
        {
        }
    }

#if defined LEM_UNICODE_EX

    if (!*Encoding)
    {
        const CodeConverter *cc = &lem::UI::get_UI().GetSessionCp();
        return cc == NULL ? cp1250 : cc;
    }

    for (Container::size_type i = 0; i < encodings.size(); i++)
        if (encodings[i]->getEncodingName() == Encoding)
            return encodings[i];

#if defined LEM_ICU 
    encodings.push_back(new CodeConverter_ICU(Encoding));
    return encodings.back();
#else
    // Неизвестная кодовая страница
    throw E_UnknownCodepage(
        wstring(L"Unknown code page '") +
        to_wstr(Encoding) +
        wstring(L"' in CodeConverter::getConverter")
    );
#endif

#else
    // Неизвестная кодовая страница
    throw E_UnknownCodepage(
        wstring(L"Unknown code page '") +
        to_wstr(Encoding) +
        wstring(L"' in CodeConverter::getConverter")
    );
#endif
}



const CodeConverter* CodeConverter::getConverter(const lem::FString & Encoding)
{
    return CodeConverter::getConverter(Encoding.c_str());
}


const CodeConverter* CodeConverter::getConverter(const std::string & Encoding)
{
    return CodeConverter::getConverter(Encoding.c_str());
}

#if defined LEM_THREADS
lem::Process::RWU_Lock CodeConverter::cs_sgml;
#endif

void CodeConverter::CreateSGML(void)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_sgml);
#endif

    if (sgml_map == NULL)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        sgml_map = new SGML_MAP();

        const int n = DIM_A(sgml_list);

        for (int i = 0; i < n; i++)
        {
            UCString::hash_type h = lem_calc_string_hash(sgml_list[i].str);
            sgml_map->insert(std::make_pair(h, i));
        }
    }

    return;
}



void CodeConverter::Prepare_Factory(void)
{
    Prepare_CodeConverter_Names();
    return;
}


void CodeConverter::Add_CodeConverter_Name(const char *name, int index)
{
    LEM_CHECKIT_Z(name);
    LEM_CHECKIT_Z(index > 0);

    lem::CString s(name);
    s.to_lower();
    cpname_2_index.insert(std::make_pair(name, index));
}


#define CPNAME( Name, Index ) Add_CodeConverter_Name(Name,Index)


void CodeConverter::Prepare_CodeConverter_Names(void)
{
    CPNAME("cp866", 866); CPNAME("csibm866", 866); CPNAME("ibm866", 866);
    CPNAME("cskoi8r", 847), CPNAME("koi8-r", 847);
    // CPNAME( "ansi_x3.4-1968", 367 ), CPNAME( "ascii", 367 ), CPNAME( "cp367", 367 ), CPNAME( "csascii", 367 ), CPNAME( "ibm367", 367 ), CPNAME( "iso-ir-6", 367 ), CPNAME( "iso646-us", 367 ), CPNAME( "iso_646.irv:1991", 367 ), CPNAME( "us", 367 ), CPNAME( "us-ascii", 367 );
    CPNAME("cp437", 437); CPNAME("ibm437", 437);
    CPNAME("cp819", 28591); CPNAME("csisolatin1", 28591); CPNAME("ibm819", 28591); CPNAME("iso-8859-1", 28591); CPNAME("iso-ir-100", 28591); CPNAME("iso8859-1", 28591); CPNAME("iso_8859-1", 28591); CPNAME("8859-1", 28591); CPNAME("iso_8859-1:1987", 28591); CPNAME("l1", 28591); CPNAME("latin1", 28591); ; CPNAME("iso-latin-1", 28591);
    CPNAME("cp-1251", 1251); CPNAME("cp1251", 1251); CPNAME("ms-cyr", 1251); CPNAME("win-1251", 1251); CPNAME("win1251", 1251); CPNAME("windows-1251", 1251);
    CPNAME("cp-1250", 1250); CPNAME("cp1250", 1250); CPNAME("ms-ee", 1250); CPNAME("windows-1250", 1250);
    CPNAME("cp-1252", 1252), CPNAME("cp1252", 1252), CPNAME("ms-ansi", 1252), CPNAME("windows-1252", 1252);
    CPNAME("ascii", 1252), CPNAME("csascii", 1252), CPNAME("us", 1252), CPNAME("us-ascii", 1252);

#if defined LEM_UNICODE_EX
    CPNAME("cp852", 852); CPNAME("ibm852", 852);
    CPNAME("iso-8859-13", 28603); CPNAME("iso-ir-179", 28603); CPNAME("iso8859-13", 28603); CPNAME("iso_8859-13", 28603); CPNAME("l7", 28603); CPNAME("latin7", 28603);
    CPNAME("iso-8859-15", 28605); CPNAME("iso-ir-203", 28605); CPNAME("iso8859-15", 28605); CPNAME("iso_8859-15", 28605); CPNAME("iso_8859-15:1998", 28605);
    CPNAME("csisolatincyrillic", 28595); CPNAME("cyrillic", 28595); CPNAME("iso-8859-5", 28595); CPNAME("iso-ir-144", 28595); CPNAME("iso8859-5", 28595); CPNAME("iso_8859-5", 28595); CPNAME("iso_8859-5:1988", 28595);
    CPNAME("csisolatin2", 28592); CPNAME("iso-8859-2", 28592); CPNAME("iso-ir-101", 28592); CPNAME("iso8859-2", 28592); CPNAME("iso_8859-2", 28592); CPNAME("iso_8859-2:1987", 28592); CPNAME("l2", 28592); CPNAME("latin2", 28592);
    CPNAME("csisolatin3", 28593); CPNAME("iso-8859-3", 28593); CPNAME("iso-ir-109", 28593); CPNAME("iso8859-3", 28593); CPNAME("iso_8859-3", 28593); CPNAME("iso_8859-3:1988", 28593); CPNAME("l3", 28593); CPNAME("latin3", 28593);
    CPNAME("csisolatin6", 28600); CPNAME("iso-8859-10", 28600); CPNAME("iso-ir-157", 28600); CPNAME("iso8859-10", 28600); CPNAME("iso_8859-10", 28600); CPNAME("iso_8859-10:1992", 28600); CPNAME("l6", 28600); CPNAME("latin6", 28600);
#endif

#if defined LEM_UNICODE_EX2

    // "armscii-8"

    // "big-5", "big-five", "big5", "bigfive", "cn-big5", "csbig5"
    // big5-hkscs, big5_hkscs, big5hk, hkscs

    CPNAME("cp-1026", 1026); CPNAME("cp1026", 1026); CPNAME("ibm1026", 1026);
    CPNAME("cp-1133", 1133); CPNAME("cp1133", 1133); CPNAME("ibm1133", 1133);
    CPNAME("cp500", 500); CPNAME("ibm500", 500);
    CPNAME("cp850", 850); CPNAME("cspc850multilingual", 850); CPNAME("ibm850", 850);
    CPNAME("cp855", 855); CPNAME("ibm855", 855);
    CPNAME("cp857", 857); CPNAME("ibm857", 857);
    CPNAME("cp860", 860); CPNAME("ibm860", 860);
    CPNAME("cp861", 861); CPNAME("ibm861", 861);
    CPNAME("cp862", 862); CPNAME("ibm862", 862);
    CPNAME("cp863", 863); CPNAME("ibm863", 863);
    CPNAME("cp864", 864); CPNAME("ibm864", 864);
    CPNAME("cp865", 865); CPNAME("ibm865", 865);

    // CPNAME( "866u CPNAME( "cp866u

    CPNAME("cp869", 869); CPNAME("csibm869", 869); CPNAME("ibm869", 869);
    CPNAME("cp874", 874); CPNAME("cs874", 874); CPNAME("ibm874", 874); CPNAME("windows-874", 874);
    CPNAME("cp875", 875); CPNAME("ibm875", 875); CPNAME("windows-875", 875);
    CPNAME("cp950", 950); CPNAME("windows-950", 950);

    //CPNAME( "cseucjp, CPNAME( "euc-jp, CPNAME( "eucjp, CPNAME( "x-euc-jp
    //CPNAME( "cseuckr, CPNAME( "euc-kr, CPNAME( "euckr
    //CPNAME( "chinese, CPNAME( "csgb2312, CPNAME( "csiso58gb231280, CPNAME( "gb2312, CPNAME( "gb_2312-80, CPNAME( "iso-ir-58
    CPNAME("cp936", 936); CPNAME("gbk", 936); CPNAME("windows-936", 936);
    //CPNAME( "geo8-gov, CPNAME( "geostd8
    CPNAME("037", 37); CPNAME("cp037", 37); CPNAME("csibm037", 37); CPNAME("ibm037", 37);
    //CPNAME( "isiri-3342, CPNAME( "isiri3342

    //CPNAME( "csiso2022jp, CPNAME( "iso-2022-jp
    CPNAME("iso-8859-11", 28601); CPNAME("iso8859-11", 28601); CPNAME("iso_8859-11", 28601); CPNAME("iso_8859-11:1992", 28601); CPNAME("tactis", 28601); CPNAME("tis-620", 28601); CPNAME("tis620", 28601);
    CPNAME("iso-8859-14", 28604); CPNAME("iso-ir-199", 28604); CPNAME("iso8859-14", 28604); CPNAME("iso_8859-14", 28604); CPNAME("iso_8859-14:1998", 28604); CPNAME("l8", 28604); CPNAME("latin8", 28604);
    CPNAME("iso-8859-16", 28606); CPNAME("iso-ir-226", 28606); CPNAME("iso8859-16", 28606); CPNAME("iso_8859-16", 28606); CPNAME("iso_8859-16:2000", 28606);
    CPNAME("csisolatin4", 28594); CPNAME("iso-8859-4", 28594); CPNAME("iso-ir-110", 28594); CPNAME("iso8859-4", 28594); CPNAME("iso_8859-4", 28594); CPNAME("iso_8859-4:1988", 28594); CPNAME("l4", 28594); CPNAME("latin4", 28594);
    CPNAME("arabic", 28596); CPNAME("asmo-708", 28596); CPNAME("csisolatinarabic", 28596); CPNAME("ecma-114", 28596); CPNAME("iso-8859-6", 28596); CPNAME("iso-ir-127", 28596); CPNAME("iso8859-6", 28596); CPNAME("iso_8859-6", 28596); CPNAME("iso_8859-6:1987", 28596);
    CPNAME("csisolatingreek", 28597); CPNAME("ecma-118", 28597); CPNAME("elot_928", 28597); CPNAME("greek", 28597); CPNAME("greek8", 28597); CPNAME("iso-8859-7", 28597); CPNAME("iso-ir-126", 28597); CPNAME("iso8859-7", 28597); CPNAME("iso_8859-7", 28597); CPNAME("iso_8859-7:1987", 28597);
    CPNAME("csisolatinhebrew", 28598); CPNAME("hebrew", 28598); CPNAME("iso-8859-8", 28598); CPNAME("iso-ir-138", 28598); CPNAME("iso8859-8", 28598); CPNAME("iso_8859-8", 28598); CPNAME("iso_8859-8:1988", 28598);
    CPNAME("csisolatin5", 28599); CPNAME("iso-8859-9", 28599); CPNAME("iso-ir-148", 28599); CPNAME("iso8859-9", 28599); CPNAME("iso_8859-9", 28599); CPNAME("iso_8859-9:1989", 28599); CPNAME("l5", 28599); CPNAME("latin5", 28599);
    //CPNAME( "iso-ir-37, CPNAME( "koi-7

   // CPNAME( "koi8-u
   // CPNAME( "macarabic
   // CPNAME( "cmac, CPNAME( "macce, CPNAME( "maccentraleurope, CPNAME( "x-mac-ce
    //CPNAME( "maccroation
    //CPNAME( "maccyrillic, x-mac-cyrillic
    //CPNAME( "macgreek
    //CPNAME( "macgujarati
    //CPNAME( "machebrew
    //CPNAME( "macisland
    //CPNAME( "csmacintosh, CPNAME( "mac, CPNAME( "macintosh, CPNAME( "macroman
    //CPNAME( "macromania
    //CPNAME( "macthai
    //CPNAME( "macturkish
    //CPNAME( "csshiftjis, CPNAME( "ms_kanji, CPNAME( "s-jis, CPNAME( "shift-jis, CPNAME( "shift_jis, CPNAME( "sjis, CPNAME( "x-sjis
    //sys-int
    //CPNAME( "tscii
    //CPNAME( "csviscii, CPNAME( "viscii, CPNAME( "visc ii1.1-1

    CPNAME("cp-1253", 1253), CPNAME("cp1253", 1253), CPNAME("ms-greek", 1253), CPNAME("windows-1253", 1253);
    CPNAME("cp-1254", 1254), CPNAME("cp1254", 1254), CPNAME("ms-turk", 1254), CPNAME("windows-1254", 1254);
    CPNAME("cp-1255", 1255), CPNAME("cp1255", 1254), CPNAME("ms-hebr", 1255), CPNAME("windows-1255", 1255);
    CPNAME("cp-1256", 1256), CPNAME("cp1256", 1256), CPNAME("ms-arab", 1256), CPNAME("windows-1256", 1256);
    CPNAME("cp-1257", 1257), CPNAME("cp1257", 1257), CPNAME("winbaltrim", 1257), CPNAME("windows-1257", 1257);
    CPNAME("cp-1258", 1258), CPNAME("cp1258", 1258), CPNAME("windows-1258", 1258);
    CPNAME("cp-65001", 65001), CPNAME("cp65001", 65001), CPNAME("utf8", 65001), CPNAME("utf-8", 65001);

#endif

    return;
}


// ******************************************************************
// SGML-представление некоторых символов (в HTML это конструкции
// типа &nbsp; или &lt;) преобразуем в UNICODE-значение символа.
//
// На вход подаются символы начиная со следующего ПОСЛЕ '&' и ДО ';'
// ******************************************************************
wchar_t CodeConverter::Sgml_2_Char(const char *str)
{
    CreateSGML();

    LEM_CHECKIT_Z(sgml_map != NULL && !sgml_map->empty());
    LEM_CHECKIT_Z(str);

    UCString::hash_type h = lem::lem_calc_string_hash(str);

    pair<SGML_MAP_ITER, SGML_MAP_ITER> r = sgml_map->equal_range(h);

    for (SGML_MAP_ITER i = r.first; i != r.second; i++)
        if (!strcmp(sgml_list[i->second].str, str))
            return sgml_list[i->second].c;

    // Соответствие не найдено.
    return 0;
}


wchar_t CodeConverter::Sgml_2_Char(const FString& str)
{
    return CodeConverter::Sgml_2_Char(str.c_str());
}


int CodeConverter::CP_Name_2_Index(const char *name)
{
    LEM_CHECKIT_Z(name);

    // Часто бывает, что название кодовой таблицы - это просто ее индекс
    int icp = 0;
    if (to_int(name, &icp, 10))
        return icp;

    lem::CString n(name);
    n.to_lower();

    std::map<CString, int>::const_iterator i = cpname_2_index.find(n);

    if (i == cpname_2_index.end())
        return UNKNOWN;

    return i->second;
}



#if defined LEM_UNICODE_EX
// ***************************************************************
// Замена лигатур на пары символов
// ***************************************************************
bool CodeConverter::Normalize_Ligatures(wchar_t c, wchar_t &c1, wchar_t& c2)
{
    switch (c)
    {
    case 198:   c1 = L'A'; c2 = L'E'; break;
    case 230:   c1 = L'a'; c2 = L'e'; break;
    case 338:   c1 = L'O'; c2 = L'E'; break;
    case 339:   c1 = L'o'; c2 = L'e'; break;
    case 64256: c1 = L'f'; c2 = L'f'; break;
    case 64257: c1 = L'f'; c2 = L'i'; break;
    case 64258: c1 = L'f'; c2 = L'l'; break;
        //    case 64259: ffi
    case 64260: c1 = L'f'; c2 = L'l'; break;
    case 307:   c1 = L'i'; c2 = L'j'; break;
    case 64261: c1 = L's'; c2 = L's'; break;
    case 64262: c1 = L's'; c2 = L't'; break;
    case 223:   c1 = L's'; c2 = L's'; break;

    default: return false;
    }

    return true;
}



void CodeConverter::Normalize_Ligatures(wchar_t *str)
{
    LEM_CHECKIT_Z(str);

    int i = 0;
    wchar_t c1, c2;

    while (str[i])
    {
        wchar_t c = str[i];

        switch (c)
        {
        case 198:   c1 = L'A'; c2 = L'E'; break;
        case 230:   c1 = L'a'; c2 = L'e'; break;
        case 338:   c1 = L'O'; c2 = L'E'; break;
        case 339:   c1 = L'o'; c2 = L'e'; break;
        case 64256: c1 = L'f'; c2 = L'f'; break;
        case 64257: c1 = L'f'; c2 = L'i'; break;
        case 64258: c1 = L'f'; c2 = L'l'; break;
            //    case 64259: ffi
        case 64260: c1 = L'f'; c2 = L'l'; break;
        case 307:   c1 = L'i'; c2 = L'j'; break;
        case 64261: c1 = L's'; c2 = L's'; break;
        case 64262: c1 = L's'; c2 = L't'; break;
        case 223:   c1 = L's'; c2 = L's'; break;

        default:
            i++;
            continue;
        }

        str[i] = c1;

        // Сдвинем остаток строки вправо
        int j = i + 1;
        wchar_t cc = c2, tt;
        while (str[j])
        {
            tt = str[j];
            str[j] = cc;
            cc = tt;
            j++;
        }

        str[j] = cc;
        str[j + 1] = 0;

        break;
    }

    return;
}
#endif // defined LEM_UNICODE_EX


wchar_t CodeConverter::to_upper(wchar_t c)
{
#if defined LEM_UNICODE_EX
    if (
        c > 32 &&
        c < DIM_A(unicode_table)
        )
    {
        const int i = static_cast<lem::uint32_t>(0x0000ffff & c);
        if ((unicode_table[i].type & CP_Char_Flags::Lower) && unicode_table[i].casing)
            return unicode_table[i].casing;
    }

    return c;
#else
    return lem::to_uupper(c);
#endif
}

wchar_t CodeConverter::to_lower(wchar_t c)
{
#if defined LEM_UNICODE_EX
    if (
        c > 32 &&
        c < DIM_A(unicode_table)
        )
    {
        const int i = static_cast<lem::uint32_t>(0x0000ffff & c);
        if ((unicode_table[i].type & CP_Char_Flags::Upper) && unicode_table[i].casing)
            return unicode_table[i].casing;
    }

    return c;
#else
    return lem::to_ulower(c);
#endif
}


bool CodeConverter::is_upper(wchar_t c)
{
#if defined LEM_UNICODE_EX
    if (c > 32 && c < DIM_A(unicode_table))
    {
        const int i = static_cast<lem::uint32_t>(0x0000ffff & c);
        return (unicode_table[i].type & CP_Char_Flags::Upper) != 0;
    }

    return false;
#else
    return is_uupper(c);
#endif
}

bool CodeConverter::is_lower(wchar_t c)
{
#if defined LEM_UNICODE_EX
    if (c > 32 && c < DIM_A(unicode_table))
    {
        const int i = static_cast<lem::uint32_t>(0x0000ffff & c);
        return (unicode_table[i].type & CP_Char_Flags::Lower) != 0;
    }

    return false;
#else
    return is_ulower(c);
#endif
}

bool CodeConverter::is_udelim(wchar_t c)
{
#if defined LEM_UNICODE_EX
    if (c > 32 && c < DIM_A(unicode_table))
    {
        const int t = unicode_table[static_cast<lem::uint32_t>(0x0000ffff & c)].type;
        return (t&CP_Char_Flags::Delim) != 0;
    }

    return false;
#else
    return lem::is_udelim(c);
#endif
}


// Убирает диактрические значки у символов
wchar_t CodeConverter::Strip_Diaktrices(wchar_t c)
{
#if defined LEM_UNICODE_EX
    /*if( c==L'й' || c==L'Й' )
     return c;
    else*/ if (c < DIM_A(unicode_table))
    {
        wchar_t r = unicode_table[static_cast<lem::uint32_t>(0x0000ffff & c)].norm1;
        if (r)
            return r;
    }
#else

    // Упрощенная реализация

    switch (c)
    {
    case L'\x00c0':
    case L'\x00c1':
    case L'\x00c2':
    case L'\x00c3':
    case L'\x00c4':
    case L'\x00c5': c = L'A'; break;

    case L'\x00c8':
    case L'\x00c9':
    case L'\x00ca':
    case L'\x00cb': c = L'B'; break;

    case L'\x00cc':
    case L'\x00cd':
    case L'\x00ce':
    case L'\x00cf': c = L'I'; break;

    case L'\x00d1': c = L'N'; break;

    case L'\x00d2':
    case L'\x00d3':
    case L'\x00d4':
    case L'\x00d5':
    case L'\x00d6': c = L'O'; break;

    case L'\x00d9':
    case L'\x00da':
    case L'\x00db':
    case L'\x00dc': c = L'U'; break;

    case L'\x00e0':
    case L'\x00e1':
    case L'\x00e2':
    case L'\x00e3':
    case L'\x00e4':
    case L'\x00e5': c = L'a'; break;

    case L'\x00e7': c = L'c'; break;

    case L'\x00e8':
    case L'\x00e9':
    case L'\x00ea':
    case L'\x00eb': c = L'e'; break;

    case L'\x00ec':
    case L'\x00ed':
    case L'\x00ee':
    case L'\x00ef': c = L'f'; break;

    case L'\x00f1': c = L'n'; break;

    case L'\x00f2':
    case L'\x00f3':
    case L'\x00f4':
    case L'\x00f5':
    case L'\x00f6': c = L'o'; break;

    case L'\x00f9':
    case L'\x00fa':
    case L'\x00fb':
    case L'\x00fc': c = L'u'; break;

    case L'\x0451': c = L'\x0415'; break;
    case L'\x0401': c = L'\x0415'; break;

#if defined LEM_MSC && _MSC_VER<1300
        // ... MSVS6.5 дает ошибку на следующих двух case'ах
        // посему я перенес соответствующие перекодировки в if'ы
#else
    case L'\x0439': c = L'\x0418'; break;
    case L'\x0419': c = L'\x0418'; break;
#endif
    }

#if defined LEM_MSC && _MSC_VER<1300
    if (c == L'\x0439')
        c = L'\x0418';
    else if (c == L'\x0419')
        c = L'\x0418';
#endif

#endif

    return c;
}


void CodeConverter::Strip_Diaktrices(wchar_t *str)
{
    LEM_CHECKIT_Z(str);

    while (*str)
    {
        wchar_t c = *str;

#if defined LEM_UNICODE_EX
        /*if( c==L'й' || c==L'Й' )
         { str++; continue; }
        else*/ if (c < DIM_A(unicode_table))
    c = unicode_table[static_cast<lem::uint32_t>(0x0000ffff & c)].norm1;
#else
        c = Strip_Diaktrices(c);
#endif

        if (c)
            *str = c;

        str++;
    }

    return;
}


void CodeConverter::List_Supported_Encodings(OFormatter &out)
{
#if defined LEM_ICU

    int n = ucnv_countAvailable();
    UErrorCode err = U_ZERO_ERROR;

    out.printf("%vfEICU encodings%vn - %vfA%d%vn total:\n", n);

    for (int i = 0; i < n; i++)
    {
        const char *name = ucnv_getAvailableName(i);
        out.printf("%W40s", name);

        // И синонимы для данной кодировки
        int num_aliases = ucnv_countAliases(name, &err);

        for (int j = 0; j < num_aliases; ++j)
        {
            const char *alias = ucnv_getAlias(name, j, &err);

            if (!!strcmp(alias, name))
                out.printf("%W40s", alias);
        }
    }

#endif

    typedef std::map< lem::CString /*name*/, int /*index*/ >::const_iterator iter;

    out.printf("\n%vfESingle byte CodeConverters%vn - %vfA%d%vn total (with aliases):\n", cpname_2_index.size());

    {
        for (iter i = cpname_2_index.begin(); i != cpname_2_index.end(); i++)
            out.printf("%W20s", i->first.c_str());
    }

    return;
}


void CodeConverter::Get_Supported_Encodings(Collect<string> &res)
{
    typedef std::map< lem::CString /*name*/, int /*index*/ >::const_iterator iter;

    {
        for (iter i = cpname_2_index.begin(); i != cpname_2_index.end(); i++)
            res.push_back(i->first.c_str());
    }

#if defined LEM_ICU

    int n = ucnv_countAvailable();
    UErrorCode err = U_ZERO_ERROR;

    for (int i = 0; i < n; i++)
    {
        FString s = ucnv_getAvailableName(i);
        s.to_lower();

        if (std::find(res.begin(), res.end(), s.c_str()) == res.end())
            res.push_back(s.c_str());

        // И синонимы для данной кодировки
        int num_aliases = ucnv_countAliases(s.c_str(), &err);

        for (int j = 0; j < num_aliases; ++j)
        {
            const char *alias = ucnv_getAlias(s.c_str(), j, &err);

            FString s = alias;
            s.to_lower();

            if (std::find(res.begin(), res.end(), s.c_str()) == res.end())
                res.push_back(s.c_str());
        }
    }

#endif

    return;
}


const CodeConverter* CodeConverter::getDefaultConverter(void)
{
    return &lem::UI::get_UI().GetSessionCp();
}


void CodeConverter::Delete_Static_Data(void)
{
    lem_rub_off(sgml_map);
    return;
}


SBCodeConverter::SBCodeConverter(void) : CodeConverter()
{
    a2u = NULL;
}

SBCodeConverter::SBCodeConverter(int Index, const wchar_t *A2U)
    : CodeConverter()
{
    LEM_CHECKIT_Z(Index >= 0);

    index = Index;

    // Текстовое представление кодовой страницы синтезируем подходящим
    // для большинства случаев образом - как cpNNN.
    encoding = string("cp") + to_str(Index).c_str();

    a2u = A2U;

    if (a2u)
        for (int i = 0; i < 256; i++)
            //u2a.insert( std::make_pair( a2u[i], i ) );
        {
            u2a[i].u = a2u[i];
            u2a[i].a = i;
        }

    std::sort(u2a, u2a + 256);

    IFDEBUG(assert());
    return;
}

char SBCodeConverter::to_ascii(wchar_t ch) const
{
    IFDEBUG(Assert());
    //LEM_CHECKIT_Z( !u2a.empty() );
    //std::map<wchar_t,char>::const_iterator i = u2a.find(ch);
    //return i!=u2a.end() ? i->second : char(ch);

    int i0 = 0, i1 = 255;
    while ((i1 - i0) > 1)
    {
        wchar_t c0 = u2a[i0].u;
        wchar_t c1 = u2a[i1].u;

        if (c0 == ch) return u2a[i0].a;
        if (c1 == ch) return u2a[i1].a;

        int ix = (i1 + i0) / 2;
        wchar_t cx = u2a[ix].u;
        if (cx == ch)
            return u2a[ix].a;
        else if (cx > ch)
        {
            i1 = ix;
        }
        else
        {
            i0 = ix;
        }
    }

    if (u2a[i0].u == ch) return u2a[i0].a;
    if (u2a[i1].u == ch) return u2a[i1].a;

    return 0;
}



wchar_t* SBCodeConverter::to_unicode(const char *src, wchar_t *dst) const
{
    IFDEBUG(assert());
    LEM_CHECKIT_Z(src);
    LEM_CHECKIT_Z(dst);

    while (*src)
        *dst++ = to_unicode(*src++);

    *dst = 0;
    IFDEBUG(assert());
    return dst;
}

int SBCodeConverter::EstimateAsciiLen(int n) const
{
    LEM_CHECKIT_Z(n >= 0);
    return n;
}

char* SBCodeConverter::to_ascii(const wchar_t *src, char *dst) const
{
    IFDEBUG(assert());
    LEM_CHECKIT_Z(src);
    LEM_CHECKIT_Z(dst);

    while (*src)
        *dst++ = to_ascii(*src++);

    *dst = 0;
    IFDEBUG(assert());
    return dst;
}


int SBCodeConverter::to_ascii(wchar_t uch, char *dst) const
{
    *dst = to_ascii(uch);
    return 1;
}



bool SBCodeConverter::IsSingleByte(void) const
{
    return true;
}



const lem::CString lem::recode(
    const lem::CString &x,
    const CodeConverter &from,
    const CodeConverter &to
)
{
    wchar_t u[LEM_CSTRING_LEN + 1];
    from.to_unicode(x.c_str(), u);

    char a[LEM_CSTRING_LEN + 1];
    to.to_ascii(u, a);

    return lem::CString(a);
}




const FString lem::recode(
    const FString &x,
    const CodeConverter &from,
    const CodeConverter &to
)
{
    wchar_t *u = new wchar_t[x.length() + 1];
    from.to_unicode(x.c_str(), u);

    char *a = new char[x.length() + 1];
    to.to_ascii(u, a);
    delete[] u;
    FString res(a);
    delete[] a;
    return res;
}

