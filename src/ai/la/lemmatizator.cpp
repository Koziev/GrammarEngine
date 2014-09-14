#include <lem/ucstring_functions.h>
#include <lem/stl.h>
#include <lem/solarix/Lemmatizator.h>
#include <lem/solarix/LemmatizatorFlags.h>


using namespace lem;
using namespace Solarix;

Lemmatizator::Lemmatizator(void)
{
 norm_ref=0;
 model_pos=0;
 n_lemma=0;
 char_size=sizeof(wchar_t);
 L_NHASHGROUP=-1;
 group_pos=NULL;
 lexemes_1=NULL;
 lexeme2lemma_1=NULL;
 fast_search1=false;
 model_available=false;
 model_loaded=false;
 model_suffix_len=0;
 return;
}

Lemmatizator::~Lemmatizator(void)
{
 delete[] group_pos;
 group_pos=NULL;

 delete[] lexemes_1;
 lexemes_1 = NULL;
 delete[] lexeme2lemma_1;
 lexeme2lemma_1 = NULL;

 return;
}


void Lemmatizator::Load( const lem::Path &DbPath, int Flags )
{
 fast_search1=false;

 #if defined LEM_WINDOWS
 if( (Flags&LEME_FASTER)==LEME_FASTER )
  {
   bin = new lem::FastFileReader(DbPath);
  }
 else
  {
   bin = new lem::BinaryReader(DbPath);
  }
 #else
 bin = new lem::BinaryReader(DbPath);
 #endif

 lem::Stream::pos_type table_pos=0;
 bin->read( &table_pos, sizeof(table_pos) );

 model_pos=0;
 bin->read( &model_pos, sizeof(model_pos) );

 min_sfx_len = bin->read_int();
 max_sfx_len = bin->read_int();
 suffices.LoadBin(*bin);

 // способ кодирования символов в справочнике базы. если этот параметр совпадает
 // с текущим размером wchar_t, то значит работаем без перекодирования.
 char_size = bin->read_int();
 L_NHASHGROUP = bin->read_int();

 delete[] group_pos;
 group_pos = new lem::Stream::pos_type[L_NHASHGROUP];

 delete[] lexemes_1;
 delete[] lexeme2lemma_1;
 lexemes_1 = new lem::MCollect<lem::CString>[L_NHASHGROUP];
 lexeme2lemma_1 = new lem::MCollect<int>[L_NHASHGROUP];


 const int nchars=bin->read_int();
 i2wchar.clear();
 wchar2i.clear();
 i2wchar.reserve(nchars);

 for( int i=0; i<nchars; ++i )
  {
   wchar_t c;
   bin->read( &c, sizeof(c) );
   i2wchar.push_back(c);
  }

 n_lemma = bin->read_int();
 norm_ref = bin->tellp();

 bin->seekp( table_pos );
 bin->read( group_pos, sizeof(*group_pos)*L_NHASHGROUP );

 if( (Flags&LEME_FASTEST)==LEME_FASTEST )
  {
   if( char_size==1 )
    fast_search1=true;
  }

 if( fast_search1 )
  {
   for( int i=0; i<nchars; ++i )
    {
     const wchar_t c = i2wchar[i];
     wchar2i.insert( std::make_pair(c,i) );
    }

   for( int g=0; g<L_NHASHGROUP; ++g )
    {
     lem::MCollect<lem::CString> & lexemes_1_H = lexemes_1[g];
     lem::MCollect<int> & lexeme2lemma_1_H = lexeme2lemma_1[g];

     const lem::Stream::pos_type pos = group_pos[g];

     // перемещается на начало группы в файле.
     bin->seekp(pos);

     // перебираем элементы группы
     const int n = bin->read_int();

     lem::uint8_t x8[3];
     lem::CString lexeme;

     for( int i=0; i<n; ++i )
      {
       LoadString1( &lexeme, *bin, 1 );

       int id_lemma=-1;
       lem::uint8_t n8 = bin->read_uint8();
       for( lem::uint8_t i8=0; i8<n8; ++i8 )
        {
         bin->read( x8, 3 );
         const int x32 = (0x00ff0000&(x8[0]<<16)) |
                         (0x0000ff00&(x8[1]<<8))  |
                         (0x000000ff&x8[2]);
         if( i8==0 )
          id_lemma=x32; 
        }

       lexemes_1_H.push_back(lexeme);
       lexeme2lemma_1_H.push_back(id_lemma);  
      }

     // отсортируем список лексем по алфавиту, синхронно с lexeme2lemma_1.
     int N=CastSizeToInt(lexemes_1_H.size());
     for( int gap=N/2; gap>0; gap/=2 )
      {
       for( int i=gap; i<N; i++ )
        for( int j=i-gap; j>=0; j-=gap )
         {
          if( lexemes_1_H[j+gap] > lexemes_1_H[j] )
           break;

          lem::CString dummy = lexemes_1_H[j];
          lexemes_1_H[j]       = lexemes_1_H[j+gap];
          lexemes_1_H[j+gap]   = dummy;

          int x2                  = lexeme2lemma_1_H[j];
          lexeme2lemma_1_H[j]     = lexeme2lemma_1_H[j+gap];
          lexeme2lemma_1_H[j+gap] = x2;
         }
      }
    }


   if( char_size==sizeof(wchar_t) )
    {
     LEM_STOPIT;
    }
   else if( char_size==1 )
    {
     bin->seekp( norm_ref );

     lemmas_1.resize(n_lemma);
     for( int i=0; i<n_lemma; ++i )
      {
       LoadString1(&lemmas_1[i],*bin,0);
      }
    }
   else
    {
     LEM_STOPIT;
    }
  }

 return;
}


