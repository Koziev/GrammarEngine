#if defined SOL_LOADTXT && defined SOL_COMPILER

// -----------------------------------------------------------------------------
// File SG_CALIBRATOR.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс SG_calibrator - информация об относительной встречаемости словоформы в
// Лексиконе объектного языка. Информация из калибраторов используется для
// начальной настройки контейнера словоформ, в частности - для выставления
// частот у словарных статей.
// -----------------------------------------------------------------------------
//
// CD->03.05.1998
// LC->30.10.2011
// --------------

#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/SG_Calibrator.h>

using namespace lem;
using namespace Solarix;

SG_calibrator::SG_calibrator( const SG_calibrator &x )
 : freq_type(x.freq_type), word(x.word), id_class(x.id_class), coords(x.coords), freq(x.freq)
{}


void SG_calibrator::operator=( const SG_calibrator &x )
{
 freq_type = x.freq_type;
 word=x.word;
 id_class=x.id_class;
 coords = x.coords;
 freq = x.freq;
 return;
}


SG_calibrator::SG_calibrator( const lem::UCString & keyword, const SynGram &sg, const Sol_IO &io, Macro_Parser &txtfile )
{
 if( keyword.eqi( L"wordentry_freq" ) )
  freq_type = WordEntryFreq;
 else if( keyword.eqi( L"wordform_score" ) )
  freq_type = WordFormScore;
 else if( keyword.eqi( L"wordforms_score" ) )
  freq_type = WordFormsScore;

 id_class=UNKNOWN;
 freq=0;

 word = txtfile.read().string();
 word.strip(L'"');

 // если далее идет открывающая фигурная скобка, то значит конкретизируется словоформа (или несколько
 // словоформ).

 if( txtfile.probe(B_OFIGPAREN) )
  {
   while( !txtfile.eof() )
    {
     if( txtfile.pick().GetToken()==B_CFIGPAREN )
      {
       txtfile.read();
       break;
      }
     
     // для обычных: координата:состояние
     // для бистабильных: координата
     lem::Iridium::BethToken coord_name = txtfile.read();

     if( id_class==UNKNOWN )
      {
       const int id_class0 = sg.FindClass(coord_name);
       if( id_class0!=UNKNOWN )
        {
         id_class = id_class0;
         continue;
        }
      }

     bool AFFIRM=true;

     if( coord_name.GetToken()==B_NEGATIVE )
      {
       // Оператор отрицания перед определением координаты!
       AFFIRM=false;
       coord_name = txtfile.read();
      }

     const GramCoordAdr iglob_coord = sg.FindCoord(coord_name.string());

     if( !iglob_coord.IsDefined() )
      {
       sg.GetIO().merr().printf( "Unknown coordinate %us\n", coord_name.c_str() );
       lem::Iridium::Print_Error(coord_name,txtfile);
       throw lem::E_BaseException();
      }

     if( sg.coords()[iglob_coord.GetIndex()].IsBistable() )
      {
       // Имя состояния не может быть указано.
       coords.push_back(GramCoordPair(iglob_coord,AFFIRM));
      }
     else
      {
       // После двоеточия должно идти имя состояния для координаты.
       txtfile.read_it(B_COLON);

       // Имя состояния.
       BethToken state_name = txtfile.read();

       // Получим индекс состояния для определенной координаты.
       const int istate = sg.coords()[iglob_coord.GetIndex()]
                              .FindState(state_name.string());
       if( istate==UNKNOWN )
        {
         // Нет такого состояния для этого измерения.
         lem::Iridium::Print_Error(state_name,txtfile);
         sg.GetIO().merr().printf(
                                  "State [%vfE%us%vn] is not declared for coordinate [%vfE%us%vn]\n"
                                  , state_name.c_str(),coord_name.c_str()
                                 );
         throw E_ParserError();
        }

       coords.push_back( GramCoordEx(iglob_coord,istate,AFFIRM) );
      }
    }
  }

 txtfile.read_it( B_EQUAL );

 if( txtfile.probe( B_SUB ) )
  freq = -txtfile.read_int();
 else
  freq = txtfile.read_int();
 return;
}


bool SG_calibrator::MatchCoords( const CP_Array &form_coords ) const
{
 for( lem::Container::size_type i=0; i<coords.size(); ++i )
  if( form_coords.FindOnce( coords[i] )==UNKNOWN )
   return false;

 return true;
}



void SG_calibrator::SaveBin( lem::Stream &bin ) const
{
 bin.write_int(freq_type);
 bin.write( &word, sizeof(word) );
 bin.write_int(id_class);
 coords.SaveBin(bin);
 bin.write_int(freq);
 
 return;
}



void SG_calibrator::LoadBin( lem::Stream &bin )
{
 freq_type = bin.read_int();

 if( !bin.eof() )
  {
   bin.read( &word, sizeof(word) );
   id_class = bin.read_int();
   coords.LoadBin(bin);
   freq = bin.read_int();
  } 

 return;
}

#endif
