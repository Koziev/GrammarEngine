#ifndef LEM_PATH__H
#define LEM_PATH__H
#pragma once

// File PATH.H
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
// Служебные операции над файлами и файловыми путями. Так как к огромному
// сожалению BOOST-библиотека Filesystem не поддерживает операции с UNICODE
// именами файлов (по соображениям платформонезависимости), приходится
// строить и использовать свою параллельную реализацию аналогичных классов.
//
// 24.02.2006 - часть static-функций класса Path переделана в обычные
//              функции-члены. Также - ряд файловых операций реализована
//              через WinAPI функции (для эффективности).
//
// 04.09.2007 - новый метод IsFolderEmpty() определяет наличие в каталоге файлов
//              или подкаталогов.
//
// 06.10.2007 - добавлен метод GetDiskFreeSpace
// 15.11.2007 - добавлен метод GetAttr 
// 21.03.2008 - добавлена привязка к wxFileName
// 21.03.2008 - добавлена процедура swap
// 21.03.2008 - добавлена конверсия с boost::filesystem::path/wpath
// 03.04.2018 - рефакторинг с использованием фич C++11
// -----------------------------------------------------------------------------
//
// CD->01.05.1995
// LC->03.04.2018
// --------------

#include <lem/config.h>

#if defined LEM_BSD
#include <sys/param.h>
#endif

#if defined LEM_LINUX
#include <limits.h>
#endif

#if defined LEM_WINDOWS
#include <windows.h>
#endif

#include <cstdio>
#include <vector>
#include <lem/fstring.h>

#if defined LEM_USE_BOOST_FILESYSTEM
#include <boost/filesystem/path.hpp>
#endif

//#include <boost/date_time/posix_time/posix_time_types.hpp>

#undef CopyFile
//#undef GetDiskFreeSpace

namespace lem
{
#define uch wchar_t

    // *********************************************
    // Имена виртуальных потоков ввода-вывода.
    // *********************************************
    extern const char NULL_DEVICE[]; // Нуль-драйвер
    extern const char TTY_DEVICE[];  // Терминал
    extern const char ERR_DEVICE[];  // Сообщения об ошибках
    extern const char PRN_DEVICE[];  // Принтер
    extern const char KBD_DEVICE[];  // Клавиатура
    extern const char CD_DEVICE[];   // Компакт-диск

    extern size_t get_file_size(FILE *file);

    extern bool is_binary_file(FILE *File);

    extern FILE *fopen(const uch *filename, const char *mode);

    /****************************************************************************
    *                                                                           *
    *       Definitions for Macintosh                                           *
    *                                                                           *
    ****************************************************************************/

#ifdef LEM_MAC

    /* Maximum path length and filename length.  Note that although in theory
       Mac paths are limited to 254 characters in length, the way HPACK does it
      allows an unlimited path length - 512 seems like a safe upper limit */
#define LEM_MAX_PATH  512
#define LEM_MAX_FILENAME 31

      /* The drive separator (a logical colon) */
#define LEM_DRIVE_DELIMITER_CHAR   ':'
#define SOL_DRIVE_DELIMITER_CHAR   L':'

/* The directory seperator (a logical slash). */
#define LEM_DIRECTORY_DELIMITER_CHAR '\x01'
#define SOL_DIRECTORY_DELIMITER_CHAR L'\x01'

#define LEM_IS_DIRECTORY_DELIMITER_CHAR(ch) (ch==LEM_DIRECTORY_DELIMITER_CHAR)
#define SOL_IS_DIRECTORY_DELIMITER_CHAR(ch) (ch==SOL_DIRECTORY_DELIMITER_CHAR)

/* The extention separator (a logical dot) */
#define LEM_EXTENTION_DELIMITER_CHAR '.'
#define SOL_EXTENTION_DELIMITER_CHAR L'.'

/* The seperator for paths in environment variables */
#define LEM_PATH_SEPARATOR ';'
#define SOL_PATH_SEPARATOR L';'

/* Whether spaces are legal in filenames */
#define LEM_PATH_SPACE_OK  true

// Неприемлимые символы в файловых путях.
#define LEM_PATH_BAD_CHARS   ":"
#define SOL_PATH_BAD_CHARS   ":"

#endif /* LEM_MAC */

/****************************************************************************
*                                                                           *
*       Definitions for MSDOS & Windows                                     *
*                                                                           *
****************************************************************************/

#if defined LEM_DOS || defined LEM_WINDOWS

#if defined LEM_DOS
    extern long lem_get_disk_free_space(int disk);
#endif

