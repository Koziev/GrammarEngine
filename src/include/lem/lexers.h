// -----------------------------------------------------------------------------
// File LEXERS.H
//
// (c) by Elijah Koziev   all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// Универсальный лексемный парсер текстовых файлов.
//
// Шаблоны SrcToken, Base_Parser, структура SourceState. Чтение полей из
// текстовых файлов с пропуском комментариев С/С++ и культурной демонстрацией
// места ошибки. Другими словами, Base_Parser - шаблон для классов ПАРСЕРОВ
// текстовых потоков.
//
// 11.06.2007 - устранена утечка памяти в конструкторе Base_Parser'а
// -----------------------------------------------------------------------------
//
// CD->11.01.1996
// LC->01.04.2018
// --------------

#ifndef LEM_SOURCE__H
#define LEM_SOURCE__H
#pragma once

#include <lem/config.h>

#include <lem/integer.h>
#include <lem/conversions.h>
#include <lem/cstring.h>
#include <lem/runtime_checks.h>
#include <lem/smart_pointers.h>
#include <lem/console_streams.h>
#include <lem/ustreams.h>
#include <lem/user_interface.h>
#include <lem/minmax.h>

#undef min
#undef max

namespace lem
{
    extern const char *SOURCE_DELIMS;

    // ****************************************************************************
    // Список стандартных (предопределенных) многосимвольных разделителей
    // эти разделители соответствуют стандарту языка C++. Пользовател класса
    // LemSource может предоставить собственную таблицу многосимвольных разделителей.
    //  ****************************************************************************
    extern const char *SOURCE_COMPL_DELIMS;


    template < typename CHAR > class Special_Char;

    template <> class Special_Char<char>
    {
    public:
        static int eof(void);
    };

    template <> class Special_Char<wchar_t>
    {
    public:
        static wchar_t eof(void);
    };

    // ------------- Флажки для модификации поведения парсера -------------
    //
    //  To set any of these control flags, add the following statement to
    //  *your* source code:
    //  SolSource txtfile;
    //  txtfile.Open("xxx.txt");
    //  txtfile.SetFlag( SOL_SRC_xxx | SOL_SRC_xxx | .... , true )
    //
    //  The default setting can be seen in [sol_src.cpp] source file, in
    //  SolSource class constructor.
    // ------------------------------------------------------------------

    // Читать поля формата чисел с плавающей точкой как единую лексему.
    const lem::uint32_t SRC_READ_FLOATING = 0x00000001u;

    /*
      Флаг заставляет читать строку в двойных апострофах
      как единую лексему. Если флаг не определен, то
      обязанность корректно считывать строку ложится на
      потребителя.
    */
    const lem::uint32_t SRC_READ_STRING = 0x00000002u;

    /*
      Будучи определен, этот флаг заставляет лексемы
      в апострофах ["..."] исключать эти апострофы перед
      возвратом лексемы потребителю. Таким образом,
      лексема ["hello, mister!"] будет преобразована
      в [hello, mister].
    */
    const lem::uint32_t SRC_STRIP_STRING = 0x00000004u;

    /*
      Флаг заставляет читать C-определение символа в апострофах 'x'
      как единую лексему. В противном случае обязанность обрабатывать
      такие ситуации лежит на потребителя.
    */
    const lem::uint32_t SRC_READ_CHAR = 0x00000008u;

    /*
      Флаг заставляет преобразовывать конструкции [\код] внутри
     C-строк ["..."] и C-символов ['...'] в коды, как это делает
     транслятор C/C++. Чтобы флаг работал, необходимо разрешить
     считываение C-строк и C-символов - см. флаги READ_STRING и
     READ_CHAR.
    */
    const lem::uint32_t SRC_PROCESS_C_CHAR = 0x00000010u;

    //  Флаг заставляет пропускать комментарии в стиле C.
    const lem::uint32_t SRC_SKIP_C_COMMENTARY = 0x00000020u;

    //  Флаг заставляет пропускать комментарии в стиле C++.
    const lem::uint32_t SRC_SKIP_CPP_COMMENTARY = 0x00000040u;

    // Пропускать паскалевские комментарии {* ... *}
    const lem::uint32_t SRC_SKIP_PASCAL_COMMENTARY = 0x00000080u;

    // Пропускать комментарии пролога % .....
    const lem::uint32_t SRC_SKIP_PROLOG_COMMENTARY = 0x00000100u;

    // Пропускать комментарии Лиспа ; .....
    const lem::uint32_t SRC_SKIP_LISP_COMMENTARY = 0x00000200u;

    /*
     Сложные многосимвольные разделители для языка C/C++ будут
     корректно распознаны, если установить этот флаг. В противном
     случае они будут разбиты на множество односимвольных лексем.
    */
    const lem::uint32_t SRC_COMPLEX_DELIMITER = 0x00000400u;

    // Флаг заставляет игнорировать регистр символов при проверке ключевых слов.
    const lem::uint32_t SRC_IGNORE_TOKCASE = 0x00000800u;

    /*
      В обычной конфигурации символ окончания строки (EOL, код '\n')
      не проникает во внешний читающий модуль, он прозрачно учитываетс
      классом LemSource при подсчете числа строк. Однако в некоторых случаях
      конец строки рассматривается как ограничитель выражений, поэтому
      он должен передаваться во внешнюю программу. Для включения такого
      режима работы необходимо выставить флаг SKIP_EOL как false. При
      извлечении конца строки внешний модуль получит токен, содержащий
      символ '\n' и имеющий код SOURCE_EOL.
    */
    const lem::uint32_t SRC_SKIP_EOL = 0x00001000u;

    // Сообщать ли пользователю о превышении максимальной длины лексемы.
    const lem::uint32_t SRC_CONTROL_OVERFLOW = 0x00002000u;

    // Simplest and fastest read method. С таким флагом чтение лексемы работает
    // намного быстрее за счет исключения проверок множества специальных
    // ситуаций. Этот флаг желательно использовать при чтении полей из
    // просто организованных текстовых файлов.
    const lem::uint32_t SRC_READ_SIMPLE = 0x00004000u;

    // Токенизировать (искать в таблице токенов) ли читаемые лексемы - по
    // умолчанию да.
    const lem::uint32_t SRC_DONT_TOKENIZE = 0x00008000u;

    struct ASrcTok : public CString
    {
        int index; // Собственно индекс токена, используемый транслятором.

        ASrcTok(void) { index = UNKNOWN; }
        ASrcTok(const ASrcTok &x) :CString(x) { index = x.index; }
        ASrcTok(const CString &s, const int Index)
            :CString(s) {
            index = Index;
        }

        inline void operator=(const ASrcTok &x)
        {
            CString::operator=(x);
            index = x.index;
            return;
        }
    };

    struct USrcTok : public UCString
    {
        int index; // Собственно индекс токена, используемый транслятором.

        USrcTok(void) { index = UNKNOWN; }
        USrcTok(const USrcTok &x) :UCString(x) { index = x.index; }
        USrcTok(const UCString &s, const int Index)
            :UCString(s) {
            index = Index;
        }

        inline void operator=(const USrcTok &x)
        {
            UCString::operator=(x);
            index = x.index;
            return;
        }
    };



    // **********************************************************************
    // Структуры для организации таблицы быстрой токенизации лексем.
    // За счет специального разбиения всего пространства хэш-кодов дл
    // лексем получается значительное ускорение перебора подходящих
    // токенов.
    // **********************************************************************
    class ASrcLookUpTable : public std::vector< ASrcTok >
    {
    public:
        ASrcLookUpTable(void) {}

        void Prepare(const std::vector<CString> &Tokens);

        int Find(const CString &s) const;

        inline const ASrcTok& get(int i) const { return operator[](i); }
        inline       ASrcTok& get(int i) { return operator[](i); }
    };

    class USrcLookUpTable : public std::vector< USrcTok >
    {
    public:
        USrcLookUpTable(void) {}

        void Prepare(const std::vector<UCString> &Tokens);

        int Find(const UCString &s) const;

        inline const USrcTok& get(int i) const { return operator[](i); }
        inline       USrcTok& get(int i) { return operator[](i); }
    };







    // *********************************************************
    // Здесь будем хранить информацию о текущем состоянии
    // указателя чтения файла, чтобы можно было возвращатьс
    // назад при чтении лексем без потери номеров строк.
    // *********************************************************
    struct SourceState
    {
        lem::Stream::pos_type pos; // Позиция в файле
        int line;      // Номер строки
        lem::int16_t symbol;    // Номер символа в строке

        SourceState(void)
        {
            pos = static_cast<Stream::pos_type>(UNKNOWN);
            line = UNKNOWN;
            symbol = UNKNOWN;
        }

        SourceState(Stream::pos_type p, int l, lem::int16_t s)
        {
            pos = p; line = l; symbol = s;
        }

        SourceState(const SourceState &ss)
        {
            pos = ss.pos; line = ss.line; symbol = ss.symbol;
        }

        inline void operator=(const SourceState &ss)
        {
            pos = ss.pos; line = ss.line; symbol = ss.symbol;
        }

        inline Stream::pos_type GetPos(void) const { return pos; }
        inline lem::int16_t GetSymbolPos(void) const { return symbol; }
        inline int GetLine(void) const { return line; }
    };

    inline bool operator==(const SourceState &s1, const SourceState &s2)
    {
        return s1.pos == s2.pos && s1.line == s2.line && s1.symbol == s2.symbol;
    }


    // ************************************************************************
    // Хранилище для лексемы, прочитанной из входного файла,
    // и некоторой вспомогательной информации.
    // ************************************************************************

    const lem::int16_t LEM_SOURCE_EOL = lem::int16_t(0xfffe); // Специальный код токена, см. описание
                                                // флага SRC_SKIP_EOL

    class ASrcToken : public CString
    {
    private:
        SourceState begin;    // Описание положение начала лексемы
                              // Lexem beginning position

        lem::int16_t token; // Для служебных слов - код.
                            // Token code (index in keyword table)

        typedef CString str_type;

