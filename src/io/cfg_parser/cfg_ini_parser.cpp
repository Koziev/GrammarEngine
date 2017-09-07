// -------------------------------------------------------------------------
// File CFG_INI_PARSER.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Работа с ini-файлами.
//
// 24.02.2006 - процедура записи в ini-файл нового значения параметра
//              реализована через WinAPI функцию (в старой реализации явно
//              есть косячок)
//
// 12.05.2007 - обнаружена утечка памяти при парсинге ini-файлов с ошибками
// ------------------------------------------------------------------------
//
// CD->21.07.1995
// LC->07.09.2017
// --------------

#include <lem/path.h>
#include <lem/cfg_parser.h>

using namespace std;
using namespace lem;
using namespace lem::Cfg_Parser;



SectionEntry::SectionEntry(void)
{
 next=prev=sub=supr=NULL;
 level=0;
 return;
}

SectionEntry::SectionEntry(
                           const std::string &Name,
                           const pos_type& Loc,
                           int Lev
                          ) : name(Name), location(Loc)
    {
     next=prev=sub=supr=NULL;
     level=Lev;
     return;
    }

SectionEntry::SectionEntry( const SectionEntry &se )
    : name(se.name), location(se.location)
    {
     next=se.next;
     prev=se.prev;
     sub=se.sub;
     supr=se.supr;
     level=se.level;
     return;
    }


SectionEntry::~SectionEntry(void)
{
 del();
 if( supr )
  supr->sub = NULL;

 return;   
}


SectionEntry& SectionEntry::operator=( const SectionEntry& se )
    {
     if( this!=&se )
      {
       name=se.name;
       location=se.location;

       next = se.next;
       prev = se.prev;
       sub  = se.sub;
       supr= se.supr;
       level=se.level;
      }

     return *this;
    }

void SectionEntry::del(void)
{
 SectionEntry *e=sub;
 SectionEntry *tmp=NULL;

 while(e)
  {
   tmp=e->next;
   e->del();
   delete e;
   e=tmp;
  }

 sub=NULL;
 return;
}


// ***********************************************


SectionTree::SectionTree(void)
{
 first=new RootEntry(this);
 current=first;
}

SectionTree::~SectionTree(void)
{
 first->del();
 lem_rub_off(first);
 current=NULL;
}

bool SectionTree::Next(void)
    {
     if( current && current->next )
      {
       current=current->next;
       return true;
      }

     return false;
    }

    bool SectionTree::Prev(void)
    {
     if( current && current->prev )
      {
       current=current->prev;
       return true;
      }

     return false;
    }


    bool SectionTree::Up(void)
    {
     if( current && current->supr )
      {
       current=current->supr;
       return true;
      }

     return false;
    }

    bool SectionTree::Down(void)
    {
     if( current && current->sub )
      {
       current=current->sub;
       return true;
      }

     return false;
    }

    // ------------------------------------------------------------------
    // Перемещаемся в позицию, описываемую именем секции loc, от текущего
    // положения. Если адрес некорректен, вернем false. В случае успешной
    // операции вернем true.
    // ------------------------------------------------------------------
    bool SectionTree::Move_To( const string &loc )
    {
     if(loc==":")
      {
       // Перемещаемся в самое начало.
       To_Start();
       return !!current;
      }

     if(!current)
      return false;

     if(loc[0]=='.')
      {
       // Возвращаемся на специфицированное число
       // уровней назад.

       int i=0;
       while( loc[i] && loc[i++]=='.' )
        if(current->supr)
         current = current->supr;
        else
         return false;

       return true;
      }

     // считаем, что имя обозначает подстатью для текущего уровня.
     if(current->sub)
      {
       // У текущей статьи есть подстатьи.
       current = current->sub;

       // Пройдем по цепочке и поймаем требуемое имя.
       while( current && current->name!=loc )
        current=current->next;

       if(current)
        return true;
       else
        return false;
      }

     return true;
    }

    // *******************************
    // Дерево в исходное состояние.
    // *******************************
    void SectionTree::Clear(void)
    {
     if(first) first->del();
     first->sub=NULL;
     current=first;
     return;
    }

// ***********************************************


Ini_Parser::Ini_Parser(void):Text_Parser()
{
 bracket_level=0;
 status=0;

 SetFlag( SRC_STRIP_STRING, false );
 use_curled_brackets = false;

 return;
}