    /* Maximum DOS path length (63 bytes + null terminator) and filename length
       (8.3 + null delimiter) */

#define LEM_MAX_PATH     _MAX_PATH //64
#define LEM_MAX_FILENAME _MAX_FNAME // 13 // 8.3 + null terminator

       /* The drive separator (a logical colon) */
#define LEM_DRIVE_DELIMITER_CHAR  ':'
#define SOL_DRIVE_DELIMITER_CHAR  L':'

/* The directory seperator (a logical slash). */
#define LEM_DIRECTORY_DELIMITER_CHAR '\\'
#define SOL_DIRECTORY_DELIMITER_CHAR L'\\'

#define LEM_IS_DIRECTORY_DELIMITER_CHAR(ch) (ch==LEM_DIRECTORY_DELIMITER_CHAR || \
                                              ch=='\\')

#define SOL_IS_DIRECTORY_DELIMITER_CHAR(ch) (ch==SOL_DIRECTORY_DELIMITER_CHAR || \
                                               ch==L'/')

  /* The extention separator (a logical dot) */
#define LEM_EXTENTION_DELIMITER_CHAR '.'
#define SOL_EXTENTION_DELIMITER_CHAR L'.'

/* The seperator for paths in environment variables */
#define LEM_PATH_SEPARATOR ';'
#define SOL_PATH_SEPARATOR L';'

/* Whether spaces are legal in filenames */
#define LEM_PATH_SPACE_OK false

// Неприемлимые символы в файловых путях.
#define LEM_PATH_BAD_CHARS  " \"*+,/:;<=>?[\\]|"

// Current directory name
#define LEM_CUR_DIR_NAME ".\\"

// One level up directory
#define LEM_UP_DIR_NAME "..\\"

#endif /* LEM_DOS || LEM_WINDOWS */

/****************************************************************************
*                                                                           *
*       Definitions for UNIX                                                *
*                                                                           *
****************************************************************************/

#if defined LEM_UNIX

// *****************************************
// Declarations for LINUX  (UNIX)
// *****************************************
#if defined LEM_LINUX || defined LEM_BSD

#if defined LEM_LINUX
#include <linux/limits.h>
#elif defined LEM_BSD
#include <limits.h>
#endif     

#define LEM_MAX_PATH  PATH_MAX
#define LEM_MAX_FILENAME NAME_MAX

/* The drive separator (a logical colon) is never used*/
#define LEM_DRIVE_DELIMITER_CHAR  0x01
#define SOL_DRIVE_DELIMITER_CHAR  L'0x01'

/* The directory seperator (a logical slash). */
#define LEM_DIRECTORY_DELIMITER_CHAR '/'
#define SOL_DIRECTORY_DELIMITER_CHAR L'/'

#define LEM_IS_DIRECTORY_DELIMITER_CHAR(ch) (ch==LEM_DIRECTORY_DELIMITER_CHAR)
#define SOL_IS_DIRECTORY_DELIMITER_CHAR(ch) (ch==SOL_DIRECTORY_DELIMITER_CHAR)

/* The extention separator (a logical dot) */
#define LEM_EXTENTION_DELIMITER_CHAR '.'
#define SOL_EXTENTION_DELIMITER_CHAR L'.'

/* The seperator for paths in environment variables */
#define LEM_PATH_SEPARATOR ';'
#define SOL_PATH_SEPARATOR L';'

/* Whether spaces are legal in filenames */
#define LEM_PATH_SPACE_OK true

// Неприемлимые символы в файловых путях.
#define LEM_PATH_BAD_CHARS  " \"*+,:;<=>?[\\]|"

// Current directory name
#define LEM_CUR_DIR_NAME "./"

// One level up directory
#define LEM_UP_DIR_NAME "../"

#else

#error Unknown UNIX

#endif

#endif /* LEM_UNIX */

#undef uch

    class Stream;


    struct IDirTraverser
    {
        virtual bool Continue() = 0;
        virtual void File(const char *path, const char *filename) = 0;
        virtual void File(const wchar_t *path, const wchar_t *filename) = 0;
        virtual void Folder(const char *path) = 0;
        virtual void Folder(const wchar_t *path) = 0;

        virtual ~IDirTraverser() {}
    };


