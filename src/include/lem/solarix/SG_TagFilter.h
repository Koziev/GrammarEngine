#if !defined SG_TagFilter__H
 #define SG_TagFilter__H

 #include <lem/noncopyable.h>
 #include <lem/smart_pointers.h>
 #include <lem/solarix/SG_TagsList.h>

 namespace Solarix
 {

  // ***************************************************
  // Ограничитель на видимые клиентом связи - по тэгам
  // ***************************************************
  class SG_TagFilter : lem::NonCopyable
  {
   public:
    SG_TagFilter(void) {}
    virtual ~SG_TagFilter() {}

    virtual bool Match( SG_TagsList x ) const=0;
    virtual bool Empty(void) const=0;
  };


  class SG_TF_AndFilter : public SG_TagFilter
  {
   private:
    lem::Ptr<SG_TagFilter> arg1;
    lem::Ptr<SG_TagFilter> arg2;

   public:
    SG_TF_AndFilter( const lem::Ptr<SG_TagFilter> &arg1, const lem::Ptr<SG_TagFilter> &arg2 );

    virtual bool Match( SG_TagsList x ) const;
    virtual bool Empty(void) const;
  };

  class SG_TF_OrFilter : public SG_TagFilter
  {
   private:
    lem::Ptr<SG_TagFilter> arg1;
    lem::Ptr<SG_TagFilter> arg2;

   public:
    SG_TF_OrFilter( const lem::Ptr<SG_TagFilter> &arg1, const lem::Ptr<SG_TagFilter> &arg2 );

    virtual bool Match( SG_TagsList x ) const;
    virtual bool Empty(void) const;
  };



  class SG_RefTagFilter : SG_TagFilter
  {
   private:
    bool matches_null;
    lem::MCollect< std::pair<int,int> > tags;

   public:
    SG_RefTagFilter( const lem::MCollect< std::pair<int,int> > &_tags, bool _matches_null );

    virtual bool Match( SG_TagsList x ) const;

    virtual bool Empty(void) const { return tags.empty(); }
  };

 }

#endif