    public:
        ASrcToken(void) { token = UNKNOWN; }

        ASrcToken(
            const str_type &Str,
            const SourceState &pos,
            bool ignore_case,
            const std::vector< CString > &Tokens
        );

        ASrcToken(
            const str_type &Str,
            const SourceState &pos
        ) :CString(Str), begin(pos)
        {
            token = UNKNOWN;
            return;
        }

        ASrcToken(const str_type &Str, int Token = UNKNOWN) :CString(Str)
        {
            token = Token;
            return;
        }

        ASrcToken(int Token, const SourceState &pos) :begin(pos)
        {
            token = Token;
        }

        explicit ASrcToken(const SourceState &pos) :begin(pos)
        {
            token = UNKNOWN;
        }

        ASrcToken(const ASrcToken &t)
            :CString(t.str), begin(t.begin)
        {
            token = t.token;
            return;
        }

        inline void operator=(const ASrcToken &t)
        {
            CString::operator=(t.string());
            begin = t.begin;
            token = t.token;
            return;
        }

        inline const CString& string(void) const
        {
            return static_cast<const str_type&>(*this);
        }

        inline       CString& string(void)
        {
            return static_cast<str_type&>(*this);
        }

        inline const SourceState& GetBegin(void) const { return begin; }
        inline lem::int16_t GetToken(void) const { return token; }
        inline void SetToken(lem::int16_t T) { token = T; }

        inline void SetString(const CString& s)
        {
            CString::operator=(s);
        }

        inline operator SourceState(void) const { return begin; }

        inline bool eol(void) const { return token == LEM_SOURCE_EOL; }

        inline bool operator==(lem::int16_t T) const { return token == T; }

        UCString GetUnicode(void) const;
    };




    class USrcToken : public UCString
    {
    private:
        SourceState begin;    // Описание положение начала лексемы
                              // Lexem beginning position

        lem::int16_t token; // Для служебных слов - код.
                              // Token code (index in keyword table)

        typedef UCString str_type;

    public:
        USrcToken(void) { token = UNKNOWN; }

        USrcToken(
            const str_type &Str,
            const SourceState &pos,
            bool ignore_case,
            const std::vector< UCString > &Tokens
        );

        USrcToken(
            const str_type &Str,
            const SourceState &pos
        ) :UCString(Str), begin(pos)
        {
            token = UNKNOWN;
            return;
        }

        USrcToken(const str_type &Str, int Token = UNKNOWN) :UCString(Str)
        {
            token = Token;
            return;
        }

        USrcToken(int Token, const SourceState &pos) :begin(pos)
        {
            token = Token;
        }

        explicit USrcToken(const SourceState &pos) :begin(pos)
        {
            token = UNKNOWN;
        }

        USrcToken(const USrcToken &t)
            :UCString(t.str), begin(t.begin)
        {
            token = t.token;
            return;
        }

        inline void operator=(const USrcToken &t)
        {
            UCString::operator=(t.string());
            begin = t.begin;
            token = t.token;
            return;
        }

        inline const UCString& string(void) const
        {
            return static_cast<const str_type&>(*this);
        }

        inline       UCString& string(void)
        {
            return static_cast<str_type&>(*this);
        }

        inline const SourceState& GetBegin(void) const { return begin; }
        inline lem::int16_t GetToken(void) const { return token; }
        inline void SetToken(lem::int16_t T) { token = T; }

        inline void SetString(const UCString& s)
        {
            UCString::operator=(s);
        }

        inline operator SourceState(void) const { return begin; }

        inline bool eol(void) const { return token == LEM_SOURCE_EOL; }

        UCString GetUnicode(void) const { return *this; }
    };

    // *******************************************************************

    template  < class CHAR >
    class Char_Source
    {
    public:
        Char_Source() {}

        char get(lem::Char_Stream::WideStream* stream) const;
    };

    // Специализация для лексера однобайтовых символов
    template<>
    class Char_Source <char>
    {
    public:
        Char_Source() {}

        inline char get(lem::Char_Stream::WideStream* stream) const { return stream->get(); }
    };


    // Специализация для лексера двухбайтовых символов
    template<>
    class Char_Source <wchar_t>
    {
    public:
        Char_Source() {}

        inline wchar_t get(Char_Stream::WideStream* stream) const { return stream->wget(); }
    };

    // **********************************************************************

    // *******************************************************************

    template  < class CHAR >
    class ChooseStr
    {
    public:
        ChooseStr() {}

        typedef lem::UCString STR;
        typedef lem::UFString FSTR;
        typedef lem::ASrcToken SRC_TOKEN;
    };

    // Специализация для лексера однобайтовых символов
    template<>
    class ChooseStr <char>
    {
    public:
        ChooseStr() {}

        typedef lem::CString STR;
        typedef lem::FString FSTR;
        typedef lem::ASrcToken SRC_TOKEN;
        typedef ASrcLookUpTable TKN_TABLE;
    };


    // Специализация для лексера двухбайтовых символов
    template<>
    class ChooseStr <wchar_t>
    {
    public:
        ChooseStr() {}

        typedef lem::UCString STR;
        typedef lem::UFString FSTR;
        typedef USrcToken SRC_TOKEN;
        typedef USrcLookUpTable TKN_TABLE;
    };



    // *******************************************************************
    // Базовый класс для форматтеров чтения текстовых потоков (парсеров).
    // *******************************************************************
    template < class CHAR >
    class Base_Parser : lem::NonCopyable
    {
    public:
        typedef SourceState           pos_type;
        typedef typename ChooseStr<CHAR>::STR  str_type;
        typedef typename ChooseStr<CHAR>::FSTR fstr_type;
        typedef typename ChooseStr<CHAR>::SRC_TOKEN  token_type;
        typedef typename ChooseStr<CHAR>::TKN_TABLE SrcLookUpTable;

        enum { LEN = ChooseStr<CHAR>::STR::max_len };

    protected:
        wchar_t *Buffer4k;
        int Buffer4kLen;

        Char_Source<CHAR> reader; // Извлекатель символов
        lem::Ptr<lem::Char_Stream::WideStream> file; // Поток, откуда мы берем символы.

        // Для ускорения операций отката выполняется кэширование UNICODE-символов.
        lem::int32_t cache[LEN * 2]; // Look-ahead cache читаемых символов.
        Stream::pos_type pcache[LEN * 2]; // Позиции символов в кэше - нужно для кодировок с переменной
                                            // длиной представления символов
        int cache_cursor;
        Stream::pos_type cache_fpos;      // Позиция в потоке для начала кэша.

        size_t file_size; // Полный размер потока.
        lem::Ptr<OFormatter> err_stream; // Для вывода сообщений об ошибках (по умолчанию merr)

        // Single-char delimiters
        fstr_type DELIMITER;

        // list of complex (multy-char) delimiters.
        std::vector< str_type > compl_delims;

        // Таблица токенов и ускорительные поля.
        std::vector< str_type > tokens;
        std::auto_ptr<SrcLookUpTable> look_up_table; // Ускорительная таблица поиска токенов.

        // Поля для организации отката считывания.
        int prev_line, prev_pos;
        Stream::pos_type prev_fpos;

        void LoadCache(void);

        int line; // Текущее положение в файле - номер строки
        int symbol_pos; // Текущее положение в файле - номер столбца
        bool eol_reached;

        lem::uint32_t flag; // Флаги, управляющие работой форматтера.

        bool was_string, was_char;

        virtual void Overflow(void);

        bool IsDelimiter(int ch) const;
        bool IsSpecial(int ch) const;
        bool IsWhite(int ch) const;
        bool IsComplexDelimiter(const CHAR *str) const;
        bool IsNumber(int ch) const;

        bool ReadValueField(CHAR *Buffer, int maxlen);
        int Read_After_Slash(void);
        void Read_C_String(typename ChooseStr<CHAR>::FSTR &Buffer, int maxlen = -1);

        void SkipComm1(void);
        void SkipComm2(void);

        void Delete(void);

        const pos_type read_simple(CHAR *Buffer, int maxlen);

    protected:
        // Usage is blocked...
        Base_Parser(const Base_Parser<CHAR>&);
        void operator=(Base_Parser<CHAR>&);

        void Preset(void);

    public:
        Base_Parser(void);
        Base_Parser(const std::vector<str_type> &Tokens);

        virtual ~Base_Parser(void);

        virtual void Open(lem::Ptr<Char_Stream::WideStream> File);
        virtual void Open(lem::Ptr<Stream> File);
        virtual void Open(const lem::Path &filename);

        inline int GetLine(void) const { return line; }

        bool eof(void) const;

        const pos_type tellp(void) const;
        Stream::pos_type seekp(const pos_type& ss);
        inline Stream::pos_type fsize(void) const { return file->fsize(); }

        bool IsOpen(void) const { return !!&*file; }
        inline const lem::Path& GetName(void) const { return file->GetName(); }
        inline void close(void) { file->close(); }
        inline Char_Stream::WideStream* GetStream(void) { return &*file; }

        /***********************************************************************
         Устанавливаем (set=true) или сбрасываем (set=false) один или
         несколько внутренних битовых флажков. Оперируемые флажки представлены
         параметром f.
        ************************************************************************/
        inline void SetFlag(lem::uint32_t f, bool set = true)
        {
            if (set) flag |= f; else flag = flag&~f;
        }

        /*************************************************************************
         Возвращает весь набор битовых флагов, управляющих работой нашего парсера.
        **************************************************************************/
        inline lem::uint32_t GetFlag(void) const { return flag; }
        inline bool ProbeFlag(lem::uint32_t f) const { return (flag&f) == f; }

        inline void SetMerr(lem::Ptr<OFormatter> err) { err_stream = err; }
        inline OFormatter& GetMerr(void) { return *err_stream; }

        virtual void skip_white(void);

        void SetTokens(const std::vector<str_type> &Tokens);
        void SetComplDelims(const std::vector<str_type> &Delims);

        void SetComplDelims(const char *t);

        inline void SetDelim(const char d[])
        {
            DELIMITER = d;
        }

