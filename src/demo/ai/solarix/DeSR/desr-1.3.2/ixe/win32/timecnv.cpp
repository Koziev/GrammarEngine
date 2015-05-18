/*
**	IXE
**	win32/timecnv.cpp
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
**
**  This file is part of IXE.
**
**  IXE is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  IXE is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#include "win32/timecnv.h"

typedef union {
    unsigned __int64	ft_i64;
    FILETIME		ft_val;
} FT_t;

/* Number of 100 nanosecond units from 1/1/1601 to 1/1/1970 */
#define EPOCH_BIAS  116444736000000000i64

long FileTimeToNetworkTime(FILETIME ftime)
{
  FT_t ft;
  ft.ft_val = ftime;
  return ((ft.ft_i64) - EPOCH_BIAS) / 10000000i64;
}

FILETIME NetworkTimeToFileTime(long time)
{
	FT_t ft;
	ft.ft_i64 = (__int64)time * 10000000i64 + EPOCH_BIAS;
	return ft.ft_val;
}

void time_now(struct timeval* tv)
{
  FT_t ft;

  /* this returns time in 100-nanosecond units  (i.e. tens of usecs) */
  GetSystemTimeAsFileTime(&ft.ft_val);

  /* seconds since epoch */
  tv->tv_sec = FileTimeToNetworkTime(ft.ft_val);

  /* microseconds remaining */
  tv->tv_usec = (long)((ft.ft_i64 / 10i64) % 1000000i64);
};

