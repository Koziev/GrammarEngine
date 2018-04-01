// LC->30.03.2018

#include <lem/streams.h>
#include <lem/conversions.h>
#include <boost/algorithm/string.hpp>
#include <lem/afstring.h>

using namespace lem;


static int my_eqi(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (tolower(*s1) != tolower(*s2))
        {
            return -1;
        }
        else
        {
            s1++; s2++;
        }
    }

    return *s1 - *s2;
}



inline int FString::count(char ch) const
{
    return std::count(begin(), end(), ch);
}


const FString lem::add_spaces(const FString& s, int n)
{
    LEM_CHECKIT_Z(n >= 0);
    FString res(s);
    res.add_spaces(n);
    return res;
}


void FString::re_clear(void)
{
    if (this->c_str() == NULL)
    {
        this->operator=("");
    }
}


char* FString::get_copy() const
{
    char * buf = new char[length() + 1];
    lem::lem_strcpy(buf, c_str());
    return buf;
}



FString& FString::trim(void)
{
    char * buf = get_copy();
    std::unique_ptr<char[]> g(buf);
    lem_trim(buf);
    this->operator=(buf);
    return *this;
}


const FString lem::trim(const FString &s)
{
    FString res(s);
    res.trim();
    return res;
}


// *********************************************************
// Добавляем пробелы чтобы длина строки стала n.
// *********************************************************
FString& FString::expand_to(int n)
{
    LEM_CHECKIT_Z(n >= 0);

    const int l = length();
    if (n > l)
    {
        for (int i = n - l - 1; i >= 0; i--)
        {
            this->operator+=(' ');
        }
    }

    return *this;
}


const FString lem::expand_to(const FString &s, int n)
{
    LEM_CHECKIT_Z(n > 0);

    FString res(s);
    res.expand_to(n);

    return res;
}


FString& FString::strip(char Bound)
{
    size_t len = length();
    if (len >= 2 && c_str() && front() == Bound && back() == Bound)
    {
        char * buf = get_copy();
        std::unique_ptr<char[]> g(buf);
        memmove(buf, buf + 1, len - 2);
        buf[len - 2] = '\0';
        this->operator=(buf);
    }

    return *this;
}


FString& FString::strip_quotes(void)
{
    return strip('"');
}


FString& FString::strip_apostrophes(void)
{
    return strip('\'');
}


const FString lem::strip(const FString &fs, char Bound)
{
    FString res = fs;
    res.strip(Bound);
    return res;
}


const FString lem::strip_quotes(const FString &str)
{
    return strip(str, '"');
}


const FString lem::strip_apostrophes(const FString &str)
{
    return strip(str, '\'');
}



FString& FString::dress(char Bound)
{
    this->operator=(FString(Bound) + *this + FString(Bound));
    return *this;
}


FString& FString::dress_quotes(void)
{
    return dress('"');
}


FString& FString::dress_apostrophes(void)
{
    return dress('\'');
}



const FString lem::dress(const FString &s, char Bound)
{
    return FString(Bound) + s + FString(Bound);
}


const FString lem::dress_quotes(const FString &s)
{
    return dress(s, '"');
}


const FString lem::dress_apostrophes(const FString &s)
{
    return dress(s, '\'');
}


const FString lem::to_Aa(const FString &s)
{
    FString res = s;
    res.to_Aa();
    return res;
}





/****************************************************************
  В указанную позицию вставляется символ, строка раздвигается.
  Если позиция вышла за диапазон [0,длина_строки), то ничего не
  происходит (это не баг, а ФИЧА).
****************************************************************/

void FString::insert_char(int pos, char ch)
{
    if (pos <= length())
    {
        // Символ вставляется внутрь строки.
        std::string::insert(begin() + pos, ch);
    }
}


/*********************************************************************
 Удаление символа из указанной позиции, строка сдвигается.
 Если позиция вне диапазона [0,длина_строки), то ничего не происходит.
**********************************************************************/
void FString::remove(int pos)
{
    std::string::erase(pos);
}

/******************************************************************
  Урезает строку на i символов, вызов reduce(0) не меняет строку.
  При выходе за пределы строки ничего не происходит.
******************************************************************/
FString& FString::reduce(int i)
{
    std::string::erase(end() - i, end());
    return *this;
}


/************************************************************************
  Формируем новую строку, состоящую из символов строки-аргумента s
  с i0-го в количестве nch. Если i0<0, то подразумевается i0=0. Если
  (i0+nch) больше, чем длина строки s, что в результатную строку будет
  занесено соответственно меньше символов.
************************************************************************/
const FString lem::mid(const FString &s, int I0, int nch)
{
    LEM_CHECKIT_Z(nch >= 0);

    if (nch <= 0 || I0 < 0 || I0 >= s.length())
    {
        return lem::FString();
    }

    char * buf = new char[nch + 1];
    std::unique_ptr<char[]> g(buf);
    buf[nch] = 0;

    if (nch >= 0)
    {
        const int i0 = I0 < 0 ? 0 : I0;
        const int l = s.length();

        if (i0 >= l)
        {
            return FString(buf);
        }

        for (int i = 0; i < nch && (i + i0) < l; i++)
        {
            buf[i] = s[i + i0];
            buf[i + 1] = '\0';
        }
    }

    return FString(buf);
}


