#if !defined KB_CheckingResult__H
 #define KB_CheckingResult__H


 namespace Solarix
 {

  class KB_CheckingResult
  {
   protected:
    int type; // 0 - boolean, 1 - integer

    int retbool;
    int false_score; // штраф за "м€гкий" false, если <0.

    int retint;

   public:
    KB_CheckingResult(void);

    bool IsUnknown() const { return type==UNKNOWN; }
    bool IsBoolean() const { return type==0; }
    bool IsInteger() const { return type==1; }

    int GetBool() const;
    bool HasFalseScore() const { return false_score!=0; }
    int GetFalseScore() const { return false_score; }

    int GetInt() const;

    bool IsMatched() const { return type!=UNKNOWN; }
  };

 }

#endif