void Lemmatizator::Lemmatize( const lem::UCString &word, lem::MCollect<lem::UCString> &lemmas )
{
 lem::UCString res(word);
 res.to_upper();

 bool rehash=false;
 for( int i=0; i<res.length(); ++i )
  if( res[i]==0x0401 )
   {
    res.set( i, 0x0415 );
    rehash=true;
   }

 if( rehash )
  res.calc_hash();

 // Определяем, в какой группе искать.
 const int igroup = (unsigned)res.GetHash16() & (L_NHASHGROUP-1);
 const lem::Stream::pos_type pos = group_pos[igroup];

 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs);
 #endif

 // перемещается на начало группы в файле.
 bin->seekp(pos);

 // перебираем элементы группы в поисках нашей формы.
 const int n = bin->read_int();

 lem::uint8_t x8[3];

 if( char_size==sizeof(wchar_t) )
  {
   lem::UCString form;
   lem::MCollect<int> inorm;

   for( int i=0; i<n; ++i )
    {
     inorm.clear();
     lem::Load_Packed( &form, *bin );

     lem::uint8_t n8 = bin->read_uint8();
     inorm.reserve(n8);
     for( lem::uint8_t i8=0; i8<n8; ++i8 )
      {
       bin->read( x8, 3 );
       const int x32 = (0x00ff0000&(x8[0]<<16)) |
                       (0x0000ff00&(x8[1]<<8))  |
                       (0x000000ff&x8[2]);
       inorm.push_back(x32);
      } 
   
     if( form==res )
      {
       // Нашли!!!
       for( lem::Container::size_type j=0; j<inorm.size(); ++j )
        {
         lemmas.push_back( GetLemma(inorm[j]) );
        }

       return;
      }
    }
  }
 else if( char_size==1 )
  {
   lem::UCString form;
   lem::MCollect<int> inorm;

   for( int i=0; i<n; ++i )
    {
     inorm.clear();
     LoadEncodedString( &form, *bin, 1 );

     lem::uint8_t n8 = bin->read_uint8();
     inorm.reserve(n8);
     for( lem::uint8_t i8=0; i8<n8; ++i8 )
      {
       bin->read( x8, 3 );
       const int x32 = (0x00ff0000&(x8[0]<<16)) |
                       (0x0000ff00&(x8[1]<<8))  |
                       (0x000000ff&x8[2]);
       inorm.push_back(x32);
      } 
   
     if( form==res )
      {
       // Нашли!!!
       for( lem::Container::size_type j=0; j<inorm.size(); ++j )
        {
         lemmas.push_back( GetLemma(inorm[j]) );
        }

       return;
      }
    }
  }
 else
  {
   LEM_STOPIT;
  }

 lemmas.clear();

 // Табличной подстановки не нашлось, проверяем замену суффикса.
 for( lem::Container::size_type i=0; i<suffices.size(); ++i )
  {
   if( res.eq_endi( suffices[i].first ) )
    {
     // Нашли замену суффикса!
     UCString lemma = lem::left( res, res.length()-suffices[i].first.length() );
     lemma += suffices[i].second;
     lemmas.push_back(lemma);
     return;
    }
  }


 // Лемматизация не выполнена, возвращаем исходное слово в качестве леммы.
 lemmas.push_back(res);
 return;
}


void Lemmatizator::DecodeWord1( const lem::CString & a, lem::UCString & u ) const
{
 for( int i=0; i<a.length(); ++i )
  u.ptr()[i] = i2wchar[ unsigned(a[i]) ];

 u.ptr()[ a.length() ] = 0;
 u.calc_hash();   
 
 return; 
}

void Lemmatizator::EncodeWord1( const lem::UCString & u, lem::CString & a ) const
{
 for( int i=0; i<u.length(); ++i )
  {
   std::map<wchar_t,int>::const_iterator it = wchar2i.find(u[i]);
   if( it==wchar2i.end() )
    a.ptr()[i] = (char)0xff;
   else
    a.ptr()[i] = it->second;
  }

 a.ptr()[ u.length() ] = 0;
 a.calc_hash();   
 
 return; 
}

int Lemmatizator::Lemmatize( const lem::UCString &word, lem::UCString &lemma )
{
 if( fast_search1 )
  {
   lem::UCString w(word);
   w.to_upper();

   int igroup = w.GetHash16()&(L_NHASHGROUP-1);

   lem::CString a;
   EncodeWord1( w, a );
   const int i = lem::find_bisection( lexemes_1[igroup], a );
 
   if( i==UNKNOWN )
    {
     // Табличной подстановки не нашлось, проверяем замену суффикса.
     for( lem::Container::size_type i=0; i<suffices.size(); ++i )
      {
       if( w.eq_endi( suffices[i].first ) )
        {
         // Нашли замену суффикса!
         lemma = lem::left( w, w.length()-suffices[i].first.length() );
         lemma += suffices[i].second;
         return 1;
        }
      }

     // Найти лемму ни одним из способов не получилось, возвращаем исходное слово.
     lemma = w;
     return 1;
    }
   else
    {
     const lem::CString &lemma8 = lemmas_1[ lexeme2lemma_1[igroup][i] ];
     DecodeWord1( lemma8, lemma );
     return 1;
    }
  }
 else
  {
   lem::MCollect<UCString> lemmas;
   Lemmatize(word,lemmas);
   if( !lemmas.empty() )
    lemma = lemmas.front();

   return CastSizeToInt(lemmas.size());
  }
}




