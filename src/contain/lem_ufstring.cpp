// LC->20.04.2018

#include <boost/algorithm/string.hpp>
#include <lem/streams.h>
#include <lem/conversions.h>
#include <lem/ufstring.h>

using namespace lem;


UFString::UFString(const char *source)
{
    if (source && *source)
    {
        wchar_t * u = new wchar_t[lem::lem_strlen(source) + 1];
        lem::lem_strcpy(u, source);
        operator=(u);
        delete[] u;
    }

    return;
}


// ******************************************************
// Создаем строку длиной nch и заполняем символами ch.
// ******************************************************
UFString::UFString(size_type nTime, wchar_t c)
{
    if (nTime > 0)
    {
        wchar_t *str = new wchar_t[nTime + 1];

        for (size_type i = 0; i < nTime; i++)
        {
            str[i] = c;
        }

        str[nTime] = L'\0';
        operator=(str);
        delete[] str;
    }

    return;
}




// *********************************************
// Создается строка из одного символа.
// *********************************************

UFString::UFString(wchar_t c)
{
    wchar_t str[2] = { c, 0 };
    operator=(str);

}


UFString& UFString::operator=(wchar_t ch)
{
    wchar_t str[2] = { ch, 0 };
    operator=(str);
    return *this;
}

UFString& UFString::operator=(const wchar_t *s)
{
    if (lem_is_empty(s))
    {
        clear();
    }
    else
    {
        std::wstring::operator=(s);
    }
    return *this;
}




const UFString lem::add_spaces(const UFString& s, int n)
{
    LEM_CHECKIT_Z(n >= 0);

    UFString res(s);
    res.add_spaces(n);
    return res;
}

void UFString::re_clear(void)
{
    return;
}


wchar_t* UFString::get_copy() const
{
    wchar_t * u = new wchar_t[length() + 1];
    lem::lem_strcpy(u, c_str());
    return u;
}



UFString& UFString::trim(void)
{
    wchar_t * u = get_copy();
    std::unique_ptr<wchar_t[]> g(u);
    lem_trim(u);
    operator=(u);
    return *this;
}


const UFString lem::trim(const UFString &s)
{
    UFString res(s);
    res.trim();
    return res;
}


// *********************************************************
// Добавляем пробелы чтобы длина строки стала n.
// *********************************************************
UFString& UFString::expand_to(int n)
{
    LEM_CHECKIT_Z(n >= 0);

    const size_t l = length();
    if (n > l)
    {
        for (size_t i = n - l - 1; i >= 0; i--)
        {
            operator+=(L' ');
        }
    }

    return *this;
}


const UFString lem::expand_to(const UFString &s, int n)
{
    LEM_CHECKIT_Z(n >= 0);
    UFString res(s);
    res.expand_to(n);
    return res;
}

const UFString lem::remove_char(const UFString &str, wchar_t chs)
{
    wchar_t * buf = str.get_copy();
    std::unique_ptr<wchar_t[]> g(buf);

    lem::lem_strcpy(buf, str.c_str());
    lem_remove_char(buf, chs);

    return UFString(buf);
}


UFString& UFString::strip(wchar_t Bound)
{
    const size_t len = length();
    if (len >= 2 && front() == Bound && back() == Bound)
    {
        wchar_t * str = get_copy();
        std::unique_ptr<wchar_t[]> g(str);
        memmove(str, str + 1, sizeof(wchar_t)*(len - 2));
        str[len - 2] = L'\0';
        operator=(str);
    }

    return *this;
}


UFString& UFString::strip_quotes(void)
{
    return strip(L'"');
}


UFString& UFString::strip_apostrophes(void)
{
    return strip(L'\'');
}


const UFString lem::strip(const UFString &fs, wchar_t Bound)
{
    UFString res = fs;
    res.strip(Bound);
    return res;
}


const UFString lem::strip_quotes(const UFString &str)
{
    return strip(str, L'"');
}


