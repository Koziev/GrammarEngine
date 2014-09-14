#if !defined(SOL_NO_NGRAMS)

// CD->09.11.2008
// LC->28.12.2010

#include <lem/solarix/NGramsCollectors.h>

using namespace std;
using namespace lem;
using namespace Solarix;


NGramsCollectors::NGramsCollectors( lem::Ptr<Solarix::Dictionary> _dict, lem::Ptr<LemmatizatorStorage> _lemm )
 : dict( _dict), lemm( _lemm )
{
 db = dict->GetNgrams()->GetStorage();
 return;
}


NGramsCollectors::~NGramsCollectors(void)
{
 return;
}

void NGramsCollectors::SetStorage( lem::Ptr<NGramsDBMS> _db )
{
 db = _db;
}

static bool probe( int flags, int mask )
{ return (flags&mask)==mask; }



void NGramsCollectors::BuildKnowledgeBase(
                                          Solarix::Search_Engine::File_Type_Detector& detector,
                                          const Solarix::Search_Engine::Scan_Options& scanning,
                                          const lem::Path &DocumentsFolder,
                                          const lem::Path &DestinationFolder,
                                          Solarix::Language language,
                                          bool echo 
                                         )
{
 lem::Collect<Solarix::NGramsCollectorFlags::Flags> flags_step;
 lem::BoolCollect lemmatize_step;

 switch(language)
 {
  case Solarix::Russian:
  {
   Solarix::NGramsCollectorFlags::Flags ngrams_flags=0;

   ngrams_flags = Solarix::NGramsCollectorFlags::Words;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw2Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);

   ngrams_flags=0;
   ngrams_flags = Solarix::NGramsCollectorFlags::Covalent2Grams;
   ngrams_flags |= Solarix::NGramsCollectorFlags::Noun_Noun;
   ngrams_flags |= Solarix::NGramsCollectorFlags::Adj_Noun | Solarix::NGramsCollectorFlags::Covalent2Grams;
   ngrams_flags |= Solarix::NGramsCollectorFlags::Noun_Verb | Solarix::NGramsCollectorFlags::Covalent2Grams;
   ngrams_flags |= Solarix::NGramsCollectorFlags::Adverb_Verb | Solarix::NGramsCollectorFlags::Covalent2Grams;
   ngrams_flags |= Solarix::NGramsCollectorFlags::Adverb_Adj | Solarix::NGramsCollectorFlags::Covalent2Grams;
   ngrams_flags |= Solarix::NGramsCollectorFlags::Prepos_Noun | Solarix::NGramsCollectorFlags::Covalent2Grams;
   ngrams_flags |= Solarix::NGramsCollectorFlags::Verb_Object | Solarix::NGramsCollectorFlags::Covalent2Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw3Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);

/*
   ngrams_flags = Solarix::NGramsCollectorFlags::Raw4Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);
  
   ngrams_flags = Solarix::NGramsCollectorFlags::Raw5Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);
*/
   break;
  }

  case Solarix::English:
  {
   Solarix::NGramsCollectorFlags::Flags ngrams_flags=0;

   ngrams_flags = Solarix::NGramsCollectorFlags::Words;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw2Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(false);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw2Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw3Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(false);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw3Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);
/*
   ngrams_flags = Solarix::NGramsCollectorFlags::Raw4Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(false);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw4Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw5Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(false);

   ngrams_flags = Solarix::NGramsCollectorFlags::Raw5Grams;
   flags_step.push_back(ngrams_flags);
   lemmatize_step.push_back(true);
*/
  }

  default:
   LEM_STOPIT;
 }

 for( lem::Container::size_type k=0; k<flags_step.size(); k++ )
  {
   const Solarix::NGramsCollectorFlags::Flags ngrams_flags=flags_step[k];
   const bool lemmatize = lemmatize_step[k]!=0;

   const bool cleanup_ngrams = true;

   ngrams.clear();
   Prepare( DestinationFolder, language, ngrams_flags, false, true, lemmatize, false, true, "", cleanup_ngrams );

   std::vector<lem::Path> files;

   if( DocumentsFolder.IsFolder() )
    DocumentsFolder.ListFiles( files, true );
   else
    files.push_back(DocumentsFolder);

   for( lem::Container::size_type i=0; i<files.size(); i++ )
    {
     const lem::Path &filename = files[i];

     try
      {
       lem::StreamPtr file( new BinaryReader(filename) );
  
       lem::Ptr<Solarix::Search_Engine::Base_File_Reader> reader = detector.FindReader(
                                                   scanning,
                                                   filename.GetUnicode(),
                                                   to_upper(filename.GetExtension()),
                                                   file 
                                                  );

       if( reader.NotNull() )
        {
         BeginDocument(echo);
           
         while( !reader->eof() )
          {
           Solarix::Search_Engine::Base_File_Lexem bl;

           // Retrive next lexem from stream
           reader->read(bl);
     
           bool process=false;

           // Do process this lexem?
           switch(language)
           { 
            case Solarix::All: process = true; break;

            case Solarix::Russian:
            // Only russian words (and numbers and punctuators) are allowed.
            process = bl.word.length() && (are_cyr_only(bl.word.c_str()) || is_int(bl.word.c_str()) || is_upunct(bl.word.front()));
            break;

           case Solarix::English:
            // Only english words are to be processed.
            process = bl.word.length() && (are_lat_only(bl.word.c_str()) || is_int(bl.word.c_str()) || is_upunct(bl.word.front()));
            break;

           case Solarix::French:
            process = bl.word.length() && (are_french_only(bl.word.c_str()) || is_int(bl.word.c_str()) || is_upunct(bl.word.front()));
            break;

           case Solarix::German:
            process = bl.word.length() && (are_german_only(bl.word.c_str()) || is_int(bl.word.c_str()) || is_upunct(bl.word.front()));
            break;

           case Solarix::Italian:
            process = bl.word.length() && (are_italian_only(bl.word.c_str()) || is_int(bl.word.c_str()) || is_upunct(bl.word.front()));
            break;

           case Solarix::Spanish:
            process = bl.word.length() && (are_spanish_only(bl.word.c_str()) || is_int(bl.word.c_str()) || is_upunct(bl.word.front()));
            break;
           }
            
           if( process )
            {
             if( bl.word==L'\'' || bl.word==L'"'  || bl.word.front()=='_' )
              continue;

             Process(bl.word);
            }        
          }

         EndDocument(echo);
        }
      }
     catch(...)
      {
      }
    }

   EndAll(echo);
  }

 return;
}



