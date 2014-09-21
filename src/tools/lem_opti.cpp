// -----------------------------------------------------------------------------
// File LEM_OPTI.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Разбор списка входных параметров для программы. Используется в
// операционных системах, поддерживающих запуск программ из командной строки.
// -----------------------------------------------------------------------------
//
// CD->20.11.1996
// LC->24.10.2005
// --------------

#include <lem/runtime_checks.h>
#include <lem/conversions.h>
#include <lem/cstring.h>
#include <lem/console_application.h>
#include <lem/quantors.h>

using namespace std;
using namespace lem;

ArgOption::ArgOption(void)
{
 code = key = 0;
 content = option = NULL;
 return;
}

// *************************************************************************
// Обычно используется в MS Windows - там опции командной строки передается
// в виде одной строки. Поэтому сначала разбиваем строку на отдельные
// опции, а затем используем другую процедуру.
// *************************************************************************
ArgOption* ParseArgList(
                        const char *cmdline,
                        int *argc,
                        const char *Template
                       )
{
 const int N_MAX_ARG=32;
 char *argv[N_MAX_ARG];

 char *buf = new char[ strlen(cmdline)+1 ];

 argv[0] = new char[2];
 strcpy( argv[0], "" );
 *argc=1;
 int isrc=0;

 while( cmdline[isrc] )
  {
   while( cmdline[isrc]!=0 && is_space(cmdline[isrc]) )
    isrc++;

   int ibuf=0;
   while( cmdline[isrc]!=0 && cmdline[isrc]!=' ' )
    buf[ibuf++] = cmdline[isrc++];

   buf[ibuf]=0;

   argv[*argc] = new char[strlen(buf)+1];
   strcpy( argv[*argc], buf );
   (*argc)++;

   if( *argc>=(int)DIM_A(argv) )
    LEM_STOPIT;
  }

 ArgOption* res = ParseArgList( *argc, argv, Template );

 delete buf;

 for( int i=(*argc)-1; i>=0; i-- )
  delete argv[i];

 return res;
}


namespace lem
{
 struct OptHolder
 {
  // Уникальный ключ параметра. Используется для указания внешнему алгоритму,
  // что параметр задан.
  int keycode;
  char name[LEM_CSTRING_LEN1];
  char alias[LEM_CSTRING_LEN1];
  bool is_followed; // У параметра есть аргумент (вроде ".../z=866...")
  bool by_int;      // Тип параметра - целое...
  bool by_bool;
  bool by_float;
  bool by_string;
  bool can_arg_be_omitted;

  OptHolder(void)
  {
   keycode            = -1;
   name[0]            =
   alias[0]           = 0;
   is_followed        =
   by_int             =
   by_bool            =
   by_float           =
   by_string          =
   can_arg_be_omitted = false;
   return;
  }

  void Load( const char *Template, int &it );
 };
}