/**************************************************************************
  Возвращается строка, состоящая из символов строки-аргумента s, начина
  с первого (индекс 0) длиной nch. Если длина исходной строки недостаточна,
  то результат будет содержать соответственно меньшее количество символов.
***************************************************************************/
const FString lem::left(const FString &s, int NCH)
{
    LEM_CHECKIT_Z(NCH >= 0);

    if (NCH <= 0)
    {
        return lem::FString();
    }

    return s.substr(0, NCH);
}


/*****************************************************************************
  Возвращается строка, состоящая из последних nch символов строки-аргумента s.
  Если длина исходной строки недостаточна, то результат будет содержать
  соответственно меньшее количество символов.
******************************************************************************/
const FString lem::right(const FString &s, int NCH)
{
    LEM_CHECKIT_Z(NCH >= 0);

    if (NCH <= 0)
    {
        return lem::FString();
    }

    return s.substr(s.length() - NCH, NCH);
}


// ********************************************************************
// Длина строки увеличивается до n за счет добавления в конец строки
// пробелов.
// ********************************************************************
FString& FString::add_spaces(int n)
{
    LEM_CHECKIT_Z(n >= 0);

    const int l = length();
    const int nn = n - l;

    // Есть что добавить?
    if (nn > 0)
    {
        for (int i = 0; i < nn; i++)
        {
            operator+=(' ');
        }
    }

    return *this;
}




// ***************************************************
// Замена каждого вхождения строки mask на text.
// ***************************************************
FString& FString::subst_all(const FString &mask, const FString &text)
{
    boost::replace_all(*this, mask, text);
    return *this;
}


FString& FString::subst_all(char old_ch, char new_ch)
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





void FString::LoadBin(Stream &bin)
{
    bin.rd(this);
}


void FString::SaveBin(Stream &bin) const
{
    bin.wr(this);
}


// *********************************************************************
// Приводим к лексему к виду 'Aaaaa', то есть первая буква - заглавная,
// все остальные - маленькие.
// *********************************************************************
FString& FString::to_Aa(void)
{
    if (!length())
    {
        return *this;
    }

    operator=(to_lower(*this));
    at(0) = lem::to_upper(get(0));

    return *this;
}






// ********************************************************
// Строка урезается до new_len символов (если это возможно)
// ********************************************************
FString& FString::truncate_to(int new_len)
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
FString& FString::cut(int from, int upto)
{
    if (from >= 0 && upto < length() && from < upto)
    {
        char * buf = get_copy();
        std::unique_ptr<char[]> g(buf);
        memmove(buf + from, buf + upto, length() - upto + 1);
        this->operator=(buf);
    }

    return *this;
}




// ************************************************
// Поиск символа справа налево.
// @retval индекс найденного символа
// @retval UNKNOWN если символ не найден
// ************************************************
int FString::find_last_of(char ch) const
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


// ***********************************************
// Строки совпадают без учета регистра?
// ***********************************************
bool FString::eqi(const FString &x) const
{
    if (x.length() != length())
    {
        return false;
    }

    if (empty())
    {
        return true;
    }

#if defined LEM_LINUX
    return !strcasecmp(c_str(), x.c_str());
#elif defined LEM_WINDOWS
    return !stricmp(c_str(), x.c_str());
#else
    return !my_eqi(c_str(), x.c_str());
#endif
}


bool FString::eqi(const char *x) const
{
    if (!x || !*x)
    {
        return !length();
    }

#if defined LEM_LINUX
    return !strcasecmp(c_str(), x);
#elif defined LEM_WINDOWS
    return !stricmp(c_str(), x);
#else
    return !my_eqi(c_str(), x);
#endif
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

bool FString::eq_beg(const FString &x) const
{
    if (x.length() > length())
    {
        return false;
    }

    if (x.length() == length())
    {
        return this->operator==(x);
    }

    const int lx = x.length();
    for (int i = 0; i < lx; i++)
    {
        if (x[i] != get(i))
        {
            return false;
        }
    }

    return true;
}



bool FString::eq_beg(const char *x) const
{
    const int lx = lem_strlen(x);
    if (lx > length())
    {
        return false;
    }

    if (lx == length())
    {
        return *this == x;
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


bool FString::eq_begi(const char *x) const
{
    const int lx = lem_strlen(x);
    if (lx > length())
    {
        return false;
    }

    for (int i = 0; i < lx; i++)
    {
        if (lem::to_lower(x[i]) != lem::to_lower(get(i)))
        {
            return false;
        }
    }

    return true;
}