        virtual int get(void);
        virtual void unget(void);

        const pos_type read(CHAR *Buffer, int maxlen);
        const token_type read(bool do_tokenize = true);
        const token_type read(fstr_type &full_str, bool do_tokenize = true);

        void read_it(const str_type& needed);
        void read_it(int needed);

        lem::int16_t read_int16(void);
        lem::int32_t read_int32(void);

        inline lem::int16_t read_short(void) { return read_int16(); }
        inline lem::int32_t read_int(void) { return read_int32(); }
        inline lem::int32_t read_long(void) { return read_int32(); }

        bool read_bool(void);

        const fstr_type read_fstring(int maxsize = 0);
        const str_type read_c_char(void);

#if !defined LEM_NOREAL
        virtual double read_real(void);
#endif

        void Read_C_String(CHAR *Buffer, int maxlen);
        void Read_C_Char(CHAR *Buffer, int maxlen);

        void Error(const pos_type& t, int tok_len = 1);
        void Error(void);

        void ToLineBegin(void);
        void ToLineEnd(void);
        bool SeekLine(int iline);
        void PrintLine(OFormatter &to);

        void SeekForToken(int Token);

        bool Is_A_Delimiter(const CHAR *string) const;

        inline const std::vector<str_type>& GetTokens(void) const { return tokens; }
    };


    template < class CHAR >
    inline Base_Parser<CHAR>::Base_Parser(void) //: file(NULL,null_deleter())
    {
        Preset();
        return;
    }


    // **************************************************************
    // Конструктор с одновременной инициализацией таблицы токенов.
    // **************************************************************
    template < class CHAR >
    inline Base_Parser<CHAR>::Base_Parser(const std::vector<str_type> &Tokens)
        //: file(NULL)
    {
        Preset();
        SetTokens(Tokens);
        return;
    }


    template < class CHAR >
    inline void Base_Parser<CHAR>::Preset(void)
    {
        Buffer4k = NULL;
        Buffer4kLen = 0;

        err_stream = lem::Ptr<OFormatter>(merr, null_deleter()); // По умолчанию - вывод сообщений в этот поток

        line = prev_line = 1;
        symbol_pos = prev_pos = 0;

        flag = SRC_READ_FLOATING | SRC_READ_STRING | SRC_STRIP_STRING |
            SRC_READ_CHAR | SRC_PROCESS_C_CHAR | SRC_SKIP_C_COMMENTARY |
            SRC_SKIP_CPP_COMMENTARY | SRC_COMPLEX_DELIMITER | SRC_SKIP_EOL;

        file_size = 0;

        was_string = was_char = false;

        ::memset(cache, 0, sizeof(cache)); // Очищам кэш предзагруженных символов.
        ::memset(pcache, 0, sizeof(pcache));

        cache_cursor = DIM_A(cache);
        prev_fpos = cache_fpos = 0;

        SetDelim(SOURCE_DELIMS);
        SetComplDelims(SOURCE_COMPL_DELIMS);

        look_up_table = std::auto_ptr<SrcLookUpTable>(new SrcLookUpTable());

        return;
    }


    /**************************************************************
     Деструктор закрывает файл, если он был открыт именно
     классом SolSource при вызове метода ::Open( const SOLACHAR* )
    ***************************************************************/
    template < class CHAR >
    inline Base_Parser<CHAR>::~Base_Parser(void)
    {
        Delete();
        return;
    }

    /****************************************************************************
      Устанавливает новую таблицу токенов (ключевых слов). Так как копирования
      таблицы не производится, то необходимо позаботиться о сохранении информации
      по указателю TOKENS во внешней вызвавшей процедуре.
    ****************************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::SetTokens(const std::vector<str_type> &Tokens)
    {
        tokens = Tokens;
        look_up_table->Prepare(tokens);
        return;
    }

    template < class CHAR >
    inline void Base_Parser<CHAR>::SetComplDelims(const char * t)
    {
        // Parse the list of delimiters, separated by '\0' in 't'
        str_type delim;

        compl_delims.clear();

        int i = 0;
        while (t[i])
        {
            delim = t[i]; // from i to '\0' which break the delimiter
            i += delim.length() + 1; // now on first char of the next delimiter

            if (delim.empty())
                break; // end of list is reached

            compl_delims.push_back(delim);
        }

        return;
    }

    template < class CHAR >
    inline void Base_Parser<CHAR>::SetComplDelims(const std::vector<str_type> &Delims)
    {
        compl_delims = Delims;
        return;
    }



    template < class CHAR >
    inline void Base_Parser<CHAR>::Open(lem::Ptr<lem::Char_Stream::WideStream> File)
    {
        LEM_CHECKIT_Z(File->IsBinary()); // See ::Open( const wchar_t *filename )
                                           // commentaries.
        was_string = was_char = false;

        cache_cursor = LEN * 2;
        file = File;
        file->Check();

        file_size = file->fsize();

        // Preload the cache.
        LoadCache();
        return;
    }


    template < class CHAR >
    inline void Base_Parser<CHAR>::Open(lem::Ptr<lem::Stream> File)
    {
        lem::Ptr<lem::Char_Stream::WideStream> r = lem::Char_Stream::WideStream::GetReader(File);
        Open(r);
        return;
    }


    template < class CHAR >
    inline void Base_Parser<CHAR>::Open(const lem::Path &filename)
    {
        Open(lem::Ptr<lem::Stream>(new lem::BinaryReader(filename)));
        return;
    }

    template < class CHAR >
    inline void Base_Parser<CHAR>::Delete(void)
    {
        if (Buffer4k != NULL)
        {
            delete[] Buffer4k;
            Buffer4kLen = 0;
        }

        err_stream.reset();
        file_size = 0;
        return;
    }

    /**************************************************************************
     Заполняем кэш символов. Последний считанный символ из предыдущего
     наполнения кэша перейдет в самую первую позицию кеша, так что
     операция unget() может быть свободно использована и после перегрузки кеша.
     Одновременно производим перекодировку символов из ASCII в UNICODE.
    ***************************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::LoadCache(void)
    {
        cache[0] = cache[cache_cursor - 1];
        pcache[0] = pcache[cache_cursor - 1];

        cache_cursor = 1;
        cache_fpos = file->tellp();

#if !defined LEM_GNUC
        if (cache_fpos < 0)
            cache_fpos = 0;
#endif

        if (file->eof())
        {
            // EOF reached - force cache tail to zero.
            for (size_t i = 1; i < DIM_A(cache); i++)
            {
                pcache[i] = cache[i] = 0;
            }

            return;
        }

        int ch;
        for (size_t i = 1; i < DIM_A(cache); i++)
        {
            ch = reader.get(&*file);
            pcache[i] = file->tellp();

            if (ch == EOF || file->eof())
            {
                // Forcing cache tail to zero.
                for (; i < DIM_A(cache); i++)
                    pcache[i] = cache[i] = 0;

                break;
            }
            else
            {
                switch (sizeof(CHAR))
                {
                case 1: cache[i] = 0x00ffU & ch; break;
                case 2: cache[i] = (CHAR)ch;     break;
                case 4: cache[i] = (CHAR)ch;     break;
                default: LEM_STOPIT;
                }
            }
        }

        return;
    }


    /**************************************************************************
     Возвращается структура (тип объявлен как pos_type), хранящая информацию
     о текущем контексте. Далее эта структура может быть возвращена для
     продолжения чтения с сохраненной таким образом позиции.
    **************************************************************************/
    template < class CHAR >
    inline const SourceState Base_Parser<CHAR>::tellp(void) const
    {
        return pos_type(cache_fpos, line, symbol_pos);
    }


    // *****************************************************************
    // Чтение будет продолжено с позиции, описываемой структурой ss.
    // *****************************************************************
    template < class CHAR >
    inline lem::Stream::pos_type Base_Parser<CHAR>::seekp(const pos_type& ss)
    {
#if defined LEM_DEBUGON
        const lem::Stream::pos_type p = file->seekp((lem::Stream::off_type)ss.pos);
        if (p != ss.pos)
        {
            // Произошла ошибка позиционирования файла.
#if defined LEM_RUSSIAN
            GetMerr().printf("Ошибка файловой операции для [%us]\n", GetName().GetUnicode().c_str());
#else
            GetMerr().printf("File operation fault for [%us]\n", GetName().GetUnicode().c_str());
#endif

            LEM_STOPIT;
        }
#else
        const lem::Stream::pos_type p = file->seekp((lem::Stream::off_type)ss.pos);
#endif

        prev_line = line = ss.GetLine();
        prev_pos = symbol_pos = ss.GetSymbolPos();
        LoadCache();
        return p;
    }

    // **********************************************************************
    // Обнаружена ситуация переполнения буфера читаемой лексемы. Выводим
    // сообщение об этом. Работа может быть продолжена.
    // **********************************************************************
    template < class CHAR >
    inline void Base_Parser<CHAR>::Overflow(void)
    {
        Error();

#if defined LEM_RUSSIAN
        GetMerr().printf("Слишком длинная лексема - выполнено усечение.");
#else
        GetMerr().printf("Lexem is too long - truncated.");
#endif

        return;
    }