void Ini_Parser::Open( const lem::Path &filepath )
{
 lem::BinaryFile *ini_file = new lem::BinaryReader(filepath);
 lem::StreamPtr ini_file_x(ini_file);
 
 lem::Char_Stream::WideStream *reader=NULL;
 
 if( lem::UI::get_UI().GetSessionCp().IsSingleByte() )
  reader = new lem::Char_Stream::Char_Reader(ini_file_x);
 else
  reader = new lem::Char_Stream::UTF8_Reader(ini_file_x);

 lem::Char_Stream::WideStreamPtr reader_x( reader );

 Open( reader_x );
 return;
}


void Ini_Parser::Open( lem::Ptr<lem::Char_Stream::WideStream> txt )
{
 bracket_level=0;
 Text_Parser::Open(txt);
 beginning=tellp();
 status=0;
 
 ReadDirectory();
 stream = txt;

 return;
}

    /******************************************************************************
     Установка позиции чтения из файла в начало специфицированной секции.
     tosection - путь к секции.

     Путь определяется аналогично тому, как это делается в файловой системе.
     Имена вложенных секций перечисляются через '\\', текущая секция обозначается
     '.', корневая для текущей '..', и т.д. Для возврата на самый первый уровень
     используется символ ':'

     По умолчанию, если путь к секции не начинается с '.' или '..', курсор
     предварительно позиционируется на корневую секцию ':', так что пути
     ':\section1' и 'section1' приводят к одному результату.
    *****************************************************************************/
bool Ini_Parser::seek_section( const string& tosection )
    {
     bracket_level=0;
     string *list=NULL;
     int nstr=ParseSectionPath(tosection,&list);
     bool stat=false;

     if( nstr && (list[0]!="." && list[0]!="..") )
      // По умолчанию позиционируемся в корневую секцию.
      tree.To_Start();

     // Теперь начинаем путешествие по дереву подсекций.
     for( int i=0; i<nstr; i++ )
      {
       stat = tree.Move_To(list[i]);
       if(!stat)
        break;
      }

     if(nstr)
      lem_rub_off_array(list);

     if(stat)
      seekp( tree.current->location );

     return stat;
    }

    /*************************************************************************
     Находит и читает значение переменной с именем name в секции,
     специфицированной путем path. Если строка path пустая, то используется
     текущая секция.
     Значение def определяет возвращаемое значение, если прочитать значение
     затребованной переменной не удалось.
    *************************************************************************/
    int Ini_Parser::get_int(
                const string &path,
                const string &name,
                int def
               )
    {
     int res=def;

     SectionEntry *back=tree.current;

     if(path.length())
      if(!seek_section(path))
       {
        seekp(back->location);
        tree.current=back;
        return res;
       }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

     string val=NextFromSection();

     // Если это "-", то прочитаем число, идущее следом.
     if(val=="-")
      val += NextFromSection();

     seekp(back->location);
     tree.current=back;

     if(!lem::to_int(val.c_str(),&res))
      return def;

     return res;
    }

    bool Ini_Parser::get_bool(
                  const string &path,
                  const string &name,
                  bool def
                 )
    {
     bool res=def;

     SectionEntry *back=tree.current;

     if(!path.empty())
      if(!seek_section(path))
       {
        seekp(back->location);
        tree.current=back;
        return res;
       }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

     string val=NextFromSection();

     seekp(back->location);
     tree.current=back;

     if(!to_bool(val.c_str(),&res))
      return def;

     return res;
    }

    #if !defined LEM_NOREAL
    double Ini_Parser::get_real(
                                         const string &path,
                                         const string &name,
                                         double def
                                        )
    {
     double res=def;

     SectionEntry *back=tree.current;

     if(!path.empty())
      if(!seek_section(path))
       {
        seekp(back->location);
        tree.current=back;
        return res;
       }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

     string val=NextFromSection();

     // Если это "-", то прочитаем число, идущее следом.
     if(val=="-")
      val += NextFromSection();

     seekp(back->location);
     tree.current=back;

     if(!to_real(val.c_str(),&res))
      return def;

     return res;
    }
    #endif


    /*****************************************************************************
     Находит и загружает лексему или текстовую строку с именем name,
     находящуюся по адресу path. Если путь задан пустой строкой, то используется
     текущая секция.

     Если найти переменную не удалось, возвращается значение строки def.
    *****************************************************************************/
    const string Ini_Parser::get_string(
                                        const string &path,
                                        const string &name,
                                        const string &def
                                       )
    {
     string res=def;

     SectionEntry *back=tree.current;

     if(!path.empty())
      {
       if(!seek_section(path))
        {
         seekp(back->location);
         tree.current=back;
         return res;
        }
      }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

//     res=NextFromSection();

     FString s = Text_Parser::read_fstring();
     s.strip_quotes();
     res = s.c_str();

     seekp(back->location);
     tree.current=back;
     return res;
    }


    // ***************************************************************************
    // Перемещает указатель чтения в файле на позицию после имени переменной,
    // то есть после символа '=', если она найдена. В противном случае положение
    // указателя чтения в файле непредсказуемо.
    // ***************************************************************************
    bool Ini_Parser::seek_variable( const string& name )
    {
     string word = GetNextVar();

     while( !word.empty() && word!=name ) word=GetNextVar();

     if(word.empty())
      return false;

     return true;
    }

    // ***************************************************************************
    // Возвращает имя следующей переменной в текущей секции. Если секция
    // закончилась, возвращаем пустую строку.
    // ***************************************************************************
    const string Ini_Parser::GetNextVar(void)
    {
     // Ищем символ =.

     string first=NextFromSection();
     string second=NextFromSection();
     string var;

     while(!second.empty())
      {
       while( second!="=" && !second.empty() )
        {
         first=second;
         second=NextFromSection();
        }

       if(second.empty())
        {
         // Очередную переменную отыскать не удалось.
         return var;
        }

       // Теперь лексема first определяет (вероятно) имя
       // очередной переменной.
       if(is_correct_var_name(second))
        {
         var=first;
         break;
        }

       first=second;
       second=NextFromSection();
      }

     return var;
    }

    // ***************************************************************************
    // Определяем, может ли лексема var быть именем переменной.
    // ***************************************************************************
    bool Ini_Parser::is_correct_var_name( const string& var )
    {
     int l=var.length();

     for( int i=0; i<l; i++ )
      {
       if(!isalpha(var[i]))
        if(!strrchr( "_$@#", var[i] ))
         {
          // Имя переменной не может начинаться с цифры.
          if( !i && isdigit(var[i]) )
           return false;

          // В остальных позициях цифры используются свободно.
          if( i && !isdigit(var[i]) )
           return false;
         }
      }

     return true;
    }



