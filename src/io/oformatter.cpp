#include <cstdarg>
#include <cctype>

#undef printf

#include <lem/conversions.h>
#include <lem/ustreams.h>
#include <lem/char_buffer.h>
#include <lem/oformatter.h>


using namespace std;
using namespace lem;
using namespace lem::Char_Stream;

/**************************************************************************************

   Класс OFormatter предназначен для замены стандартного пакета форматного
 вывода информации в текстовые потоки (терминал и файлы) из C, то есть
 процедур ...printf. Необходимость такой замены обусловлена значительным
 расширением стандартного набора типов данных в Библиотеке INDEPENDENCE,
 в частности, присутствием типов String, FString, INT64, REAL18 и других.
 Значительно расширены возможности форматирования выводимых полей. Автоматически
 осуществляется настройка на текущий тип REAL, так что в программах нет
 надобности перебивать спецификации %e на %le и так далее, достаточно
 указания %re (подробнее см. далее). Идеология C-процедур printf уже достаточно
 близка к форматному выводу информации в языке ФОРТРАН. Одно из важнейших
 достоинств такого способы вывода данных - чрезвычайная компактность описани
 весьма сложных законов форматирования, поэтому мы значительно расширили не
 только диапазон стандартных выводимых типов, но и добавили специальные флаги
 форматирования, например, выравнивание на границу поля и так далее.

   Следует заметить, что ряд редко используемых спецификаций из ...printf
 исключен, в частности, %x. Далее, вместо %e, %le, %f, %lf, %g, %lg используетс
 другой набор спецификаторов, более приспособленных для нашей Библиотеки, хот
 можно свободно использовать и %e, %f, %g.

   Без изменений осталось использование спецификаторов %%, %c, %s, %d, %ld.
 Впрочем, значительно расширены возможности вывода (форматирования) целых
 чисел.

   Так как вывод текста производится в 'виртуальный файл' Stream, то не
 составляет труда реализовать специальные режимы вывода - достаточно написать
 класс-потомок Stream и перегрузить в нем часть методов (с подробностями
 лучше знакомиться в "lem_bstr.h").

   Однако, в целом расширение возможностей OFormatter ограничивается принятым
 механизмом передачи параметров через стек. Недостаток такого подхода - сложность
 расширения возможностей по выводу новых типов данных. Поэтому класс OFormatter
 реализует и второй подход, а именно тот, что применен в библиотеке IOStream языка
 C++. То есть, мы переопределили операторы << для всех базовых стандартных
 типов Библиотеки, а прикладной программист может написать необходимое число
 дополнительных функций OFormatter& operator<<(...) для своих типов. Однако
 необходимо отметить, что управление режимами форматирования для такого подхода
 производится не столь просто, как для печати через метод OFormatter::printf.
 Кстати, можно совершенно свободно перемежать вывод через OFormatter::printf и
 operator<<, без какой-либо синхронизации потоков (это необходимо в IOStream C++).

   Чтобы предельно облегчить использование OFormatter вместо стандартного
 printf, для вывода на терминал в прикладных модулях доступен объект mout. В
 результате, строка кода

              printf( "Hello, world!\n" );

 должна быть заменена на

              mout.printf( "Hello, world!\n" );


 Также доступен объект merr для вывода сообщений об ошибках (стандартный
 поток stderr).

 Для вывода форматированного текста в обычный дисковый файл необходимо написать
 нечто вроде:

             OFormatter mfile( "filename.txt" );
             mfile.printf( "Hello, disk file!\n" );


 При определенном макросе LEM_NOREAL исключаются (становятся недействительными)
 все спецификации, обслуживающие типы REAL/REAL4/... (подробности - в модуле
 "lem_real.h").


                         --------------

       Операции сложного форматного вывода в текстовые потоки.


                        Поля спецификации:

  %XYYY.ZZZZ
   | |   |
   | |   +------ Число цифр мантиссы после дес.точки, выводимых в поток.
   | +---------- Общая длина поля.
   |
   +------------ Поле для указания способа указания знака числа.
                 X = '+' - печатается '+' или '-' соответственно.
                 X = ' ' - печатается ' ', если число>0, иначе печатается '-'

                 По умолчанию печатается только '-', когда число <0.

  %...Xn...    - основание системы счисления будет равно 'n' для след. поля.

  %...Wn...    - длина суперполя будет равна n.

  %...An...    - устанавливается тип выравнивания для поля в суперполе.

                 Al - выравнивание к левому краю.

                 Ac - центрирование.

                 Ar - выравнивание к правому краю.

  %...Ln...    - преобразование символов.

                 Lc - все к большим.

                 Ls - все к малым.

  %...Knnn...  - строковый аргумент, который будет прочитан со стека (обычно
                 через спецификацию s), будет в кодировке nnn (например 1251 -
                 кодировка MS Windows). После считывания строка будет
                 автоматически перекодирована в 866 кодировку MSDOS.

  %...in...    - подготовленное символьное представление поля выводитс
                 подряд n раз, к стеку аргументов обращение производится только
                 один раз.

  %...Fnm...   - специальный флаг управления вывода поля с обозначением 'n'
                 устанавливается в состояние 'm'. Значение флагов и их состояний
                 определяется конкретно для разных типов. Будучи установлен в,
                 определенное стстояние, флаг продолжает действовать при выводе
                 всех следующих полей до того момента, когда другая команда %Fnm
                 изменит его значение.

  %...^n...    - число знакомест под порядок числа с плавающей точкой.


  %...n...     - тип нормальной длины ( double, INT16 ).

  %...l...     - тип с приставкой 'long' ( long int, long double )

  %...u...     - тип с приставкой 'unsigned' ( unsigned int, unsigned long )

  %...q...     - тип с приставкой 'quatro' ( int64, REAL18 )


  %v           - изменение режима вывода символов для видеомонитора (только MSDOS).

     %vl - LOWVIDEO
     %vh - HIGHVIDEO
     %vn - NORMALVIDEO
     %vx - смена режима BLINK/не BLINK
     %vb# - новый цвет фона ('#' == 0,...,9,A,...F )
     %vf# - новый цвет символов

            #    цвет

            0    BLACK
            1    BLUE
            2    GREEN
            3    CYAN
            4    RED
            5    MAGENTA
            6    BROWN
            7    LIGHTGRAY
            8    DARKGRAY
            9    LIGHTBLUE
            A    LIGHTGREEN
            B    LIGHTCYAN
            C    LIGHTRED
            D    LIGHTMAGENTA
            E    YELLOW
            F    WHITE


                     СПЕЦИФИКАТОРЫ ТИПОВ.


   d,D - целочисленный тип int, unsigned int, long, unsigned long.
       Буква D означает, что длина поля будет принята такой, чтобы
       поместить наибольшее число данного типа.

   s - текстовая C-строка.
   us - текстовая UNICODE-строка

   re, rg, rf - текущий тип REAL.
   e, g, f    -

   Re, Rf, Rg - текущий REAL с выводом всех значащих цифр.

   rre,rrg,rrf,Rre,Rrg,Rrf - принудительно тип REAL4...REAL18
   rce, rcf, rcg - поле LemComplex.
   Rce, Rcg, Rcf - поле типа LemComplex с выводом максимума знаков.

   Rde, Rdf, Rdg, rde, rdf, rdg - поле DUPEL.

   hc - печать строки символов 'c'. Длина последовательности равна
        установленной длине поля.

   Hc - печать строки символов 'c', длина строки берется со стека.

   x  - печать последовательности из символа, который считывается со стека.

   c - печать единичного символа.
   uc - печать единичного UNICODE-символа.

   b - логические bool.

   t - табуляция до позиции field_len от начала текущей строки.

   T - табуляция до позиции, снимаемой со стека.

   Yc - вывод символов 'c' от текущей позиции до field_len.

   M, m - установка специального режима полей:

        Ml, ml - установка поля слева, число пробелов берется со стека (M) или из форматной строки (m)
        Mw, mw - ширина страницы, считая и левое поле, число знакомест берется со стека (M) или из форматной строки (m)
        Mn, mn - возврат к параметрам по умолчанию


   *:lang(слово[,падеж]) - вывод слова, согласованного с числовым аргументом типа
                         int, для указанного падежа. Используется словарь
                         языка lang. Допустимые значения lang: 'ru' и 'en' без
                         кавычек. Пример: %*:en(file) или %*:ru(файл,им)

                         По умолчанию - именительный падеж.


               ЗНАЧЕНИЕ СПЕЦИАЛЬНЫХ ФЛАГОВ ...Fnm...


  1. Для стандартных целочисленных.

  Fz1  - если размер поля больше, чем получилось значимых цифр, то слева
         дописываются нули. Следует помнить, что по умолчанию, если не
         встретился спецификатор ...k[.l]..., то длина поля принимаетс
         максимальной для типа [unsigned][long]int, чтобы разместить
         число MAXINT, UINT_MAX и так далее. Если спецификатор ...k[.l]...
         дает размер поля больше, чем получается знакомест, то флаг Fz1
         срабатывает.


  2. Для комплексных.

  Ff0 - вывод в виде '{re,im}' (режим по умолчанию).
  Ff1 - вывод в виде '(re,im)'
  Ff2 - вывод в виде 're im'
  Ff3 - вывод в виде 're=x im=y'


  3. Для bool.

  Ff0 - 'true'/'false' (режим по умолчанию)
  Ff1 - '.TRUE.'/'.FALSE.' (для ФОРТРАНовских программ)
  Ff2 - '1'/'0'

  4. Для типа DUPELxxx

  Ff1 - вывод в виде { среднее +/- отклонение }

  5. Прочие.

  F$3 - формат вывода денежных сумм с разделением запятой по 3 цифры справа.
  F$4 - аналогично предыдущему, но с разделением пробелом

****************************************************************************/