const UFString lem::strip_apostrophes(const UFString &str)
{
    return strip(str, L'\'');
}


UFString& UFString::dress(wchar_t Bound)
{
    (*this) = UFString(Bound) + (*this) + UFString(Bound);
    return *this;
}


UFString& UFString::dress_quotes(void)
{
    return dress(L'"');
}


UFString& UFString::dress_apostrophes(void)
{
    return dress(L'\'');
}


const UFString lem::dress(const UFString &s, wchar_t Bound)
{
    return UFString(Bound) + s + UFString(Bound);
}


const UFString lem::dress_quotes(const UFString &s)
{
    return dress(s, L'"');
}


const UFString lem::dress_apostrophes(const UFString &s)
{
    return dress(s, L'\'');
}


const UFString lem::to_lower(const UFString &s)
{
    UFString res = s;
    res.to_lower();
    return res;
}


const UFString lem::to_upper(const UFString &s)
{
    UFString res = s;
    res.to_upper();
    return res;
}


const UFString lem::subst(
    const UFString &s,
    const UFString &mask,
    const UFString &text,
    int nentry
)
{
    UFString res(s);
    res.replace(s.find(mask), mask.length(), text);
    return res;
}


const UFString lem::to_Aa(const UFString &s)
{
    UFString res(s);
    res.to_Aa();
    return res;
}

/***************************************************************
                   ОПЕРАТОР КОПИРОВАНИЯ
****************************************************************/


UFString& UFString::operator=(const char *s)
{
    if (!s || !*s)
    {
        this->clear();
        return *this;
    }

    wchar_t * str = new wchar_t[strlen(s) + 1];
    std::unique_ptr<wchar_t[]> g(str);
    lem_strcpy(str, s);
    operator=(str);

    return *this;
}



UFString& UFString::operator+=(const char *s)
{
    const int l = length(), sl = lem_strlen(s);

    if (!sl)
    {
        return *this;
    }

    wchar_t * str = new wchar_t[l + sl + 1];
    std::unique_ptr<wchar_t[]> g(str);

    lem_strcpy(str, c_str());
    lem_strcat(str, s);

    operator=(str);

    return *this;
}


UFString& UFString::operator+=(const wchar_t *s)
{
    std::wstring::append(s);
    return *this;
}


UFString& UFString::operator+=(const UFString& s)
{
    std::wstring::append(s.c_str());
    return *this;
}




UFString& UFString::operator+=(wchar_t c)
{
    std::wstring::append(1, c);
    return *this;
}



void UFString::insert_char(int pos, wchar_t ch)
{
    if (pos <= length())
    {
        std::wstring::insert(begin() + pos, ch);
    }

    return;
}

void UFString::remove(int pos)
{
    if (pos < length())
    {
        std::wstring::erase(pos);
    }

    return;
}

/******************************************************************
  Урезает строку на i символов, вызов reduce(0) не меняет строку.
  При выходе за пределы строки ничего не происходит.
******************************************************************/

UFString& UFString::reduce(int i)
{
    LEM_CHECKIT_Z(i >= 0);

    int l = length();
    int term_pos = l - i;

    if (term_pos > l)
    {
        return *this;
    }

    wchar_t * str = get_copy();
    std::unique_ptr<wchar_t[]> g(str);
    str[term_pos] = '\0';
    operator=(str);

    return *this;
}


const UFString lem::mid(const UFString &s, int I0, int nch)
{
    LEM_CHECKIT_Z(nch >= 0);

    if (nch <= 0 || I0 < 0 || I0 >= s.length())
    {
        return lem::UFString();
    }

    return UFString(s.substr(I0, nch));
}


const UFString lem::left(const UFString &s, int NCH)
{
    LEM_CHECKIT_Z(NCH >= 0);

    if (NCH <= 0)
    {
        return lem::UFString();
    }

    return UFString(s.substr(0, NCH));
}