void Lemmatizator::LoadEncodedString( UCString *str, lem::Stream &bin, int compression )
{
 switch( char_size )
 {
  case 1:
  {
   lem::uint8_t str8[ lem::CString::max_len+1 ];

   if( compression==0 )
    {
     bin.read( str8, lem::CString::max_len );
     str8[lem::CString::max_len]=0;

     int i=0;
     while( str8[i]!=0 )
      {
       str->ptr()[i] = i2wchar[str8[i]];
       ++i;
      }

     str->ptr()[i]=0;
    }
   else
    {
     lem::uint8_t len = bin.read_uint8();
     bin.read( str8, len );
     str8[len]=0;

     for( int i=0; i<len; ++i )
      {
       str->ptr()[i] = i2wchar[str8[i]];
      }

     str->ptr()[len]=0;
    }
   
   str->calc_hash();

   break;
  }

  default:
  {
   LEM_STOPIT;
  }
 }
}


void Lemmatizator::LoadString1( lem::CString *str, lem::Stream &bin, int compression )
{
 switch( char_size )
 {
  case 1:
  {
   if( compression==0 )
    {
     bin.read( str->ptr(), lem::CString::max_len );
     str->ptr()[lem::CString::max_len]=0;
    }
   else
    {
     lem::uint8_t len = bin.read_uint8();
     bin.read( str->ptr(), len );
     str->ptr()[len]=0;
    }
   
   str->calc_hash();

   break;
  }

  default:
  {
   LEM_STOPIT;
  }
 }
}


lem::UCString Lemmatizator::GetLemma( int idx )
{
 LEM_CHECKIT_Z( idx>=0 && idx<n_lemma );

 UCString s;

 if( char_size==sizeof(wchar_t) )
  {
   bin->seekp( norm_ref + sizeof(lem::UCString)*idx );
   bin->read( &s, sizeof(s) );
  }
 else if( char_size==1 )
  {
   bin->seekp( norm_ref + (lem::UCString::max_len)*idx );
   LoadEncodedString(&s,*bin,0);
  }
 else
  {
   // ... todo
   LEM_STOPIT;
  }

 return s;
}


void Lemmatizator::LoadModel()
{
 model_loaded = true;

 lem::uint32_t model_flags;
 bin->read( &model_flags, sizeof(model_flags) ); // поле пока не используется.

 model_suffix_len = bin->read_int();

 const int n_suffix = bin->read_int();
 for( int i=0; i<n_suffix; ++i )
  {
   lem::int32_t id;
   bin->read( &id, sizeof(id) );
   lem::UCString s;
   lem::Load_Packed( &s, *bin );
   s = lem::UCString(L'~')+s;
   suffix2id.insert( std::make_pair(s,id) );
   id2suffix.insert( std::make_pair(id,s) );
  }

 const int n_word = bin->read_int();
 for( int i=0; i<n_word; ++i )
  {
   lem::int32_t id;
   bin->read( &id, sizeof(id) );
   lem::UCString s;
   lem::Load_Packed( &s, *bin );
   suffix2id.insert( std::make_pair(s,id) );
   id2suffix.insert( std::make_pair(id,s) );
  }

 const int n_ngram2 = bin->read_int();
 for( int i=0; i<n_ngram2; ++i )
  {
   LEMM_Ngram2 n2;
   bin->read( &n2, sizeof(n2) );
   model_ngram2.push_back(n2);
  }

 const int n_ngram2_1 = bin->read_int();
 for( int i=0; i<n_ngram2_1; ++i )
  {
   LEMM_Ngram2 n2;
   bin->read( &n2, sizeof(n2) );
   model_ngram2_1.push_back(n2);
  }


 const int n_ngram3 = bin->read_int();
 for( int i=0; i<n_ngram3; ++i )
  {
   LEMM_Ngram3 n3;
   bin->read( &n3, sizeof(n3) );
   model_ngram3.push_back(n3);
  }

 const int n_ngram3_1 = bin->read_int();
 for( int i=0; i<n_ngram3_1; ++i )
  {
   LEMM_Ngram3 n3;
   bin->read( &n3, sizeof(n3) );
   model_ngram3_1.push_back(n3);
  }

 const int n_ngram3_2 = bin->read_int();
 for( int i=0; i<n_ngram3_2; ++i )
  {
   LEMM_Ngram3 n3;
   bin->read( &n3, sizeof(n3) );
   model_ngram3_2.push_back(n3);
  }

 const int n_ngram4 = bin->read_int();
 for( int i=0; i<n_ngram4; ++i )
  {
   LEMM_Ngram4 n4;
   bin->read( &n4, sizeof(n4) );
   model_ngram4.push_back(n4);
  }

 BuildIndex();

 return;
}