/*********************************************************
 После этого конструктора поток еще не готов к выводу,
 будет аварийная остановка выполнения в случае первого же
 вызова метода ::printf().
**********************************************************/
OFormatter::OFormatter(void)
{
    CONTROLFLAG = 0x00000000L;
    stream = NULL;
    doubler = NULL;
    can_i_close = false;
    npos = 0;
    left_margin = 0;
    page_width = 0;

    ClearFlags();

    return;
}


OFormatter::OFormatter(FILE *file)
{
    doubler = NULL;

    ClearFlags();

    CONTROLFLAG = 0x00000000L;
    npos = 0;
    left_margin = 0;
    page_width = 0;

    Init(file);

    return;
}

/***************************************************************
 Открываем поток выдачи в текстовый файл (задан именем). Формат
 имени целиком зависит от ОС.
****************************************************************/
OFormatter::OFormatter(const lem::Path& filename)
{
    doubler = NULL;
    stream = NULL;
    can_i_close = false;

    ClearFlags();

    CONTROLFLAG =
        npos =
        left_margin =
        page_width = 0;

    Open(filename, false);

    can_i_close = true;

    return;
}

/********************************************************************
 Создание потока выдачи для виртуального файла, который был создан и
 будет удалён где-то во внешнем коде.
*********************************************************************/
OFormatter::OFormatter(Stream *file, bool CanClose)
{
    doubler = NULL;

    CONTROLFLAG =
        npos =
        left_margin =
        page_width = 0;

    ClearFlags();

    stream = file;
    can_i_close = CanClose;

    return;
}

void OFormatter::Open(FILE *file)
{
    Delete();
    Init(file);
    return;
}


// ***************************************************
// Открываем файл с именем filename. Создается поток
// вывода в текстовый файл (класс TextFile).
// ***************************************************
void OFormatter::Open(const Path& filename, bool write_bom)
{
    // Так как этот форматтер работает с ASCII потоками вывода, то write_bom 
    // должен быть false.
    LEM_CHECKIT_Z(write_bom == false);

    Delete();

    stream = new TextFile(filename, false, true);

    can_i_close = true;
    left_margin = page_width = npos = 0;
    return;
}


void OFormatter::Open(Stream *file, bool CanClose)
{
    Delete();
    stream = file;
    can_i_close = CanClose;
    return;
}


void OFormatter::ClearFlags(void)
{
    total_len =
        after =
        exp_len =
        field_len =
        after =
        caps = -1;

    aligment =
        sign_out =
        nflag = 0;

    // Основание системы счисления по умолчанию
    radix = 10;

    nrepeate = 1;

    is_normal =
        is_unsigned =
        is_long =
        is_quatro =
        is_complex = false;

    autoflush = false;

    // local_cp    = cp1251;
    local_cp = &lem::UI::get_UI().GetSessionCp();
    out_cp = &lem::UI::get_UI().GetSessionCp();

    return;
}


void OFormatter::Init(FILE *file)
{
    npos = 0;

    if (file)
    {
        if (can_i_close)
            delete stream;

        stream = new BinaryFile(file);
        can_i_close = true;
    }

    left_margin = page_width = 0;
    can_i_close = false;

    return;
}



void OFormatter::Init(const OFormatter &ms)
{
    can_i_close = ms.can_i_close;

    // Контроль за объектом ФАЙЛ осуществляется извне,
    // поэтому не будем озабачиваться переоткрытием
    // файла.
    LEM_CHECKIT_Z(!can_i_close);

    stream = ms.stream;
    doubler = ms.doubler;

    CONTROLFLAG = ms.CONTROLFLAG;
    left_margin = ms.left_margin;
    page_width = ms.page_width;
    npos = ms.npos;
    out_cp = ms.out_cp;

    return;
}

void OFormatter::Delete(void)
{
    if (can_i_close && stream)
    {
        stream->close();
        delete stream;
    }

    stream = NULL;
    doubler = NULL;
    return;
}


OFormatter::~OFormatter(void)
{
    Delete();
    return;
}

void OFormatter::operator=(FILE *file)
{
    Delete();
    Init(file);
    return;
}

void OFormatter::operator=(const OFormatter &ms)
{
    Delete();
    Init(ms);
    return;
}