// **************************************************
// Инициализируем дерево секций из текущего файла.
// **************************************************
void Ini_Parser::ReadDirectory(void)
{
 AToken word;

 section_type *inprocess=new section_type; // Текущая инициализируемая.
 bool del_inprocess=false;
 section_type *last=NULL;             // Пред. на одном уровне.
 section_type *supr=tree.first;      // Корневая для текущей.


 int CurLevel=0;                     // Текущий уровень вложенности.
 int subbrackets=0;                  // Число вложений фигурных скобочек,
                                     // не имеющих отношения к структуре
                                     // каталога.

 tree.Clear();
 tree.Set_First(inprocess);
 seekp(beginning);

 tree.current->location = tellp();

 FOREVER
  {
   word=read();

   if( word.string().empty() || eof() )
    break;

   if( word.string()=='[' )
    {
     // Определение новой секции.

     string secname=read().string().c_str();

     // Считываем имя секции.
     FOREVER
      {
       word=read();

       if( word.string()==']' || eof() || !word.string().length() )
        break;

       secname += string(" ")+word.string().c_str();
      }

     del_inprocess=false;
     inprocess->name     = secname;
     inprocess->location = tellp();
     inprocess->level    = CurLevel;
     inprocess->prev     = last;
     inprocess->supr     = supr;

     if(last)
      {
       // Предыдущая указывает на нашу.
       last->next = inprocess;
       last=inprocess; // Теперь мы будем предыдущей.
      }

     if(supr)
      if(!supr->sub)
       {
        // Корневая указывает на свою первую подсекцию.
        supr->sub=inprocess;
       }

     // За объявлением секции может идти открывающая скобочка - начало тела секции.
     word=read();

     if( use_curled_brackets && word.string()=='{' )
      {
       // Открывается новый подуровень.
       CurLevel++; // Глубже !!!

       // Текущая обрабатываемая секция становится
       // корневой.
       supr = inprocess;

       // Начинаем строить цепочку на этом подуровне.
       last=NULL; // Первый в цепочке.

       inprocess = new section_type;

       inprocess->level=CurLevel;
       inprocess->supr=supr;
       del_inprocess=false;
      }
     else if( use_curled_brackets && word.string()!='{' )
      {
       throw ECheckFault( to_wstr("Missing '{' after section head\n").c_str() );
      }
     else
      {
       // Тело секции начато без фигурной скобочки - тогда завершится
       // секция началом новой секции (токеном '[').
//       use_curled_brackets = false;

       last = inprocess;
       inprocess=new section_type;
       del_inprocess=true;

       while( !eof() && !word.string().empty() )
        {
         word = read();

         if( word.string() == '[' )
          {
           seekp( word.GetBegin() );
           break;
          }
        }
      }

     continue;
    }

   if( use_curled_brackets && word.string()=='{' )
    {
     // Фигурная скобочка открывает блок, не имеющий отношения к структуре
     // дерева. Пользовательская программа может сама поддерживать вложенность
     // для каждой под-статьи по своим правилам.
     subbrackets++;
     continue;
    }

   if( use_curled_brackets && word.string()=='}' )
    {
     if(subbrackets)
      {
       subbrackets--;
       continue;
      }

     // Текущий уровень завершен. Вернемся к формированию предыдущего уровня.

     // Корневая секция для завершенного уровня.
     section_type *s1 = inprocess->supr;

     CurLevel--; //s1->level;

     // Определим последнюю секцию, определенную
     // на нашем текущем уровне.
     last = s1;
     while(last->next) last=last->next;

     // Корневой для этого уровня известен.
     supr = s1->supr;

     inprocess->supr=supr;
     del_inprocess=false;

     continue;
    }
  } // end while

 if( del_inprocess )
  lem_rub_off(inprocess);

 tree.To_Start();
 return;
}