const UFString lem::right(const UFString &s, int NCH)
{
    LEM_CHECKIT_Z(NCH >= 0);

    if (NCH <= 0)
    {
        return lem::UFString();
    }

    return UFString(s.substr(s.length() - NCH, NCH));
}


// ********************************************************************
// Длина строки увеличивается до n за счет добавления в конец строки
// пробелов.
// ********************************************************************

UFString& UFString::add_spaces(int n)
{
    LEM_CHECKIT_Z(n >= 0);

    const int l = length();
    const int nn = n - l;

    // Есть что добавить?
    if (nn > 0)
    {
        for (int i = 0; i < nn; i++)
        {
            operator+=(L' ');
        }
    }

    return *this;
}



// *************************************************
// Фрагмент mask в строке s заменяем на text.
// nentry - номер вхождения маски в исходный текст.
// *************************************************

UFString& UFString::subst(
    const UFString &mask,
    const UFString &text,
    int nentry
)
{
    const int istart = search(mask, nentry);

    if (istart == UNKNOWN)
        return *this;

    // Часть слева длиной istart
    const UFString left = lem::left(*this, istart);

    // Часть справа
    const UFString right = lem::right(*this, length() - mask.length() - istart);

    // Результат собираем из 3х частей.
    (*this) = left + text + right;

    return *this;
}


// ***************************************************
// Замена каждого вхождения строки mask на text.
// ***************************************************

UFString& UFString::subst_all(const UFString &mask, const UFString &text)
{
    boost::replace_all(*this, mask, text);
    return *this;
}


UFString& UFString::subst_all(wchar_t old_ch, wchar_t new_ch)
{
    int l = length();
    for (int i = 0; i < l; i++)
    {
        if (get(i) == old_ch)
        {
            set(i, new_ch);
        }
    }

    return *this;
}




// ***********************************************
// Строки совпадают без учета регистра?
// ***********************************************
bool UFString::eqi(const UFString &x) const
{
    if (x.length() != length())
    {
        return false;
    }

    for (int i = 0; i < length(); i++)
    {
        if (lem::to_uupper(x.get(i)) != lem::to_uupper(get(i)))
        {
            return false;
        }
    }

    return true;
}


bool UFString::eqi(const wchar_t *x) const
{
    size_t len = length();
    if (!len)
    {
        return x == nullptr || *x == 0;
    }

    if (!x || !*x)
    {
        return !len;
    }

    for (int i = 0; i < len + 1; i++)
    {
        if (lem::to_uupper(get(i)) != lem::to_uupper(x[i]))
        {
            return false;
        }
    }

    return true;
}

// ************************************************************
// Строка text содержит подстроку x, причем x должна быть
// с самого начала строки text.
//
// Например:
//
//       text =     ABCDEFG
//       x    =     ABC
//
// ************************************************************
bool UFString::eq_beg(const UFString &x) const
{
    size_t len = length();
    if (x.length() > len)
    {
        return false;
    }

    if (x.length() == len)
    {
        return operator==(*this, x);
    }

    const int lx = x.length();
    for (int i = 0; i < lx; i++)
    {
        if (x.get(i) != get(i))
        {
            return false;
        }
    }

    return true;
}

// Без учета регистра
bool UFString::eq_begi(const UFString &x) const
{
    size_t len = length();
    if (x.length() > len)
    {
        return false;
    }

    if (x.length() == len)
    {
        return eqi(x);
    }

    const int lx = x.length();
    for (int i = 0; i < lx; i++)
    {
        if (lem::to_uupper(x[i]) != lem::to_uupper(get(i)))
        {
            return false;
        }
    }

    return true;
}


bool UFString::eq_beg(const char *x) const
{
    const int lx = lem_strlen(x);
    if (lx > length())
    {
        return false;
    }

    if (lx == length())
    {
        return lem::operator==(*this, x);
    }

    for (int i = 0; i < lx; i++)
    {
        if (x[i] != get(i))
        {
            return false;
        }
    }

    return true;
}