// *******************************************************
// Метод для замены стандартного библиотечного ...PRINTF
// *******************************************************
void OFormatter::printf(const char *format, ...)
{
#if defined LEM_THREADS
    // Блокируем повторное вхождение в метод, так как код класса
    // нереентерабелен.
    lock_mstr.Enter();
#endif

    LEM_CHECKIT_Z(!!(stream));
    if (!stream)
        return;

    va_list ap;
    va_start(ap, format);

    int i = 0;
    char ch;

    while ((ch = format[i++]))
    {
        if (ch == '%')
        {
            read_field_spec(format, i);
            ch = format[i++];

            switch (ch)
            {
            case 'v':
            {
                // Специальное управление видеорежимом для вывода на монитор.
                VideoControl(format, i);
                break;
            }

            case 's':
            {
                // C-строка
                if (is_unsigned || is_long)
                {
                    const wchar_t *val = va_arg(ap, const wchar_t*);
                    Print_C_String(val);
                }
                else
                {
                    const char *val = va_arg(ap, const char*);
                    Print_C_String(val);
                }

                break;
            }

            case 'h':
            case 'H':
            {
                LEM_CHECKIT_Z(after < 1);
                LEM_CHECKIT_Z(radix == 10);

                if (ch == 'H')
                    field_len = va_arg(ap, int);

                char filler = format[i++];

                do
                    for (int i = 0; i < field_len; i++)
                        printf(filler);
                while (--nrepeate > 0);

                break;
            }

            case 'Y':
            {
                char filler = format[i++];
                Print_Tab(field_len, filler);
                break;
            }

            /*
                   case 'x':
                    {
                     LEM_CHECKIT_Z(after<1);
                     LEM_CHECKIT_Z(radix==10);

            //         char filler = va_arg(ap,char);
                     char filler = va_arg(ap,int);

                     do
                      for( int i=0; i<field_len; i++ )
                       printf( filler );
                     while( --nrepeate>0 );

                     break;
                    }
            */

            case 'c':
            {
                if (is_unsigned)
                {
                    wchar_t buffer[2];

                    //           buffer[0]=va_arg(ap,wchar_t); buffer[1]=0;
                    buffer[0] = va_arg(ap, int); buffer[1] = 0;
                    Print_C_String(buffer);
                }
                else
                {
                    char buffer[2];
                    //           buffer[0]=va_arg(ap,char); buffer[1]=0;
                    buffer[0] = va_arg(ap, int); buffer[1] = 0;
                    Print_C_String(buffer);
                }

                break;
            }

            case 'b':
            {
                //         bool b = va_arg(ap,bool);
                bool b = !!va_arg(ap, int);
                Print_Boolean(b);
                break;
            }

            case '%':
            {
                printf('%');
                break;
            }

            case 't':
            {
                Print_Tab();
                break;
            }

            case 'T':
            {
                int to = va_arg(ap, int);
                Print_Tab(to);
                break;
            }

            case 'k':
            {
                // Смена кодовой страницы для выхода.
                out_cp = CodeConverter::getConverter(read_digits(format, i));
                break;
            }

            case 'M':
            {
                char m = format[i++];
                switch (m)
                {
                case 'n':
                    left_margin = page_width = 0;
                    break;

                case 'l':
                {
                    left_margin = va_arg(ap, int);
                    break;
                }

                case 'w':
                {
                    page_width = va_arg(ap, int);
                    break;
                }

                default:
                    LEM_STOPIT;
                }

                break;
            }

            case 'm':
            {
                char m = format[i++];

                switch (m)
                {
                case 'n':
                    left_margin = page_width = 0;
                    break;

                case 'l':
                {
                    left_margin = read_digits(format, i);
                    break;
                }

                case 'w':
                {
                    page_width = read_digits(format, i);
                    break;
                }

                default:
                    LEM_STOPIT;
                }

                break;
            }

            case 'p':
            {
                // Указатель.
                char p_str[20];
                const void * ptr = va_arg(ap, const void*);
                sprintf(p_str, "%p", ptr);
                Print_C_String(p_str);
                break;
            }

            case 'x':
            {
                char p_str[20];
                const void * ptr = va_arg(ap, const void*);
                sprintf(p_str, "%x", ptr);
                Print_C_String(p_str);
                break;
            }

            case 'd':
            case 'D':
            {
                // *********************************************
                // *             Поле типа int.                *
                // *********************************************

                LEM_CHECKIT_Z(after == -1);
                is_complete = ch == 'D';

                if (is_normal)
                {
                    if (is_unsigned)
                    {
                        unsigned int val = va_arg(ap, int);
                        Print_UINT(val);
                    }
                    else
                    {
                        int val = va_arg(ap, int);
                        Print_INT(val);
                    }

                    break;
                }

                if (!is_long && !is_quatro)
                {
                    if (is_unsigned)
                    {
                        unsigned int val = va_arg(ap, unsigned int);
                        Print_UINT(val);
                    }
                    else
                    {
                        int val = va_arg(ap, int);
                        Print_INT(val);
                    }

                    break;
                }

                if (is_long)
                {
                    if (is_unsigned)
                    {
                        lem::uint32_t val = va_arg(ap, lem::uint32_t);
                        Print_UINT32(val);
                    }
                    else
                    {
                        lem::int32_t val = va_arg(ap, lem::int32_t);
                        Print_INT32(val);
                    }

                    break;
                }

                if (is_quatro)
                {
                    if (is_unsigned)
                    {
#if defined LEM_UI64
                        lem::uint64_t val = va_arg(ap, lem::uint64_t);
                        Print_UINT64(val);
#else
                        LEM_STOPIT; // Тип uinteger64 не подключен!
#endif
                    }
                    else
                    {
#if defined LEM_I64
                        lem::int64_t val = va_arg(ap, lem::int64_t);
                        Print_INT64(val);
#else
                        LEM_STOPIT; // Тип integer64 не подключен!
#endif
                    }
                    }

                break;
                    } // end case INT


                   // ***************************************************************
#if !defined(LEM_NOREAL)
            case 'r':
            case 'R':
            case 'e':
            case 'f':
            case 'g':
            {
                char FORMAT[80];
                MakeRealFormat(format, i, FORMAT);

                // Поле типа REAL.
                if (is_complex)
                {
                    // Комплексная величина.
         //           LemComplex cx = va_arg(ap,LemComplex);
         //           Print_Complex( FORMAT, cx );
                    break;
                }

#if !defined LEM_NODUP
                if (is_dupel)
                {
                    char BUFFER[256];
                    if (is_normal)
                    {
                        DUPEL8 cx = va_arg(ap, DUPEL8);
                        Print_Dupel(BUFFER, FORMAT, cx);
                    }

                    if (is_long)
                    {
                        DUPEL10 cx = va_arg(ap, DUPEL10);
                        Print_Dupel(BUFFER, FORMAT, cx);
                    }
                    /*
                               #if (defined(SETREAL18) || defined(DEFREAL18))
                               if( is_quatro )
                                {
                                 DUPEL18 val = va_arg(ap,DUPEL18);
                                 Print_Dupel( BUFFER, FORMAT, val );
                                }
                               #endif
                    */
                    print_field(BUFFER);

                    break;
                }
#endif

                if (is_normal)
                {
                    double val = va_arg(ap, double);
                    Print_Real8(FORMAT, val);
                    break;
                }

                if (is_long)
                {
                    long double val = va_arg(ap, long double);
                    Print_Real10(FORMAT, val);
                    break;
                }

#if (defined(SETREAL18) || defined(DEFREAL18) )
                if (is_quatro)
                {
                    REAL18 val = va_arg(ap, REAL18);
                    Print_Real18(FORMAT, val);
                    break;
                }
#endif

                break;
            } // end case REAL
#endif

            default:
            {
                char b[48];
                sprintf(b, "Invalid specification [%c]\n", ch);
                throw E_BaseException(wstring(UFString(b).c_str()));
            }
                } // end switch(ch)

            } // end if ch=='%'
        else
            printf(ch, true);

            } // end while

    va_end(ap);

    if (autoflush)
        stream->flush();

    End_Of_Printf();

#if defined LEM_THREADS
    lock_mstr.Leave();
#endif

    return;
        }

/****************************************************************************
  Вывод единичного символа в поток. Если наш выходной поток связан с другим
  файлом (указатель doubler), то также выводим символ в него. Такой способ
  связывания протоков позволяет строить произвольно длинные цепочки потоков,
  вывод в которые одинаковой информации производится обращением лишь к одному
  потоку, первому в цепочке.
****************************************************************************/
void OFormatter::printf(char CH, bool do_recode)
{
    LEM_CHECKIT_Z(!!(stream));
    if (!(stream)) return;

    if (!!(doubler))
        doubler->printf(CH);

    if (CH == 7)
        return;

    // Перекодировка для целевого символьного потока
#if defined LEM_UNIX
    char ch = CH;
#else
    char ch = do_recode ?
        recode_char(CH, local_cp->get_Index(), out_cp->get_Index())
        :
        CH;
#endif 

    if (GetControlFlag(LEM_MSTREAM_HTML) && ch == '\n')
        // Файлы в формате HTML требуют указания токена <BR> в конце строки.
        stream->puts("<BR>");
    else if (ch == '\t')
    {
        after = 0;

        if (GetControlFlag(LEM_MSTREAM_RAWTAB))
            stream->put('\t');
        else
            Print_Tab((npos / 8 + 1) * 8, ' ');

        return;
    }
    else if (ch == '\n' && stream->IsBinary())
        stream->put('\r');

    stream->put(ch);

    npos = ch == '\n' ? 0 : npos + 1;
    if (npos == 0 && left_margin)
        for (int i = left_margin - 1; i >= 0; i--)
            printf(' ');

    if (page_width && npos == page_width)
        printf('\n');

    return;
}

