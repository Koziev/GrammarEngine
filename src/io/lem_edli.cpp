// -----------------------------------------------------------------------------
// File LEM_EDLI.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2002
//
// Content:
// Простенький текстовый строчный редактор - используется для организации более
// комфортного ввода данных с терминала, вместо стандартной системной процедуры.
// -----------------------------------------------------------------------------
//
// CD->17.05.96
// LC->19.04.02
// ------------

#include <conio.h>
#include <signal.h>

#include <lem_scan.h>
#include <lem_mstr.h>


using namespace lem;

// ***********************************************************************
// Если psw=true, то вводимые символы заменяются на экране символом '*'.
// Это обычно используется при вводе паролей.
// ***********************************************************************
const FString lem::edline( const char *question, const bool psw )
{
 int pos=0;
 mout.printf( "%s", question );

 FString buffer;

 #if defined LEM_WATCOM

 bool cont=true;

 while(cont)
  {
   char ch=getch();

   switch(ch)
    {
     case '\r':
      // Вернем текущую строку.
      cont=false;
      break;

     #if !defined LEM_BORLAND_3_1
     case 3: // Ctrl-C
       raise(SIGBREAK);
       buffer="";
       cont=false;
       break;
     #endif

     case 27:
      {
       // Нажата 'ESC' - очистим буфер и вернем пустую строку.
       buffer="";
       cont=false;
       break;
      }

     case '\b':
      {
       // '<-'
       if( buffer.len() )
        {
         pos--;
         buffer.remove(pos);

         mout.printf( "'\b'" );
        }

       break;
      }

     case 0:
       getch();
       break;

     default:
       {
        buffer.set(pos,ch);

         if( psw )
          mout.printf( "*" );
         else
          mout.printf( "%c", ch );

        break;
       }
    }
  }

 #elif defined LEM_SYMANTEC || defined LEM_DJGPP

  // Ввод паролей не реализован.
  LEM_CHECKIT_Z( psw=false );

  char *b = new char[128];
  lem_check_ptr(b);
  gets( b );
  buffer=b;
  delete b;

 #else

 bool cont=true;
 bool insert=true;

 int x0=wherex(), y0=wherey();

 while(cont)
  {
   int x=wherex(), y=wherey();
   char ch=getch();

   switch(ch)
    {
     case '\r':
      // Вернем текущую строку.
      cont=false;
      mout.eol();
      break;

     #if !defined LEM_BORLAND_3_1
     case 3: // Ctrl-C
       raise(SIGBREAK);
       buffer="";
       cont=false;
       break;
     #endif

     case 27:
      {
       // Нажата 'ESC' - очистим буфер и вернем пустую строку.
       buffer="";
       cont=false;
       mout.eol();
       break;
      }

     case '\b':
      {
       // '<-'

       if( pos>0 )
        {
         pos--;
         buffer.remove(pos);
         gotoxy(x0,y0);

         if( !psw )
          mout.printf( "%lS ", buffer );
         else
          mout.printf( "%H* ", buffer.len() );

         gotoxy(x-1,y);
        }

       break;
      }

     case 0:
      {
       ch=getch();

       switch(ch)
        {
         case 'K':
          if(pos>0)
           {
            pos--;
            gotoxy(x-1,y);
           }
          break;

         case 'M':
          if(pos<buffer.len())
           {
            pos++;
            gotoxy(x+1,y);
           }
          break;

         case 'R':
          #if !defined LEM_WINDOWS
          if( insert=!insert )
           _setcursortype(_NORMALCURSOR);
          else
           _setcursortype(_SOLIDCURSOR);
          break;
          #endif

         case 'S':
          buffer.remove(pos);
          gotoxy(x0,y0);

          if( !psw )
           mout.printf( "%lS ", buffer );
          else
           mout.printf( "%H* ", buffer.len() );

          gotoxy(x,y);
          break;
        }

       break;
      }

     default:
      if( insert )
       {
        // Режим вставки символов
        buffer.insert(pos,ch);
        gotoxy(x0,y0);

         if( !psw )
          mout.printf( "%lS ", buffer );
         else
          mout.printf( "%H* ", buffer.len() );

        gotoxy(x+1,y);
        pos++;
       }
      else
       {
        // Режим 'overwrite'
        buffer.set(pos,ch);
        gotoxy(x0,y0);

         if( !psw )
          mout.printf( "%lS ", buffer );
         else
          mout.printf( "%H* ", buffer.len() );

        gotoxy(x,y);
       }
    }
  }
 #endif

 return buffer;
}

// -------------------------- End Of File [LEM_EDLI.CPP] -----------------------