void OptHolder::Load( const char *Template, int &it )
{
 // Считываем имя параметра (основное имя) - до символа ':' или '='.

 size_t ii=0;
 while(
       Template[it]!=0 &&
       Template[it]!=':' &&
       Template[it]!='='
      )
  {
   if( ii==DIM_A(name)-1 )
    // Слишком много символов в имени параметра.
    LEM_STOPIT;

   name[ii++] = Template[it++];
  }

 name[ii]=0;

 // С какой это стати нулевая длина имени???
 LEM_CHECKIT_Z( lem_isnt_empty(name) );

 if( Template[it]==':' )
  {
   // Задан alias!
   it++;
   ii=0;

   while( Template[it]!=0 && Template[it]!='=' )
    {
     // Слишком много символов в доп. имени параметра.
     LEM_CHECKIT_Z( ii<int(DIM_A(alias))-1 );

     alias[ii++] = Template[it++];
    }

   alias[ii]=0;

   // Нет уж, нечего было дёргаться и начинать задавать alias!
   LEM_CHECKIT_Z( lem_isnt_empty(alias) )
  }
 else
  strcpy( alias, name );

 it++;

 // Считываем уникальный код параметра.
 ii=0;
 char Code[LEM_CSTRING_LEN1];
 while( Template[it]!=0 && isdigit(Template[it]) )
  {
   // Слишком много символов в числе!
   LEM_CHECKIT_Z( ii<DIM_A(Code)-1 );
   Code[ii++] = Template[it++];
  }

 Code[ii]=0;

 LEM_CHECKIT_Z( lem_isnt_empty(Code) );

 keycode = to_int(Code);

 if( Template[it]==':' )
  {
   // Обнаружена секция дополнительных параметров.
   it++;

   while( Template[it]!=0 && Template[it]!=',' )
    {
     if( Template[it]=='F' )
      {
       // Какие аргументы может принимать опция в командной строке.
       is_followed=true;
       it++;

       switch(Template[it++])
       {
        case 'i': by_int=true;    break;
        case 'b': by_bool=true;   break;
        case 'f': by_float=true;  break;
        case 's': by_string=true; break;

        // Неприемлимый аргумент флага 'F'
        default: LEM_STOPIT;
       }
      }
     else if( Template[it]=='O' )
      {
       // Признак того, что аргумент опции в ком. строке может быть
       // пропущен.
       it++;
       can_arg_be_omitted = true;
      }
     else
      // Флаг не признан.
      LEM_STOPIT;
    }
  }

 // Теперь все винтики и гаечки для описания ОДНОГО параметра найдены.
 return;
}

