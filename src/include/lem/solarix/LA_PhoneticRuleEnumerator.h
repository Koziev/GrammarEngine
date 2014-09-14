#if !defined LA_PHONETIC_RULE_ENUMERATOR__H
 #define LA_PHONETIC_RULE_ENUMERATOR__H

 namespace Solarix
 {
  class LA_PhoneticRule;

  class LA_PhoneticRuleEnumerator
  {
   public:
    LA_PhoneticRuleEnumerator(void) {}
    virtual ~LA_PhoneticRuleEnumerator(void) {}

    virtual bool Fetch(void)=0;
    virtual const LA_PhoneticRule& Get(void)=0;
  };
 }

#endif
