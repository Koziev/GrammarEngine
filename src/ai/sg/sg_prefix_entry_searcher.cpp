#include <lem/WideStringUcs4.h>
#include <lem/Ucs4ToWideString.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/Charpos2EntryStorage.h>
#include <lem/solarix/Charpos2EntryEnumerator.h>
#include <lem/solarix/PrefixEntrySearcher.h>

using namespace lem;
using namespace Solarix;

PrefixEntrySearcher::PrefixEntrySearcher( Charpos2EntryStorage *_storage, int max_ies )
 : storage(_storage), max_ie_count(max_ies)
{
 return;
}


PrefixEntrySearcher::~PrefixEntrySearcher(void)
{
 delete storage;
 return;
}

void PrefixEntrySearcher::AddEntry( int ie, const SG_Entry &e )
{
 if( !e.IsTerminal() )
  return;

 std::set<lem::UCString> used_forms;
 for( lem::Container::size_type i=0; i<e.forms().size(); ++i )
  {
   const UCString &s = e.forms()[i].name();

/*
   if(
      s.front()==L'_' ||
      lem::is_udelim(s.front()) ||
      lem::is_udigit(s.front()) ||
      s.front()==L'~'
     )
    continue;
*/

   if( used_forms.find(s)!=used_forms.end() )
    continue;

   used_forms.insert( s );

   Add( s, ie );
  }

 return;
}


void PrefixEntrySearcher::Add( const UCString &str, int ie )
{
 lem::WideStringUcs4 enum4( str.c_str() );

 int pos=0;
 lem::uint32_t c;
 while( (c=enum4.Fetch())!=0 )
  {
   lem::uint32_t charpos = CharPos2Int( c, pos );
   
   std::map< lem::uint32_t, std::set<int>* >::iterator it = charpos2keys.find(charpos);
   if( it==charpos2keys.end() )
    {
     std::set<int> * ekeys = new std::set<int>;
     ekeys->insert(ie);
     keys.push_back(ekeys);
     charpos2keys.insert( std::make_pair( charpos, ekeys ) );
    }
   else
    {
     it->second->insert(ie);
    }

   pos++;
  }

 return;
}



void PrefixEntrySearcher::Commit(void)
{
 // Выгружаем созданные списки в БД

 storage->BeginTx();

 for( std::map< lem::uint32_t, std::set<int>* >::const_iterator it=charpos2keys.begin(); it!=charpos2keys.end(); ++it )
  {
   const lem::uint32_t charpos = it->first;
   const std::set<int> &ies = *it->second;

   const lem::uint32_t c = 0x00ffffffU & charpos;
   const int pos = (0xff000000U & charpos)>>24;

   storage->Store( c, pos, ies );
  } 

 storage->CommitTx();
 
 return;
}



void PrefixEntrySearcher::Search(
                                 const wchar_t *prefix,
                                 lem::MCollect<int> &ies
                                ) const
{
 LEM_CHECKIT_Z(prefix!=NULL);
 ies.clear();

 if( lem::lem_is_empty(prefix) )
  return;

 std::set<int> *ies1 = new std::set<int>;
 std::set<int> *ies2 = new std::set<int>;

 WideStringUcs4 ucs4( prefix );
 lem::uint32_t c;
 int pos=0;
 while( (c=ucs4.Fetch())!=0 )
  {
   if( pos==0 )
    {
     storage->Get( c, pos, *ies1 );
    }
   else
    {
     std::swap( ies1, ies2 );
     ies1->clear();
     storage->GetIntersected( c, pos, *ies2, *ies1 );
    }
 
   pos++;
  }

 if( max_ie_count!=lem::int_max && CastSizeToInt(ies1->size())>max_ie_count )
  {
   for( std::set<int>::const_iterator it=ies1->begin(); it!=ies1->end() && CastSizeToInt(ies.size())<=max_ie_count; ++it )
    ies.push_back( *it );
  }
 else
  {
   std::copy( ies1->begin(), ies1->end(), std::back_inserter(ies) );
  } 

 delete ies1;
 delete ies2;

 return;
}


void PrefixEntrySearcher::PreciseSearch(
                                        const wchar_t *prefix,
                                        Solarix::SynGram &sg,
                                        lem::MCollect<int> &ies
                                       ) const
{
 const UCString cprefix(prefix);
 const int plen = cprefix.length();

 lem::Ptr<WordEntryEnumerator> wenum( sg.GetEntries().ListEntries() );
 while( wenum->Fetch() )
  {
   const SG_Entry &e = wenum->GetItem();
   if( e.IsTerminal() )
    {
     if( e.GetMaxLen()>=plen )
      {
       if( !e.GetRoot().empty() )
        {
         if( e.GetRoot().front()!=*prefix )
          continue;

         if( !e.GetRoot().eq_begi(cprefix) && !cprefix.eq_beg(e.GetRoot()) )
          continue; 
        }
       
       bool matched=false; 
       for( lem::Container::size_type q=0; q<e.forms().size(); ++q )
        {
         const UCString &fname = e.forms()[q].name();
         if( fname.length()>=plen )
          {
           if( fname.eq_beg(cprefix) )
            {
             matched = true;
             break;
            }
          }
        }

       if( matched )
        {
         ies.push_back(e.GetKey());
         if( CastSizeToInt(ies.size())>=max_ie_count )
          break;
        } 
      } 
    }
  }

 return;
}