#if defined LEM_WINDOWS
    struct IDirTraverser2
    {
        virtual bool Continue() = 0;
        virtual void File(
            const wchar_t *folder, int path_len,
            const WIN32_FIND_DATAW * find_data
        ) = 0;
        virtual bool CanEnterFolder(const wchar_t *folder) { return true; }
        virtual void Folder(const wchar_t *path) = 0;
    };
#endif


    // *********************************************************************************
    // Класс - аналог Path в .NET, инкапсулирует операции с именами файлов (точнее -
    // с путями файловой системы). Также предоставляет значительное количество 
    // расширенных возможностей по работе с каталогами, файлами и т.д.
    // *********************************************************************************
    class Path
    {
    private:
        UFString uname; // если имя задано в UNICODE
        FString name;   // имя в ASCII, возможно - в системной кодовой странице

#if defined LEM_UNIX
        void PurgeFolderPosix() const;
#endif

#if !defined LEM_WINDOWS && !defined LEM_UNIX
        void PurgeFolderPortable() const;
#endif

    public:
#if defined LEM_WINDOWS
        enum { MaxLen = _MAX_PATH };
#elif defined LEM_LINUX || defined LEM_SOLARIS
        enum { MaxLen = PATH_MAX };
#elif defined LEM_BSD
        enum { MaxLen = MAXPATHLEN };
#else
#error 
#endif

    private:

    public:
        Path() {}
        Path(const Path &x) : uname(x.uname), name(x.name) {}

        Path(Path && x) :uname(std::move(x.uname)), name(std::move(x.name)) {}

        explicit Path(const char *Name) : name(Name) {}
        explicit Path(const wchar_t *UName) : uname(UName) {}

        explicit Path(const FString& Name) : name(Name) {}
        explicit Path(const UFString& UName) : uname(UName) {}

        explicit Path(const std::string& Name) : name(Name) {}
        explicit Path(const std::wstring& UName) : uname(UName) {}

        Path(const char *Name, const wchar_t *UName)
            : uname(UName), name(Name) {}

        inline void operator=(const Path &x)
        {
            uname = x.uname;
            name = x.name;
        }

        inline void operator=(Path &&x)
        {
            if (this != &x)
            {
                uname = std::move(x.uname);
                name = std::move(x.name);
            }
        }


        bool operator==(const Path &x) const;
        bool operator!=(const Path &x) const;

        // Сериализация в виртуальный поток.
        void SaveBin(lem::Stream &bin) const;
        void LoadBin(lem::Stream &bin);

        // Вернет true, если путь представлен только в ASCII, а UNICODE не задан
        inline bool IsAscii() const { return uname.empty() && !name.empty(); }

        // Вернет true, если путь задан в UNICODE
        inline bool IsUnicode() const { return !uname.empty(); }

        UFString GetUnicode() const;
        FString  GetAscii() const;

        // Path string is empty
        bool empty() const { return uname.empty() && name.empty(); }
        size_t length() const { return uname.empty() ? name.length() : uname.length(); }

        // Make the strings empty
        inline void clear() { uname.clear(); name.clear(); }

        static const UFString GetFileNameWithoutExtension(const UFString &path);

        void AddExtension(const char *ext);

        // Append '\' or '/' if not already appened
        void AppendPathDelimiter();

        static const UFString RemoveLeaf(const UFString &path);

        // Returns the file extension (without '.')
        const lem::UFString GetExtension() const;
        static const lem::FString GetExtension(const char *filename);
        static const lem::UFString GetExtension(const wchar_t *filename);
        static const std::wstring GetExtension(const std::wstring &filename);
        static const lem::UFString GetExtension(const UFString &filename);

        void ChangeExtension(const wchar_t *new_ext);

        // Для целевой платформы символ - разделитель расширения файла?
        static bool IsExtDelimiter(wchar_t ch);

        // Для целевой платформы символ отделяет букву диска (DOS/Win)?
        static bool IsDriveDelimiter(wchar_t ch);

        // Для целевой платформы символ - разделитель элемента пути?
        static bool IsPathDelimiter(wchar_t ch);

        // Для целевой платформы - символ для разделения имен каталогов (файлов)
        static wchar_t GetPathDelimiter();

        // Для целевой платформы - символ для отделения расширения
        static wchar_t GetExtDelimiter();

        // Get temporary file name (with extension given)
        static const lem::Path GetTmpFilename(const char *ext = nullptr);

        // ВОзвращает путь к каталогу для временных файлов
        static const lem::Path GetTmpFolder();

        lem::Path& ConcateLeaf(const lem::Path &Filename);
        lem::Path& ConcateLeaf(const wchar_t *Filename);
        lem::Path& ConcateLeaf(const lem::UFString &Filename);
        lem::Path& ConcateLeaf(const std::wstring &Filename);

        // Приведение имени файла к верхнему (или нижнему) регистру
        void ToUpper();
        void ToLower();

        // Выполняется очистка каталога от находящихся в нем файлов и
        // вложенных каталогов (рекурсивно).
        void PurgeFolder() const;

        // Из пути удаляется последний элемент. Например, из полного пути к файлу
        // получается имя каталога, в котором файл размещен.
        void RemoveLastLeaf();

        // Оставляет имя файла, убирая путь к нему.
        UFString GetFileName() const;

        // Имя файла или имя последней папки в пути
        UFString GetLastLeaf() const;

#if defined LEM_UNIX
        static void Win_2_Lin(FString &p);
        static void Win_2_Lin(UFString &p);
#endif

        // Рекурсивный обход подкаталогов. Возвращается размер
        // обработанных файлов. Также можно указать visitor для
        // обработки файлов в каталогах.
        lem::uint64_t Crawl(bool recurse, IDirTraverser *traverser) const;

#if defined LEM_WINDOWS
        lem::uint64_t Crawl(bool recurse, IDirTraverser2 *traverser) const;
#endif


        // Путь корректен, то есть файл или каталог существует?
        bool DoesExist() const;
        static bool DoesExist(const lem::UFString &p);
        static bool DoesExist(const lem::FString &p);
        static bool DoesExist(const wchar_t* name);
        static bool DoesExist(const char* name);


        // Путь указывает на реально существующий каталог?
        bool IsFolder() const;

        // Удаляем файл или каталог вместе с содержимым
        bool DoRemove() const;

        // Если каталога не существует, создаем его.
        // Если subfolders=true, то также будут созданы все родительские
        // каталоги.
        void CreateFolder(bool subfolders = false) const;

        // Копирование содержимого файла src в dst.
        static void CopyFile(const lem::Path& src, const lem::Path& dst);
        static void CopyFile(const char *src, const char *dst);
        static void CopyFile(const wchar_t *src, const wchar_t *dst);

        // Копирование содержимого каталога в указанное место
        static void CopyFolder(const lem::Path& src, const lem::Path& dst);

        static bool RenameFile(const wchar_t *oldname, const wchar_t *newname);
        static bool RenameFile(const char *oldname, const char *newname);

        // Возвращает размер файла
        size_t FileSize() const;
        static size_t FileSize(const char *name);
        static size_t FileSize(const wchar_t *name);

        // Возвращает список элементов (файлов и подкаталогов)
        // в данном каталоге.
        void List(std::vector< std::pair< lem::Path, bool /*is_file*/ > > &list) const;

        // Заполняет список файлов полными путями.
        void ListFiles(std::vector< lem::Path > &list, bool recursive) const;
        void ListFiles(const wchar_t *mask, std::vector< lem::Path > &list, bool recursive) const;

        // Есть ли в каталоге хоть один файл или вложенная папка?
        bool IsFolderEmpty() const;

        // Проверка синтаксиса файлового пути. Возвращает признак успеха проверки.
        bool Check() const;

        // Вернет true для путей в локальной файловой системе (local file system)
        // или в локальной сети: в формате UNC для Windows \\имя_хоста\имя_ресурса,
        // long UNCW: \\?\путь или \\?\имя_хоста\имя_ресурса).
        bool IsLocal() const;

        // Вернет true, если путь указывает на FTP-сервер
        bool IsFtp() const;

        // Вернет true, если путь указывает на HTTP-сервер
        bool IsHttp() const;

        // Является ли хранимая строка URLом
        bool IsUrl() const;

        // Подходит ли файловый путь под указанную маску (с символами * и ?)
        bool Match(const wchar_t *mask) const;
        bool Match(const lem::UFString & mask) const;

        // Маска, соответстуующая любому файлу для текущей платформы
        // *.* для Dos/Win
        // *   для Unix
        static lem::UFString AllFilesMask();

        // Раскрывает относительные части типа . и ..
        lem::Path GetAbsolutePath() const;

        friend void swap(lem::Path &x, lem::Path &y);
    };

    extern void swap(lem::Path &x, lem::Path &y);

} // namespace 'lem'


namespace std
{
    inline void swap(lem::Path &x, lem::Path &y)
    {
        lem::swap(x, y);
    }
}

#endif