void OFormatter::put_direct(char ch)
{
    LEM_CHECKIT_Z(!!(stream));
    if (!(stream)) return;

    if (!!(doubler))
        doubler->put_direct(ch);

    stream->put(ch);
    return;
}


char OFormatter::get_flag_state(int fi)
{
    for (int i = 0; i < nflag; i++)
        if (flag_index[i] == fi)
            return flag_state[i];

    return 0;
}

// *************************************************************************
// Установка нового состояния флага (не путать с флагами SetControlFlag(...)
//
//   fi - имя флага (символ)
//   state - состояние флага (символ)
// *************************************************************************
void OFormatter::set_flag_state(int fi, int state)
{
    for (int i = 0; i < nflag; i++)
        if (flag_index[i] == fi)
        {
            flag_state[i] = char(state);
            break;
        }

    return;
}

int OFormatter::read_digits(const char* format, int& i)
{
    char buffer[16];
    int ii = 0;

    while (is_digit(format[i]))
    {
        LEM_CHECKIT_Z(ii < (int)DIM_A(buffer));
        buffer[ii++] = format[i++];
    }

    buffer[ii] = '\0';
    LEM_CHECKIT_Z((buffer[0]));

    int d;
    to_int(buffer, &d);
    return d;
}

/******************************************************************
  Метод считывает набор уточняющих флагов спецификации.

   format - указатель на начало форматной строки
   i      - курсор считывания в форматной строке
*******************************************************************/
void OFormatter::read_field_spec(const char *format, int &i)
{
    total_len =
        after = -1;
    exp_len = -1;
    field_len = -1;
    after = -1;
    aligment = 0;
    sign_out = 0;
    nflag = 0;
    nrepeate = 1;
    radix = 10;
    caps = -1;

    is_normal =
        is_unsigned =
        is_long =
        is_quatro =
        is_complex = false;

    // local_cp    = 866;

    char ch = format[i];

    if (ch == ' ' || ch == '+')
    {
        // Определение вывода знака.
        switch (ch)
        {
        case ' ': sign_out = 1; break;
        case '+': sign_out = 2; break;
        }

        i++;
    }

    if (is_digit(format[i]))
        field_len = read_digits(format, i);

    // Если точка оборвала спецификацию размера поля, то
    // считаем также вторую часть.
    if (format[i] == '.')
    {
        i++;

        // Тогда считываем цифры.
        after = read_digits(format, i);
    }


    bool cont = true;
    while (cont)
    {
        switch (format[i++])
        {
        case 'A':
        {
            // Спецификация типа выравнивания поля.
            char align_type = (char)to_lower(format[i++]);
            LEM_CHECKIT_Z(align_type == 'l' || align_type == 'c' || align_type == 'r');

            switch (align_type)
            {
            case 'l': aligment = 0; break;
            case 'c': aligment = 1; break;
            case 'r': aligment = 2; break;
            }

            break;
        }


        case 'X':
        {
            // Спецификация основания системы счисления для вывода целых.
            radix = read_digits(format, i);
            break;
        }

        case 'K':
        {
            // Смена кодовой страницы для читаемых строковых аргументов.
            local_cp = CodeConverter::getConverter(read_digits(format, i));
            break;
        }

        case 'W':
        {
            // Общий размер поля.
            total_len = read_digits(format, i);
            break;
        }

        case '^':
        {
            // Число знакомест под порядок числа с плавающей точкой.
            exp_len = read_digits(format, i);
            break;
        }

        case 'u':
        {
            // Объект 'unsigned'
            LEM_CHECKIT_Z(!is_unsigned);
            is_unsigned = true;
            break;
        }

        case 'n':
        {
            // Объект 'single'
            LEM_CHECKIT_Z(!is_quatro);
            LEM_CHECKIT_Z(!is_long);
            LEM_CHECKIT_Z(!is_normal);
            is_normal = true;
            break;
        }

        case 'l':
        {
            // Объект 'long'
            LEM_CHECKIT_Z(!is_quatro);
            LEM_CHECKIT_Z(!is_long);
            LEM_CHECKIT_Z(!is_normal);
            is_long = true;
            break;
        }

        case 'q':
        {
            // Объект 'quatro'
            LEM_CHECKIT_Z(!is_long);
            LEM_CHECKIT_Z(!is_quatro);
            LEM_CHECKIT_Z(!is_normal);
            is_quatro = true;
            break;
        }


        case 'L':
        {
            // Тип преобразования букв (все маленькие, все большие).

            char caps_type = to_lower(format[i++]);
            LEM_CHECKIT_Z(caps_type == 'c' || caps_type == 's');

            switch (caps_type)
            {
            case 'c': caps = 0; break;
            case 's': caps = 1; break;
            }

            break;
        }


        case 'F':
        {
            // Специальный флаг управления, анализируется подмодулем отображени
            // конкретного типа.
            char index = to_lower(format[i++]);
            char state = to_lower(format[i++]);

            LEM_CHECKIT_Z(is_al_num(state));
            LEM_CHECKIT_Z(nflag < (int)DIM_A(flag_index));
            LEM_CHECKIT_Z(nflag != LEM_MSTREAM_NFLAG);

            flag_index[nflag] = index;
            flag_state[nflag] = state;
            nflag++;

            break;
        }

        case 'i':
        {
            // Оператор повтора вывода.
            nrepeate = read_digits(format, i);
            break;
        }

        default:
        {
            i--;
            cont = false;
            break;
        }

        } // end switch
    }

    return;
}

void OFormatter::print_field(char *buffer)
{
    if (!(stream)) return;

    int str_len = lem_strlen(buffer);   // Длина пол
    int nspace = 0;

    switch (caps)
    {
    case 0:
    {
        to_upper(buffer);
        break;
    }

    case 1:
    {
        to_lower(buffer);
        break;
    }
    }

    if (get_flag_state('$') == '3' || get_flag_state('$') == '4')
    {
        char delim = ' ';
        if (get_flag_state('$') == '3')
            delim = ',';

        int is = 0, es = 0;
        char ip[100] = "", fp[100] = "", ep[100] = "";

        split(
            buffer,
            &is, ip, sizeof(ip),
            fp, sizeof(fp),
            &es, ep, sizeof(ep)
        );

        if (strlen(ep))
        {
            set_flag_state('$', 0);
            if (int(npos + lem_strlen(buffer)) > (int)page_width)
                printf('\n');

            print_field(buffer);
            return;
        }

        lem_strcpy(buffer, ip);

        // Специальный формат вывода денежных сумм.
        int blen = lem_strlen(buffer);
        int nblen = blen + blen / 3 + 1;
        char *nbuf = new char[nblen + 1];
        nbuf[nblen] = 0;

        // Пропустим пробелы справа.
        int iscan = blen - 1, idest = nblen - 1;
        while (buffer[iscan] == ' ' && iscan >= 0) nbuf[idest--] = buffer[iscan--];

        int iblock = 0;
        while (iscan >= 0 && is_digit(buffer[iscan]))
        {
            nbuf[idest--] = buffer[iscan--];

            if (!(++iblock % 3) && iscan >= 0 && is_digit(buffer[iscan]))
            {
                nbuf[idest--] = delim;
                iblock = 0;
            }
        }

        while (iscan >= 0 && buffer[iscan] == ' ')
            nbuf[idest--] = buffer[iscan--];

        set_flag_state('$', 0);

        if (page_width && int(npos + lem_strlen(nbuf + idest + 1)) > int(page_width))
            eol();

        print_field(nbuf + idest + 1);
        delete[] nbuf;
        return;
    }

    if (total_len > 0)
    {
        nspace = total_len - str_len;   // Сколько пробелов необходимо.

        if (nspace < 0)
            nspace = 0;
    }
    else
    {
        do
        {
            int ip = 0;
            while (buffer[ip])
                printf(buffer[ip++]);
        } while (--nrepeate > 0);

        return;
    }


    switch (aligment)
    {
    case 0:
    {
        // От левого края (по умолчанию).
        do
        {
            int ip = 0, i = 0;
            while (buffer[ip])
                printf(buffer[ip++]);

            while (i++ != nspace)
                printf(' ');
        } while (--nrepeate > 0);

        break;
    }

    case 2:
    {
        // От правого края.

        // Итак, поле будет содержать before знакомест, из которых
        // str_len заполняется символами строки, остальное слева пробелы.
        do
        {
            int i = 0;
            while (i++ != nspace)
                printf(' ');

            int ip = 0;
            while (buffer[ip])
                printf(buffer[ip++]);
        } while (--nrepeate > 0);

        break;
    }

    case 1:
    {
        // С центрированием.

        do
        {
            int i = 0;
            while (i++ != nspace / 2)
                printf(' ');

            int ip = 0;
            while (buffer[ip])
                printf(buffer[ip++]);

            i = 0;
            while (i++ != (nspace / 2 + nspace % 2))
                printf(' ');
        } while (--nrepeate > 0);

        break;
    }
    }

    return;
}

