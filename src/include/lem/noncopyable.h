#ifndef LEM_NONCOPYABLE__H
#define LEM_NONCOPYABLE__H
#pragma once

 #include <lem/config.h>
 #include <boost/noncopyable.hpp>

 namespace lem
 {
  struct NonCopyable : boost::noncopyable
  {
  };
 }

#endif