void Lemmatizator::BuildIndex()
{
 // ------------------ 2-ГРАММЫ

 // индекс для поиска диграмм по первому тегу
 for( lem::Container::size_type i=0; i<model_ngram2.size(); ++i )
  {
   const LEMM_Ngram2 & x = model_ngram2[i];
   const int tags0 = x.tags.first;

   std::map<int, lem::MCollect<const LEMM_Ngram2*>* >::iterator it = tag0_2_ngram2.find(tags0);
   if( it==tag0_2_ngram2.end() )
    {
     lem::MCollect<const LEMM_Ngram2*> * list = new lem::MCollect<const LEMM_Ngram2*>();
     list->push_back( &x );
     gc_2.push_back(list);
     tag0_2_ngram2.insert( std::make_pair( tags0, list ) );
    }
   else
    {
     it->second->push_back( &x );
    }
  }

 // индекс для поиска диграмм по второму тегу
 for( lem::Container::size_type i=0; i<model_ngram2_1.size(); ++i )
  {
   const LEMM_Ngram2 & x = model_ngram2_1[i];
   const int tags1 = x.tags.second;

   std::map<int, lem::MCollect<const LEMM_Ngram2*>* >::iterator it = tag1_2_ngram2.find(tags1);
   if( it==tag1_2_ngram2.end() )
    {
     lem::MCollect<const LEMM_Ngram2*> * list = new lem::MCollect<const LEMM_Ngram2*>();
     list->push_back( &x );
     gc_2.push_back(list);
     tag1_2_ngram2.insert( std::make_pair( tags1, list ) );
    }
   else
    {
     it->second->push_back( &x );
    }
  }

 // ТРИГРАММЫ - индекс для поиска 1,2->3

 for( lem::Container::size_type i=0; i<model_ngram3.size(); ++i )
  {
   const LEMM_Ngram3 & x = model_ngram3[i];
   const int tags0 = x.tags.first;
   const int tags1 = x.tags.second;

   std::pair<int,int> k2( tags0, tags1 );
   std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::iterator it = tag0_2_ngram3.find(k2);

   if( it==tag0_2_ngram3.end() )
    {
     lem::MCollect<const LEMM_Ngram3*> * list = new lem::MCollect<const LEMM_Ngram3*>();
     list->push_back( &x );
     gc_3.push_back(list);
     tag0_2_ngram3.insert( std::make_pair( k2, list ) );
    }
   else
    {
     it->second->push_back( &x );
    }
  }

 // индекс для поиска 0 -> 1 <- 2
 for( lem::Container::size_type i=0; i<model_ngram3_1.size(); ++i )
  {
   const LEMM_Ngram3 & x = model_ngram3_1[i];
   const int tags0 = x.tags.first;
   const int tags2 = x.tags.third;

   std::pair<int,int> k2( tags0, tags2 );
   std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::iterator it = tag1_2_ngram3.find(k2);

   if( it==tag1_2_ngram3.end() )
    {
     lem::MCollect<const LEMM_Ngram3*> * list = new lem::MCollect<const LEMM_Ngram3*>();
     list->push_back( &x );
     gc_3.push_back(list);
     tag1_2_ngram3.insert( std::make_pair( k2, list ) );
    }
   else
    {
     it->second->push_back( &x );
    }
  }

 // индекс для поиска триграмм 0 <- 1,2
 for( lem::Container::size_type i=0; i<model_ngram3_2.size(); ++i )
  {
   const LEMM_Ngram3 & x = model_ngram3_2[i];
   const int tags1 = x.tags.second;
   const int tags2 = x.tags.third;

   std::pair<int,int> k2( tags1, tags2 );
   std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::iterator it = tag2_2_ngram3.find(k2);

   if( it==tag2_2_ngram3.end() )
    {
     lem::MCollect<const LEMM_Ngram3*> * list = new lem::MCollect<const LEMM_Ngram3*>();
     list->push_back( &x );
     gc_3.push_back(list);
     tag2_2_ngram3.insert( std::make_pair( k2, list ) );
    }
   else
    {
     it->second->push_back( &x );
    }
  }


 // индекс для поиска тетраграмм 0,1,2->3

 for( lem::Container::size_type i=0; i<model_ngram4.size(); ++i )
  {
   const LEMM_Ngram4 & x = model_ngram4[i];
   const int tags0 = x.tags.first;
   const int tags1 = x.tags.second;
   const int tags2 = x.tags.third;

   lem::triple<int,int,int> k3( tags0, tags1, tags2 );
   std::map< lem::triple<int,int,int>, lem::MCollect<const LEMM_Ngram4*>* >::iterator it = tag0_2_ngram4.find(k3);

   if( it==tag0_2_ngram4.end() )
    {
     lem::MCollect<const LEMM_Ngram4*> * list = new lem::MCollect<const LEMM_Ngram4*>();
     list->push_back( &x );
     gc_4.push_back(list);
     tag0_2_ngram4.insert( std::make_pair( k3, list ) );
    }
   else
    {
     it->second->push_back( &x );
    }
  }

 return;
}


void Lemmatizator::Lemmatize( const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs);
 #endif

 if( !model_loaded )
  {
   bin->seekp( model_pos );
   model_loaded = true;
   model_available = bin->read_bool();
   if( model_available )
    {
     LoadModel();
    }
  }


 if( model_available )
  {
   LemmatizeViaModel( words, lemmas );
  }
 else
  {
   for( lem::Container::size_type i=0; i<words.size(); ++i )
    {
     lem::UCString lemma;
     Lemmatize( words[i], lemma );
     lemmas.push_back( lemma );
    }
  }

 return;
}



int Lemmatizator::MatchSuffix( const lem::UCString & suffix ) const
{
 LEM_CHECKIT_Z( !suffix.empty() );

 int id = -1;

 std::map<lem::UCString,int>::const_iterator it = suffix2id.find(suffix);
 if( it!=suffix2id.end() )
  id = it->second;

 return id;
}



lem::UCString Lemmatizator::GetSuffix( const lem::UCString & word ) const
{
 LEM_CHECKIT_Z( !word.empty() );

 lem::UCString uword(word);
 uword.to_lower();

 if( word.length()==7 && uword==L"~~end~~" )
  return word;
 else if( word.length()==9 && uword==L"~~begin~~" )
  return word;
 else if( word.length()<=model_suffix_len )
  return uword;
 else
  return lem::UCString(L'~')+lem::right( uword, model_suffix_len );
}




int Lemmatizator::GetTag( const lem::UCString & word ) const
{
 return MatchSuffix( GetSuffix(word) );
}


