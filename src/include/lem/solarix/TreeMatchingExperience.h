#if !defined TreeMatchingExperience__H
 #define TreeMatchingExperience__H

 #include <set>
 #include <lem/ucstring.h>
 #include <lem/ptr_container.h>
 #include <lem/solarix/SynPatternResult.h>
 #include <lem/solarix/KB_CheckingResult.h>

 namespace Solarix
 {
  class Word_Form;

  struct TreeMatchingExperienceKey
  {
   int id_tree;
   const LexerTextPos * token;

   TreeMatchingExperienceKey(void) : token(NULL) {}
   TreeMatchingExperienceKey( int _id_tree, const LexerTextPos * _token ):id_tree(_id_tree), token(_token) {} 

   inline bool operator==( const TreeMatchingExperienceKey & x ) const
   { return token==x.token && id_tree == x.id_tree; }

   inline bool operator>( const TreeMatchingExperienceKey & x ) const
   { return token > x.token || (token==x.token && id_tree > x.id_tree ); }

   inline bool operator<( const TreeMatchingExperienceKey & x ) const
   { return token < x.token || (token==x.token && id_tree < x.id_tree ); }
  };


  struct TreeMatchingExperienceItem : lem::NonCopyable
  {
   lem::PtrCollect<SynPatternResult> results;
   bool success;

   TreeMatchingExperienceItem( bool src_success, const lem::PtrCollect<SynPatternResult> &src );

   void Add( const SynPatternResult & ext );

   void Copy( const BackTrace *parent_trace, lem::PtrCollect<SynPatternResult> & ext ) const;
  };

  struct TME_KBChecker : lem::NonCopyable
  {
   lem::MCollect< const Solarix::Word_Form * > arg_values;
   KB_CheckingResult res;

   TME_KBChecker( const lem::MCollect< const Solarix::Word_Form * > & _arg_values, const KB_CheckingResult & _res )
   : arg_values(_arg_values), res(_res) {}
  };


  class TreeMatchingExperience : lem::NonCopyable
  {
   private:
    typedef std::map< TreeMatchingExperienceKey, TreeMatchingExperienceItem* > KEY2ITEM;
    KEY2ITEM key2item;

    typedef std::multimap< std::pair<int,const Solarix::Word_Form*>, TME_KBChecker* > KBID2ITEM;
    KBID2ITEM kbid2item;

    std::set< std::pair<const LexerTextPos*,int> > token_accel_success, token_accel_mismatch;

    typedef std::map< const LexerTextPos*, TreeMatchingExperienceItem* > FRAGMENT2ITEM;
    FRAGMENT2ITEM fragment2item;

   public:
    TreeMatchingExperience(void) {}
    ~TreeMatchingExperience(void);

    const TreeMatchingExperienceItem* Find( int id_tree, const LexerTextPos * token ) const
    {
     LEM_CHECKIT_Z( id_tree!=UNKNOWN );
     KEY2ITEM::const_iterator it = key2item.find( TreeMatchingExperienceKey(id_tree,token) );
     if( it==key2item.end() )
      return NULL;
     else
      return it->second;
    }

    void ClearPatternMatchings();
    void Clear();

    void Add( int id_tree, const LexerTextPos * token, bool success, const lem::PtrCollect<SynPatternResult> &results );

    void Update( int id_tree, const LexerTextPos * token, bool success, const SynPatternResult & result );

    bool FindKBCheckerMatching( int id_facts, const lem::MCollect< const Solarix::Word_Form * > & arg_values, KB_CheckingResult * res ) const;
    void AddKBCheckerMatching( int id_facts, const lem::MCollect< const Solarix::Word_Form * > & arg_values, const KB_CheckingResult & res );

    int FindAccelerator( const LexerTextPos * token, int id_accel ) const;
    void StoreAccelerator( const LexerTextPos * token, int id_accel, bool result );

    bool GetMatchedFragmentAt( const LexerTextPos * token, lem::PtrCollect<SynPatternResult> & results, bool * matched ) const;
    void StoreMatchedFragment( const LexerTextPos * token, bool matched, const lem::PtrCollect<SynPatternResult> & results );
  };

 }
#endif
