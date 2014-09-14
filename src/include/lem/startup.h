#if !defined LEM_STARTUP__H
 #define LEM_STARTUP__H

 namespace lem
 {
  struct CP_Initialized
  {
   CP_Initialized(void);
   ~CP_Initialized(void);
  };


  extern void Init(void);
  extern void Leave(void);

  struct LemInit
  {
   LemInit(void) { lem::Init(); }
   ~LemInit(void) { lem::Leave(); }
  };
 }

#endif

