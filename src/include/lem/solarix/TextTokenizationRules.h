#if !defined TextTokenizationRules__H
 #define TextTokenizationRules__H

#include <lem/ufstring.h>
#include <lem/noncopyable.h>
#include <lem/containers.h>
#include <lem/solarix/PrefixEntrySearcher.h>

namespace Solarix {

class Dictionary;
class SentenceTokenizer;

struct TextTokenizationItem
{
 lem::UCString word;
 int start_pos;
 int len;
};

struct TextTokenizationRules : lem::NonCopyable
{
 private:
  enum { Whitespace /*пробелы как разделители*/, Streaming /*текст без разрывов*/, External /*внешний модуль токенизации DLL/SO*/ };
  int segmentation_flag;

  static wchar_t DefaultSpaceChars[];

  lem::MCollect<wchar_t> spaces; // пробельные символы.
  lem::MCollect<wchar_t> delimiters; // символы-разделители.
  SentenceTokenizer * tokenizer;

  int SkipSpace( const lem::UFString & Text, int pos ) const;

  lem::Ptr<PrefixEntrySearcher> prefix_lookup;

/*
  #if defined LEM_THREADS
  lem::Process::RWU_Lock cs_unbreakable_begginnings, cs_not_unbreakable;
  #endif
  std::set<lem::UCString> not_unbreakable_begginnings, not_unbreakable;
*/

  friend class Dictionary;

 public:
  lem::MCollect<int> id_language; // список id языков, для группы которых предназначены эти правила.

 public:
  TextTokenizationRules( const lem::MCollect<int> & langs, SentenceTokenizer * _tokenizer );

  void AddSpaceCharacters( const wchar_t * whitespace );
  void AddDelimiterCharacters( const wchar_t * delimiters );

  int Extract(
              Solarix::Dictionary & dict,
              const lem::UFString & Text,
              int CurrentPosition,
              lem::MCollect<int> & WordLengths,
              bool * is_unbreakable_token
             );

  void ExtractNextWords(
                        Solarix::Dictionary & dict,
                        const lem::UFString & Text,
                        int CurrentPosition,
                        int NumberToExtract,
                        lem::MCollect<TextTokenizationItem> & extracted
                       ) const;

  inline bool IsWhitespace( wchar_t c ) const { return spaces.find(c)!=UNKNOWN; }

  inline bool IsStreamingSegmentation() const { return segmentation_flag==Streaming; }
  inline bool IsExternalSegmentation() const { return segmentation_flag==External; }

  const SentenceTokenizer& GetTokenizer() const { return *tokenizer; }

};

}

#endif
