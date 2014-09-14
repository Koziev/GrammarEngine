#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>

using namespace Solarix;


WordFormEnumerator_File1::WordFormEnumerator_File1( WordEntries_File * _entries, const lem::UCString &_word )
:entries(_entries), word(_word), icur_entry(-1), icur_form(-1), finished(false)
{
}


bool WordFormEnumerator_File1::Fetch(void)
{
 if( !finished )
  {
   if( icur_entry==-1 )
    {
     icur_entry=0;
     FetchEntry();
    }
   else
    {
     // работаем с текущей статьей, просматриваем остаток форм в ней.
     const SG_Entry &e = entries->GetWordEntry(icur_entry);
     
     for( lem::Container::size_type i=icur_form+1; i<e.forms().size(); ++i )
      {
       if( e.forms()[i].name()==word )
        {
         // нашли очередную подходящую форму в текущей статье
         icur_form = CastSizeToInt(i);
         return true;
        }
      }

     // в текущей статье больше нет подходящих форм, ищем следующую статью.
     FetchEntry();
    }
  }

 return !finished;
}


void WordFormEnumerator_File1::FetchEntry(void)
{
 if( !finished )
  {
   while( icur_entry<(CastSizeToInt(entries->entry.size())-1) )
    {
     icur_entry++;
     icur_form=UNKNOWN; 

     const SG_Entry &e = entries->GetWordEntry(icur_entry);
    
     if( e.GetMinLen()>word.length() || e.GetMaxLen()<word.length() )
      {
       // не подходит по длине.
       continue;
      }

     // в этой статье может быть такая форма?
     if( !e.GetRoot().empty() && !word.eq_begi(e.GetRoot()) )
      {
       // корень не подходит.
       continue;
      }

     // предварительные проверки прошли, теперь пройдемся по формам статьи до первого попадания.
     for( lem::Container::size_type i=0; i<e.forms().size(); ++i )
      {
       if( e.forms()[i].name()==word )
        {
         // нашли и статью и форму в ней.
         icur_form = CastSizeToInt(i);
         return; 
        } 
      }
    }

   finished=true;
  }

 return; 
}

int WordFormEnumerator_File1::GetEntryKey(void)
{
 LEM_CHECKIT_Z(!finished);
 LEM_CHECKIT_Z(icur_entry!=UNKNOWN);

 return entries->GetWordEntry(icur_entry).GetKey();
}


int WordFormEnumerator_File1::GetFormIndex(void)
{
 LEM_CHECKIT_Z(!finished);
 LEM_CHECKIT_Z(icur_form!=UNKNOWN);
 return icur_form;
}

float WordFormEnumerator_File1::GetValue(void)
{
 return 1.0F;
}

int WordFormEnumerator_File1::GetMatchedWordIndex(void)
{
 return 0;
}