    /************************************************************************
      Вывод подробной информации об местонахождении
      ошибки в текстовом файле словаря.

      Распечатываем строку с проблемой и указываем символом
      '^' проблемное место. tok_len - длина лексемы, которая вызвала ошибку.
    *************************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::Error(const pos_type& t, int tok_len)
    {
        file->seekp((lem::Stream::off_type)t.GetPos());
        LoadCache();

#if defined LEM_RUSSIAN
        GetMerr().printf("\n%vfCОШИБКА%vn в строке %d файла [%us]:\n", t.GetLine(), GetName().GetUnicode().c_str());
#else
        GetMerr().printf("\n%vfCERROR%vn in line %vfE%d%vn of file [%vfE%us%vn]:\n", t.GetLine(), GetName().GetUnicode().c_str());
#endif

        ToLineBegin(); // Перемещаемся в начало строки с ошибкой
        PrintLine(GetMerr()); // Распечатываем всю строку с ошибкой
        GetMerr().eol();

        // В начало токена с ошибкой.
        int nsp = t.GetSymbolPos();
        GetMerr().printf("%H ", nsp);

        int l = tok_len;
        if (l < 1) l = 1;
        GetMerr().printf("%H^\n", l);

        return;
    }

    /*************************************************************
      Печатаем сообщение об ошибке и выводим проблемную строку.
      Информацией об реальной символьной позиции с ошибкой мы не
      располагаем, поэтому укажем на текущее положение.
    **************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::Error(void)
    {
#if defined LEM_RUSSIAN
        GetMerr().printf("\n\nОШИБКА:\n");
#else
        GetMerr().printf("\n\nERROR:\n");
#endif

        ToLineBegin(); // Перемещаемся в начало строки с ошибкой
        PrintLine(GetMerr());   // Распечатываем строку с ошибкой
        GetMerr().eol();
        return;
    }


    /****************************************************************************
    Извлекает очередной символ из текстового файла. Попутно обновляются поля
    номера строки и символа. Эта процедура в основном предназначена для
    внутреннего использования классом Base_Parser. В паре с ней работает процедура
    unget() (см. далее).
    *****************************************************************************/
    template < class CHAR >
    inline int Base_Parser<CHAR>::get(void)
    {
        prev_pos = symbol_pos;
        prev_line = line;
        prev_fpos = cache_fpos;

        if (cache_cursor >= LEN * 2)
            LoadCache();

        const int ch = cache[cache_cursor];
        cache_fpos = pcache[cache_cursor];

        cache_cursor++;

        // Инкрементируем счетчик символов в строке. Когда достигаем
        // конца строки, счетчик обнуляется.
        symbol_pos++;

        if (ch == L'\n')
        {
            // End-Of-Line char retrieved. Set chars counter to zero and
            // increment lines counter.
            line++;
            symbol_pos = 0;
        }

        return ch;
    }

    /****************************************************************************
     Откат на одну позицию назад. Так как перед извлечением символа мы запомнили
     положение, можем корректно восстановить состояние счетчиков, и не потерять
     контекст. Не допускается обращение к данному методу два раза подряд без
     промежуточного вызова get()
    *****************************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::unget(void)
    {
        LEM_CHECKIT_Z(cache_cursor > 0);
        cache_cursor--;
        cache_fpos = prev_fpos;
        line = prev_line;
        symbol_pos = prev_pos;
        return;
    }

    /*******************************************************************************
     Определяем принадлежность символа к классу односимвольных разделителей.
     Эти символы отделяют две лексемы. Особый случай составляют числа с
     плавающей точкой, где десятичная точка '.' интерпретируется как часть лексемы.
     Считывание таких лексем организуется особо.
    *********************************************************************************/
    template < class CHAR >
    inline bool Base_Parser<CHAR>::IsDelimiter(int ch) const
    {
        return (DELIMITER.find_char((CHAR)ch) > 0 || ch == SOL_FEOF_CHAR);
    }



    /****************************************
    Специальные символы-разделители.
    *****************************************/
    template < class CHAR >
    inline bool Base_Parser<CHAR>::IsSpecial(int ch) const
    {
        return ch == L' ' || ch == L'\n' || ch == L'\t';
    }



    // ****************************************************************************
    // Является ли символ цифрой
    // ****************************************************************************
    template < class CHAR >
    inline bool Base_Parser<CHAR>::IsNumber(int ch) const
    {
        return !(ch & 0xffffff00U) && lem_strrchr("0123456789", ch) != NULL;
    }


    /***********************************************************
    Определяем принадлежность символа к классу 'пробельных'.
    ************************************************************/
    template < class CHAR >
    inline bool Base_Parser<CHAR>::IsWhite(int ch) const
    {
        if (
            ch == ' ' ||
            ch == '\t' ||
            ch == '\r'   // This character occurs when MSDOS-formatted text is read by UNIX-program
            )
            return true;

        return GetFlag()&SRC_SKIP_EOL ? ch == L'\n' : false;
    }

    /*******************************************************************
     Возвращает true, если достигнут конец файла, то есть все символы из
     файла извлечены. Учитываем наличие look-a-head кэша.
    ********************************************************************/
    template < class CHAR >
    inline bool Base_Parser<CHAR>::eof(void) const
    {
        return /*cache[cache_cursor]==EOF ||*/ cache_fpos >= file_size;
    }


    /*******************************************************************
     Возвращает true, если лексема относится к категории разделителей.
    *******************************************************************/
    template < class CHAR >
    inline bool Base_Parser<CHAR>::Is_A_Delimiter(const CHAR *string) const
    {
        if (string[1] == 0 && IsDelimiter(*string))
            return true;

        if (IsComplexDelimiter(string))
            return true;

        return false;
    }

    /**************************************************************************
     Для текстов C/C++ характерно наличие специальных многосимвольных
     комбинаций, которые должны рассматриваться как единый символ. Определяем
     принадлежность группы символов к такому классу.
    ***************************************************************************/
    template < class CHAR >
    inline bool Base_Parser<CHAR>::IsComplexDelimiter(const CHAR *str) const
    {
        if (!(GetFlag()&SRC_COMPLEX_DELIMITER))
            return false; // Учет многосимвольных разделителей подавлен.

        for (lem::Container::size_type i = 0; i < compl_delims.size(); i++)
            if (lem_eq(str, compl_delims[i].c_str()))
                return true;

        return false;
    }

    /*************************************************************
      Пропускаем, начиная с текущей позиции, пробельные символы.
    **************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::skip_white(void)
    {
        if (!eof())
        {
            int i_limit = 1000000; // Защита от зацикливани
            while (IsWhite(get()) && i_limit--) {}
            unget();
        }

        return;
    }

    /*******************************************************************
      Бежим до конца строки. Используется при пропуске комментари
      в стиле C++ <//>, Пролога <%>, Лиспа <;>
    ********************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::SkipComm1(void)
    {
        if (eof())
            return;

        wchar_t ch = 0;
        int i_limit = 1000000; // Защита от зацикливани
        while (!eof() && (ch = get()) != '\n' && i_limit--) {}

        if (ch == '\n' && !(GetFlag()&SRC_SKIP_EOL))
            unget();

        return;
    }

    /************************************************************/
    // Пропуск комментария C, то есть текста в /* ... */. Бежим //
    // до встречи с парой символов */. Также можем обработать   //
    // паскалевский комментарий {...}                           //
    /************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::SkipComm2(void)
    {
        if (eof())
            return;

        if (flag & SRC_SKIP_C_COMMENTARY)
        {
            CHAR ch1 = get();
            CHAR ch2 = get();

            int i_limit = 1000000; // Защита от зацикливани
            while (!eof() && i_limit--)
                if (ch1 == '*' && ch2 == '/')
                    break;
                else
                {
                    ch1 = ch2;
                    ch2 = get();
                }
        }
        else if (flag & SRC_SKIP_PASCAL_COMMENTARY)
        {
            int i_limit = 1000000; // Защита от зацикливани
            while (!eof() && get() != '}' && i_limit--) {}
        }

        return;
    }

    /**************************************************************
     Извлекает следующую лексему из входного потока.
     Автоматически пропускает строки комментариев в стиле C++ и C.
    ***************************************************************/
    template < class CHAR >
    inline const typename Base_Parser<CHAR>::token_type Base_Parser<CHAR>::read(bool do_tokenize)
    {
        CHAR Buffer[LEN + 1];

        const pos_type ss = read(Buffer, LEN);

        if (!(GetFlag()&SRC_SKIP_EOL) && eol_reached)
        {
            token_type res(LEM_SOURCE_EOL, ss);
            res.SetString(Buffer);
            return res;
        }

        return do_tokenize && !(GetFlag()&SRC_DONT_TOKENIZE) ?
            token_type(
                Buffer,
                ss,
                !!(GetFlag() & SRC_IGNORE_TOKCASE),
                tokens
            )
            :
            token_type(Buffer, ss);
    }


    template < class CHAR >
    inline const typename Base_Parser<CHAR>::token_type Base_Parser<CHAR>::read(fstr_type &full_str, bool do_tokenize)
    {
        CHAR Buffer[LEN + 1];

        if (Buffer4k == NULL)
        {
            Buffer4kLen = 4096;
            Buffer4k = new wchar_t[Buffer4kLen];
        }

        Buffer4k[0] = 0;
        const pos_type ss = read(Buffer4k, Buffer4kLen);
        const int blen = lem_strlen(Buffer4k);

        if (blen < LEN)
        {
            lem::lem_strcpy(Buffer, Buffer4k);
        }
        else
        {
            lem::lem_strncpy(Buffer, Buffer4k, LEN);
            Buffer[LEN] = 0;
        }

        if (!(GetFlag()&SRC_SKIP_EOL) && eol_reached)
        {
            token_type res(LEM_SOURCE_EOL, ss);
            res.SetString(Buffer);
            full_str = Buffer;
            return res;
        }

        if (blen >= str_type::max_len)
        {
            full_str = Buffer4k;
            return token_type(
                Buffer,
                ss,
                !!(GetFlag() & SRC_IGNORE_TOKCASE),
                tokens
            );
        }
        else
        {
            full_str = Buffer4k;
            return do_tokenize && !(GetFlag()&SRC_DONT_TOKENIZE) ?
                token_type(
                    Buffer,
                    ss,
                    !!(GetFlag() & SRC_IGNORE_TOKCASE),
                    tokens
                )
                :
                token_type(Buffer, ss);
        }
    }


