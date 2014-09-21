#include <stdlib.h>
#include <lem/console_streams.h>
#include <lem/streams.h>
#include <lem/startup.h>

static lem::CP_Initialized *cp_init = NULL;

void lem::Init(void)
{
 if( cp_init==NULL )
  cp_init = new lem::CP_Initialized;


 // ... other initializations ...

 return;
}


void lem::Leave(void)
{
 delete cp_init;
 cp_init=NULL;
}

