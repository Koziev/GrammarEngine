/*
**  IXE C++ Library
**  include/Timer.h: timing durations.
** ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
**
**  This file is part of DeSR.
**
**  DeSR is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  DeSR is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef IXE_Timer_H
#define IXE_Timer_H

#ifdef	_WIN32
# include <winsock2.h>
# include "win32/timecnv.h"
#else
#include <sys/time.h>           // gettimeofday
#endif
#include <cstdio>		// snprintf

namespace IXE {

class Timer {

public:
  Timer() { start(); }

  void start() { time_now(&l0); }

  /**
   * Freezes the current time, for reading.
   */
  void split() { time_now(&l1); }

  /** Get the elapsed seconds. */
  long seconds() { return l1.tv_sec - l0.tv_sec; }

  /**
   * Gets a reading of the elapsed time into @param buf.
   */
  void reading(char* buf, size_t bufSize) {
    long sec = l1.tv_sec - l0.tv_sec;
    long usec = l1.tv_usec - l0.tv_usec;
    if (usec < 0) {
      sec--;
      usec += 1000000;
    }
    if (sec > 60)
      snprintf(buf, bufSize, "%ld' %ld.%03ld sec", sec/60, sec%60, usec/1000);
    else if (sec > 0)
      snprintf(buf, bufSize, "%ld.%03ld sec", sec, usec/1000);
    else
      snprintf(buf, bufSize, "%ld.%03ld msec", usec/1000, usec%1000);
  }

  struct timeval l0, l1;
};

}

#endif // IXE_Timer_H