    /*****************************************************************************
     Читает лексему из потока и заносит ее в буфер Buffer. Входной параметр
     maxlen задает максимальную длину читаемой строки без учета терминирующего
     нуля, так что размер Buffer должен быть как минимум maxlen+1. Если указать
     maxlen==-1, то проверки переполнения не будет.
    *****************************************************************************/
    template < class CHAR >
    inline const SourceState Base_Parser<CHAR>::read(CHAR *Buffer, int maxlen)
    {
        *Buffer = 0; // Terminate the string for calling code doesn't
                   // worry about preparing Buffer.

        if (eof())
            return tellp();

        if (GetFlag() & SRC_READ_SIMPLE)
            return read_simple(Buffer, maxlen);

        bool overflow = false;

        eol_reached = false;

        wchar_t ch;
        int pos = 0;
        bool IsComment = false; // Если комментарий, =true

        pos_type ss(cache_fpos, line, symbol_pos);

        int i_limit1 = 100000; // Защита от зацикливани
        int i_limit2 = 100000;

        do
        {
            do
            {
                IsComment = false;
                pos = 0;

                skip_white();

                if (eof())
                    break;

                ss = tellp();
                ch = get();

                if (ch == Special_Char<CHAR>::eof() || eof())
                    break; // Конец файла

                if (ch == '\n')
                {
                    if (!(GetFlag()&SRC_SKIP_EOL))
                    {
                        Buffer[0] = static_cast<CHAR>(ch);
                        Buffer[1] = 0;
                        eol_reached = true;
                        return ss;
                    }

                    continue;
                }

                if (IsSpecial(ch))
                    continue;

                if (maxlen > 0 && pos >= maxlen)
                {
                    // Слишком длинная лексема.
                    if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                        Overflow();

                    overflow = true; // Сообщение выводим только один раз для читаемой лексемы.
                }
                else
                {
                    Buffer[pos++] = static_cast<CHAR>(ch); // Переносим символ в буфер
                    Buffer[pos] = 0; // Заканчиваем строку на всякий случай
                }

                if (
                    pos == 1 &&
                    GetFlag()&SRC_READ_FLOATING &&
                    (is_udigit(Buffer[0]) || Buffer[0] == '.')
                    )
                {
                    // Читаем числовое поле.
                    pos_type before_value = tellp();

                    if (!ReadValueField(Buffer, maxlen))
                    {
                        // Ошибка чтения числового поля - возвращаемся на начало и читаем
                        // как простую лексему.
                        seekp(before_value);
                    }
                    else
                        continue;
                }

                bool lexem_loaded = false;
                int i_limit = 1000000; // Защита от зацикливания
                while (!IsDelimiter(ch) && ch && i_limit--) // До разделителя
                {
                    if (maxlen > 0 && pos >= maxlen)
                    {
                        if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                            Overflow();

                        overflow = true;
                        ch = get(); // Символы не запоминаем, но читаем...
                    }
                    else
                    {
                        Buffer[pos] = static_cast<CHAR>(ch = get()); // Читаем строку символ за символом
                        Buffer[pos + 1] = 0;
                        pos++;
                    }

                    if (eof() || ch == Special_Char<CHAR>::eof())
                    {
                        if (!overflow)
                            Buffer[pos - 1] = 0;

                        lexem_loaded = true;
                        break;
                    }
                }

                if (lexem_loaded)
                    break;

                if (ch == '%' && pos == 1 && GetFlag()&SRC_SKIP_PROLOG_COMMENTARY)
                {
                    // Пропускаем прологовский комментарий % ....
                    SkipComm1();
                    IsComment = true;
                    Buffer[0] = 0;
                    continue;
                }

                if (ch == ';' && pos == 1 && GetFlag()&SRC_SKIP_LISP_COMMENTARY)
                {
                    // Пропускаем лисповский комментарий ; ....
                    SkipComm1();
                    IsComment = true;
                    Buffer[0] = 0;
                    continue;
                }

                if (ch == '{' && pos == 1 && GetFlag()&SRC_SKIP_PASCAL_COMMENTARY)
                {
                    // PASCAL-комментарий.
                    SkipComm2();
                    IsComment = true;                 // Повторим процесс чтени
                    Buffer[pos = 0] = 0; // Очистим буфер
                    continue;
                }

                if (ch == '/' && pos == 1) // Может это комментарий C++ или C ?
                {
                    wchar_t next_char = (wchar_t)get();       // Следующий символ

                    if (GetFlag()&SRC_SKIP_CPP_COMMENTARY && next_char == '/')
                    {
                        // C++ комментарий
                        SkipComm1();

                        IsComment = true;                 // Повторим процесс чтени
                        Buffer[pos = 0] = 0; // Буфер должен быть пустой
                        continue;
                    }

                    if (GetFlag()&SRC_SKIP_C_COMMENTARY && next_char == '*')
                    {
                        // C-комментарий.
                        SkipComm2();
                        IsComment = true;                 // Повторим процесс чтени
                        Buffer[pos = 0] = 0; // Очистим буфер
                        continue;
                    }

                    unget(); // Это не комментарий, поэтому вернем символ
                }

                if (pos > 1)                       // Если разделитель является единствен-
                {                                // ным символом, то оставим его
                    unget();                        // Возвращаем разделитель во входной поток
                    if (!overflow)
                        Buffer[--pos] = 0;   // Стираем разделитель
                }
                else                              // Возможно, имеем дело со сложным разделителем
                {
                    // Сложный разделитель может иметь до 3-х символов для C.
                    Buffer[1] = get();                // След. символ
                    Buffer[2] = 0;

                    // Тогда на 2-х
                    if (!IsComplexDelimiter(Buffer) || Buffer[1] == Special_Char<CHAR>::eof())// Если не сложный, то вернем символ
                    {
                        unget();
                        Buffer[1] = 0;
                    }
                    else
                    {
                        // Учитываем тот факт, что трех-символьные
                        // разделители являются комбинацией двух-символьных
                        // и знака '='.

                        Buffer[2] = get();
                        Buffer[3] = 0;
                        if (!IsComplexDelimiter(Buffer) || Buffer[2] == Special_Char<CHAR>::eof())
                        {
                            // Не, вернем символ в поток.
                            unget();
                            Buffer[2] = 0;
                        }
                    }
                }

                if (Buffer[0] == 0 && (eof() || ch == Special_Char<CHAR>::eof())) // Если считывать было нечего
                    return ss;
            } while (Buffer[0] == 0 && !eof() && i_limit1--); // Обязательно заполним буфер
        } while (IsComment && !eof() && i_limit2--); // Пропускаем C-комментарии

        if (overflow)
            Buffer[maxlen] = 0;

        // Символьные константы и строки требуют особого внимания - они
        // должны извлекаться полностью.

        if (Buffer[0] == '\'')
        {
            if (GetFlag()&SRC_READ_CHAR)
                Read_C_Char(Buffer, maxlen);
        }
        else
        {
            // Символ '"' является началом C-строки. Считываем лексему
            // до встречи с другим символом '"'.
            if (GetFlag()&SRC_READ_STRING && *Buffer == '"')
                Read_C_String(Buffer, maxlen);
        }

#if defined LEM_DEBUGNON
        lem_check_file(*file);
#endif

        return ss;
    }

    /*********************************************************
     Ускоренная процедура чтения токена из текстового файла.
     Используется вместо ::read в случае, если установлен
     флаг SRC_READ_SIMPLE. Данная процедура не умеет читать
     числа с плавающей точкой. Тем не менее, комментарии
     пропускаются!

     ВХОДНЫЕ ПАРАМЕТРЫ:

      Buffer - указатель на буфер читаемых символов.
      maxlen - максимально допустимая длина читаемой лексемы.


     ВОЗВРАЩАЕМЫЙ ПАРАМЕТР:

      Возвращается описатель положения считанной лексемы в
      файле (начало лексемы!).
    *********************************************************/
    template < class CHAR >
    inline const SourceState Base_Parser<CHAR>::read_simple(
        CHAR *Buffer,
        int maxlen
    )
    {
        bool overflow = false;
        Buffer[0] = 0; // Буфер принудительно пуст.

        eol_reached = false;

        wchar_t ch;
        int pos = 0;
        bool IsComment = false;   // Если комментарий, =true
        pos_type ss = tellp(); // Для сохранения контекста начала лексемы.

        if (eof())
            return ss;

        int i_limit1 = 100000; // Защита от зацикливани
        int i_limit2 = 100000;

        do
        {
            do
            {
                skip_white();
                IsComment = false;
                pos = 0;
                ss = tellp();
                ch = get();

                if (
                    ch == Special_Char<CHAR>::eof() ||
                    eof()
                    )
                    break; // Конец файла

                if (ch == '\n')
                    continue;

                if (IsSpecial(ch))
                    continue;

                if (maxlen > 0 && pos >= maxlen)
                    overflow = true;
                else
                {
                    Buffer[pos++] = (CHAR)ch; // Переносим символ в буфер
                    Buffer[pos] = 0; // Заканчиваем строку на всякий случай
                }

                bool lexem_loaded = false;
                int i_limit = 100000; // Защита от зацикливани
                while (!IsDelimiter(ch) && i_limit--) // До разделител
                {
                    if (maxlen > 0 && pos >= maxlen)
                    {
                        overflow = true;
                        ch = get();
                    }
                    else
                    {
                        Buffer[pos] = (CHAR)(ch = get()); // Читаем строку символ за символом
                        Buffer[pos + 1] = 0;
                        pos++;
                    }

                    if (eof() || ch == Special_Char<CHAR>::eof())
                    {
                        if (!overflow)
                            Buffer[pos - 1] = 0;

                        lexem_loaded = true;
                        break;
                    }
                }

                if (lexem_loaded)
                    break;

                if (ch == L'/' && pos == 1)           // Может это комментарий C++ или C ?
                {
                    wchar_t next_char = get();       // Следующий символ

                    if (GetFlag()&SRC_SKIP_CPP_COMMENTARY && next_char == L'/')
                    {
                        // C++ комментарий
                        SkipComm1();

                        IsComment = true;               // Повторим процесс чтени
                        Buffer[pos = 0] = 0; // Буфер должен быть пустой
                        continue;
                    }

                    if (GetFlag()&SRC_SKIP_C_COMMENTARY && next_char == L'*')
                    {
                        // C-комментарий.
                        SkipComm2();
                        IsComment = true;               // Повторим процесс чтени
                        Buffer[pos = 0] = 0;              // Очистим буфер
                        continue;
                    }

                    unget(); // Это не комментарий, поэтому вернем символ
                }

                if (pos > 1)                       // Если разделитель является единствен-
                {                                // ным символом, то оставим его
                    unget();                        // Возвращаем разделитель во входной поток
                    if (!overflow)
                        Buffer[--pos] = 0;// Стираем разделитель
                }
                else                              // Возможно, имеем дело со сложным разделителем
                    Buffer[1] = 0;

                if (Buffer[0] == 0 && (cache_fpos >= file_size || ch == Special_Char<CHAR>::eof()))      // Если считывать было нечего
                    return ss;
            } while (Buffer[0] == 0 && !eof() && i_limit1--); // Обязательно заполним буфер
        } while (IsComment && !eof() && i_limit2--); // Пропускаем C-комментарии

        if (overflow)
            // В случае переполнения принудительно терминируем лексему.
            Buffer[maxlen] = 0;

        // Символьные константы и строки требуют особого внимания - они
        // должны извлекаться полностью.

        // Символ '"' является началом C-строки. Считываем лексему
        // до встречи с другим символом '"'.
        if (GetFlag()&SRC_READ_STRING && Buffer[0] == L'"')
            Read_C_String(Buffer, maxlen);

#if defined LEM_DEBUGON
        file->Check();
#endif

        return ss;
    }