lem::UCString Lemmatizator::GetSuffixById( int id ) const
{
 LEM_CHECKIT_Z( id!=UNKNOWN );
 return id2suffix.find(id)->second;
}



void Lemmatizator::LemmatizeViaModel( const lem::MCollect<lem::UCString> & words, lem::MCollect<lem::UCString> &lemmas )
{
 // Для каждого слова получим списки альтернативных лемматизаций.
 lem::Collect< lem::MCollect<lem::UCString> > word2lemmas;
 word2lemmas.resize( words.size() );

 lem::MCollect<int> lemma_scores;
 lem::MCollect<int> lemma_order;

 for( lem::Container::size_type i=0; i<words.size(); ++i )
  {
   Lemmatize( words[i], word2lemmas[i] );

   for( lem::Container::size_type j=0; j<word2lemmas[i].size(); ++j )
    word2lemmas[i][j].to_lower();

   lemmas.push_back( word2lemmas[i][0] );
   lemma_scores.push_back(0);
   lemma_order.push_back(1);
  }


 const int last_word_index = CastSizeToInt(words.size())-1;

 const bool use_4grams=true;
 const bool use_3grams=true;
 const bool use_2grams=true;

 for( lem::Container::size_type iword = 0; iword < words.size(); ++iword )
  {
   lem::UCString lemma;
   int lemma_score = 0;
   bool lemma_created = false;

   if( !lemma_created && iword > 2 && use_4grams )
    {
     // ======================
     // ИСПОЛЬЗУЕМ ТЕТРАГРАММЫ
     // ======================

     const lem::UCString & word1 = words[iword-3];
     const int id_suffix1 = GetTag( word1 );

     const lem::UCString & word2 = words[iword-2];
     const int id_suffix2 = GetTag( word2 );

     const lem::UCString & word3 = words[iword-1];
     const int id_suffix3 = GetTag( word3 );

     lem::triple<int,int,int> k3( id_suffix1, id_suffix2, id_suffix3 );

     std::map< lem::triple<int,int,int>, lem::MCollect<const LEMM_Ngram4*>* >::const_iterator it = tag0_2_ngram4.find( k3 );
     if( it!=tag0_2_ngram4.end() )
      {
       const lem::MCollect<const LEMM_Ngram4*> & n4_list = * it->second;

       std::map<lem::UCString,int> sfx2score;

       int proj_count = word2lemmas[iword].size();
       for( int iproj = 0; iproj < proj_count; ++iproj )
        {
         const lem::UCString & entry_name = word2lemmas[iword][iproj];
         lem::UCString i_sfx = GetSuffix( entry_name );
         if( sfx2score.find( i_sfx )==sfx2score.end() )
          sfx2score.insert( std::make_pair( i_sfx, 0 ) );
        }

       for( lem::Container::size_type j=0; j<n4_list.size(); ++j )
        {
         const LEMM_Ngram4 & n4_probe = *n4_list[j];
         const int id_suffix4 = n4_probe.tags.fourth;
         const lem::UCString & suffix4 = GetSuffixById(id_suffix4);

         std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix4);
         if( it2!=sfx2score.end() )
          it2->second += n4_probe.freq;
        }

       // теперь надо выбрать самый достоверный вариант.
       int best_score = 0;

       lem::UCString prev_lemma;
       int prev_score = 0;

       // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
       for( lem::Container::size_type iproj = 0; iproj < word2lemmas[iword].size(); ++iproj )
        {
         const lem::UCString & ename = word2lemmas[iword][iproj];
         lem::UCString proj_suffix = GetSuffix( ename );
         std::map<lem::UCString,int>::const_iterator it3 = sfx2score.find(proj_suffix);
         if( it3!=sfx2score.end() )
          {
           const int new_score = it3->second;
           if( new_score > best_score )
            {
             prev_score = new_score;
             prev_lemma = ename;
            }
          }
        }

       // Если текущее слово лемматизировано с меньшей достоверностью, то меняем его.
       if( lemma_scores[iword] < prev_score )
        {
         lemma_scores[iword] = prev_score;
         lemmas[iword] = prev_lemma;
         lemma_order[iword] = 4;
        }
      }
    }



   if( !lemma_created && use_3grams )
    {
     // ======================
     // ИСПОЛЬЗУЕМ ТРИГРАММЫ
     // ======================

     // Если текущее слово имеет 1 вариант лемматизации, то можно использовать его для перепроверки предыдущего слова.

     if( iword>2 && word2lemmas[iword].size() == 1 && word2lemmas[iword - 1].size() == 1 && word2lemmas[iword - 2].size() > 1 && lemma_order[iword-2]<3 )
     {
      // переоцениваем слово в iword-2
      const lem::UCString & word1 = words[iword-1];
      const int id_suffix1 = GetTag( word1 );

      const lem::UCString & word2 = words[iword];
      const int id_suffix2 = GetTag( word2 );

      std::pair<int,int> k2( id_suffix1, id_suffix2 );

      std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::const_iterator it = tag2_2_ngram3.find( k2 );
      if( it!=tag2_2_ngram3.end() )
       {
        const lem::MCollect<const LEMM_Ngram3*> & n3_list = * it->second;

        std::map<lem::UCString,int> sfx2score;

        int proj_count = word2lemmas[iword-2].size();
        for( int iproj = 0; iproj < proj_count; ++iproj )
         {
          const lem::UCString & entry_name = word2lemmas[iword-2][iproj];
          lem::UCString i_sfx = GetSuffix( entry_name );
          if( sfx2score.find( i_sfx )==sfx2score.end() )
           sfx2score.insert( std::make_pair( i_sfx, 0 ) );
         }

        for( lem::Container::size_type j=0; j<n3_list.size(); ++j )
         {
          const LEMM_Ngram3 & n3_probe = *n3_list[j];
          const int id_suffix0 = n3_probe.tags.first;
          const lem::UCString & suffix0 = GetSuffixById(id_suffix0);

          std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix0);
          if( it2!=sfx2score.end() )
           it2->second += n3_probe.freq;
         }

        // теперь надо выбрать самый достоверный вариант.
        int best_score = 0;

        lem::UCString prev_lemma;
        int prev_score = 0;

        // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
        for( lem::Container::size_type iproj = 0; iproj < word2lemmas[iword].size(); ++iproj )
         {
          const lem::UCString & ename = word2lemmas[iword-2][iproj];
          lem::UCString proj_suffix = GetSuffix( ename );
          std::map<lem::UCString,int>::const_iterator it3 = sfx2score.find(proj_suffix);
          if( it3!=sfx2score.end() )
           {
            const int new_score = it3->second;
            if( new_score > best_score )
             {
              prev_score = new_score;
              prev_lemma = ename;
             }
           }
         }

        // Если текущее слово лемматизировано с меньшей достоверностью, то меняем его.
        if( lemma_scores[iword-2] < prev_score )
         {
          lemma_scores[iword-2] = prev_score;
          lemmas[iword-2] = prev_lemma;
          lemma_order[iword-2] = 3;
         }
       }
     }
     else if( iword>1 && word2lemmas[iword].size() == 1 && word2lemmas[iword - 1].size() > 1 && lemma_order[iword-1]<3 )
     {
      // переоцениваем слово в iword-1
      const lem::UCString & word0 = words[iword-2];
      const int id_suffix0 = GetTag( word0 );

      const lem::UCString & word2 = words[iword];
      const int id_suffix2 = GetTag( word2 );

      std::pair<int,int> k2( id_suffix0, id_suffix2 );

      std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::const_iterator it = tag1_2_ngram3.find( k2 );
      if( it!=tag1_2_ngram3.end() )
       {
        const lem::MCollect<const LEMM_Ngram3*> & n3_list = * it->second;

        std::map<lem::UCString,int> sfx2score;

        int proj_count = word2lemmas[iword-1].size();
        for( int iproj = 0; iproj < proj_count; ++iproj )
         {
          const lem::UCString & entry_name = word2lemmas[iword-1][iproj];
          lem::UCString i_sfx = GetSuffix( entry_name );
          if( sfx2score.find( i_sfx )==sfx2score.end() )
           sfx2score.insert( std::make_pair( i_sfx, 0 ) );
         }

        for( lem::Container::size_type j=0; j<n3_list.size(); ++j )
         {
          const LEMM_Ngram3 & n3_probe = *n3_list[j];
          const int id_suffix1 = n3_probe.tags.second;
          const lem::UCString & suffix1 = GetSuffixById(id_suffix1);

          std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix1);
          if( it2!=sfx2score.end() )
           it2->second += n3_probe.freq;
         }

        // теперь надо выбрать самый достоверный вариант.
        int best_score = 0;

        lem::UCString prev_lemma;
        int prev_score = 0;

        // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
        for( lem::Container::size_type iproj = 0; iproj < word2lemmas[iword].size(); ++iproj )
         {
          const lem::UCString & ename = word2lemmas[iword-2][iproj];
          lem::UCString proj_suffix = GetSuffix( ename );
          std::map<lem::UCString,int>::const_iterator it3 = sfx2score.find(proj_suffix);
          if( it3!=sfx2score.end() )
           {
            const int new_score = it3->second;
            if( new_score > best_score )
             {
              prev_score = new_score;
              prev_lemma = ename;
             }
           }
         }

        // Если текущее слово лемматизировано с меньшей достоверностью, то меняем его.
        if( lemma_scores[iword-1] < prev_score )
         {
          lemma_scores[iword-1] = prev_score;
          lemmas[iword-1] = prev_lemma;
          lemma_order[iword-1] = 3;
         }
       }
     }
     else if( word2lemmas[iword].size() > 1 )
     {
      std::map<lem::UCString,int> sfx2score;
      bool needs_resort=false;

      if( iword>1 )
       {
        // iword-2,iword-1 --> iword

        const lem::UCString & word1 = words[iword-2];
        const int id_suffix1 = GetTag( word1 );
      
        const lem::UCString & word2 = words[iword-1];
        const int id_suffix2 = GetTag( word2 );
      
        std::pair<int,int> k2( id_suffix1, id_suffix2 );
      
        std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::const_iterator it = tag0_2_ngram3.find( k2 );
        if( it!=tag0_2_ngram3.end() )
         {
          const lem::MCollect<const LEMM_Ngram3*> & n3_list = * it->second;
      
          needs_resort=true;
      
          int proj_count = word2lemmas[iword].size();
          for( int iproj = 0; iproj < proj_count; ++iproj )
           {
            const lem::UCString & entry_name = word2lemmas[iword][iproj];
            lem::UCString i_sfx = GetSuffix( entry_name );
            if( sfx2score.find( i_sfx )==sfx2score.end() )
             sfx2score.insert( std::make_pair( i_sfx, 0 ) );
           }
      
          for( lem::Container::size_type j=0; j<n3_list.size(); ++j )
           {
            const LEMM_Ngram3 & n3_probe = *n3_list[j];
            const int id_suffix3 = n3_probe.tags.third;
            const lem::UCString & suffix3 = GetSuffixById(id_suffix3);
      
            std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix3);
            if( it2!=sfx2score.end() )
             it2->second += n3_probe.freq;
           }
         }
       }


      if( iword>0 && iword<last_word_index )
       {
        // iword-1 --> iword <-- iword+1
    
        const lem::UCString & word0 = words[iword-1];
        const int id_suffix0 = GetTag( word0 );
    
        const lem::UCString & word2 = words[iword+1];
        const int id_suffix2 = GetTag( word2 );
    
        std::pair<int,int> k2( id_suffix0, id_suffix2 );
    
        std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::const_iterator it = tag1_2_ngram3.find( k2 );
        if( it!=tag1_2_ngram3.end() )
         {
          const lem::MCollect<const LEMM_Ngram3*> & n3_list = * it->second;
    
          needs_resort=true;
    
          int proj_count = word2lemmas[iword].size();
          for( int iproj = 0; iproj < proj_count; ++iproj )
           {
            const lem::UCString & entry_name = word2lemmas[iword][iproj];
            lem::UCString i_sfx = GetSuffix( entry_name );
            if( sfx2score.find( i_sfx )==sfx2score.end() )
             sfx2score.insert( std::make_pair( i_sfx, 0 ) );
           }
    
          for( lem::Container::size_type j=0; j<n3_list.size(); ++j )
           {
            const LEMM_Ngram3 & n3_probe = *n3_list[j];
            const int id_suffix1 = n3_probe.tags.second;
            const lem::UCString & suffix1 = GetSuffixById(id_suffix1);
    
            std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix1);
            if( it2!=sfx2score.end() )
             it2->second += n3_probe.freq;
           }
         }
       }

      if( iword<last_word_index-1 )
       {
        // iword <-- iword+1,iword+2

        const lem::UCString & word1 = words[iword+1];
        const int id_suffix1 = GetTag( word1 );

        const lem::UCString & word2 = words[iword+2];
        const int id_suffix2 = GetTag( word2 );
      
        std::pair<int,int> k2( id_suffix1, id_suffix2 );
      
        std::map< std::pair<int,int>, lem::MCollect<const LEMM_Ngram3*>* >::const_iterator it = tag2_2_ngram3.find( k2 );
        if( it!=tag2_2_ngram3.end() )
         {
          const lem::MCollect<const LEMM_Ngram3*> & n3_list = * it->second;
      
          needs_resort=true;
      
          int proj_count = word2lemmas[iword].size();
          for( int iproj = 0; iproj < proj_count; ++iproj )
           {
            const lem::UCString & entry_name = word2lemmas[iword][iproj];
            lem::UCString i_sfx = GetSuffix( entry_name );
            if( sfx2score.find( i_sfx )==sfx2score.end() )
             sfx2score.insert( std::make_pair( i_sfx, 0 ) );
           }
      
          for( lem::Container::size_type j=0; j<n3_list.size(); ++j )
           {
            const LEMM_Ngram3 & n3_probe = *n3_list[j];
            const int id_suffix0 = n3_probe.tags.first;
            const lem::UCString & suffix0 = GetSuffixById(id_suffix0);
      
            std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix0);
            if( it2!=sfx2score.end() )
             it2->second += n3_probe.freq;
           }
         }
       }


      if( needs_resort )
       {
        // теперь надо выбрать самый достоверный вариант.
        int best_score = 0;

        lem::UCString prev_lemma;
        int prev_score = 0;

        // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
        for( lem::Container::size_type iproj = 0; iproj < word2lemmas[iword].size(); ++iproj )
         {
          const lem::UCString & ename = word2lemmas[iword][iproj];
          lem::UCString proj_suffix = GetSuffix( ename );
          std::map<lem::UCString,int>::const_iterator it3 = sfx2score.find(proj_suffix);
          if( it3!=sfx2score.end() )
           {
            const int new_score = it3->second;
            if( new_score > best_score )
             {
              prev_score = new_score;
              prev_lemma = ename;
             }
           }
         }

        // Если текущее слово лемматизировано с меньшей достоверностью, то меняем его.
        if( lemma_scores[iword] < prev_score )
         {
          lemma_scores[iword] = prev_score;
          lemmas[iword] = prev_lemma;
          lemma_order[iword] = 3;
         }
       }
     }
   } // конец триграм


   if( !lemma_created && use_2grams )
   {
    // ======================
    // ИСПОЛЬЗУЕМ ДИГРАММЫ
    // ======================

    // Если текущее слово имеет 1 вариант лемматизации, то можно использовать его для перепроверки предыдущего слова.
    if( iword>0 && word2lemmas[iword].size()==1 && word2lemmas[iword-1].size()>1 && lemma_order[iword-1]<2 )
    {
     // ...... [лемматизируемое_слово]  [опорное_слово] .......

     const lem::UCString & word2 = words[iword]; // опорное слово
     const int id_suffix2 = GetTag( word2 );

     std::map<int, lem::MCollect<const LEMM_Ngram2*>* >::const_iterator it = tag1_2_ngram2.find( id_suffix2 );
     if( it!=tag1_2_ngram2.end() )
      {
       const lem::MCollect<const LEMM_Ngram2*> & n2_list = * it->second;

       std::map<lem::UCString,int> sfx2score;

       int proj_count = word2lemmas[iword - 1].size();
       for( int iproj = 0; iproj < proj_count; ++iproj )
        {
         const lem::UCString & entry_name = word2lemmas[iword-1][iproj]; // вариант лемматизации лемматизируемого слова
         lem::UCString i_sfx = GetSuffix( entry_name );
         if( sfx2score.find( i_sfx )==sfx2score.end() )
          sfx2score.insert( std::make_pair( i_sfx, 0 ) );
        }

       for( lem::Container::size_type j=0; j<n2_list.size(); ++j )
        {
         const LEMM_Ngram2 & n2_probe = *n2_list[j];
         const int id_suffix1 = n2_probe.tags.first;
         const lem::UCString & suffix1 = GetSuffixById(id_suffix1);

         std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix1);
         if( it2!=sfx2score.end() )
          it2->second += n2_probe.freq;
        }

       // теперь надо выбрать самый достоверный вариант.
       int best_score = 0;

       lem::UCString prev_lemma;
       int prev_score = 0;

       // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
       for( lem::Container::size_type iproj = 0; iproj < word2lemmas[iword - 1].size(); ++iproj )
        {
         const lem::UCString & ename = word2lemmas[iword - 1][iproj];
         lem::UCString proj_suffix = GetSuffix( ename );
         std::map<lem::UCString,int>::const_iterator it3 = sfx2score.find(proj_suffix);
         if( it3!=sfx2score.end() )
         {
          const int new_score = it3->second;
          if( new_score > best_score )
          {
           prev_score = new_score;
           prev_lemma = ename;
          }
         }
        }

       // Если предыдущее слово лемматизировано с меньшей достоверностью, то меняем его.
       if( lemma_scores[iword-1] < prev_score )
        {
         lemma_scores[iword-1] = prev_score;
         lemmas[iword-1] = prev_lemma;
         lemma_order[iword-1] = 2;
        }
      }
    }
    else if( word2lemmas[iword].size() > 1 && lemma_order[iword]<2 )
    {
     bool needs_resort=false;
     std::map<lem::UCString,int> sfx2score;

     if( iword>0 )
      {
       // ...... [опорное_слово]  [лемматизируемое_слово] .......
       const lem::UCString & word1 = words[iword-1];
       const int id_suffix1 = GetTag( word1 );
    
       std::map<int, lem::MCollect<const LEMM_Ngram2*>* >::const_iterator it = tag0_2_ngram2.find( id_suffix1 );
       if( it!=tag0_2_ngram2.end() )
        {
         needs_resort=true;
         const lem::MCollect<const LEMM_Ngram2*> & n2_list = * it->second;
   
         int proj_count = word2lemmas[iword].size();
         for( int iproj = 0; iproj < proj_count; ++iproj )
          {
           const lem::UCString & entry_name = word2lemmas[iword][iproj];
           lem::UCString i_sfx = GetSuffix( entry_name );
           if( sfx2score.find( i_sfx )==sfx2score.end() )
            sfx2score.insert( std::make_pair( i_sfx, 0 ) );
          }
    
         for( lem::Container::size_type j=0; j<n2_list.size(); ++j )
          {
           const LEMM_Ngram2 & n2_probe = *n2_list[j];
           const int id_suffix2 = n2_probe.tags.second;
           const lem::UCString & suffix2 = GetSuffixById(id_suffix2);
    
           std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix2);
           if( it2!=sfx2score.end() )
            it2->second += n2_probe.freq;
          }
        }
      }


     if( iword<last_word_index )
      {
       // iword <-- iword+1
       const lem::UCString & word2 = words[iword+1];
       const int id_suffix2 = GetTag( word2 );
    
       std::map<int, lem::MCollect<const LEMM_Ngram2*>* >::const_iterator it = tag1_2_ngram2.find( id_suffix2 );
       if( it!=tag1_2_ngram2.end() )
        {
         needs_resort=true;
         const lem::MCollect<const LEMM_Ngram2*> & n2_list = * it->second;
    
         int proj_count = word2lemmas[iword].size();
         for( int iproj = 0; iproj < proj_count; ++iproj )
          {
           const lem::UCString & entry_name = word2lemmas[iword][iproj];
           lem::UCString i_sfx = GetSuffix( entry_name );
           if( sfx2score.find( i_sfx )==sfx2score.end() )
            sfx2score.insert( std::make_pair( i_sfx, 0 ) );
          }
    
         for( lem::Container::size_type j=0; j<n2_list.size(); ++j )
          {
           const LEMM_Ngram2 & n2_probe = *n2_list[j];
           const int id_suffix1 = n2_probe.tags.first;
           const lem::UCString & suffix1 = GetSuffixById(id_suffix1);
    
           std::map<lem::UCString,int>::iterator it2 = sfx2score.find(suffix1);
           if( it2!=sfx2score.end() )
            it2->second += n2_probe.freq;
          }
        }
      }

     if( needs_resort )
      {
       // теперь надо выбрать самый достоверный вариант.
       int best_score = 0;

       lem::UCString prev_lemma;
       int prev_score = 0;

       // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
       for( lem::Container::size_type iproj = 0; iproj < word2lemmas[iword].size(); ++iproj )
        {
         const lem::UCString & ename = word2lemmas[iword][iproj];
         lem::UCString proj_suffix = GetSuffix( ename );
         std::map<lem::UCString,int>::const_iterator it3 = sfx2score.find(proj_suffix);
         if( it3!=sfx2score.end() )
          {
           const int new_score = it3->second;
           if( new_score > best_score )
            {
             prev_score = new_score;
             prev_lemma = ename;
            }
          }
        }

       // Если текущее слово лемматизировано с меньшей достоверностью, то меняем его.
       if( lemma_scores[iword] < prev_score )
        {
         lemma_scores[iword] = prev_score;
         lemmas[iword] = prev_lemma;
         lemma_order[iword] = 2;
        }
      }
    }
   }

  }

 return;
}


