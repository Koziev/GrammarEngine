#if !defined SOL_THESAURUS_NOTES__H
 #define SOL_THESAURUS_NOTES__H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/syntax_analyzer_timeout.h>

namespace Solarix
{
 class ThesaurusNotesProcessor
 {
  private:
   Solarix::Dictionary* sol_id;

   lem::Ptr<SentenceTokenizer> tokenizer;
//   lem::Ptr<Solarix::Text_Processor> tpu;
   wchar_t segmentation_delimiter;

   lem::zbool syntax, cleanup, segmentation,
            lemmatization, pivot, detect_class;
   int tn_type;

   lem::UCString language;
   int id_lang;

   lem::MCollect<int> pivot_iclass;

   lem::MCollect<int> prepositions; // id классов для разных языков, определяющих предлоги
   int IsPreposition( int id_class ) const { return prepositions.find(id_class)!=UNKNOWN; }
   
   std::map< int /*id_language*/, int /*id_class*/ > adverb_for_language; // id классов наречия для разных языков
   int GetAdverbClassForLanguage( int id_language ) const;


   int NeutralLanguageId;
   int ieu;
   int uekey;

   int id_JAP_VERB, id_JAP_VERB_BASE, id_JAP_VB_PARTICIPLE;


  public:
   SyntaxAnalyzerTimeout timeout;

  public:
   ThesaurusNotesProcessor( Solarix::Dictionary *dict );

   void SetLanguage( const lem::UCString &language );
   void SetLanguage( int id );
   void SetScenario( const lem::UFString &scenario );
   void SetSegmentationDelimiter( wchar_t c );

   std::pair<bool/*processed*/,bool/*error*/> ProcessPhrase( int te_id );
 };

}
#endif
