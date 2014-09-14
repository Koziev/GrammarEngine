#if !defined TreeScorerApplicationContext__H
#define TreeScorerApplicationContext__H

namespace Solarix
{
 class TreeScorerApplicationContext : lem::NonCopyable
 {
  private:
   const TreeScorerApplicationContext * parent;

   lem::MCollect<const Word_Form *> matched_token;
   lem::MCollect<int> matched_relative_position;

   //typedef std::map<lem::UCString,const Solarix::Word_Form*> BOUND_VARIABLES;
   //BOUND_VARIABLES bound_variables;

  public:
   TreeScorerApplicationContext( const TreeScorerApplicationContext * _parent ) : parent(_parent) {}

   void StoreMatchedPosition( const Word_Form & token, int relative_position );
   bool CheckPosition( const Word_Form & token, int relative_position ) const;

   bool CheckRelativePositions() const;

   //void AddVariable( const lem::UCString & upper_name, const Solarix::Word_Form * wordform );
   //const Solarix::Word_Form* GetVariable( const lem::UCString & upper_name ) const;
 };


 class TreeScorerBoundVariables : lem::NonCopyable
 {
  private:
   typedef std::map<lem::UCString,const Solarix::Word_Form*> BOUND_VARIABLES;
   BOUND_VARIABLES bound_variables;

  public:
   TreeScorerBoundVariables() {}

   void Clear();
   void AddVariable( const lem::UCString & upper_name, const Solarix::Word_Form * wordform );
   const Solarix::Word_Form* GetVariable( const lem::UCString & upper_name ) const;
 };

}

#endif
