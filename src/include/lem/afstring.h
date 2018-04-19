#ifndef LEM_AFSTRING__H
#define LEM_AFSTRING__H
#pragma once

#include <string>

#include <lem/config.h>
#include <lem/strings.h>
#include <memory>

#include <stdlib.h>

namespace lem
{
    extern int lem_strlen(const char*);
    extern char* to_lower(char *s);
    extern char* to_upper(char *s);

    extern int to_int(const char *s);
    extern bool to_bool(const char *s);

    class Stream;


    class FString : public std::string
    {
    public:
        FString() {}
        FString(char c) { this->operator+=(c); }
        FString(const char * str) { if(str!=nullptr) std::string::operator=(str); }
        FString(const FString & s) :std::string(s) {}
        FString(const std::string s) :std::string(s) {}
        FString(const char * start, const char * beyond_end) :std::string(start, beyond_end) {}

        void operator=(char c)
        {
            char s[2] = { c, 0 };
            std::string::operator=(s);
        }

        bool operator==(char c) const
        {
            return length() == 1 && get(0) == c;
        }

        bool operator==(const FString & s) const
        {
            return lem::lem__strcmp(c_str(), s.c_str());
        }


        bool operator==(const char * s) const
        {
            return lem::lem__strcmp(c_str(), s);
        }

        inline char get(int i) const { return operator[](i); }


        // *******************************************************************
        // Возвращается последний символ в строке (перед терминирующим '\0').
        // Для пустой строки возвращается '\0'
        // *******************************************************************
        char last_char(int i = 0) const;

        void set(int i, char ch);

        int count(char ch) const;
        int find_char(char ch) const;
        int find_last_of(char ch) const;
        inline int rfind(char ch) const { return find_last_of(ch); }

        int search(char to_find, int nentry = 1) const;
        int search(const FString &to_find, int nentry = 1) const;
        int search(const char *to_find, int nentry = 1) const;

        int search_from(char to_find, int start_pos) const;
        int search_from(const FString &to_find, int start_pos) const;
        int search_from(const char *to_find, int start_pos) const;

        bool eq_beg(const FString &to_find) const;
        bool eq_beg(const char* to_find) const;
        bool eq_begi(const char* to_find) const;

        bool eqi(const FString &x) const;
        bool eqi(const char *x) const;

        // Заменяем все вхождения строки mask на строку text.
        FString& subst_all(const FString &mask, const FString &text);
        FString& subst_all(char old_ch, char new_ch);

        FString& to_Aa(void);

        FString& strip(char Bound);
        FString& strip_quotes(void);
        FString& strip_apostrophes(void);

        FString& dress(char Bound);
        FString& dress_quotes(void);
        FString& dress_apostrophes(void);
        FString& trim(void);

        FString& add_spaces(int n);
        FString& expand_to(int n);

        FString& truncate_to(int new_len);
        FString& cut(int from, int upto);
        FString& reduce(int i);
        void remove(int pos);
        void insert_char(int pos, char ch);
        void set_dir(int i, char ch);

        void re_clear(void);

        void LoadBin(lem::Stream &bin);
        void SaveBin(lem::Stream &bin) const;

        char* get_copy() const;
    };


    inline void FString::set(int i, char ch)
    {
        if (i >= 0 && i < length())
        {
            at(i) = ch;
        }
    }

    inline void FString::set_dir(int i, char ch)
    {
        at(i) = ch;
    }

    /**************************************************************************
      Возвращает символ, содержащийся в позиции, отсчитываемой от конца строки.
      То есть last_char(0) вернет последний символ перед '\0'. При выходе за
      пределы существующей строки возвращаем '\0'.
    ***************************************************************************/
    inline char FString::last_char(int i) const
    {
        const size_t pos = length() - i - 1;
        return pos >= length() ? 0 : at(pos);
    }

    /************************************************************************
     Определяет число появлений символа ch в строке s. Функция может
     использоваться для определения самого факта появления символа в строке
     так как отсутствие таковых дает нулевой результат (то есть 'false'!).
    *************************************************************************/
    inline int FString::find_char(char ch) const
    {
        return lem_nentry(c_str(), ch);
    }

    /**************************************************************************
      Находит n-ое (по умолчанию первое) вхождение символа ch в строку-аргумент
      s. Если символ не найден, или число его вхождений менее nentry, то
      возвращается -1.
    **************************************************************************/
    inline int FString::search(char ch, int nentry) const
    {
        return lem_find(c_str(), ch, nentry);
    }



    /***************************************************************************
     Определяет положение nentry-го вхождения подстроки [f] в строку [s].
     Возвращает индекс первого совпавшего символа. Если подстрока не
     обнаружена, или число ее появлений в строке менее nentry, то возвращаем -1.
    ****************************************************************************/

    inline int FString::search(const FString &f, int nentry) const
    {
        return lem_find(c_str(), f.c_str(), nentry);
    }


    inline int FString::search(const char *to_find, int nentry) const
    {
        return lem_find(c_str(), to_find, nentry);
    }


    inline int FString::search_from(const FString &to_find, int start_pos) const
    {
        return lem_find_from(c_str(), to_find.c_str(), start_pos);
    }


    inline int FString::search_from(const char *to_find, int start_pos) const
    {
        return lem_find_from(c_str(), to_find, start_pos);
    }


    inline int FString::search_from(char to_find, int start_pos) const
    {
        return lem_find_from(c_str(), to_find, start_pos);
    }


    extern const FString add_nl(const FString& s);
    extern const FString add_spaces(const FString& s, int n);
    extern const FString trim(const FString &s);
    extern const FString expand_to(const FString &s, int n);

    extern const FString strip(const FString &fs, char Bound);
    extern const FString strip_quotes(const FString &str);
    extern const FString strip_apostrophes(const FString &str);

    extern const FString dress(const FString &s, char Bound);
    extern const FString dress_quotes(const FString &s);
    extern const FString dress_apostrophes(const FString &s);

    inline FString to_lower(const FString &s)
    {
        char * buf = s.get_copy();
        std::unique_ptr<char[]> g(buf);
        lem::to_lower(buf);
        return FString(buf);
    }


    inline FString to_upper(const FString &s)
    {
        char * buf = s.get_copy();
        std::unique_ptr<char[]> g(buf);
        lem::to_upper(buf);
        return FString(buf);
    }

    extern const FString to_Aa(const FString &s);


    /************************************************************************
      Формируем новую строку, состоящую из символов строки-аргумента s
      с i0-го в количестве nch. Если i0<0, то подразумевается i0=0. Если
      (i0+nch) больше, чем длина строки s, что в результатную строку будет
      занесено соответственно меньше символов.
    ************************************************************************/
    extern const FString mid(const FString &s, int I0, int nch);


    /**************************************************************************
      Возвращается строка, состоящая из символов строки-аргумента s, начина
      с первого (индекс 0) длиной nch. Если длина исходной строки недостаточна,
      то результат будет содержать соответственно меньшее количество символов.
    ***************************************************************************/
    extern const FString left(const FString &s, int NCH);

    /*****************************************************************************
      Возвращается строка, состоящая из последних nch символов строки-аргумента s.
      Если длина исходной строки недостаточна, то результат будет содержать
      соответственно меньшее количество символов.
    ******************************************************************************/
    extern const FString right(const FString &s, int NCH);

    extern FString format_str(const char *fmt, ...);

} // end of namespace 'lem'
#endif