ArgOption* lem::ParseArgList(
                             int argc,
                             char *argv[],
                             const char *Template
                            )
{
 // Разберём строку шаблонов Template на элементы.
 MCollect<OptHolder> holder;

 // **************************************************************************
 // Общий формат строки Template:
 //
 //          "opname:alias=keycode:FLAGS,"
 //
 // Возможное сокращение:
 //
 //         "opname=keycode:FLAGS,"
 //
 // означает, что сокращение имени параметра не допускается.
 //
 // Если опустить секцию флагов:
 //         "opname:alias=keyword,",
 //
 // то они все становяться false.
 //
 // Допустимые флаги:
 //
 //  Fi - followed by int argument (e.g. "... /X=123 ...")
 //  Fb - followed by boolean argument (e.g. "... /X=on ...")
 //  Ff - followed by floating point value (e.g. "... /X=3.142 ...")
 //  Fs - followed by string of chars (e.g. "... /X=c:\tmp ...")
 //  O  - аргумент опции может быть пропущен, т.е. допустимы формы /h и /h=1
 //
 // Описатели разделяются запятыми, после самого последнего описателя ставить
 // запятую не обязательно.
 // **************************************************************************

 int it=0;

 if( lem_isnt_empty(Template) )
  {
   while( Template[it]!=0 )
    {
     OptHolder h;
     h.Load(Template,it);
     holder.push_back( h );

     if( Template[it]==',' )
      {
       it++;
       continue;
      }
     else
      if( Template[it]==0 )
       break;
      else
       LEM_STOPIT;
    }

   // Итак, список описателей параметров создан. На всякий случай проверим
   // его на разумность - это разовая операция, накладные расходы малы, а
   // надёжность подрастёт.
   const int n=holder.size();
   int i0,i1;
   for( i0=0; i0<n; i0++ )
    for( i1=i0+1; i1<n; i1++ )
     if(
        holder[i0].keycode==holder[i1].keycode ||
        !strcmp(holder[i0].name,holder[i1].name) ||
        !strcmp(holder[i0].name,holder[i1].alias) ||
        !strcmp(holder[i0].alias,holder[i1].name)
       )
      LEM_STOPIT;
  }

 // Приступаем к анализу списка входных, сырых параметров.
 ArgOption *op = new ArgOption[argc-1];

 for( int i=0; i<argc-1; i++ )
  {
   if( argv[i+1][0]=='/' || argv[i+1][0]=='-' )
    {
     const char *o = argv[i+1]+1;

     // Ключ! Если возможно, проверим созданные прежде описатели.
     if( lem_isnt_empty(Template) )
      {
       // Будем искать максимально длинное совпадение...
       bool found=false;
       int max_match=0;
       int imatch=UNKNOWN;

       for( Container::size_type ii=0; ii<holder.size(); ii++ )
        {
         const OptHolder &h = holder[ii];
         const int l = strlen( h.alias );

         if( !strncmp(h.name,o,l) )
          {
           found=true;
           const int m = lem_str_match_len(h.name,o);

           if( m>max_match )
            {
             max_match = m;
             imatch = ii;
            }
          }
        }

       // Теперь imatch содержит порядковый номер максимально подходящей
       // опции.

       if( found )
        {
         const OptHolder &h = holder[imatch];
         const int l = strlen( h.alias );

         if( !strncmp(h.name,o,l) )
          {
           found=true;
           const int m = lem_str_match_len(h.name,o);
           const bool is_there_arg = o[m]=='=';

           // Сокращенное имя вполне подходит. Проверим, должен ли следовать
           // какой-либо аргумент.
           if( is_there_arg && !h.is_followed )
            {
             // Аргумента быть не должно!
             // Ошибка: неверное употребление опции.
             FString mes = "Incorrect use of option /";
             mes += o;
             mes += " : argument not allowed!\n";

             LEM_STOPIT_A( mes.c_str() );
            }
           else if( !is_there_arg && !h.is_followed )
            // Аргумента нет и не должно быть.
            op[i] = ArgOption( h.keycode, h.name, 0, "" );
           else if( is_there_arg && h.is_followed )
            // Аргумент есть, как и должно быть.
            op[i] = ArgOption( h.keycode, o, 0, o+m+1 );
           else
            {
             if( h.can_arg_be_omitted )
              // Аргумент пропущен, и это законно.
              op[i] = ArgOption( h.keycode, h.name, 0, "" );
             else
              {
               // Должен быть аргумент!
               FString mes = "Incorrect use of option /";
               mes += o;
               mes += " : argument expected!\n";

               LEM_STOPIT_A(mes.c_str());
              }
            }
          }
        }
       else // if( found ) ...
        {
         if( lem_is_empty(Template) )
          {
           op[i] = ArgOption( -1, o, o[0], o+1 );
          }
         else
          {
           // Параметр так и не подошел к описателям.
           FString mes = "Incorrect use of option /";
           mes += o;

           LEM_STOPIT_A(mes.c_str());
          }
        }
      }
     else
      op[i] = ArgOption( -1, o, o[0], o+1 );
    }
   else
    op[i] = ArgOption( -1, argv[i+1], 0, argv[i+1] );
  }

 return op;
}

ArgOption::ArgOption(
                     int Code,
                     const char *Option,
                     char Key,
                     const char *Content
                    )
{
 code = Code;
 key  = Key;

 content = new char[strlen(Content)+1];
 strcpy( content, Content );

 option = new char[strlen(Option)+1];
 strcpy( option, Option );

 return;
}

ArgOption::ArgOption( const ArgOption &x )
{
 code = x.code;
 key  = x.key;

 content = new char[strlen(x.content)+1];
 strcpy( content, x.content );

 option  = new char[strlen(x.option)+1];
 strcpy( option, x.option );
 return;
}

ArgOption::~ArgOption(void)
{
 delete[] content; content=NULL;
 delete[] option;  option=NULL;
 return;
}

void ArgOption::operator=( const ArgOption &x )
{
 if( this==&x )
  return;

 key  = x.key;
 code = x.code;
 delete content;
 delete option;

 content = new char[strlen(x.content)+1];
 strcpy( content, x.content );

 option  = new char[strlen(x.option)+1];
 strcpy( option, x.option );
 return;
}


// ------------------------ End Of File [LEM_OPTI.CPP] -------------------------
