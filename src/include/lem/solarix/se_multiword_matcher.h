#if !defined Multiword_Matcher__H
 #define Multiword_Matcher__H

 #include <lem/noncopyable.h>
 #include <lem/containers.h>

 namespace Solarix
 {
  class Dictionary;
  class Text_Processor;
  class LD_Seeker;

  namespace Search_Engine
  {
   class Topic_Finder;
   class Fuzzy_Comparator;
   class MultiwordMatchResults;
   class Text;
   struct Lexer_Options;
   struct Search_Options;

   struct MultiwordMatcherNode
   {
    bool is_terminal;
    int id_ngram;
    lem::MCollect<int> id_topic;
    lem::UCString word;
 
    lem::MCollect<MultiwordMatcherNode*> leaf;
    std::map< lem::UCString, MultiwordMatcherNode* > word2leaf;

    MultiwordMatcherNode(void);
    ~MultiwordMatcherNode(void);

    void AddLeaf( const lem::UCString &w, MultiwordMatcherNode *n );

    bool Match( const Text &text, int i0, int icur, MultiwordMatchResults **results ) const;
   };


   class Word;
   struct Rec_NGram;
   struct Rec_Keyword;
   class Multiword_Matcher : lem::NonCopyable
   {
    private:
     MultiwordMatcherNode *root;

     Word* CreateWordMatcher(
                             const lem::UCString &word,
                             const Search_Options &flags,
                             Solarix::Dictionary &dict,
                             Fuzzy_Comparator &fuzzy_eq,
                             const Lexer_Options &lo
//                             #if !defined SOL_NO_AA
//                             , Solarix::Text_Processor &tpu
//                             #endif
                            ) const;

     void AddNGram(
                   MultiwordMatcherNode *parent_node,
                   int iword,
                   const Rec_NGram & ngram,
                   int id_topic,
                   Topic_Finder &topics_db,
                   const Search_Options &flags,
                   Solarix::Dictionary &dict,
                   Fuzzy_Comparator &fuzzy_eq,
                   const Lexer_Options &lo
//                   #if !defined SOL_NO_AA
//                   , Solarix::Text_Processor &tpu
//                   #endif
                  );

     void AddSingleKeyword(
                           MultiwordMatcherNode *parent_node,
                           const Rec_Keyword & kwd,
                           int id_topic,
                           Topic_Finder &topics_db,
                           const Search_Options &flags,
                           Solarix::Dictionary &dict,
                           Fuzzy_Comparator &fuzzy_eq,
                           const Lexer_Options &lo
//                           #if !defined SOL_NO_AA
//                           , Solarix::Text_Processor &tpu
//                           #endif
                          );

    public:
     Multiword_Matcher(
                       Topic_Finder &topics_db,
                       const Search_Options &flags,
                       Solarix::Dictionary &dict,
                       Fuzzy_Comparator &fuzzy_eq,
                       const Lexer_Options &lo
//                       #if !defined SOL_NO_AA
//                       , Solarix::Text_Processor &tpu
//                       #endif
                      );

     ~Multiword_Matcher(void);

     MultiwordMatchResults* Match(
                                  Solarix::Search_Engine::Text &text,
                                  int i0
                                 ) const;
   };

  }
 }
#endif
