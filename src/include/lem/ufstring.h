#ifndef LEM_UFSTRING__H
#define LEM_UFSTRING__H
#pragma once

#include <lem/config.h>
#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>

#include <lem/strings.h>

namespace lem
{
    extern int lem_strlen(const char*);
    extern int lem_strlen(const wchar_t*);

    extern wchar_t* to_lower(wchar_t *s);
    extern wchar_t* to_upper(wchar_t *s);

    extern int to_int(const wchar_t *s);
    extern bool to_bool(const wchar_t *s);

    class Stream;

    class UFString : public std::wstring
    {
    public:
        UFString() :std::wstring() {}
        UFString(const UFString &s) :std::wstring(s) {}
        UFString(const std::wstring &s) :std::wstring(s) {}
        UFString(const wchar_t *ustr)
        {
            if (!lem_is_empty(ustr))
            {
                operator=(ustr);
            }
        }

        explicit UFString(const char *astr);

        // ************************************************************
        // Создание строки, состоящей из одного заданного символа ch.
        // ************************************************************
        explicit UFString(wchar_t Ch);

        // ***************************************************
        // Создается строка, состоящая из nTime символов ch.
        // ***************************************************
        UFString(size_type nTime, wchar_t ch);

        // *************************************************************
        // Создается строка из символов от beg до end-1,
        // терминирующий нуль добавляется к результату автоматически.
        // *************************************************************
        UFString(const wchar_t *beg, const wchar_t *end) :std::wstring(beg, end) {}

        // Конструкторы конкатенации
        //UFString( const UFString& s1, const UFString& s2 );
        //UFString( const UFString& s1, const UFString& s2, const UFString& s3 );


        UFString& operator=(const char *s);
        UFString& operator=(const wchar_t *s);
        UFString& operator=(const UFString& s)
        {
            std::wstring::operator=((const std::wstring&)s);
            return *this;
        }

        UFString& operator=(wchar_t ch);

        inline wchar_t get(size_t i) const { return i>=length() ? wchar_t(0) : at(i); }

        // *******************************************************************
        // Возвращается последний символ в строке (перед терминирующим '\0').
        // Для пустой строки возвращается '\0'
        // *******************************************************************
        wchar_t last_char(int i = 0) const;

        void set(int i, wchar_t ch) { at(i) = ch; }

        UFString& reduce(int i);
        void insert_char(int pos, wchar_t ch);
        void remove(int pos);

        UFString& operator+=(const char *s);
        UFString& operator+=(wchar_t ch);
        UFString& operator+=(const wchar_t *s);
        UFString& operator+=(const UFString& s);

        int count(wchar_t ch) const;
        int find_char(wchar_t ch) const;
        int find_last_of(wchar_t ch) const;
        int rfind(wchar_t ch) const { return find_last_of(ch); }

        int search(wchar_t to_find, int nentry = 1) const;
        int search(const UFString &to_find, int nentry = 1) const;
        int search(const char *to_find, int nentry = 1) const;
        int search(const wchar_t *to_find, int nentry = 1) const;

        // Поиск подстроки без учета регистра
        int searchi(const UFString &to_find, int nentry = 1) const;

        int search_from(wchar_t to_find, int start_pos) const;
        int search_from(const UFString &to_find, int start_pos) const;
        int search_from(const char *to_find, int start_pos) const;
        int search_from(const wchar_t *to_find, int start_pos) const;

        int searchi_from(const UFString &to_find, int start_pos) const;

        // Совпадает ли начало строки с указанным паттерном. Суффикс 'i' - без учета регистра
        bool eq_beg(const UFString &to_find) const;
        bool eq_begi(const UFString &to_find) const;
        bool eq_beg(const wchar_t* to_find) const;
        bool eq_begi(const wchar_t* to_find) const;
        bool eq_beg(const char* to_find) const;

        // Совпадает ли конец строки с указанным паттерном
        bool eq_end(const wchar_t* to_find) const;
        bool eq_end(const UFString & to_find) const;

        // ***********************************************
        // Строки совпадают без учета регистра?
        // ***********************************************
        bool eqi(const UFString &x) const;
        bool eqi(const wchar_t *x) const;

        // ********************************************
        // Замена вхождения строки на другую строку
        // ********************************************
        UFString& subst(
            const UFString &mask,
            const UFString &text,
            int nentry = 1
        );

        // Заменяем все вхождения строки mask на строку text.
        //UFString& subst_all(const UFString &mask, const UFString &text, bool case_sensitive = true);
        UFString& subst_all(const UFString &mask, const UFString &text);
        UFString& subst_all(wchar_t old_ch, wchar_t new_ch);

        UFString& to_upper(void);
        UFString& to_lower(void);
        UFString& to_Aa(void);