    /********************************************************************************
     Внутренняя процедура чтения С-строки.

     String constants, like in C/C++, are enclosed in double quote ("). Special
     characters are expressed within strings the same way as in character
     constants. All the special characters are the same as in character constants
     with the exception of (\n) which inserts both a carrage return and a line feed.
    *********************************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::Read_C_String(CHAR *Buffer, int maxlen)
    {
        fstr_type res;
        Read_C_String(res, maxlen);

        int ic = (int)res.length();
        int len = lem::min(maxlen, ic);
        if (len < 0)
            len = ic;

        if (ProbeFlag(SRC_STRIP_STRING) && ProbeFlag(SRC_READ_STRING))
        {
            // Отсекаем концевые апострофы.
            if (ic == 1)
                Buffer[ic = 0] = 0;
            else if (len)
            {
                lem_strcpy(Buffer, res.c_str());
                Buffer[len - 1] = 0;
            }
        }
        else
        {
            // Добавляем считанную строку к начальному апострофу.
            lem_strncat(Buffer + 1, res.c_str(), maxlen - 1);
            const int lll = lem_strlen(Buffer);

            if (Buffer[lll - 1] != L'"')
                // Correct error: closing ["] character is missing.
                Buffer[lll - 1] = L'"';

            Buffer[lll] = 0;
        }

        return;
    }

    /******************************************************************************
     Вспомогательный класс-контейнер для загрузки цепочки символов неизвестной
     заранее длины. Благодаря увеличению размера выделенного куска памяти большими
     шагами уменьшаются потери процессорного времени на работу с глобальной кучей.
    *******************************************************************************/
    template < class CHAR >
    struct SrcMemBuf : public std::vector<CHAR>
    {
#if defined __MINGW32__ || defined LEM_GNUC
        inline typename std::vector<CHAR>::const_iterator begin(void) const { return std::vector<CHAR>::begin(); }
        inline void reserve(typename std::vector<CHAR>::size_type n) { std::vector<CHAR>::reserve(n); }
        inline bool empty(void) const { return std::vector<CHAR>::empty(); }
        inline CHAR operator[](typename std::vector<CHAR>::size_type i) const { return std::vector<CHAR>::operator[](i); }
        inline CHAR operator[](typename std::vector<CHAR>::size_type i) { return std::vector<CHAR>::operator[](i); }
#endif

        SrcMemBuf(void) { reserve(256); }

        inline const CHAR* content(void) const
        {
            return empty() ? NULL : static_cast<const CHAR*>(&*begin());
        }
    };

    template < class CHAR >
    inline void Base_Parser<CHAR>::Read_C_String(
        typename ChooseStr<CHAR>::FSTR &Buffer,
        int maxlen
    )
    {
        wchar_t ch;
        int len = 0;
        bool wasslash = false;
        bool overflow = false;

        SrcMemBuf<CHAR> buf;

        int i_limit = 1000000; // Защита от зацикливани

        while (i_limit--)
        {
            ch = (CHAR)get();

            if (eof() || ch == Special_Char<CHAR>::eof())
                break;

            if (ch == '\n' || ch == '\r')
            {
                // Недопустимая ситуация - отсутствует символ закрытия C-строки.
                break;
            }

            if (GetFlag()&SRC_PROCESS_C_CHAR && ch == L'\\')
            {
                lem::uint32_t ucs4 = Read_After_Slash();
                if (sizeof(wchar_t) == 4 || ucs4 < 0x00010000)
                {
                    if (maxlen < 0 || len < maxlen)
                    {
                        buf.push_back(ucs4);
                        len++;
                    }
                    else
                    {
                        if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                            Overflow();

                        Read_After_Slash();
                        overflow = true;
                    }
                }
                else
                {
                    LEM_CHECKIT_Z(sizeof(CHAR) != 1);

                    if (maxlen < 0 || len < maxlen - 1)
                    {
                        lem::uint32_t x = ucs4 - 0x00010000;
                        lem::uint16_t high_surrogate = 0xD800 + lem::uint16_t((x >> 10) & 0x3FF);
                        lem::uint16_t low_surrogate = 0xDC00 + lem::uint16_t(x & 0x3FF);
                        buf.push_back((CHAR)high_surrogate);
                        buf.push_back((CHAR)low_surrogate);
                        len += 2;
                    }
                    else
                    {
                        if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                            Overflow();

                        Read_After_Slash();
                        overflow = true;
                    }
                }

                continue;
            }

            if (!wasslash && ch == L'"')
            {
                // Встречен закрывающий апостроф - конец строки.
                if (GetFlag() & SRC_READ_STRING)
                {
                    if (maxlen < 0 || len < maxlen)
                    {
                        buf.push_back(CHAR(ch));
                        len++;
                    }
                    else
                    {
                        if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                            Overflow();

                        overflow = true;
                    }
                }

                break;
            }

            if (maxlen < 0 || len < maxlen)
            {
                buf.push_back(CHAR(ch));
                len++;
            }
            else
            {
                if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                    Overflow();

                overflow = true;
            }

            if (!(GetFlag()&SRC_PROCESS_C_CHAR) && ch == L'\\' && !wasslash)
            {
                wasslash = true;
                continue;
            }

            wasslash = false;
        }

        if (!buf.empty())
        {
            // Терминируем накопленную строку.
            buf.push_back(0);
            Buffer = buf.content();
        }
        else
            Buffer = "";

        return;
    }

    /******************************************************************
     Считываем необходимое количество символов после '\' при обработке
     C-строки или C-символа.
    *******************************************************************/
    template < class CHAR >
    inline int Base_Parser<CHAR>::Read_After_Slash(void)
    {
        wchar_t Code[LEN + 1];
        wchar_t ch = (wchar_t)get();
        int radix = 10; // Основание системы счисления, в которой записан код.

        // ЗртхЁшхэшх фрщыр тююсщх-тю эх фюыцэю сыть чфхёь. Ню Ёрч уц тётЁхтшыюёь,
        // тю эрфю чтю-тю фхырть. Тръ ъръ яЁш чтхэшш юсычэых тхъётют (эх c-яЁюуЁрьь)
        // фюЁьрт \xxx ёютёхь эх ятыяхтёя ъръшь-тю юсячртхыьэыь, тю ъюэхц фрщыр эх
        // ЁрёёьртЁштрхь ъръ юшшсъу, хютя яЁш чтхэшш тхъётр c-яЁюуЁрььы чфхёь фюыцэр
        // ухэхЁшЁютртьёя юшшсър.
        if (eof() || ch == Special_Char<CHAR>::eof())
            return 0;

        switch (ch)
        {
        case L'x':
        {
            radix = 16;
            ch = get();

            if (eof() || ch == Special_Char<CHAR>::eof())
                LEM_STOPIT;
            break;
        }

        case L'o':
        {
            radix = 8;
            ch = get();

            if (eof() || ch == Special_Char<CHAR>::eof())
                LEM_STOPIT;

            break;
        }

        case L'u':
        {
            // считываем 4 hex-символа и возвращаем как 16-битное целое
            for (int i = 0; i < 4; ++i)
            {
                wchar_t c = get();
                Code[i] = c;
                if (c == 0)
                    throw E_BaseException();
            }

            Code[4] = 0;
            int res;
            if (!to_int(Code, &res, 16))
                throw E_BaseException();

            return res;
        }

        case L'U':
        {
            // считываем 8 hex-символов и возвращаем как 32-битное целое
            for (int i = 0; i < 8; ++i)
            {
                wchar_t c = get();
                Code[i] = c;
                if (c == 0)
                    throw E_BaseException();
            }

            Code[8] = 0;
            int res;
            if (!to_int(Code, &res, 16))
                throw E_BaseException();

            return res;
        }
        }

        if (is_udigit(ch) || (radix == 16 || is_uhex_digit(ch)))
        {
            int ic = 0;

            Code[ic++] = ch;

            FOREVER
            {
             ch = get();

             if (eof() || ch == Special_Char<CHAR>::eof())
              break;

             if ((radix != 16 && !is_udigit(ch)) || (radix == 16 && !is_uhex_digit(ch) && !is_udigit(ch)))
              {
               unget();
               break;
              }

             Code[ic++] = ch;
            }

            Code[ic] = 0;

            int res;
            to_int(Code, &res, radix);
            return res;
        }

        switch (ch)
        {
        case wchar_t('a') : return L'\a';
        case wchar_t('f') : return L'\f';
        case wchar_t('t') : return L'\t';
        case wchar_t('n') : return L'\n';
        case wchar_t('r') : return L'\r';
        case wchar_t('b') : return L'\b';
        case wchar_t('\\') : return L'\\';
        default:   return ch;
        }

        //   return 0; // Unreachable code
    }