// ************************************************************
// Управление цветовыми параметрами текстового вывода.
// Работает не для всех платформ! Если поддержка отсутствует,
// то просто ничего не делаем.
// ************************************************************
void OFormatter::VideoControl(const char *format, int &i)
{
    switch (format[i++])
    {
    case 'b':
    {
        // Установка цвета заднего фона
        lem::uint8_t iColor = (lem::uint8_t) format[i++];
        iColor = iColor - (iColor >= lem::uint8_t('A') ? lem::uint8_t('A') - 10 : lem::uint8_t('0'));
        stream->SetBackGroundColor(iColor);
        break;
    }

    case 'f':
    {
        // Установка цвета символов
        lem::uint8_t iColor = (lem::uint8_t)format[i++];
        iColor = iColor - (iColor >= 'A' ? 'A' - 10 : '0');
        stream->SetForeGroundColor(iColor);
        break;
    }

    case 'x':
        stream->SetBlinkMode(true);
        break;

    case 'n':
        stream->SetNormalMode();
        break;

    case 'l':
        stream->SetLowLightMode();
        break;

    case 'h':
        stream->SetHighLightMode();
        break;

    default:
        LEM_STOPIT;
    }

    return;
}

// ******************************************************
// Печатаем C-строку (внутренняя процедура).
// ******************************************************
void OFormatter::Print_C_String(const char *val)
{
    LEM_CHECKIT_Z(after == -1);
    LEM_CHECKIT_Z(!is_quatro);

    // Наша задача - распечатать либо всю строку,
    // если параметр field_len в спецификации поля не определен,
    // либо field_len символов из строки.
    int len = lem_strlen(val);   // Действительная длина строки
    if (field_len > 0 && field_len < len)
        len = field_len;

    char *buffer = new char[len + 1];

    if (buffer == NULL)
        return;

    if (!!(val))
        strncpy(buffer, val, len);
    else
        *buffer = '\0';

    buffer[len] = '\0'; // На всякий случай терминируем строку (после strncpy).

    print_field(buffer);

    delete[] buffer;
    return;
}

void OFormatter::Print_Boolean(bool b)
{
    LEM_CHECKIT_Z(after < 1);
    LEM_CHECKIT_Z(radix == 10);

    char buffer[20];

    if (get_flag_state('f') == '0' || get_flag_state('f') == 0)
    {
        if (b) strcpy(buffer, "true");
        else  strcpy(buffer, "false");
    }
    else
        if (get_flag_state('f') == '1')
        {
            if (b) strcpy(buffer, ".TRUE.");
            else  strcpy(buffer, ".FALSE.");
        }
        else
            if (get_flag_state('f') == '1')
            {
                if (b) strcpy(buffer, "1");
                else  strcpy(buffer, "0");
            }
            else
                LEM_STOPIT;

    print_field(buffer);
    return;
}


/*******************************************************************
  Перемещение до указанной позиции. Если текущая позици
  лежит левее, то перемещения не будет. Если параметр to!=SHT_MAX,
  то именно он задает новую позицию, иначе новая позиция берется из
  поля field_len.
********************************************************************/
void OFormatter::Print_Tab(int to, char ch)
{
    LEM_CHECKIT_Z(after < 1);
    if (!(stream)) return;

    int TO = to == INT_MAX ? field_len : to;
    int n = TO - npos;
    if (n < 0)
        n = 0;

    for (int i = n - 1; i >= 0; i--)
        printf(ch);

    return;
}

#if !defined LEM_NOREAL
/******************************************************************

  Считываем специальные флаги управления для вывода поля REAL.
  Эта процедура должна вызываться только в том случае, если
  встретилась спецификация %R... или %r...

*******************************************************************/
void OFormatter::MakeRealFormat(const char *format, int &i, char *f1)
{
    if (!(format)) return;

#if REAL_TYPE==1008 || REAL_TYPE==10010 || REAL_TYPE==10018
    // Тип REAL определен как один из DUPELxx
    is_dupel = true;
#else
    is_dupel = false;
#endif

    // Если длина типа явно не указана, то примем ее как
    // длину текущего типа REAL.
    if (!is_normal && !is_long && !is_quatro)
    {
        //#if REAL_TYPE==4 || REAL_TYPE==8 || REAL_TYPE==1008
        is_normal = true;
        //#elif REAL_TYPE==10 || REAL_TYPE==10010
        // is_long=true;
        //#elif REAL_TYPE==18 || REAL_TYPE==10018
        // is_quatro=true;
        //#else
        // #error UNKNOWN REAL TYPE
        //#endif
    }

    // Начинаем читать спецификацию поля сначала, дабы различить
    // Rxx и rxx объявления.
    char ch = format[i - 1];
    is_complete = false;

    bool is_efg = false;

    if (ch == 'e' || ch == 'g' || ch == 'f')
    {
        is_complete = false;
        is_dupel = false;
        is_complex = false;
        is_efg = true;
    }
    else if (ch == 'R')
    {
        is_complete = true;

        // Так как этот символ означает вывод всех значащих
        // цифр поля, то прямое указание размера поля недопустимо.
        LEM_CHECKIT_Z(field_len < 1);
        LEM_CHECKIT_Z(after < 1);

        if (!is_normal && !is_long && !is_quatro)
        {
#if REAL_TYPE==4
            field_len = 14;
            after = 7;
#elif REAL_TYPE==8 || REAL_TYPE==1008
            field_len = 23;
            after = 15;
#elif REAL_TYPE==10 || REAL_TYPE==10010
            field_len = 26;
            after = 17;
#elif REAL_TYPE==18 || REAL_TYPE==10018
            field_len = 56;
            after = 32;
#endif
        }
        else
        {
            if (is_normal)
            {
                // Явно требуется double
                field_len = 23;
                after = 15;
            }

            if (is_long)
            {
                // Явно требуется long double
                field_len = 26;
                after = 17;
            }

            if (is_quatro)
            {
                // Явно требуется REAL18
                field_len = 56;
                after = 32;
            }
        }
        }

    if (!is_efg)
    {
        // Возможно, признак комплексного числа.
        ch = format[i++];

        if (ch == 'c')
        {
            // Принудительно LemComplex
            is_complex = true;
            ch = format[i++];
        }

        if (ch == 'd')
        {
            // Принудительно DUPELxx
            is_dupel = true;
            ch = format[i++];
            LEM_CHECKIT_Z(!is_complex);
        }

        if (ch == 'r')
        {
            // Принудительно REALxx
            LEM_CHECKIT_Z(!is_dupel);
            LEM_CHECKIT_Z(!is_complex);
            is_dupel = false;
            ch = format[i++];
        }
    }

    char lc[2] = " ";
    if (is_long)
        lc[0] = 'L';
    else
        lc[0] = 0;

    const char *sign_formats[] = { "", " ", "+" };

    if (field_len < 1 && after == -1)
    {
        sprintf(f1, "%c%s%s%c", '%', sign_formats[sign_out], lc, ch);
    }
    else
    {
        if (after != -1)
            sprintf(f1, "%c%s%d.%d%s%c", '%', sign_formats[sign_out], field_len, after, lc, ch);
        else
            sprintf(f1, "%c%s%d%s%c", '%', sign_formats[sign_out], field_len, lc, ch);
    }

    return;
    }