        // ***********************************************************************
        // Отбрасывает двойные апостофы, обрамляющие строку. Если на концах строки
        // находятся не апострофы, то строка не меняется.
        // ***********************************************************************
        UFString& strip(wchar_t Bound);
        UFString& strip_quotes(void);
        UFString& strip_apostrophes(void);

        UFString& dress(wchar_t Bound);
        UFString& dress_quotes(void);
        UFString& dress_apostrophes(void);

        UFString& trim(void);
        UFString& add_spaces(int n);
        UFString& expand_to(int n);
        UFString& cut(int from, int upto);

        // *********************************************************
        // Урезает строку до новой длины new_len. Если строка короче,
        // чем new_len, то ничего не происходит.
        // *********************************************************
        UFString& truncate_to(int new_len);

        // *****************************************************************
        // Если содержится пустая строки и указатель из-за оптимизации 
        // равен NULL, то выделяем строку с единственным символом '\0'.
        // Это необходимо для некоторых C'шных функций, которые в качестве
        // аргумента получают c-строку и валятся на NULL.
        // *****************************************************************
        void re_clear(void);

        //int    to_int(void)  const;
        //bool   to_bool(void) const;

        // Потоковые операции - запись и сохранение строки
        void SaveBin(Stream &bin) const;
        void LoadBin(Stream &bin);

        wchar_t* get_copy() const;
    };





    /**************************************************************************
      Возвращает символ, содержащийся в позиции, отсчитываемой от конца строки.
      То есть last_char(0) вернет последний символ перед '\0'. При выходе за
      пределы существующей строки возвращаем '\0'.
    ***************************************************************************/

    inline wchar_t UFString::last_char(int i) const
    {
        const size_t pos = length() - i - 1;
        return pos >= length() ? 0 : get(pos);
    }

    /************************************************************************
     Определяет число появлений символа ch в строке s. Функция может
     использоваться для определения самого факта появления символа в строке
     так как отсутствие таковых дает нулевой результат (то есть 'false'!).
    *************************************************************************/

    inline int UFString::find_char(wchar_t ch) const
    {
        return lem_nentry(c_str(), ch);
    }

    /**************************************************************************
      Находит n-ое (по умолчанию первое) вхождение символа ch в строку-аргумент
      s. Если символ не найден, или число его вхождений менее nentry, то
      возвращается -1.
    **************************************************************************/

    inline int UFString::search(wchar_t ch, int nentry) const
    {
        return lem_find(c_str(), ch, nentry);
    }


    inline int UFString::count(wchar_t ch) const
    {
        int n = 0;
        for (wchar_t c : *this)
        {
            if (c == ch)
            {
                n++;
            }
        }

        return n;
    }

    /***************************************************************************
     Определяет положение nentry-го вхождения подстроки [f] в строку [s].
     Возвращает индекс первого совпавшего символа. Если подстрока не
     обнаружена, или число ее появлений в строке менее nentry, то возвращаем -1.
    ****************************************************************************/

    inline int UFString::search(const UFString &f, int nentry) const
    {
        return lem_find(c_str(), f.c_str(), nentry);
    }

    inline int UFString::searchi(const UFString &f, int nentry) const
    {
        return lem_findi(c_str(), f.c_str(), nentry);
    }

    inline int UFString::search(const char *to_find, int nentry) const
    {
        return lem_find(c_str(), to_find, nentry);
    }


    inline int UFString::search(const wchar_t *to_find, int nentry) const
    {
        return lem_find(c_str(), to_find, nentry);
    }



    inline int UFString::search_from(const UFString &to_find, int start_pos) const
    {
        return lem_find_from(c_str(), to_find.c_str(), start_pos);
    }


    inline int UFString::searchi_from(const UFString &to_find, int start_pos) const
    {
        return lem_findi_from(c_str(), to_find.c_str(), start_pos);
    }


    inline int UFString::search_from(const char *to_find, int start_pos) const
    {
        return lem_find_from(c_str(), to_find, start_pos);
    }


    inline int UFString::search_from(const wchar_t *to_find, int start_pos) const
    {
        return lem_find_from(c_str(), to_find, start_pos);
    }


    inline int UFString::search_from(wchar_t to_find, int start_pos) const
    {
        return lem_find_from(c_str(), to_find, start_pos);
    }


    extern const UFString add_spaces(const UFString& s, int n);
    extern const UFString trim(const UFString &s);
    extern const UFString expand_to(const UFString &s, int n);


    inline bool operator==(const UFString &s1, const char *s2)
    {
        return lem_eq(s1.c_str(), s2);
    }


    inline bool operator==(const char *s1, const UFString &s2)
    {
        return lem_eq(s2.c_str(), s1);
    }


    inline bool operator==(const UFString &s, wchar_t ch)
    {
        if (s.empty())
            return ch == L'\0';

        return s.front() == ch && s[1] == L'\0';
    }


