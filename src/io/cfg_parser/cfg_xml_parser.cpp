// -------------------------------------------------------------------------
// File CFG_XML_PARSER.CPP
//
// (c) by Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Работа с конфигурационными файлами в простом XML-формате.
// ------------------------------------------------------------------------
//
// CD->21.07.1995
// LC->13.08.2006
// --------------

#include <lem/cfg_parser.h>
#include <lem/cfg_parser.h>

using namespace std;
using namespace lem;
using namespace lem::Cfg_Parser;

Xml_Parser::Xml_Parser(void)
:Base_ProFile< SectionEntry< Xml_Entry<char,Text_Parser> > >()
{
 return;
}

// **************************************************
// Инициализируем дерево секций из текущего файла.
//
//  Общий вид дерева узлов:
//
//   <aaa>
//
//    <bbb>
//       ...
//    </bbb>
//
//   </aaa>
//
// **************************************************
void Xml_Parser::ReadDirectory(void)
{
 Read_Head();

 AToken word;
 section_type *inprocess=new section_type; // Текущая инициализируемая.
 section_type *last=NULL;                  // Пред. на одном уровне.
 section_type *supr=tree.first;           // Корневая для текущей.

 int CurLevel=0;                     // Текущий уровень вложенности.

 tree.Clear();
 tree.Set_First(inprocess);
 seekp(beginning);

 tree.current->location = tellp();

 FOREVER
  {
   word=read();

   if( word.string().empty() || eof() )
    break;

   if( word.string()=='<' )
    {
     // Определение новой секции.
     string secname=read().string().c_str();

     if( word.string()=='/' )
      {
       string end_node = read().string().c_str();

       if( end_node != inprocess->name )
        throw ECheckFault( to_wstr("Invalid XML file: mismatched nodes") );

       // Текущий уровень завершен. Вернемся к формированию предыдущего уровня.

       read_it( ">" );

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

       continue;
      }

     // Считываем имя секции.
     FOREVER
      {
       word=read();

       if( word.string()=='>' || eof() || !word.string().length() )
        break;

       secname += string(" ")+word.string().c_str();
      }

     inprocess->name     = secname;
     inprocess->location = tellp();
     inprocess->level    = CurLevel;
     inprocess->prev     = last;
     inprocess->supr    = supr;

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

     // Тело секции начато.

     last = inprocess;
     inprocess=new section_type;

     while( !eof() && !word.string().empty() )
      {
       word = read();

       if( word.string() == '<' )
        {
         seekp( word.GetBegin() );
         break;
        }
      }

     continue;
    }

  } // end while

 if(inprocess->name.empty())
  lem_rub_off(inprocess);

 tree.To_Start();
 return;
}



/****************************************************************************
 Читаем очередную лексему из текущей словарной статьи. Отслеживаем вложенные
 фигурные скобочки. Когда текущая словарная статья исчерпана, начинаем
 возвращать пустую строку. Если попадается заголовок секции, то пропускаем
 его и соотв. секцию тоже.
****************************************************************************/
const string Xml_Parser::NextFromSection(void)
{
 AToken word;

 if(bracket_level<0 )
  return word.string().c_str();

 word = read();

 if( word.string()=='<' )
  {
   // Начало новой секции - так как вложенные секции запрещены, то
   // значит найти следующую лексему в секции не удалось.
   seekp( word.GetBegin() );
   return "";
  }

 return word.string().c_str();
}

void Xml_Parser::Read_Head(void)
{
 // Загружаем первый стандартный тэг:
 // <?xml version="1.0"?>
 read_it( "<" );

 read_it( "?" );

 head_section.Read(*this);

 read_it( ">" );
 return;
}

// ---------------------- End Of File [CFG_XML_PARSER.CPP] ---------------------