    template < class CHAR >
    inline const typename Base_Parser<CHAR>::str_type Base_Parser<CHAR>::read_c_char(void)
    {
        CHAR Buffer[LEN + 1];
        Buffer[0] = 0;
        Read_C_Char(Buffer, LEN);
        return str_type(Buffer);
    }

    /******************************************************************************
                          Character Constants.

     Single character constants are, like in C/C++, enclosed in single
     quotes ('). Also like in C/C++, special characters are expressed
     by a back slash (\) followed by the key letter or letters. Special
     characteds supported are:

                '\a'    - alert
                '\b'    - backspace
                '\f'    - form feed
                '\l'    - line feed
                '\n'    - carrage return
                '\r'    - return to beginning of current line
                '\t'    - tabulation
                '\x??'  - ASCII character formed from ?? which would be two
                          hexadecimal digits for the characted value.
                '\???'  - like the previous format, but ??? are three decimal
                          digits (0 to 9).
                '\o???' - like the previous format, but ??? are three octal
                          digits (0 to 7).

     Any other character following a back slash is just accepted. This allows
     the single quote to be included by '\'', for '' is the NULL chacter. Sovereign
     Subsystem treats all chacter constants as a numeric value of the ASCII value
     of the character (65 for 'A', 97 for 'a', et cetera).
    *******************************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::Read_C_Char(CHAR *Buffer, int maxlen)
    {
        // Мы встретили символьную константу C/C++, заключенную в одиночные
        // кавычки '...'. Извлекаем ее полностью.

        // Перепишем в буфер ВСЮ символьную константу.
        int ic = lem_strlen(Buffer);
        bool overflow = false;

        if (GetFlag()&SRC_STRIP_STRING && ic == 1)
        {
            // Удаляем начальный апостроф.
            Buffer[ic = 0] = 0;
        }

        wchar_t ch;
        bool wasslash = false;
        bool was_load = false;

        int i_limit = 1000000; // Защита от зацикливани

        while (i_limit--)
        {
            ch = get();

            if (eof() || ch == Special_Char<CHAR>::eof())
                break;

            if (!wasslash && ch == L'\'')
            {
                // Встречен закрывающий апостроф - конец определения символа.

                if (!was_load)
                {
                    if (GetFlag()&SRC_STRIP_STRING)
                    {
                        Buffer[ic++] = 0;
                    }
                    else if (maxlen > 0 && ic < (maxlen - 1))
                    {
                        Buffer[ic++] = (CHAR)ch;
                        Buffer[ic++] = 0;
                    }
                }

                if (GetFlag() & SRC_READ_CHAR)
                {
                    if (maxlen > 0 && ic >= maxlen)
                    {
                        if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                            Overflow();

                        overflow = true;
                    }
                    else
                        Buffer[ic++] = static_cast<CHAR>(ch);
                }

                break;
            }

            was_load = true;

            if (ch == L'\n')
            {
                // Недопустимая ситуация - отсутствует символ закрытия символьной константы.
                break;
            }

            if (GetFlag()&SRC_PROCESS_C_CHAR && ch == L'\\')
            {
                if (maxlen > 0 && ic >= maxlen)
                {
                    if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                        Overflow();

                    Read_After_Slash();
                    overflow = true;
                }
                else
                    Buffer[ic++] = Read_After_Slash();

                continue;
            }

            if (maxlen > 0 && ic >= maxlen)
            {
                if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                    Overflow();

                overflow = true;
            }
            else
                Buffer[ic++] = static_cast<CHAR>(ch);

            if (!(GetFlag()&SRC_PROCESS_C_CHAR) && ch == L'\\' && !wasslash)
            {
                wasslash = true;
                continue;
            }

            wasslash = false;
        }

        if (!overflow)
        {
            if (GetFlag()&SRC_STRIP_STRING && GetFlag()&SRC_READ_CHAR && ic > 1)
                Buffer[ic - 1] = 0;
            else
                Buffer[ic] = 0;
        }
        else
            Buffer[maxlen] = 0;

        return;
    }

    /*******************************************************************
     Чтение числового поля в одном из форматов C/C++.
     Распознаются специфические форматы языка C/C++:

                     0xABCD - hexadecimal
                     0o1234 - octal
                     0b0101 - binary

     Возвращает true, если число нормально прочитано. Если лексему не
     удается прочитать как число (например начинается с цифры, а затем
     идет другой символ - '1r'), то возвращается false.
    *******************************************************************/
    template < class CHAR >
    inline bool Base_Parser<CHAR>::ReadValueField(CHAR *Buffer, int maxlen)
    {
        wchar_t ch = Buffer[0];
        int pos = 0;
        bool overflow = false;
        int radix = 10;

        // Часть до десятичной точки или до знака показателя.
        bool do_load = true;
        int i_limit = 100000;
        while (do_load && !eof() && i_limit)
        {
            if (maxlen > 0 && pos >= maxlen)
            {
                if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                    Overflow();

                overflow = true;
            }
            else
            {
                Buffer[pos++] = static_cast<CHAR>(ch);
                Buffer[pos] = 0;
            }

            ch = get();

            if (pos == 1 && Buffer[0] == L'0' && !is_udigit(ch) && ch != L'.')
                switch (ch)
                {
                case L'x': radix = 16; break;
                case L'o': radix = 8;  break;
                case L'b': radix = 2;  break;
                default:
                    do_load = false;
                    break;
                }
            else
            {
                if (radix == 16 && is_uhex_digit(ch))
                    continue;

                if (!is_udigit(ch))
                    break;
            }
        }

        if (radix != 10)
        {
            // Только целые числа могут быть записаны в системе счисления с другим
            // основанием.
            unget();
            return false;
        }

        if (eof())
            return true;

        // Загружаем дробную часть, если она есть - после десятичной точки
        if (ch == L'.')
        {
            if (maxlen > 0 && pos >= maxlen)
            {
                if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                    Overflow();

                overflow = true;
            }
            else
            {
                Buffer[pos++] = static_cast<CHAR>(ch);
                Buffer[pos] = 0;
            }

            ch = get();

            while (is_udigit(ch))
            {
                if (maxlen > 0 && pos >= maxlen)
                {
                    if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                        Overflow();

                    overflow = true;
                }
                else
                {
                    Buffer[pos++] = static_cast<CHAR>(ch);
                    Buffer[pos] = 0;
                }

                if (pos >= maxlen)
                    pos = 0;

                ch = get();
            }
        } // конец загрузки дробной части после десятичной точки

        if (eof())
            return true;

        // Загружаем экспоненту, если она есть
        if (
            (is_udigit(Buffer[0]) ||
            (Buffer[0] == L'.' && is_udigit(Buffer[1])))
            &&
            is_uexponent(ch)
            )
        {
            if (maxlen > 0 && pos >= maxlen)
            {
                if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                    Overflow();

                overflow = true;
            }
            else
            {
                Buffer[pos++] = static_cast<CHAR>(ch);
                Buffer[pos] = 0;
            }

            ch = get();

            if (is_usignum(ch))
            {
                if (maxlen > 0 && pos >= maxlen)
                {
                    if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                        Overflow();

                    overflow = true;
                }
                else
                {
                    Buffer[pos++] = static_cast<CHAR>(ch);
                    Buffer[pos] = 0;
                }

                ch = get();
            }

            // Показатель степени
            int i_limit = 10000;
            while (is_udigit(ch) && !eof() && i_limit--)
            {
                if (maxlen > 0 && pos >= maxlen)
                {
                    if ((GetFlag() & SRC_CONTROL_OVERFLOW) && !overflow)
                        Overflow();

                    overflow = true;
                }
                else
                {
                    Buffer[pos++] = static_cast<CHAR>(ch);
                    Buffer[pos] = 0;
                }

                ch = get();
            }
        } // конец загрузки экспоненты
        else
        {
            if (ch && !IsDelimiter(ch) && ch != Special_Char<CHAR>::eof())
                return false;
        }

        unget();
        return true;
    }

    /********************************************************************
      От текущей позиции бежим к началу текущей строки. Процедура
      используется для вывода сообщения об ошибке, когда распечатываетс
      строка с указанием проблемного места.

      В первой строке бежим до начала файла. В остальных - до символа
      конца предыдущей строки.
    *********************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::ToLineBegin(void)
    {
        wchar_t ch;

        // Synchronize the read position in file and cache cursor cache_fpos.
        file->seekp((lem::Stream::off_type)cache_fpos);

        // Move backwards until the EOL char is read or file beginning is reached.
        long i_limit = 100000l;
        while (i_limit--)
        {
            const lem::Stream::pos_type pos = file->tellp();

            if (!pos)
                break;

            file->seekp(-1, SEEK_CUR);

            ch = (*file)();
            if (ch == L'\n' || ch == L'\r')
                break;

            file->seekp(-1, SEEK_CUR);
        }

        LoadCache();
        return;
    }

    /********************************************************************
     От текущей позиции перемещаемся к концу строки, причём указатель
     считывания устанавливается на символе, следующем за символом конца
     строки.
    *********************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::ToLineEnd(void)
    {
        wchar_t ch;

        // Synchronize the read position in file and cache cursor cache_fpos.
        file->seekp(cache_fpos);

        long i_limit = 100000l;
        while (!file->eof() && i_limit--)
        {
            ch = (*file)();
            if (ch == L'\n' || ch == L'\r')
                break;
        }

        LoadCache();
        return;
    }

    template < class CHAR >
    inline bool Base_Parser<CHAR>::SeekLine(int iline)
    {
        file->rewind();
        /*
           while( !eof() )
            {
             token_type t = read();
             if( t.GetBegin().line+1 == iline )
              {
               ToLineBegin();
               return true;
              }
            }
        */
        LEM_CHECKIT_Z(iline >= 0);
        int line_counter = 1;
        while (!file->eof())
        {
            if (line_counter == iline)
            {
                LoadCache();
                return true;
            }

            wchar_t ch = (*file)();
            if (ch == L'\n')
                line_counter++;
        }

