#if !defined LA_PRONETIC_MATCHER__H
 #define LA_PRONETIC_MATCHER__H

 #include <lem/noncopyable.h>
 #include <lem/RWULock.h>
 #include <lem/process.h>
 #include <lem/math/fp1.h>

 namespace Solarix
 {
  class Dictionary;

  class LA_PhoneticRule;

 /********************************************************************
  Индексный список для правил фонетической продукции с одинаковым
  числом опорных точек. Создается при подготовке работы ЛА и позволяет
  ускорить работу Фонетического Алеф-Алгоритма за счет исключени
  просмотра заведомо неподходящих правил. Каждая группа - это набор
  индексов правил фонетической продукции LA с равноразмерным опорным
  контекстом.
 *********************************************************************/
 struct LA_PhoneticRuleGroup : lem::NonCopyable
 {
  lem::MCollect<const LA_PhoneticRule*> rules;
  inline bool empty(void) const { return rules.empty(); }
 };


  class LS_ResultSet;
  class LexiconStorage;

 struct Rule_1_to_1
 {
  wchar_t From; // из символа
  wchar_t To;   // в символ

  Rule_1_to_1(void) { From=To=0; }
  Rule_1_to_1( wchar_t From_Char, wchar_t To_Char ) 
  :From(From_Char), To( To_Char ) {}


  inline bool operator>( const Rule_1_to_1&x ) const 
  { 
   if( From>x.From ) return true;
   if( From==x.From ) return To>x.To;
   return false;
  }

  inline bool operator<( const Rule_1_to_1&x ) const 
  { 
   if( From<x.From ) return true;
   if( From==x.From ) return To<x.To;
   return false;
  }

  inline bool operator==( const Rule_1_to_1&x ) const 
  { return From==x.From && To==x.To; }
 };

  class LA_PhoneticRuleEnumerator;

  class LA_PhoneticMatcherForLanguage : lem::NonCopyable
  {
   private:
    typedef std::map< Rule_1_to_1, lem::Real1 > RULES11;
    RULES11 rules_11;

    int id_language;
    lem::MCollect<LA_PhoneticRule*> rules;
    int min_context, max_context; // минимальное и максимальное число опорных точек в фонетических правилах

    LA_PhoneticRuleGroup groups[ lem::UCString::max_len ];

    void Load( LexiconStorage *storage, LS_ResultSet *rs );

   public:
    LA_PhoneticMatcherForLanguage( int Id_Lang );
    ~LA_PhoneticMatcherForLanguage(void);

    void Load( Solarix::Dictionary *dict, LexiconStorage *storage );
  
    int GetMinContext(void) const { return min_context; }
    int GetMaxContext(void) const { return max_context; }

    // Получаем подгруппу правил для опорных контекстов заданной длины
    const LA_PhoneticRuleGroup& GetGroup( int len ) const
    { LEM_CHECKIT_Z( len>=0 && len<lem::UCString::max_len ); return groups[len]; }

    lem::Real1 MatchRule11( const Rule_1_to_1 &r ) const;
    LA_PhoneticRuleEnumerator* EnumerateRules(void) const;
  };


  class LA_PhoneticMatcher : lem::NonCopyable
  {
   private:
    Solarix::Dictionary *dict;
    LexiconStorage *storage;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs;
    #endif    

    lem::MCollect<LA_PhoneticMatcherForLanguage*> matcher;
    lem::MCollect<int> id_langs;

    const LA_PhoneticMatcherForLanguage* LoadRules( int id_language );
    void DeleteRules(void);

   public:
    LA_PhoneticMatcher( Solarix::Dictionary *Dict );
    ~LA_PhoneticMatcher(void);

    void Connect( LexiconStorage *Storage );

    const LA_PhoneticMatcherForLanguage* GetMatcherForLanguage( int id_language );
  };
 }

#endif