void NGramsCollectors::Prepare(
                               const lem::Path &_outdir,
                               Language _language,
                               NGramsCollectorFlags::Flags _flags,
                               bool do_erase_freq1,
                               bool do_segmentation,
                               bool do_lemmatization,
                               bool use_disk_cache,
                               bool upload_to_db,
                               const lem::FString &segment_n,
                               bool do_cleanup_database
                              )
{
 flags = _flags;
 language = _language;
 outdir = _outdir;
 erase_freq1 = do_erase_freq1;
 clean_database = do_cleanup_database;

 // Открываем БД
 if( !db->Connected() ) // если база уже открыта в предыдущем проходе сбора других N-грамм
  { 
   lem::Path ngrams_path( _outdir);
   ngrams_path.ConcateLeaf( L"NGRAMS" );
   db->Connect(ngrams_path);
  }

 db->BeginTx(); // открывается транзакция, она будет активна на протяжении обработки
               // всех документов!

 if( !db->TableExists( "NGRAM_SEGMENTS" ) )
  {
   db->CreateTable_Segments();
   db->CommitTx();
   db->BeginTx();
  }


 // Подключаем нужные модули сбора статистики

 ngrams.clear();

 if(
    probe(flags,NGramsCollectorFlags::Words) ||
    probe(flags,NGramsCollectorFlags::Raw2Grams) ||
    probe(flags,NGramsCollectorFlags::Raw3Grams) ||
    probe(flags,NGramsCollectorFlags::Raw4Grams) ||
    probe(flags,NGramsCollectorFlags::Raw5Grams)
   )
  {
   RawNGramsCollector *c = new RawNGramsCollector;

   c->accum_1grams=false;
   c->needs_NGRAM1=false;
   c->needs_NGRAM2=false;
   c->needs_NGRAM3=false;
   c->needs_NGRAM4=false;
   c->needs_NGRAM5=false;

   if( probe(flags,NGramsCollectorFlags::Words) )
    {
     c->accum_1grams=true;
     c->needs_NGRAM1=true;
    } 

   if( probe(flags,NGramsCollectorFlags::Raw2Grams) )
    {
     c->accum_2grams=true;
     c->needs_NGRAM2=true;
    }

   if( probe(flags,NGramsCollectorFlags::Raw3Grams) )
    {
     c->accum_3grams=true;
     c->needs_NGRAM3=true;
    }

   if( probe(flags,NGramsCollectorFlags::Raw4Grams) )
    {
     c->accum_4grams=true;
     c->needs_NGRAM4=true;
    }

   if( probe(flags,NGramsCollectorFlags::Raw5Grams) )
    {
     c->accum_5grams=true;
     c->needs_NGRAM5=true;
    }
 
   ngrams.push_back( c );
  }

 if( probe(flags,NGramsCollectorFlags::Covalent2Grams) )
  {
   if( probe(flags,Solarix::NGramsCollectorFlags::Noun_Noun) )
    ngrams.push_back( new CovalentNGramsCollector(Solarix::NGramsCollectorFlags::Noun_Noun) );

   if( probe(flags,Solarix::NGramsCollectorFlags::Adj_Noun) )
    ngrams.push_back( new CovalentNGramsCollector(Solarix::NGramsCollectorFlags::Adj_Noun) );

   if( probe(flags,Solarix::NGramsCollectorFlags::Noun_Verb) )
    ngrams.push_back( new CovalentNGramsCollector(Solarix::NGramsCollectorFlags::Noun_Verb) );

   if( probe(flags,Solarix::NGramsCollectorFlags::Adverb_Verb) )
    ngrams.push_back( new CovalentNGramsCollector(Solarix::NGramsCollectorFlags::Adverb_Verb) );

   if( probe(flags,Solarix::NGramsCollectorFlags::Adverb_Adj) )
    ngrams.push_back( new CovalentNGramsCollector(Solarix::NGramsCollectorFlags::Adverb_Adj) );

   if( probe(flags,Solarix::NGramsCollectorFlags::Prepos_Noun) )
    ngrams.push_back( new CovalentNGramsCollector(Solarix::NGramsCollectorFlags::Prepos_Noun) );

   if( probe(flags,Solarix::NGramsCollectorFlags::Verb_Object) )
    ngrams.push_back( new CovalentNGramsCollector(Solarix::NGramsCollectorFlags::Verb_Object) );

   LEM_CHECKIT_Z( !ngrams.empty() );
  }


 if( do_lemmatization )
  {
   if( lemm.IsNull() )
    {
     throw E_BaseException( L"Lemmatizer is required for N-gram processing" );
    }
  }

 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  {
   ngrams[i]->segmentation  = do_segmentation;
   ngrams[i]->lemmatization = do_lemmatization;
   ngrams[i]->db = db;
   ngrams[i]->lemm = lemm;
   ngrams[i]->segment_n = segment_n;
   ngrams[i]->use_disk_cache = use_disk_cache;
   ngrams[i]->upload_to_db = upload_to_db;
   ngrams[i]->clean_database = clean_database;
   ngrams[i]->Prepare( dict, outdir, language );
  }

 return;
}




