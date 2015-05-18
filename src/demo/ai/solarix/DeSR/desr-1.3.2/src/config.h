/*
**  DeSR
**  src/config.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
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

#ifndef DeSR_config_H
#define DeSR_config_H

// Version for MSVC

// Define if your compiler has std::unordered_map  
/* #undef HAVE_STD_UNORDERED_MAP   */
  
// Define if your compiler has std::unordered_set  
/* #undef HAVE_STD_UNORDERED_SET   */
  
// Define if your compiler has std::tr1::unordered_map  
#define HAVE_TR1_UNORDERED_MAP 
  
// Define if your compiler has std::tr1::unordered_set  
#define HAVE_TR1_UNORDERED_SET 

// Define if you have hash_map and hash_set includes in ext/ directory.
#undef HAVE_EXT_HASH_MAP_SET

#undef HAVE_PYTHON 

#endif // DeSR_config_H