void PrefixEntrySearcher::Save_SQL( const lem::Path &filename, const SQL_Production &sql_version )
{
 lem::OFormatter out( filename );

 if( sql_version.type==SQL_Production::MsSql )
  {
   out.printf( "!! @echo Loading the prefix entry searcher ...\n" );
  }
 else if( sql_version.type==SQL_Production::Oracle )
  {
   out.printf( "HOST echo Loading the prefix entry searcher ...\n" );
  }

 if( !sql_version.noschema )
  {
   // Создаем таблицы
   if( sql_version.type==SQL_Production::Oracle )
    {
     out.printf(
                "SET AUTOCOMMIT OFF;\n\n"
                "drop table charpos2entry;\n"
                "create table charpos2entry( charpos number NOT NULL PRIMARY KEY, ies clob );\n"
                "\n"
               );
    }
   else if( sql_version.type==SQL_Production::MySql )
    {
     out.printf(
                "drop table if exists charpos2entry;\n"
                "create table charpos2entry( charpos integer NOT NULL PRIMARY KEY, ies longtext NOT NULL );\n"
                "\n" 
               ); 
    }
   else if( sql_version.type==SQL_Production::SQLite )
    {
     const int lexlen = lem::UCString::max_len;

     out.printf(
                "begin;\n"
                "drop table if exists charpos2entry;\n"
                "create table charpos2entry( charpos integer NOT NULL PRIMARY KEY, ies varchar(1000000) NOT NULL );\n"
                "commit;"
                "\n" 
               ); 
    }
   else if( sql_version.type==SQL_Production::FireBird )
    {
     out.printf(
                "drop table charpos2entry;\n"
                "commit;\n"
                "\n"
               );              

     out.printf(
                "create table charpos2entry( charpos integer NOT NULL PRIMARY KEY, ies BLOB SUB_TYPE 1 SEGMENT SIZE 64 NOT NULL );\n"
                "commit;\n"
                "\n"
               ); 
    }
   else if( sql_version.type==SQL_Production::MsSql )
    {
     out.printf(
                "BEGIN TRANSACTION\n"
                "IF EXISTS(SELECT TABLE_NAME FROM solarix.INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'charpos2entry') drop table charpos2entry;\n"
                "CREATE TABLE charpos2entry( charpos integer NOT NULL PRIMARY KEY, ies text NOT NULL );\n"
                "COMMIT\n"
                "GO\n"
                "\n"
               );
    }
  }


 out.printf( "%s\n", sql_version.BeginTx().c_str() );

 lem::Ptr<Charpos2EntryEnumerator> cenum( storage->Enumerate() );

 std::set<int> ies;

 lem::FString str_ies;
 str_ies.reserve(1000000);

 while( cenum->Fetch() )
  {
   const lem::uint32_t c = cenum->GetChar();
   const int pos = cenum->GetPos();
   ies.clear();
   storage->Get( c, pos, ies );

   const lem::uint32_t charpos = c | (pos<<24);

   str_ies.clear();

   int key0=-1;
   for( std::set<int>::const_iterator k=ies.begin(); k!=ies.end(); ++k )
    {
     const int keyi = *k;
     if( key0==-1 )
      {
       str_ies.Add_Dirty( lem::to_str(keyi).c_str() );
      }
     else
      {
       str_ies.Add_Dirty( ' ' );
       str_ies.Add_Dirty( lem::to_str(keyi-key0).c_str() );
      }

     key0 = keyi;
    }

   out.printf( "INSERT INTO charpos2entry(charpos,ies) VALUES (%ud,'%s');\n", charpos, str_ies.c_str() );
  }

 out.printf( "\n%s\n", sql_version.CommitTx().c_str() );

 if( sql_version.type==SQL_Production::MsSql )
  {
   out.printf( "!! @echo Prefix entry searcher has been loaded.\n" );
  }
 else if( sql_version.type==SQL_Production::Oracle )
  {
   out.printf( "HOST echo Prefix entry searcher has been loaded.\n" );
  }

 return;
}


void PrefixEntrySearcher::GetEntriesForCharPos( int ipos, lem::uint32_t ucs4, std::set<int> &result )
{
 storage->Get( ucs4, ipos, result );
 return;
}



int PrefixEntrySearcher::FindMaxPrefixLen( const wchar_t * text ) const
{
 std::set<int> *ies1 = new std::set<int>;
 std::set<int> *ies2 = new std::set<int>;

 Ucs4ToUCString prefix_assembler;

 WideStringUcs4 ucs4( text );
 lem::uint32_t c;
 int pos=0;
 while( (c=ucs4.Fetch())!=0 )
  {
   if( pos==0 )
    {
     storage->Get( c, pos, *ies1 );
    }
   else
    {
     std::swap( ies1, ies2 );
     ies1->clear();
     storage->GetIntersected( c, pos, *ies2, *ies1 );
    }
 
   if( ies1->empty() )
    break; // данный префикс уже негоден.

   prefix_assembler.Add(c);

   pos++;
  }

 delete ies1;
 delete ies2;

 return prefix_assembler.ToString().length(); 
}