void OFormatter::Print_Real8(const char *FORMAT, double val)
{
    char aval[80];
    sprintf(aval, FORMAT, val);
    print_field(aval);
    return;
}

void OFormatter::Print_Real10(const char *FORMAT, long double val)
{
    char aval[80];
    sprintf(aval, FORMAT, val);
    print_field(aval);
    return;
}

#if (defined(SETREAL18) || defined(DEFREAL18))
void OFormatter::Print_Real18(const char *FORMAT, REAL18 val)
{
    char aval[80];
    qreal_to_str(val, aval, sign_out, true, false, after);

    print_field(aval);
    return;
}
#endif

/*
// Распечатка комплексного числа.
void OFormatter::Print_Complex( const char *FORMAT, const LemComplex &cx )
{
 char re_part[256];
 char im_part[256];

 if( !is_dupel )
  {
   if( is_normal || is_long )
    {
     sprintf( re_part, FORMAT, cx.Re() );
     sprintf( im_part, FORMAT, cx.Im() );
    }
   else
    {
     #if (defined(SETREAL18) || defined(DEFREAL18)) && REAL_TYPE==18
      qreal_to_str( cx.Re(), re_part );
      qreal_to_str( cx.Re(), im_part );
     #else
      LEM_STOPIT;
     #endif
    }
  }
 else
  {
   #if REAL_TYPE==1008 || REAL_TYPE==10010 || REAL_TYPE==10018

   // Мрачноватый случай: тип LemComplex с компонентами DUPEL...
   if( is_normal || is_long )
    {
     Print_Dupel( re_part, FORMAT, cx.Re() );
     Print_Dupel( im_part, FORMAT, cx.Im() );
    }

   if( is_quatro )
    {
     #if (defined(SETREAL18) || defined(DEFREAL18))
      Print_Dupel( re_part, FORMAT, cx.Re() );
      Print_Dupel( im_part, FORMAT, cx.Im() );
     #else
      LEM_STOPIT;
     #endif
    }
   #endif
  }

 char buffer[256]; // ??? может 512 ???

 if( get_flag_state('f')=='0' || get_flag_state('f')==0 )
  sprintf( buffer, "{%s,%s}",  re_part, im_part );
 else
  if( get_flag_state('f')=='1' )
   sprintf( buffer, "(%s,%s)",  re_part, im_part );
  else
   if( get_flag_state('f')=='2' )
    sprintf( buffer, "%s %s",  re_part, im_part );
   else
    if( get_flag_state('f')=='3' )
     sprintf( buffer, "re=%s im=%s",  re_part, im_part );
    else
     LEM_STOPIT;

 print_field(buffer);
 return;
}
*/

#if !defined LEM_NODUP
void OFormatter::Print_Dupel(
    char *BUFFER,
    const char *FORMAT,
    const DUPEL8 &D
)
{
    char a_part[128], b_part[32];

    sprintf(a_part, FORMAT, D.real());

    if (!is_complete)
    {
        b_part[0] = 0;
        sprintf(BUFFER, "{%s}", a_part);
    }
    else
    {
        if (get_flag_state('f') == '1')
            sprintf(b_part, FORMAT, D.diverg());
        else
            sprintf(b_part, "%7.1e%%", double(D.error()*100.));

        sprintf(BUFFER, "{%s err=%s}", a_part, b_part);
    }

    return;
}
#endif // !defined LEM_NODUP

#if !defined LEM_NODUP
#if !defined NOlong double
void OFormatter::Print_Dupel(
    char *BUFFER,
    const char *FORMAT,
    DUPEL10 &D
)
{
    char a_part[128], b_part[128];

    sprintf(a_part, FORMAT, D.real());

    if (!is_complete)
    {
        b_part[0] = 0;
        sprintf(BUFFER, "{%s}", a_part);
    }
    else
    {
        if (get_flag_state('f') == '1')
            sprintf(b_part, FORMAT, D.diverg());
        else
            sprintf(b_part, "%7.1e%%", double(D.error()*100.));

        sprintf(BUFFER, "{%s err=%s}", a_part, b_part);
    }

    return;
}
#endif // !defined NOlong double
#endif // !defined LEM_NODUP

#if !defined LEM_NODUP
/*
#if defined(SETREAL18) || defined(DEFREAL18)
void OFormatter::Print_Dupel( char *BUFFER, const char *FORMAT, const DUPEL18 &D )
{
 char a_part[128],b_part[128];

 qreal_to_str( D.abs(), a_part );

 if( !is_complete )
  {
   b_part[0]=0;
   sprintf( BUFFER, "{%s}", a_part );
  }
 else
  {
   if( get_flag_state('f')=='1' )
   qreal_to_str( D.div(), b_part );
   else
    sprintf( b_part, "%7.1e%%", double(D.error()*100.) );

   sprintf( BUFFER, "{%s err=%s}",  a_part, b_part );
 }

 return;
}
#endif
*/
#endif // !defined LEM_NODUP

#endif // !defined LEM_NOREAL

void OFormatter::Print_UINT(unsigned int val)
{
    char aval[80] = "";

    if (!field_len && is_complete)
        field_len = strlen(uint_to_str(UINT_MAX, aval, radix));

    uint_to_str(val, aval, radix);
    int val_signum = val > 0;

    PrintInt(aval, val_signum);
    return;
}

void OFormatter::Print_INT(int Val)
{
    char aval[80] = "";
    int val_signum = 0;
    int val = Val;

    if (!field_len && is_complete)
        field_len = strlen(int_to_str(INT_MIN, aval, radix));

    if (val < 0)
    {
        val = -val;
        val_signum = -1;
    }
    else
        if (val) val_signum = 1;

    if (val < 0)
    {
        // Этот хокус-покус из-за эффекта -MININT < 0 !
        // Так что abs(MININT) печатаем напрямую. Знак
        // уже учтен через val_signum.
#if INT_TYPE==2
        strcpy(aval, "32768");
#else
        strcpy(aval, "2147483648");
#endif
    }
    else
        int_to_str(val, aval, radix);

    PrintInt(aval, val_signum);
    return;
}

void OFormatter::Print_UINT32(unsigned int val)
{
    char aval[80] = "";
    int val_signum = 0;

    if (!field_len && is_complete)
        field_len = strlen(uint32_to_str(UINT_MAX, aval, radix));

    uint32_to_str(val, aval, radix);
    val_signum = val > 0;

    PrintInt(aval, val_signum);
    return;
}

void OFormatter::Print_INT32(int Val)
{
    char aval[80] = "";
    int val_signum = 0;
    lem::int32_t val = Val;

    if (field_len == 0 && is_complete)
        field_len = strlen(int32_to_str(0, aval, radix));

    if (val < 0)
    {
        val = -val;
        val_signum = -1;
    }
    else
        if (val) val_signum = 1;

    if (val < 0)
    {
        // Этот хокус-покус из-за эффекта -MININT32 < 0 !
        // Так что abs(MININT32) печатаем напрямую. Знак
        // уже учтен через val_signum.
        strcpy(aval, "2147483648");
    }
    else
        uint_to_str(val, aval, radix);

    PrintInt(aval, val_signum);
    return;
}

#if defined LEM_UI64

void OFormatter::Print_UINT64(lem::uint64_t val)
{
    char aval[256] = "";
    int val_signum = 0;

    const int sl = strlen(lem::to_str(lem::uint64_max, aval, radix));
    if (!field_len && is_complete)
        field_len = sl;

    val_signum = val > 0;
    PrintInt(aval, val_signum);
    return;
}
#endif