/*******************************************************************
 Сервисная процедура для обновления содержимого поля переменной в
 профайле. Умеет создавать секции и поля переменных, если указан
 адрес несуществующих. В ходе работы затрачиваются немалые ресурсы
 процессора - открывается временный файл, выделяются блоки памяти.
********************************************************************/
bool Ini_Parser::write_to_config(
                                 const char *section_name,
                                 const char *var_name,
                                 const char *new_value
                                )
{
 #if defined LEM_WINDOWS
 stream->close();
 return WritePrivateProfileStringA(
                                   section_name,
                                   var_name,
                                   new_value,
                                   GetName().GetAscii().c_str()
                                  )==TRUE;
 #else

 // ...

 #endif

/*
 // Сохраним имя профайла.
 const lem::Path filename=GetName();

 // Имя временного файла.
 const FString tmp_file_name = get_tmp_name();

 bool print_in_var_name     = false;
 bool print_in_section_name = false;

 if( !seek_section(section_name) )
  {
   // Даже секции с указанным именем не существует! Создадим её потом.
   print_in_section_name = true;
   print_in_var_name     = true;

   // Перемещаемся в конец файла, где и будем создавать новую секцию...
   SourceState back=tellp();

   while( !eof() )
    back=read(false).GetBegin();

   seekp(back);
  }
 else
  {
   // По крайней мере, такая секция есть.
   if( !seek_variable( var_name ) )
    {
     // Секция существует, но такой переменной в ней нет. Поэтому
     // выставим флаг необходимости впечатать имя переменной. Положение
     // курсора выставим принудительно - в начале тела секции.
     seek_section(section_name);
     print_in_var_name = true;
    }
  }

 // Теперь надо закрыть файл profile, открыть его для чтения, переписать
 // поле, закрыть файл для чтения и снова открыть как файл данных.
 const SourceState field_pos=tellp();

 int ne=0;
 if( !print_in_var_name )
  {
   // Подсчитаем, сколько полей до символа конца строки. Это поможет пропустить
   // значение переменной.
   while( !eof() )
    {
     char c = get();
     if( c==L'\n' || c==L'\r' )
      break;

     ne++;
    }
  }

 // Необходим закрыть поток для профайла, иначе ОС не даст нам открыть его
 // второй раз.
 close();

 BinaryFile bin_old( filename, true,  false );

 lem::Path tmp(tmp_file_name);
 BinaryFile bin_new( tmp, false, true );

 // Загружаем в буфер часть текста от начала профайла до точки: начало
 // поля значения переменной, или: начало тела секции, или: конец файла.
 char *buffer;
 const long s = field_pos.GetPos()+1;

 #if defined LEM_16
 // Ограничение на memory chunk because of 16-битовых смещений!
 if(s>=LEM_MAX_MEM_SIZE)
  LEM_STOPIT;
 #endif

 buffer = new char[(size_t)s];
 bin_old.read(  buffer, (size_t)field_pos.GetPos() );
 bin_new.write( buffer, (size_t)field_pos.GetPos() );
 delete[] buffer;
 buffer = NULL;

 // Нужно впечатать заголовок секции?
 if( print_in_section_name )
  {
   bin_new.write( "\r\n\r\n[", 5 );

   // Надо разобрать путь к секции на компоненты и извлечь последний
   // компонент - собственно имя секции.
   string *path=NULL;
   int nsec = ParseSectionPath( section_name, &path );
   bin_new.write( path->c_str(), path->length() );

   if( use_curled_brackets )
    bin_new.write( "]\r\n{\r\n", 6 );
   else
    bin_new.write( "]\r\n", 3 );

   delete[] path;
  }

 // Нужно ли впечатать имя переменной?
 if( print_in_var_name )
  {
   if( !print_in_section_name )
    bin_new.write( "\r\n", 2 );

   bin_new.write( " ", 1 );
   bin_new.write( var_name, lem_strlen(var_name) );
   bin_new.write( " = ", 3 );
  }

 // Здесь печатаем новое значение поля...
 bin_new.write( new_value, lem_strlen(new_value) );

 // Если создавалась новая переменная, то необходимо добавить перевод строки.
 if( print_in_var_name && !print_in_section_name )
  bin_new.write( "\r\n", 2 );

 // А если была создана новая секция, то следует правильно закрыть её тело.
 if( print_in_section_name )
  {
   if( use_curled_brackets )
    bin_new.write( "\r\n}\r\n", 5 );
   else
    bin_new.write( "\r\n\r\n", 4 );
  }

 // Теперь нужно добавить остаток старого профайла. Пропускаем значение
 // переменной, если таковая была...
 bin_old.seekp( field_pos.GetPos()+ne );
 while( !bin_old.eof() )
  {
   const int ch=bin_old.get();
   if( ch==EOF )
    break;

   bin_new.write( &ch, 1 );
  }

 // Теперь новое содержимое профайла находится во временном файле.
 // Содержимое файла bin_new переписываем в bin_old.
 bin_old.close();
 bin_new.close();

 lem::Path::Copy_File( lem::Path(tmp_file_name), filename );

 // Удаляем временный файл.
 lem::Path(tmp_file_name).Do_Remove();

 // Настраиваем профайл на новый файл с вписанными полями.
 BinaryFile fil( filename, true, false );
 lem::Char_Stream::WideStream *reader = lem::Char_Stream::WideStream::get_Suitable_Reader( lem::Ptr<Stream>(&fil,null_deleter()) );
 Text_Parser::Open( lem::Ptr<Char_Stream::WideStream>(reader) );
 ReadDirectory();

 // Всё успешно завершено.
 return true;
*/

 return true;
}