void NGramsCollectors::SetFilter( NGramFilter *filter )
{
 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  ngrams[i]->SetFilter(filter->Clone());

 delete filter;

 return;
}



void NGramsCollectors::Process( const UCString &l )
{
 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  ngrams[i]->Process(l);

 return;
}


void NGramsCollectors::BeginDocument( bool echo )
{
 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  ngrams[i]->BeginDocument(echo);

 return;
}


void NGramsCollectors::EndDocument( bool echo )
{
 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  ngrams[i]->EndDocument(echo);

 db->CommitRetaining();

 return;
}


void NGramsCollectors::EndAll( bool echo )
{
 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  {
   ngrams[i]->EndAll(echo);

   if( erase_freq1 )
    ngrams[i]->EraseFreq1();

   ngrams[i]->ProcessFinalStat(echo);
  }

 // Завершение обработки всех документов - закрываем транзакцию.
 db->CommitTx();

 return;
}



void NGramsCollectors::Report(void)
{
 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  {
   ngrams[i]->Report();
  }

 return;
}


void NGramsCollectors::Merge( const lem::Path &folder, bool echo )
{
 for( lem::Container::size_type k=0; k<ngrams.size(); k++ ) 
  {
   lem::Path dbpath = folder;
   ngrams[k]->Merge( dbpath, echo );
  }

 return;
}


void NGramsCollectors::SetDocCacheCapacity( int n )
{
 for( lem::Container::size_type k=0; k<ngrams.size(); k++ ) 
  {
   ngrams[k]->SetDocCacheCapacity(n);
  }
 
 return;
}


void NGramsCollectors::SetNGramsCacheCapacity( int n )
{
 for( lem::Container::size_type k=0; k<ngrams.size(); k++ ) 
  {
   ngrams[k]->SetNGramsCacheCapacity(n);
  }

 return;
}


void NGramsCollectors::SetDBCache( int cache_size )
{
 db->SetDBCache(cache_size);
 return;
}


void NGramsCollectors::PrintNgrams( const FString &format, lem::Ptr<OFormatter> to )
{
 for( lem::Container::size_type k=0; k<ngrams.size(); k++ ) 
  {
   ngrams[k]->print_ngrams = true;
   ngrams[k]->print_format = format;
   ngrams[k]->print_file = to;
  }

 return;
}


void NGramsCollectors::StoreNGram( const UFString &a, const UFString &b, int freq )
{
 for( lem::Container::size_type k=0; k<ngrams.size(); k++ ) 
  {
   ngrams[k]->StoreNGram(a,b,freq);
  }

 return;
}

void NGramsCollectors::StoreNGram( const UFString &a, const UFString &b, const UFString &c, int freq )
{
 for( lem::Container::size_type k=0; k<ngrams.size(); k++ ) 
  {
   ngrams[k]->StoreNGram(a,b,c,freq);
  }

 return;
}

void NGramsCollectors::InternalFlush( bool echo )
{
 for( lem::Container::size_type k=0; k<ngrams.size(); k++ ) 
  {
   ngrams[k]->InternalFlush(echo);
  }

 return;
}

#endif