#if defined LEM_I64
void OFormatter::Print_INT64(lem::int64_t val)
{
    char aval[256];
    int val_signum = 0;

    if (val < 0)
    {
        val = -val;
        val_signum = -1;
    }
    else
        if (!!val) val_signum = 1;

    if (val < 0)
    {
        sprintf(aval, "%I64d", val);
        val_signum = 1;
    }
    else
    {
        lem::uint64_t uval = lem::uint64_t(val);
        to_str(uval, aval, radix);
    }

    PrintInt(aval, val_signum);
    return;
}
#endif


void OFormatter::PrintInt(const char *aval, int val_signum)
{
    char buffer[80] = "";
    char zeros[80] = "";
    char forsign[2] = { '\0', '\0' };

    switch (sign_out)
    {
    case 0:
        if (val_signum < 0) *forsign = '-';
        break;

    case 1:
    {
        if (val_signum >= 0)
            *forsign = ' ';
        else
            *forsign = '-';

        break;
    }

    case 2:
    {
        if (val_signum > 0)
            *forsign = '+';
        else
            if (!val_signum)
                *forsign = ' ';
            else
                *forsign = '-';

        break;
    }
    }

    *zeros = 0;

    // Если размер поля field_len больше, чем получилось
    // цифр, до допишем нули слева.
    int nzero = field_len - strlen(aval) - strlen(forsign);

    if (nzero > 0)
    {
        int iz = 0;
        while (nzero--)
            zeros[iz++] = get_flag_state('z') == '1' ? '0' : ' ';

        zeros[iz] = 0;
    }

    sprintf(buffer, "%s%s%s", forsign, zeros, aval);
    print_field(buffer);
    return;
}


// ******************************************************
// Перегружаем процедуру печати UNICODE-строки.
// ******************************************************
void OFormatter::Print_C_String(const wchar_t *uStr)
{
    LEM_CHECKIT_Z(after == -1);
    LEM_CHECKIT_Z(!is_quatro);

    if (uStr == NULL)
        return;

    // Наша задача - распечатать либо всю строку,
    // если параметр field_len в спецификации поля не определен,
    // либо field_len символов из строки.
    int len = lem_fullstrlen(uStr);   // Действительная длина строки
    if (field_len > 0 && field_len < len)
        len = field_len;

    wchar_t *buffer = new wchar_t[len + 1];

    if (!(buffer))
        return;

    if (uStr)
        lem_strncpy(buffer, uStr, len);
    else
        buffer[0] = 0;

    print_field(buffer);

    delete[] buffer;
    return;
}


void OFormatter::print_field(wchar_t *buffer)
{
    if (!(stream)) return;

    int str_len = lem_strlen(buffer);   // Длина пол
    int nspace = 0;

    switch (caps)
    {
    case 0:
    {
        to_upper(buffer);
        break;
    }

    case 1:
    {
        to_lower(buffer);
        break;
    }
    }

    if (get_flag_state('$') == '3' || get_flag_state('$') == '4')
    {
        wchar_t delim = ' ';
        if (get_flag_state('$') == '3')
            delim = ',';

        int is = 0, es = 0;
        wchar_t ip[100] = { 0 }, fp[100] = { 0 }, ep[100] = { 0 };

        split(
            buffer,
            &is, ip, sizeof(ip),
            fp, sizeof(fp),
            &es, ep, sizeof(ep)
        );

        if (lem_strlen(ep))
        {
            set_flag_state('$', 0);
            if (int(npos + lem_strlen(buffer)) > (int)page_width)
                printf('\n');

            print_field(buffer);
            return;
        }

        lem_strcpy(buffer, ip);

        // Специальный формат вывода денежных сумм.
        int blen = lem_strlen(buffer);
        int nblen = blen + blen / 3 + 1;
        wchar_t *nbuf = new wchar_t[nblen + 1];
        nbuf[nblen] = 0;

        // Пропустим пробелы справа.
        int iscan = blen - 1, idest = nblen - 1;

        while (buffer[iscan] == L' ' && iscan >= 0)
            nbuf[idest--] = buffer[iscan--];

        int iblock = 0;
        while (is_udigit(buffer[iscan]) && iscan >= 0)
        {
            nbuf[idest--] = buffer[iscan--];

            if (!(++iblock % 3) && iscan >= 0 && is_udigit(buffer[iscan]))
            {
                nbuf[idest--] = delim;
                iblock = 0;
            }
        }

        while (buffer[iscan] == L' ' && iscan >= 0)
            nbuf[idest--] = buffer[iscan--];

        set_flag_state('$', 0);

        if (page_width && int(npos + lem_strlen(nbuf + idest + 1)) > int(page_width))
            eol();

        print_field(nbuf + idest + 1);
        delete nbuf;
        return;
    }

    if (total_len > 0)
    {
        nspace = total_len - str_len;   // Сколько пробелов необходимо.

        if (nspace < 0)
            nspace = 0;
    }
    else
    {
        do
        {
            int ip = 0;
            while (buffer[ip] != 0)
            {
                uprintf(buffer[ip++]);
            }
        } while (--nrepeate > 0);

        return;
    }

    switch (aligment)
    {
    case 0:
    {
        // От левого края (по умолчанию).
        do
        {
            int ip = 0, i = 0;
            while (buffer[ip])
                uprintf(buffer[ip++]);

            while (i++ != nspace)
                uprintf(L' ');
        } while (--nrepeate > 0);

        break;
    }

    case 2:
    {
        // От правого края.

        // Итак, поле будет содержать before знакомест, из которых
        // str_len заполняется символами строки, остальное слева пробелы.
        do
        {
            int i = 0;
            while (i++ != nspace)
                uprintf(L' ');

            int ip = 0;
            while (buffer[ip])
                uprintf(buffer[ip++]);
        } while (--nrepeate > 0);

        break;
    }

    case 1:
    {
        // С центрированием.

        do
        {
            int i = 0;
            while (i++ != nspace / 2)
                uprintf(L' ');

            int ip = 0;
            while (buffer[ip])
                uprintf(buffer[ip++]);

            i = 0;
            while (i++ != (nspace / 2 + nspace % 2))
                uprintf(L' ');
        } while (--nrepeate > 0);

        break;
    }
    }

    return;
}

// **************************************************************************
// Перегруженная процедура печати одиночного UNICODE-символа с перекодировкой
// в ASCII с помощью текущей кодовой страницы.
// **************************************************************************
void OFormatter::uprintf(wchar_t uCh)
{
    LEM_CHECKIT_Z(out_cp);
    if (out_cp->IsSingleByte())
    {
        printf(((SBCodeConverter*)out_cp)->to_ascii(uCh), false);
    }
    else
    {
        lem::CharBuffer aCh(out_cp->EstimateAsciiLen(1) + 1);
        int n = out_cp->to_ascii(uCh, aCh);
        for (int i = 0; i < n; i++)
            printf(aCh[i], false);
    }

    return;
}

void OFormatter::print_string(const wchar_t *buffer)
{
    printf("%us", buffer);
}

void OFormatter::print_string(const char *buffer)
{
    printf("%s", buffer);
}


// ***************************************************************


// Настраиваем поток вывода в буфер в памяти.
MemFormatter::MemFormatter(void)
    : OUFormatter(new lem::Char_Stream::UTF16_MemWriter(), true)
{}


const UFString MemFormatter::string(void) const
{
    lem::Char_Stream::UTF16_MemWriter* s = static_cast<lem::Char_Stream::UTF16_MemWriter*>(stream);
    UFString res = s->string();
    s->clear();
    return res;
}

/*
const FString MemFormatter::stringa(void) const
{
 lem::Char_Stream::UTF16_MemWriter* s = static_cast<lem::Char_Stream::UTF16_MemWriter*>( stream );
 return lem::to_ascii(s->string());
}
*/

// ***************************************************************

OUFormatter::OUFormatter(void)
    : OFormatter()
{}

OUFormatter::OUFormatter(const lem::Path &filename, bool write_bom)
    : OFormatter()
{
    UTF8_Reader *w = new UTF8_Reader(lem::Ptr<Stream>(new lem::BinaryWriter(filename)));

    if (write_bom)
        w->Write_Beginning();

    stream = w;
    can_i_close = true;
    return;
}

