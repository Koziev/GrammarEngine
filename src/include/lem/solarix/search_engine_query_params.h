#ifndef SEARCH_ENGINE_QUERY_PARAMS__H
#define SEARCH_ENGINE_QUERY_PARAMS__H
#pragma once

 #include <lem/containers.h>
 #include <lem/ufstring.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
 
   typedef lem::Collect< std::pair<lem::UFString,lem::UFString> > QueryParams;

  }

 }

#endif
