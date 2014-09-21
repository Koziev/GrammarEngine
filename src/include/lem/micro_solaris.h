// -----------------------------------------------------------------------------
// File MS_DICT.H
//
// Copyright:    Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//               Yhem High Tech Software
//
// Content:
// Микросолярис - упрощенная автономная модель Системы для использования в
// качестве генератора грамматически корректных сообщений (с точки зрения
// правильности склонений и так далее). Максимально компактная и без внешних
// файлов словарей и т.д.
// -----------------------------------------------------------------------------
//
// CD->07.03.1997
// LC->23.04.2007
// --------------

#ifndef SOL_MS_DICT__H
#define SOL_MS_DICT__H
#pragma once

 #include <vector>
 #include <map>
 
 #include <lem/cstring.h>
 #include <lem/fstring.h>
 #include <lem/unicode.h>
 #include <lem/quantors.h>
 #include <lem/runtime_checks.h>


 namespace lem
 {
  namespace Micro_Solaris
  {

 // Символические имена для обозначения морфологических категорий
 // грамматики для русского и других языков.

 // Род.
 enum {
       MASCULINE_GENDER,    // Мужской
       FEMININE_GENDER,     // Женский
       NEUTER_GENDER        // Средний
      };

 // Падеж.
 enum {
       NOMINATIVE_CASE,     // Именительный
       GENITIVE_CASE,       // Родительный
       INSTRUMENTAL_CASE,   // Творительный
       ACCUSATIVE_CASE,     // Винительный
       DATIVE_CASE,         // Дательный
       PREPOSITIONAL_CASE   // Предложный
      };

 // Признак одушевленности
 enum {
       ANIMATIVE_FORM,      // Одушевленное
       INANIMATIVE_FORM     // Неодушевленное
      };

 // Число.
 enum {
       SINGULAR_NUMBER,     // Единственное
       PLURAL_NUMBER        // Множественное
      };

 // Часть речи.
 enum {
       NOUN_PART,           // Имя существительное
       ADJECTIVE_PART       // Имя прилагательное
      };


 /************************************************************
  Таблица формообразования - команды продукции словоформ для
  Автомата Формообразования.
 ************************************************************/
 class MS_Declension
 {
  private:
   int code;      // Условный код склонения, на который ссылаются словарные статьи.
   int part;      // Часть речи, для которой работает таблица.

   int anim;      // Признак одушевленности
   int gender;    // Грамматический род

   int to_reduce; // Число отрезаемых символов аффикса (у лексического
                  // содержимого базовой формы).

   std::vector<UCString> affix; // Список аффиксов.

   MS_Declension( const MS_Declension & );
   void operator=( const MS_Declension & );

  public:
   MS_Declension(void)
   {
    code=part=anim=gender=UNKNOWN;
    to_reduce=0;
   }

   MS_Declension(
                 int Code,
                 int Part,
                 int Anim,
                 int Gender,
                 int To_Reduce,
                 const char *Affices,
                 lem::CodeConverter &cp
                );

   inline int GetCode(void) const     { return code;      }
   inline int GetToReduce(void) const { return to_reduce; }
   inline int GetPart(void) const     { return part;      }

   inline int GetAnim(void) const
   { LEM_CHECKIT_Z(part==NOUN_PART); return anim; }

   inline int GetGender(void) const
   { LEM_CHECKIT_Z(part==NOUN_PART); return gender; }

   inline const std::vector<UCString>& affices() const { return affix; }
 };


 /********************************************
   Класс для представления словарной статьи.
 *********************************************/
 class MS_Entry
 {
  private:
   UCString word; // Лексическое содержимое базовой формы парадигмы.
   int decl;      // Условный индекс таблицы склонений.

   std::vector<UCString> form; // Словоформы для "неправильных" существительных,
                               // с изменением корневого гласного или просто
                               // исключений из правила.

   MS_Entry( const MS_Entry & );
   void operator=( const MS_Entry & );

  public:
   MS_Entry(void) { decl=UNKNOWN; }

   MS_Entry( int Decl, const char *Root, CodeConverter &cp );

   // Корневая форма
   inline const UCString& GetWord(void) const { return word; }

   // Код склонения
   inline int GetDecl(void) const { return decl; }

   // Список словоформ
   inline const std::vector<UCString>& forms(void) const { return form; }
 };



 /***************************************************************************
  Словарь - списки словарных статей (Лексикон) и таблиц склонений(морфемика).
 ****************************************************************************/
 class MS_Dictionary
 {
  protected:
   // Maps are born to be used for dictionary...
   std::map< int /*id_decl*/, MS_Declension* /*T*/ > decl;
   std::multimap< lem::uint8_t /*hash*/, MS_Entry* /*T*/ > entry;

   const MS_Declension* FindDecl( int Decl ) const;
   const MS_Entry* FindWord( const UCString &word ) const;

  public:
   MS_Dictionary(void) {};
   virtual ~MS_Dictionary(void);

   virtual const UCString Decline(
                                  const UCString &word,
                                  int Case,
                                  int Number,
                                  int Gender=MASCULINE_GENDER,
                                  int Anim=INANIMATIVE_FORM
                                 ) const;

   virtual const UCString Correlate(
                                    const UCString &word,
                                    int value,
                                    int Case=NOMINATIVE_CASE,
                                    int Gender=MASCULINE_GENDER,
                                    int Anim=INANIMATIVE_FORM
                                   ) const;

   virtual const UFString Correlate(
                                    const UCString &word1,
                                    const UCString &word2,
                                    int value,
                                    int Case
                                   ) const;

  virtual const UFString Correlate(
                                   const UCString &word1,
                                   const UCString &word2,
                                   int value
                                  ) const;

   virtual int GetGender( const UCString &word ) const;
   
   int GetAnim( const MS_Entry &e ) const;
   int GetGender( const MS_Entry &e ) const;
   int GetPart( const MS_Entry &e ) const;

   // ****************************************************************
   // Перегружаемый в производных словарях метод: по строковому
   // представлению падежа возвращает его код.
   // ****************************************************************
   virtual int ParseCase( const char *Case ) const { return NOMINATIVE_CASE; }

   // Для указанной части речи возвращает индекс аффикса во внутреннем
   // списке объекта класса MS_Declension для указанной грамматической
   // категории.
   virtual int GetAffix(
                        int Part,
                        int Case,
                        int Number,
                        int Gender,
                        int Anim
                       ) const { return 0; }
 };


 // **********************************************
 // СЛОВАРЬ ДЛЯ РУССКОГО ЯЗЫКА
 // **********************************************
 class RusDict : public MS_Dictionary
 {
  private:
   const UCString Correlate_All(
                                const UCString &word,
                                int factor,
                                int Case,
                                int Gender,
                                int Anim,
                                int Part
                               ) const;

   const UCString Correlate_Nom(
                                const UCString &word,
                                int factor,
                                int Gender,
                                int Anim,
                                int Part
                               ) const;

   const UCString Correlate_Instr(
                                  const UCString &word,
                                  int factor,
                                  int Gender,
                                  int Anim,
                                  int Part
                                 ) const;

   const UCString Correlate_Accus(
                                  const UCString &word,
                                  int factor,
                                  int Gender,
                                  int Anim,
                                  int Part
                                 ) const;

  public:
   RusDict(void);

   virtual const UCString Decline(
                                  const UCString &word,
                                  int Case,
                                  int Number,
                                  int Gender=MASCULINE_GENDER,
                                  int Anim=INANIMATIVE_FORM
                                 ) const;

   virtual const UCString Correlate(
                                    const UCString &word,
                                    int value,
                                    int Case=NOMINATIVE_CASE,
                                    int Gender=MASCULINE_GENDER,
                                    int Anim=INANIMATIVE_FORM
                                   ) const;

   virtual const UFString Correlate(
                                    const UCString &word1,
                                    const UCString &word2,
                                    int value,
                                    int Case
                                   ) const;

   virtual int FindGender( const UCString &word ) const;

   virtual int ParseCase( const char *Case ) const;

   virtual int GetAffix(
                        int Part,
                        int Case,
                        int Number,
                        int Gender,
                        int Anim
                       ) const;
 };


 // **********************************************
 // СЛОВАРЬ ДЛЯ АНГЛИЙСКОГО ЯЗЫКА
 // **********************************************
 class EngDict : public MS_Dictionary
 {
  private:
   virtual int GetAffix( int Part, int Case, int Number, int Gender, int Anim ) const;
   virtual int ParseCase( const char *Case ) const;

  public:
   EngDict(void);

   virtual const UCString Decline(
                                  const UCString &word,
                                  int Case,
                                  int Number,
                                  int Gender=MASCULINE_GENDER,
                                  int Anim=INANIMATIVE_FORM
                                 ) const;

   virtual const UCString Correlate(
                                    const UCString &word,
                                    int value,
                                    int Case=NOMINATIVE_CASE,
                                    int Gender=MASCULINE_GENDER,
                                    int Anim=INANIMATIVE_FORM
                                   ) const;
 };


  // Глобально доступные объекты для работы с языками.
  extern RusDict ms_rus;
  extern EngDict ms_eng;


   } // namespace Micro_Solaris
 } // namespace lem

#endif
// ------------------------- End Of File [MS_DICT.H] ---------------------------