/****************************************************************************
 Читаем очередную лексему из текущей словарной статьи. Отслеживаем вложенные
 фигурные скобочки. Когда текущая словарная статья исчерпана, начинаем
 возвращать пустую строку. Если попадается заголовок секции, то пропускаем
 его и соотв. секцию тоже.
****************************************************************************/
const string Ini_Parser::NextFromSection(void)
{
 AToken word;

 if(bracket_level<0 )
  return word.string().c_str();

 word = read();

 if( !use_curled_brackets && word.string()=='[' )
  {
   // Начало новой секции - так как вложенные секции запрещены, то
   // значит найти следующую лексему в секции не удалось.
   seekp( word.GetBegin() );
   return "";
  }

 while(word.string()=='[')
  {
   // Ух ты! нарвались на вложенную секцию.
   // Ее надо обойти.
   while( word.string()!=']' && !eof() ) word=read();

   // Теперь читаем все, что в фигурных скобочках...

   word=read(); // Не дай Бог это не "{"...

   int brackets=1;

   if( word.string()!='{' )
    throw ECheckFault( to_wstr("Missing '{' after section head\n").c_str() );

   while( brackets && !eof() )
    {
     word=read();
     if(word.string()=='{')
      brackets++;
     else
      if(word.string()=='}')
       brackets--;
    }

   // Возможно, тут еще одна статья...
   word=read();
  } // end while

 if( word.string()=='{' )
  bracket_level++;

 if( word.string()=='}' )
  bracket_level--;

 if(bracket_level<0)
  word=AToken();


 if( word.string().front()=='"' )
  {
   seekp( word.GetBegin() );
   FString whole_str = read_fstring();
   whole_str.strip_quotes();
   return whole_str.c_str();
  }

 return word.string().c_str();
}

