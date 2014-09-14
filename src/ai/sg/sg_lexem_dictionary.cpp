// -----------------------------------------------------------------------------
// File SG_LEXEM_DICTIONARY.CPP
//
// (c) by Elijah Koziev
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// Класс LexemDictionary - справочник лексем для Словаря.
// -----------------------------------------------------------------------------
//
// CD->06.08.2005
// LC->24.11.2010
// --------------

#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/LexemDictionary.h>

using namespace std;
using namespace lem;
using namespace Solarix;


LexemDictionary::LexemDictionary( int Reserve ):SolidRef<Lexem>(Reserve)
{}

LexemDictionary::~LexemDictionary(void)
{}


LD_Seeker* LexemDictionary::Get_Seeker( SynGram &sg, LexicalAutomat *la )
{
 return new LD_Seeker(this,la,sg);
}


#if defined SOL_LOADBIN
LD_Seeker* LexemDictionary::Load_Seeker( lem::Stream &bin, LexicalAutomat *La )
{
 LD_Seeker * seeker = new LD_Seeker( this, La );
 seeker->LoadBin(bin);
 return seeker;
}
#endif

#if defined SOL_SAVEBIN
// *******************************************************************
// Сохранение словаря лексем в бинарном потоке - с реализацией
// сжатия. Это сжатие эффективно для всех языков, использующих
// флексии - когда многочисленные словоформы образуются изменением
// флексий (в конце слов). Таким образом, в этом словаре образуются
// многочисленные ПОСЛЕДОВАТЕЛЬНЫЕ записи типа РЫБА-РЫБЫ-РЫБОЙ-...
// *******************************************************************
void LexemDictionary::SaveBin( lem::Stream &bin ) const
{
 const Lexem *first = &*list.begin();
 bin.write( &first, sizeof(first) );

 int n=list.size();
 bin.write( &n, sizeof(n) );

 for( Container::size_type i=0; i<list.size(); i++ )
  {
   const Lexem& l = list[i];

   uint8_t packed=0, pack_flags=0;

   // Проверим, можно ли сжимать текущую мультилексему.

   if(
      i &&                  // Это не должна быть самая первая мультилексема
                            // - надо ведь с чем-то ее сравнивать.

      l.Can_Be_Packed( list[i-1], &pack_flags ) // должна быть
                                         // выгода от сжатия - если у лексем
                                         // нет общей части, то сжимать
                                         // бессмысленно.
     )
    packed = pack_flags;

   bin.write( &packed, sizeof(packed) );

   if( packed )
    {
     // Сохраняем со сжатием
     l.SaveBin_Packed( bin, list[i-1], pack_flags );
    }
   else
    {
     // Сохраняем без сжатия
     l.SaveBin(bin);
    }
  }

 // Для контроля целостности словаря
 lem::Stream::pos_type pos = bin.tellp();
 bin.write( &pos, sizeof(pos) );

 return;
}
#endif


#if defined SOL_LOADBIN
void LexemDictionary::LoadBin( lem::Stream &bin )
{
 bin.read( &old_first_item, sizeof(old_first_item) );

 lem::Stream::pos_type beg_is = bin.tellp();

 int n=0;
 bin.read( &n, sizeof(n) );

 const int cap = CastSizeToInt(list.capacity());
 list.clear();

 #if defined SOL_LOADTXT && defined SOL_COMPILER
 Lexem prior;

 for( int i=0; i<n; i++ )
  {
   Lexem add;

   uint8_t pack_flags;
   bin.read( &pack_flags, sizeof(pack_flags) );
   if( !pack_flags )
    add.LoadBin(bin);
   else
    add.LoadBin_Packed( bin, prior, pack_flags );

   const int iSublist = unsigned( get_hash(add) ) & 0x00ffU;
   MCollect<int> &sl = sublist[iSublist];
   sl.push_back( CastSizeToInt(list.size()) );

   list.push_back(add);
   prior = add;
  }
 #else

 list.resize(n);

 if( cap>n )
  list.reserve( cap );

 #if LEM_DEBUGGING==1
 const int cap2 = CastSizeToInt(list.capacity());
 #endif

 const Lexem * prior = NULL;

 for( int i=0; i<n; i++ )
  {
   Lexem & add = list[i];

   uint8_t pack_flags;
   bin.read( &pack_flags, sizeof(pack_flags) );
   if( !pack_flags )
    add.LoadBin(bin);
   else
    add.LoadBin_Packed( bin, *prior, pack_flags );

   prior = &add;
  }

 #endif

 lem::Stream::pos_type pos_is = bin.tellp();

 lem::Stream::pos_type pos;
 bin.read( &pos, sizeof(pos) );

 LEM_CHECKIT_Z( pos==pos_is );

 return;
}
#endif
