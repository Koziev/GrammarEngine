// LC->03.09.2009
// --------------

#ifndef SE_FIX_CONTEXT__H
#define SE_FIX_CONTEXT__H
#pragma once

 #include <lem/math/fp1.h>
 #include <lem/forms/ContextHighlight.h>
 #include <lem/runtime_checks.h>
 #include <lem/solarix/se_text.h>


 namespace Solarix
 {
  namespace Search_Engine
  {
   using lem::UFString;
   using lem::Collect;
   using lem::PtrCollect;
   using lem::Real1;

   class Doc_Topic;

   // *********************************************************
   // Описание степени уверенности фиксации для одного слова.
   // *********************************************************
   struct Fix_Rel
   {
    Real1 rel; // достоверность фиксации
    int sem_dist; // расстояние по семантической сети

    Fix_Rel(void) { rel=0; sem_dist=UNKNOWN; }

    inline void operator=( float Rel ) { rel=Rel; }

    inline void Clear(void) { rel=0; sem_dist=0; }
   };

  // ************************************************************************
  // Вектор различных кумулятивных оценок достоверности контекста фиксации.
  // ************************************************************************
  struct Fix_Rank : public Solarix::Search_Engine::Doc_Info
  {
   float word_rel; // достоверность фиксации контекста - пословная (учет нечеткой фиксации)
   int freq; // кумулятивная оценка частоты ключевых слов в документе,
             // в котором найден контекст
   lem::Stream::pos_type doc_size; // размер документа (для вычисления относительной частоты) 
   boost::shared_ptr<Doc_Topic> topic;
 
   Fix_Rank(void);

   Fix_Rank( const Fix_Rank &x );

   void operator=( const Fix_Rank &x );

   void clear(void);

   void operator += ( const Fix_Rank &x );

   double GetTotal(void) const
   { return (freq ? freq : 1) * ( word_rel>0 ? word_rel : 1.); }
  };


  class Base_Node;

  // **********************************************************************
  // Описатель места в тексте, где произошла успешная фиксация контекста, то
  // есть где был найден искомый текст.
  // **********************************************************************
  struct Fix_Point
  {
   UFString name; // Для именованных опорных точек	   
   File_Lexem word; // слово из файла
   UFString regex_match; // Контекст фиксации регэкспа
   const Base_Node *pattern; // опорная точка, которая сделала фиксацию
   Fix_Rel rel;

   Fix_Point(void);

   Fix_Point( const Fix_Point& x );

   inline const Fix_Rel& GetRel(void) const { return rel; }
   
   void operator=( const Fix_Point &x );

   inline bool IsWordFixed(void) const { return !word.word.empty(); }
   inline bool IsRegexFixed(void) const { return !regex_match.empty(); }

   inline const wchar_t* GetText(void) const
   { return regex_match.empty() ? word.original.c_str() : regex_match.c_str(); }
  };


  // **********************************************************
  // Ячейка столбца в результирующем множестве - формируется,
  // если есть именованные опорные точки.
  // **********************************************************
  class Fix_Column
  {
   public:
    UFString name;     // имя опорной точки
    UFString content;  // на чем зафиксирована точка - если просто лексема.
    #if !defined SOL_NO_AA
    //PtrCollect<Solarix::Tree_Node> trees; // на каких грамматических узлах зафиксирована 
                                          // точка
    #endif

   public:
    Fix_Column(void);
    Fix_Column( const UFString &Name );
    Fix_Column( const UFString &Name, const UFString &Content );
    Fix_Column( const Fix_Column& x );

    #if !defined SOL_NO_AA
    //void Add( const Tree_Node* n );
    #endif

    void operator=( const Fix_Column& x );

    inline const UFString& GetName(void) const { return name; }

    inline const UFString& GetContent(void) const { return content; }

    #if !defined SOL_NO_AA
    //inline const PtrCollect<Solarix::Tree_Node>& GetTrees(void) const { return trees; }
    #endif
  };


  // *********************************************************************************
  // Для размещения после каждого контекста фиксации на странице результатов
  // разнообразной дополнительной информации (например, результатов интеллектуальной
  // обработки документа) используются наследники этого класса.
  // *********************************************************************************
  class ResultSet_Element
  {
   public: 
    ResultSet_Element(void) {}

    virtual void operator=( const ResultSet_Element& ) {}

    virtual ~ResultSet_Element(void) {}

    virtual ResultSet_Element *clone(void) const { LEM_STOPIT; LEM_NO_RET(NULL); }
    virtual const UFString GetHTML(void) const { LEM_STOPIT; LEM_NO_RET(UFString()); }
    virtual const UFString GetTXT(void) const { LEM_STOPIT; LEM_NO_RET(UFString()); }
    virtual const UFString GetXML(void) const { LEM_STOPIT; LEM_NO_RET(UFString()); }
    virtual void Print( OFormatter &out ) const { LEM_STOPIT; }
  };

  class RSE_Table : public ResultSet_Element
  {
   public:
    UFString title;    
    lem::PtrCollect< lem::Collect< UFString > > rows;
    lem::PtrCollect<UFString> column_names; // условные названия столбцов

   public: 
    RSE_Table(void) {}
    RSE_Table( const wchar_t *Title ) : title(Title) {}
    RSE_Table( const RSE_Table& x );

    virtual void operator=( const ResultSet_Element& x );

    void AddColumnName( const wchar_t *Name ); 

    lem::Collect<UFString>& AddRow(void);
    inline int CountRows(void) const { return CastSizeToInt(rows.size()); }

    virtual ResultSet_Element *clone(void) const { return new RSE_Table(*this); }
    virtual const UFString GetHTML(void) const;
    virtual const UFString GetTXT(void) const;
    virtual const UFString GetXML(void) const;
    virtual void Print( OFormatter &out ) const;
  };



  // ********************************************************************* 
  // Класс для представления контекста фиксации - места в тексте, где были
  // удовлетворены условия запроса.
  // ********************************************************************* 
  class Fix_Context : public lem::WxForms::ContextHighlight
  {
   public:
    lem::Collect< Fix_Point > points;

   private:
    friend class Query_Matcher;

    int id; // уникальный номер фиксации контекста.
    int id_pattern; // для какого паттерна
    int id_query; // для какого запроса

    // В этом списке будет участок файла, содержащий все лексемы,
    // на которых произошла фиксация, включая не участвовавшие в
    // совпадении с образцом.
    lem::Collect<Fix_Point> printable;

    // Список именованных столбцов
    lem::PtrCollect<Fix_Column> columns; 

    Fix_Rank rank; // различные оценки достоверности контекста

    lem::CloneCollect< ResultSet_Element > addons; // добавляемые на страницу
                                                   // результатов данные с разным
                                                   // содержимым

    UFString forced_html; // принудительно заданное представление контекста в HTML,
                          // используется в случаях, когда конструирование HTML представления
                          // из опорных точек невозможно 

   public:
    boost::shared_ptr<Doc_Topic> topic;

   public:
    virtual lem::Container::size_type GetPrintableCount(void) const;
    virtual lem::UFString GetPrintableText( int ipoint ) const;

    virtual void GetWordSelectors( lem::Collect<lem::UFString> &words ) const;

    // Возвращает строку-регулярное выражение,
    // с помощью которой можно выделить в исходном документе
    // весь контекст фиксации.
    virtual const UFString GetRegexSelector(void) const;


   public:
    Fix_Context( int Id_Query=UNKNOWN, int Id_Pattern=UNKNOWN );

    Fix_Context( const Fix_Context& x );

    virtual ~Fix_Context(void);

    void operator=( const Fix_Context& x );

    void Add( const Fix_Context &x );

    void ForceHtml( const lem::UFString &html_str );

    const Collect<Fix_Point>& GetPrintable(void) const { return printable; }

    const PtrCollect<Fix_Column>& GetColumns(void) const { return columns; }

    void Clear(void);

    void Add( const Fix_Point &x );
    void AddPrintable( const Fix_Point &x );
    void Add( Fix_Column *col );
    void Add( ResultSet_Element *x );

    inline const Fix_Rank& GetRank(void) const { return rank; }
    void ApplyDocRank( const Fix_Rank &r );

    inline void SetRel( float R ) { rank.word_rel=R; }
    inline void FactorRel( float f ) { rank.word_rel*=f; }

    inline int GetId(void) const { return id; }
    inline void SetId( int Id ) { id=Id; }

    inline int GetIdPattern(void) const { return id_pattern; }
    inline int GetIdQuery(void) const { return id_query; }

    const UFString GetXML(void) const;
    const UFString GetHTML(void) const;
    const UFString GetPlainTxt(void) const;

	const UFString GetXMLColumns(void) const;
    const UFString GetHTMLColumns(void) const;
    const UFString GetPlainTxtColumns(void) const;
 
    const UFString GetHTMLAddons(void) const;
    const UFString GetXMLAddons(void) const;

    const UFString GetDrawerStr( int max_width_chars=UNKNOWN, bool allow_newlines=true ) const;

    inline bool HasAddons(void) const { return !addons.empty(); }
    void PrintAddons( OFormatter &out ) const;
  };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
