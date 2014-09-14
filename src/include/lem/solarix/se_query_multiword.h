#if !defined Query_Multiword__H
 #define Query_Multiword__H

 #include <lem/ufstring.h>
 #include <lem/solarix/se_query.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
   class Topic_Finder;
   class Multiword_Matcher;

   #if defined FAIND_MULTIWORD_QUERY
   // ***************************************************************
   // Оптовый поиск слов - в документах ищутся слова из загружаемого
   // справочника.
   // ***************************************************************
   class Query_Multiword : public Query_Root
   {
    private:
     lem::UFString filename; // имя файла со справочником слов
     Solarix::Search_Engine::Topic_Finder * topics_db; // СУБД рубрикатора
     Solarix::Search_Engine::Multiword_Matcher * matcher; // для быстрого поиска множества словосочетаний
     Solarix::Search_Engine::Search_Options flags;

    public:
     Query_Multiword( const lem::UFString &Name, const lem::UFString &Pattern );
     virtual ~Query_Multiword(void);

     virtual void Parse(
                        const lem::UFString &txt,
                        const Search_Options &flags
                       );

     virtual const std::wstring GetName(void) const;
     virtual const std::wstring GetAttrs(void) const;

     // Нам нужен текст в виде одной строки
     virtual bool NeedsSerializedText(void) const { return false; }

     // А разбивка на слова не требуется
     virtual bool NeedsWordedText(void) const { return true; }

     virtual void ApplyDictionary(
                                  Dictionary *dict,
                                  Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                  const Lexer_Options &lo
                                  #if !defined SOL_NO_AA
//                                  , Solarix::Text_Processor *tpu
                                  #endif
                                 );

     virtual void SaveBin( lem::Stream &bin ) const;
     virtual void LoadBin( lem::Stream &bin );

     virtual void PrepareToMatch(void);

     virtual bool Fix(
                      Text &text,
                      Dictionary *dict,
                      const LD_Seeker *seeker, 
                      #if !defined SOL_NO_AA
//                      Solarix::Text_Processor *tpu,
                      #endif 
                      Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                      Fix_Context& context,
                      Fix_States& fx_states 
                     );

     virtual bool ContainedInString( const lem::UFString &str ) const;

     virtual Base_Node* Optimize(void);
   };
   #endif
  }
}
#endif
