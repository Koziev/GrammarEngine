#include <stdlib.h>
#include <lem/console_streams.h>
#include <lem/streams.h>
#include <lem/startup.h>

static lem::CP_Initialized *cp_init = nullptr;

void lem::Init()
{
    if (cp_init == nullptr)
        cp_init = new lem::CP_Initialized;


    // ... other initializations ...

    return;
}


void lem::Leave()
{
    delete cp_init;
    cp_init = nullptr;
}