    inline bool operator==(wchar_t ch, const UFString &s)
    {
        if (s.empty())
            return ch == L'\0';

        return s[0] == ch && s[1] == L'\0';
    }

    // ************************************************************************


    inline bool operator!=(const UFString &s1, const char *s2)
    {
        return lem_neq(s1.c_str(), s2);
    }


    inline bool operator!=(const char *s1, const UFString &s2)
    {
        return lem_neq(s1, s2.c_str());
    }


    inline bool operator!=(const UFString &s, wchar_t ch)
    {
        if (s.empty())
            return ch != '\0';

        return s[0] != ch || s[1] != '\0';
    }


    inline bool operator!=(wchar_t ch, const UFString &s)
    {
        if (s.empty())
            return ch != '\0';

        return s[0] != ch || s[1] != '\0';
    }


    // ****************************************************************

    inline bool operator>(const UFString& s1, const char *s2)
    {
        return lem_gt(s1.c_str(), s2);
    }


    inline bool operator>(const char *s1, const UFString& s2)
    {
        return lem_gt(s2.c_str(), s1);
    }


    inline bool operator>(const UFString& s, wchar_t ch)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_gt(s.c_str(), s2);
    }


    inline bool operator>(wchar_t ch, const UFString& s)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_gt(s2, s.c_str());
    }


    // ****************************************************************

    inline bool operator>=(const UFString& s1, const char *s2)
    {
        return lem_ge(s1.c_str(), s2);
    }


    inline bool operator>=(const char *s1, const UFString& s2)
    {
        return lem_ge(s2.c_str(), s1);
    }


    inline bool operator>=(const UFString& s, wchar_t ch)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_ge(s.c_str(), s2);
    }


    inline bool operator>=(wchar_t ch, const UFString& s)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_ge(s2, s.c_str());
    }

    // ****************************************************************

    inline bool operator<(const UFString& s1, const char *s2)
    {
        return lem_lt(s1.c_str(), s2);
    }



    inline bool operator<(const char *s1, const UFString& s2)
    {
        return lem_lt(s2.c_str(), s1);
    }


    inline bool operator<(const UFString& s, wchar_t ch)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_lt(s.c_str(), s2);
    }


    inline bool operator<(wchar_t ch, const UFString& s)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_lt(s2, s.c_str());
    }

    // ****************************************************************


    inline bool operator<=(const UFString& s1, const char *s2)
    {
        return lem_le(s1.c_str(), s2);
    }


    inline bool operator<=(const char *s1, const UFString& s2)
    {
        return lem_le(s2.c_str(), s1);
    }


    inline bool operator<=(const UFString& s, wchar_t ch)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_le(s.c_str(), s2);
    }


    inline bool operator<=(wchar_t ch, const UFString& s)
    {
        wchar_t s2[2] = { ch, '\0' };
        return lem_le(s2, s.c_str());
    }



    inline UFString& UFString::to_upper(void)
    {
        wchar_t * buf = get_copy();
        std::unique_ptr<wchar_t[]> g(buf);
        lem::to_upper(buf);
        operator=(buf);
        return *this;
    }


    inline UFString& UFString::to_lower(void)
    {
        wchar_t * buf = get_copy();
        std::unique_ptr<wchar_t[]> g(buf);
        lem::to_lower(buf);
        operator=(buf);
        return *this;
    }


    inline bool in_quotes(const UFString &s)
    {
        return s.length() > 1 && s.front() == L'"' && s.back() == L'"';
    }

    extern const UFString to_lower(const UFString &s);
    extern const UFString to_upper(const UFString &s);
    extern const UFString subst(
        const UFString &s,
        const UFString &mask,
        const UFString &text,
        int nentry
    );


    extern const UFString to_Aa(const UFString &s);

    extern const UFString remove_char(const UFString &str, wchar_t chs);
    extern const UFString strip(const UFString &fs, wchar_t Bound);
    extern const UFString strip_quotes(const UFString &str);
    extern const UFString strip_apostrophes(const UFString &str);
    extern const UFString dress(const UFString &s, wchar_t Bound);
    extern const UFString dress_quotes(const UFString &s);
    extern const UFString dress_apostrophes(const UFString &s);

    extern const UFString operator+(const UFString& s1, const UFString& s2);
    extern const UFString operator+(const UFString& s1, const wchar_t *s2);
    extern const UFString operator+(const UFString& s1, wchar_t s2);

    extern const UFString mid(const UFString &s, int I0, int nch);
    extern const UFString left(const UFString &s, int NCH);
    extern const UFString right(const UFString &s, int NCH);

    extern const UFString encode_chars_to_xml(const UFString &str);
    extern const UFString encode_str_to_sql(const UFString &str);

    // Аналог sprintf, только возвращает результат через UFString
    extern UFString format_str(const wchar_t *fmt, ...);
} // end of namespace 'lem'
#endif