OUFormatter::OUFormatter(FILE *file)
    : OFormatter(file)
{}

OUFormatter::OUFormatter(Stream *file, bool CanClose)
    : OFormatter(file, CanClose)
{}

void OUFormatter::Open(const lem::Path &filename, bool write_bom)
{
    Delete();

    UTF8_Reader *w = new UTF8_Reader(lem::Ptr<lem::Stream>(new lem::BinaryWriter(filename)));

    if (write_bom)
        w->Write_Beginning();

    stream = w;
    can_i_close = true;
    return;
}


void OUFormatter::uprintf(wchar_t ch)
{
    LEM_CHECKIT_Z(!!(stream));
    if (!(stream)) return;

    if (!!(doubler))
        doubler->uprintf(ch);

    if (ch == 7)
        ch = L' ';

    if (GetControlFlag(LEM_MSTREAM_HTML) && ch == '\n')
        // Файлы в формате HTML требуют указания токена <BR> в конце строки.
        stream->puts("<BR>");
    else if (ch == L'\t')
    {
        after = 0;
        Print_Tab((npos / 8 + 1) * 8, ' ');
        return;
    }
    else if (ch == L'\n' && stream->IsBinary())
        stream->put('\r');

    stream->wput(ch);

    npos = ch == L'\n' ? 0 : npos + 1;
    if (npos == 0 && left_margin)
        for (int i = left_margin - 1; i >= 0; i--)
            uprintf(L' ');

    if (page_width && npos == page_width)
        uprintf(L'\n');

    return;
}


OFormatter& lem::operator << (OFormatter &o, int d)
{
    o.printf("%d", d);
    return o;
}

OFormatter& lem::operator<<(OFormatter &to, const FString &s)
{
    to.printf("%s", s.c_str());
    return to;
}

OFormatter& lem::operator<<(OFormatter &to, const UFString &s)
{
    to.printf("%us", s.c_str());
    return to;
}

OFormatter& lem::operator<<(OFormatter &to, const CString &s)
{
    to.print_field((char*)s.c_str());
    return to;
}

OFormatter& lem::operator<<(OFormatter &to, const UCString &s)
{
    to.print_field((wchar_t*)s.c_str());
    return to;
}

void OFormatter::flush(void)
{
    if (!!(stream))
        stream->flush();

    if (!!(doubler))
        doubler->flush();

    return;
}


XmlFormatter::XmlFormatter(const lem::Path &filename)
    :OUFormatter(filename, false)
{
}


void XmlFormatter::WriteBeginning(void)
{
    printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    return;
}



void OFormatter::eol(void)
{
    printf('\n');
    return;
}



void OFormatter::cr(void)
{
    printf('\r');
    return;
}



void OFormatter::close(void)
{
    Delete();
    return;
}


void OFormatter::dot(void)
{
    printf('.');
    flush();
    return;
}

void OFormatter::SetControlFlag(unsigned long Flags, bool SetAction)
{
    CONTROLFLAG &= ~Flags;

    if (SetAction)
        CONTROLFLAG |= Flags;

    return;
}


bool OFormatter::GetControlFlag(unsigned long Flags) const
{
    return !!(CONTROLFLAG&Flags);
}


void OFormatter::SetDoubler(OFormatter *Doubler)
{
    doubler = Doubler;
}

void OFormatter::ClearDoubler(void)
{
    doubler = NULL;
}

OFormatter* OFormatter::GetDoubler(void)
{
    return doubler;
}

Stream* OFormatter::GetStream(void)
{
    return stream;
}

void OFormatter::SetLeftMargin(int X)
{
    left_margin = X;
}


void OFormatter::SetLocalCP(const CodeConverter *Page)
{
    local_cp = Page;
}

void OFormatter::SetOutCP(const CodeConverter *Page)
{
    out_cp = Page;
}

void OFormatter::SetCP(const CodeConverter *Device, const CodeConverter *Local)
{
    out_cp = Device; local_cp = Local;
}

const CodeConverter* OFormatter::GetOutCP(void)
{
    return out_cp;
}


void OFormatter::SetAutoflush(void)
{
    autoflush = true;
}


void OFormatter::cprintf(const char *fmt, ...)
{
    if (fmt == NULL)
        return;

    va_list argptr;
    va_start(argptr, fmt);

    int size = 1024;

    char *buf = NULL;
    while (true)
    {
        buf = (char*)malloc(sizeof(char)*(size + 1));
        if (!buf)
        {
            // out of memory
            va_end(argptr);
            return;
        }

#if defined LEM_WINDOWS
        int len = _vsnprintf(buf, size, fmt, argptr);
#else
        int len = vsnprintf(buf, size, fmt, argptr);
#endif


        // some implementations of vsnprintf() don't NUL terminate the string
        // if there is not enough space for it so always do it manually
        buf[size] = '\0';

        if ((len >= 0) && (len <= size))
            break;

        // still not enough, double it again
        size *= 2;
        free(buf);
    }

    va_end(argptr);

    if (buf != NULL)
    {
        print_string(buf);
        free(buf);
    }

    return;
}


void OFormatter::cprintf(const wchar_t *fmt, ...)
{
    if (fmt == NULL)
        return;

    va_list argptr;
    va_start(argptr, fmt);

    int size = 1024;

    wchar_t *buf = NULL;
    while (true)
    {
        buf = (wchar_t*)malloc(sizeof(wchar_t)*(size + 1));
        if (!buf)
        {
            // out of memory
            va_end(argptr);
            return;
        }

#if defined LEM_WINDOWS
        int len = _vsnwprintf(buf, size, fmt, argptr);
#else
        int len = vswprintf(buf, size, fmt, argptr);
#endif

        // some implementations of vsnprintf() don't NUL terminate the string
        // if there is not enough space for it so always do it manually
        buf[size] = L'\0';

        if ((len >= 0) && (len <= size))
            break;

        // still not enough, double it again
        size *= 2;
        free(buf);
    }

    va_end(argptr);

    if (buf != NULL)
    {
        print_string(buf);
        free(buf);
    }

    return;
}



U16Formatter::U16Formatter(void)
    : OFormatter()
{}


U16Formatter::U16Formatter(const lem::Path &filename, bool write_bom)
    : OFormatter()
{
    UTF16_Reader *w = new UTF16_Reader(SET_UTF16, lem::Ptr<Stream>(new lem::BinaryWriter(filename)));

    if (write_bom)
        w->Write_Beginning();

    stream = w;
    can_i_close = true;
    return;
}

void U16Formatter::Open(const lem::Path &filename, bool write_bom)
{
    Delete();

    UTF16_Reader *w = new UTF16_Reader(SET_UTF16, lem::Ptr<lem::Stream>(new lem::BinaryWriter(filename)));

    if (write_bom)
        w->Write_Beginning();

    stream = w;
    can_i_close = true;
    return;
}


void U16Formatter::uprintf(wchar_t ch)
{
    LEM_CHECKIT_Z(!!(stream));
    if (!(stream)) return;

    if (!!(doubler))
        doubler->uprintf(ch);

    if (ch == 7)
        ch = L' ';

    if (GetControlFlag(LEM_MSTREAM_HTML) && ch == '\n')
        // Файлы в формате HTML требуют указания токена <BR> в конце строки.
        stream->puts("<BR>");
    else if (ch == L'\t')
    {
        after = 0;
        Print_Tab((npos / 8 + 1) * 8, ' ');
        return;
    }
    else if (ch == L'\n' && stream->IsBinary())
        stream->put('\r');

    stream->wput(ch);

    npos = ch == L'\n' ? 0 : npos + 1;
    if (npos == 0 && left_margin)
        for (int i = left_margin - 1; i >= 0; i--)
            uprintf(L' ');

    if (page_width && npos == page_width)
        uprintf(L'\n');

    return;
}