bool UFString::eq_beg(const wchar_t *x) const
{
    size_t len = length();
    const int lx = lem_strlen(x);
    if (lx > len)
    {
        return false;
    }

    if (lx == len)
    {
        return operator==(*this, x);
    }

    for (int i = 0; i < lx; i++)
    {
        if (x[i] != get(i))
        {
            return false;
        }
    }

    return true;
}


bool UFString::eq_begi(const wchar_t* x) const
{
    size_t len = length();
    const int lx = lem_strlen(x);
    if (lx > len)
    {
        return false;
    }

    if (lx == len)
    {
        return operator==(*this, x);
    }

    for (int i = 0; i < lx; i++)
    {
        if (lem::to_uupper(x[i]) != to_uupper(get(i)))
        {
            return false;
        }
    }

    return true;
}


// *********************************************************************
// Приводим к лексему к виду 'Aaaaa', то есть первая буква - заглавная,
// все остальные - маленькие.
// *********************************************************************

UFString& UFString::to_Aa(void)
{
    if (empty())
    {
        return *this;
    }

    to_lower();
    at(0) = lem::to_uupper(get(0));

    return *this;
}





// ********************************************************
// Строка урезается до new_len символов (если это возможно)
// ********************************************************
UFString& UFString::truncate_to(int new_len)
{
    LEM_CHECKIT_Z(new_len >= 0);
    resize(new_len);
    return *this;
}

// ******************************************************************
// Из строки вырезается и выкидывается участок начиная с символа from
// до (включая) символа upto. Возвращается ссылка на себя же.
// Для того, чтобы получить строку [from,upto], используй mid(...)
// ******************************************************************

UFString& UFString::cut(int from, int upto)
{
    if (from >= 0 && upto < length() && from < upto)
    {
        std::wstring::erase(from, upto - from + 1);
        //memmove(str + from, str + upto, sizeof(wchar_t)*(len - upto + 1));
    }


    return *this;
}



void UFString::LoadBin(lem::Stream &bin)
{
    bin.rd(this);
}


void UFString::SaveBin(Stream &bin) const
{
    bin.wr(this);
}


/*
int UFString::to_int(void) const
{
    return lem::to_int(c_str());
}


bool UFString::to_bool(void) const
{
    return lem::to_bool(c_str());
}
*/


// ************************************************
// Поиск символа справа налево.
// @retval индекс найденного символа
// @retval UNKNOWN если символ не найден
// ************************************************
int UFString::find_last_of(wchar_t ch) const
{
    if (empty())
    {
        return UNKNOWN;
    }

    int pos = length() - 1;
    for (int i = pos; i >= 0; i--)
    {
        if (get(i) == ch)
        {
            return i;
        }
    }

    return UNKNOWN;
}



bool lem::UFString::eq_end(const wchar_t* to_find) const
{
    int l = lem_strlen(to_find);
    if (l > length())
    {
        return false;
    }

    return lem_eq(to_find, c_str() + length() - l);
}


bool lem::UFString::eq_end(const UFString & to_find) const
{
    int l = to_find.length();
    if (l > length())
    {
        return false;
    }

    return lem_eq(to_find.c_str(), c_str() + length() - l);
}

const UFString lem::operator+(const UFString& s1, const UFString& s2)
{
    wchar_t * buf = new wchar_t[s1.length() + s2.length() + 1];
    std::unique_ptr<wchar_t[]> g(buf);
    lem_strcpy(buf, s1.c_str());
    lem_strcat(buf, s2.c_str());
    return UFString(buf);
}


const UFString lem::operator+(const UFString& s1, const wchar_t * s2)
{
    wchar_t * buf = new wchar_t[s1.length() + lem_strlen(s2) + 1];
    std::unique_ptr<wchar_t[]> g(buf);
    lem_strcpy(buf, s1.c_str());
    lem_strcat(buf, s2);
    return UFString(buf);
}
