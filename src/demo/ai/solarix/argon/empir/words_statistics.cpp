// -----------------------------------------------------------------------------
// File WORDS_STATISTICS.CPP
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project
// CHARS program
//
// Words processor - part of CHARS code.
// Специализированный модуль - накапливает и обрабатывает статистику для
// целых слов.
//
// Создает как простые текстовые файлы '*.dat' с описанием статистических
// результатов, пригодные для загрузки в программы визуализации, так и ряд
// КАЛИБРОВОЧНЫХ файлов '*.sol', которые транслируются модулем YGRES и
// содержат важную инфу по буквам, слогам, словам.
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->20.08.2009
// --------------

#include <lem/solarix/dictionary.h>
#include <lem/solarix/gg_autom.h>

#include "empir.h"


WordStatProcessor::WordStatProcessor(void)
{
 words_count=0;
 return;
}

// ******************************************************
// Обработка очередного слова ustr с частотой word_freq
// ******************************************************
void WordStatProcessor::Add(
                            const UCString &ustr,
                            lem::int64_t word_freq
                           )
{
 // Ведем подсчет только реально разных слов, а тот факт,
 // что каждое слово встречается в обработанных текстах word_freq
 // раз, игнорируем.
 words_count++;

 // Get the numerical estimations <p> for word.
 const GraphGram &gg = sol_id->GetGraphGram();

 Nfreq.push_back( word_freq );

 return;
}


void WordStatProcessor::Post_Process(void)
{
 mout->printf( "Postprocessing word statistics (%vfE%d%vn records): ", Nfreq.size() );
 mout->flush();

 tot_freq=0;
 for( lem::Container::size_type j=0; j<Nfreq.size(); j++ )
  tot_freq += Nfreq[j];


 mout->printf( "%vfAOK%vn\n" );

 return;
}


// *******************************************************
// Подготовка и сохранение результатов обработки.
// *******************************************************
void WordStatProcessor::Report( OFormatter &rep ) const
{
 mout->printf( "Writing the calibration tables for GG..." ); mout->flush();
 rep.printf(
            "\nStatistics for words\n"
            " Number of different words processed: %qd\n\n"
            , words_count
           );

 try
  {
   Report_Chars(rep);
   Report_Syllabs(rep);
   mout->printf( "%vfAOK%vn\n" );
  }
 catch(...)
  {
   mout->printf( "%vfCError%vn\n" );
  }

 return;
}


void WordStatProcessor::Report_Chars( OFormatter &rep ) const
{
 return;
}


void WordStatProcessor::Report_Syllabs( OFormatter &rep ) const
{
 return;
}

lem::Path WordStatProcessor::GetOutPath( const wchar_t *filename ) const
{
 LEM_CHECKIT_Z( filename!=NULL );
 lem::Path p(outdir);
 p.ConcateLeaf(filename);
 return p;
}
