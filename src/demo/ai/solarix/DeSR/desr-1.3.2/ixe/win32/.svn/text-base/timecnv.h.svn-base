/*
**	IXE
**	win32/timecnv.h
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

#ifndef IXE_win32_timecnv_H
#define IXE_win32_timecnv_H

// reduce unnecessary linking
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <ctime>
#include <winsock2.h>	// timeval

#define GMTIME(time, tm)	    tm = *gmtime(time)

void		time_now(struct timeval* tv);

long		FileTimeToNetworkTime(FILETIME ft);

FILETIME	NetworkTimeToFileTime(long time);

#endif	// IXE_win32_timecnv_H
