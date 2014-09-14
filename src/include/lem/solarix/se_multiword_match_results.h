#if !defined MultiwordMatchResults__H
 #define MultiwordMatchResults__H

 #include <lem/containers.h>
 #include <lem/ptr_container.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
   class MultiwordMatchResult : lem::NonCopyable
   {
    public:
     int id_topic, id_keyword;
     lem::MCollect<int> words;

    public:
     MultiwordMatchResult(void) : id_topic(UNKNOWN), id_keyword(UNKNOWN) {}
   };


   class MultiwordMatchResults : lem::NonCopyable
   {
    public:
     int ipos;
     lem::Ptr_NC_Collect<MultiwordMatchResult> result;

    public:
     MultiwordMatchResults( int _ipos ) : ipos(_ipos) {}

     bool Empty(void) const { return result.empty(); }
     void Add( MultiwordMatchResult *r ) { result.push_back(r); }
   };
  }
 }

#endif
