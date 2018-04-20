#if !defined LEM_STARTUP__H
#define LEM_STARTUP__H

namespace lem
{
    struct CP_Initialized
    {
        CP_Initialized();
        ~CP_Initialized();
    };


    extern void Init();
    extern void Leave();

    struct LemInit
    {
        LemInit() { lem::Init(); }
        ~LemInit() { lem::Leave(); }
    };
}

#endif