        return false;
    }

    /******************************************************************
     Печатаем текущую строку от текущей позиции до конца. Используется
     при выводе сообщений об ошибке. Обращаю внимание на такую
     особенность. Мы сначала накапливаем символы в буфере, а потом
     разом кидаем буфер в поток to. Такая схема нужна, если поток
     to сконфигурирован на сброс буфера (flush) после выдачи очередного
     элемента, и to является потоком для ошибок в MS Windows. В этом
     случае flush потока приводит к высвечиванию символов в буфере
     в специальном MessageBox'е. Если кидать символы строки по одному,
     то каждый символ будет выведен в отдельном MessageBox'е, что
     является бредом. Кинув же содержимое строки целиком в поток to,
     мы будем уверены, что flush сработает только после приемки
     последнего символа строки.
    *******************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::PrintLine(OFormatter &to)
    {
        fstr_type buffer;
        int i_limit = 100000;

        while (i_limit--)
        {
            const wchar_t ch = wchar_t(get());

            if (ch == L'\n' || eof() || ch == Special_Char<CHAR>::eof())
                break;

            if (ch == L'\t')
            {
                // табуляция имеет разную ширину, зависящую от настройки
                // отображающего редактора, поэтому заменим ее одним пробелом.
                buffer += static_cast<CHAR>(' ');
            }
            else
            {
                buffer += static_cast<CHAR>(ch);
            }
        }

        to << buffer.c_str();

        return;
    }

    template < class CHAR >
    inline lem::int16_t Base_Parser<CHAR>::read_int16(void)
    {
        const token_type t = read(false);
        const str_type& str = t.string();

        if (str == L'-' || str == L'+')
            str += read(false).string();

        lem::int16_t res = 0;
        const bool correct = lem_str_c_to_int16(str, &res);

        if (correct)
            return res;

#if defined LEM_DEBUGON

        Error(t);
        GetMerr() << "Incorrect lem::int16_t field: " << str << "\n";
        LEM_STOPIT;

#endif

        return res;
    }

    template < class CHAR >
    inline lem::int32_t Base_Parser<CHAR>::read_int32(void)
    {
        const token_type t = read(false);
        str_type str = t.string();

        if (str == "-" || str == "+")
            str += read(false).string();

        lem::int32_t res = 0;
        const bool correct = str_c_to_int(str.c_str(), &res);

        if (correct)
            return res;

#if defined LEM_DEBUGON

        Error(t);
        GetMerr() << "Incorrect INT32 field: " << str << "\n";
        LEM_STOPIT;

#endif

        return res;
    }

#if !defined LEM_NOREAL
    template < class CHAR >
    inline double Base_Parser<CHAR>::read_real(void)
    {
        const token_type t = read(false);
        str_type str = t.string();

        if (str == L'-' || str == L'+')
            str += read(false).string();

        double res = 0.;
        const bool correct = to_real(str.c_str(), &res);

        if (correct)
            return res;

#if defined LEM_DEBUGON

        Error(t);
        GetMerr() << "Incorrect double field: " << str << "\n";
        LEM_STOPIT;

#endif

        return res;
    }
#endif

    template < class CHAR >
    inline bool Base_Parser<CHAR>::read_bool(void)
    {
        const token_type t = read(false);
        const str_type &str = t.string();

        bool res;
        const bool correct = to_bool(str.c_str(), &res);

#if defined LEM_DEBUGON
        if (!correct)
        {
            Error(t);
            GetMerr() << "Incorrect BOOLEAN field: " << str << "\n";
        }
#endif

        return res;
    }

    /****************************************************************************
     SolToken enforcer. Called whenever syntax requires a lexem to be next in line.
    *****************************************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::read_it(const str_type& needed)
    {
        const token_type t = read(false);

        if (!lem_eq(t.string().c_str(), t.c_str()))
        {
            Error(t, needed.length());
            UFString u1(to_unicode(needed.c_str()).c_str());
            UFString u2(t.GetUnicode().c_str());
            GetMerr().printf("Missing [%vfE%us%vn], got [%us]\n", u1.c_str(), u2.c_str());
            LEM_STOPIT;
        }

        return;
    }

    // ***********************************************
    // Scans lexems until given token reached. Cursor
    // is set AFTER that lexem.
    // ***********************************************
    template < class CHAR >
    inline void Base_Parser<CHAR>::SeekForToken(int Token)
    {
        long i_limit = 100000l; // Для предотвращения зацикливания
        while (!eof() && i_limit--)
            if (read().GetToken() == Token)
                break;

        return;
    }

    /*********************************************************
     Требуется прочитать лексему-токен, заданную через индекс
     для таблицы токенов нашего класса.
    **********************************************************/
    template < class CHAR >
    inline void Base_Parser<CHAR>::read_it(int token)
    {
        const token_type t = read();

        if (t.GetToken() != token)
        {
            Error(t);

#if defined LEM_RUSSIAN
            GetMerr() << "Отсутствует [" << tokens[token] << "]";
#else
            GetMerr() << "Missing [" << tokens[token] << "]";
#endif

            LEM_STOPIT;
        }

        return;
    }

    /************************************************************************
     Читаем строку символов в формате C длиной не более заданной как maxsize.
     Если задать maxsize<=0, то загружаем все символы строки с динамическим
     определением ее длины.
    *************************************************************************/
    template < class CHAR >
    inline const typename Base_Parser<CHAR>::fstr_type Base_Parser<CHAR>::read_fstring(int maxsize)
    {
        bool first_quote = false;
        skip_white();

        if (eof())
            return fstr_type();

        if (get() != L'"')
            unget();
        else
            first_quote = true;

        typename ChooseStr<CHAR>::FSTR res;

        if (maxsize > 0)
        {
            CHAR *buffer = new CHAR[maxsize + 2];

            if (first_quote)
            {
                buffer[0] = L'"';
                buffer[1] = 0;
                Read_C_String(buffer, maxsize);
            }
            else
                read(buffer, maxsize);

            res = buffer;
            delete buffer;
        }
        else
        {
            typename ChooseStr<CHAR>::FSTR buffer;
            Read_C_String(buffer);

            if (first_quote)
#if defined LEM_BORLAND
                res = ChooseStr<CHAR>::FSTR(L'"') + buffer;
#elif defined LEM_MSC && _MSC_VER<=1200
                res = ChooseStr<CHAR>::FSTR(L'"') + buffer;
#else
                res = typename ChooseStr<CHAR>::FSTR(L'"') + buffer;
#endif
            else
                res = buffer;
        }

        if (GetFlag() & SRC_STRIP_STRING)
            res.strip_quotes();

        return res;
    }


    template < class CHAR >
    inline Base_Parser<CHAR>& operator >> (Base_Parser<CHAR>& in, short &d)
    {
        d = in.read_short();
        return in;
    }

    template < class CHAR >
    inline Base_Parser<CHAR>& operator >> (Base_Parser<CHAR>& in, int &d)
    {
        d = (int)in.read_int();
        return in;
    }

    template < class CHAR >
    inline Base_Parser<CHAR>& operator >> (Base_Parser<CHAR>& in, long &d)
    {
        d = in.read_long();
        return in;
    }

#if !defined LEM_NOREAL
    template < class CHAR >
    inline Base_Parser<CHAR>& operator >> (Base_Parser<CHAR>& in, double &r)
    {
        r = in.read_real();
        return in;
    }
#endif


    /*************************************************************************
    // Размер lookahead кэша символов из файла. Данная константа настроена на
    // максимальную эффективность чтения последовательных лексем одна за
    // другой из простого текстового файла без комментариев.
    **************************************************************************/
    class Base_A_Parser : public Base_Parser<char>
    {
    private:
        /**************************************************************************
         Заполняем кэш символов. Последний считанный символ из предыдущего
         наполнения кэша перейдет в самую первую позицию кеша, так что
         операция unget() можут быть свободно использована и после перегрузки кеша.
        ***************************************************************************/
        void LoadCache(void)
        {
            cache[0] = cache[cache_cursor - 1];
            cache_cursor = 1;
            cache_fpos = file->tellp();

            for (size_t i = 1; i < DIM_A(cache); i++)
                cache[i] = (*file)();

            return;
        }

    public:
        Base_A_Parser(void) :Base_Parser<char>() {}

        Base_A_Parser(const std::vector< CString > &tokens)
            :Base_Parser<char>(tokens) {}

        //    Base_A_Parser( const char *filename )
        //    :Base_Parser<char>(filename) {}
    };



    // ************************************************************************
    // Без кэширования - используется в случаях, когда
    // предзагрузка данных в кэш может быть неприемлемой (например при загрузке
    // из канала передачи данных по сети).
    // ************************************************************************
    class Text_NC_Parser : public Base_A_Parser
    {
    private:
        virtual void LoadCache(void) {}

    public:
        Text_NC_Parser(void) {}

        //    Text_NC_Parser( int NTOKEN=0, Base_A_Parser::str_type *TOKENS=NULL )
        //     :Base_A_Parser(NTOKEN,TOKENS) {}

        virtual int get(void)
        {
            LEM_CHECKIT_Z(file);
            return (*file)();
        }

        // There is no way to get back - so throw exception
        virtual void unget(void) { LEM_STOPIT; }

        bool eof(void) const { return file->eof(); }
    };


    // *******************************************************
    // Головной класс ЛЕКСИЧЕСКИЙ ПАРСЕР для UNICODE-символов.
    // *******************************************************
    class CodeConverter;

    class UTextParser : public Base_Parser<wchar_t>
    {
    public:
        UTextParser(void) : Base_Parser<wchar_t>() {}
        UTextParser(const std::vector<UCString> &Tokens)
            :Base_Parser<wchar_t>(Tokens) {}

        virtual void Open(lem::Ptr<lem::Char_Stream::WideStream> File)
        {
            Preset();
            Base_Parser<wchar_t>::Open(File);
            return;
        }
    };

    typedef Base_Parser<char>::token_type    AToken;
    typedef Base_Parser<wchar_t>::token_type UToken;

    typedef Base_A_Parser Text_Parser;

} // end of namespace 'lem'

#endif
