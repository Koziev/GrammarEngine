#if !defined RWU_Lock__H
 #define RWU_Lock__H

 #include <lem/config.h>

 #if defined LEM_THREADS

 #include <boost/thread/shared_mutex.hpp>
 #include <boost/thread/locks.hpp>

 namespace lem
 {
  namespace Process
  {
   // ******************************************************
   // Multiple reader, single writer, upgradable mutex.
   // ******************************************************
   class RWU_Lock
   {
    private:
     boost::shared_mutex cs;

     friend class RWU_ReaderGuard;
     friend class RW_UniqueGuard;
   
    public:
     RWU_Lock(void) {}
   };


   class RWU_ReaderGuard
   {
    private:
     RWU_Lock &mx;
     boost::shared_lock<boost::shared_mutex> locker;
     friend class RWU_WriterGuard;

     boost::shared_mutex& ReleaseMutex(void)
     {
      locker.unlock();
      return mx.cs;
     }

    public:
     RWU_ReaderGuard( RWU_Lock &x ) : mx(x), locker(x.cs) {}
     ~RWU_ReaderGuard(void) {}
   };

   class RWU_WriterGuard
   {
    private:
     boost::unique_lock<boost::shared_mutex> lock;

    public:
     RWU_WriterGuard( RWU_ReaderGuard &x ) : lock(x.ReleaseMutex()) {}
     ~RWU_WriterGuard(void) {}
   };


   class RW_UniqueGuard
   {
    private:
     boost::unique_lock<boost::shared_mutex> lock;

    public:
     RW_UniqueGuard( RWU_Lock &x ) : lock(x.cs) {}
     ~RW_UniqueGuard(void) {}
   };

  }
 }

#endif

#endif
