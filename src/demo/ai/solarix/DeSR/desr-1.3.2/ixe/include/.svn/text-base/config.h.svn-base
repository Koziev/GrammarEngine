/*
**  IXE C++ Library
**  ixe/include/config.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2000  Ideare SpA.
**  Copyright (c) 2000  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef	IXE_include_config_H
#define	IXE_include_config_H

#include "platform.h"

/**
 *	Global configuration parameters.
 */

namespace IXE {

////////// Word parameters ////////////////////////////////////////////////////

int const	WordMaxSize			= 25;
//		The maximum length of words.
int const	WordMinSize			= 2;
//		The minimum length of words.

////////// Miscellaneous parameters ///////////////////////////////////////////

char const	ConfigFileDefault[]		= "ixe.conf";
//		Default name of the configuration file.

char const	TableNameDefault[]	      = "INDEX/docinfo";
//		Default name of table containing indexes generated/searched;
// 		can be overridden either in a config. file or on the command 
//		line.

int const	FilesGrowDefault		= 100;
//		Default number of files to grow reserved space for when
//		incrementally indexing.

char const	IndexExt[]			= ".fti";
//		Extension of index files.

char const	PostingExt[]			= ".pst";
//		Extension of postings files.

char const	TableExt[]			= ".bdb";
//		File extension for Berkeley DB tables.

char const	ContentsExt[]			= ".gz";
//		File extension for zipped contents files.

int const	ResultsMaxDefault		= 10;
//		Default maximum number of search results; this can be
//		overridden either in a config. file or on the command line.

#ifdef _WIN32
char const	TempDirectoryDefault[]		= "/windows/temp";
#else
char const	TempDirectoryDefault[]		= "/tmp";
#endif
//		Default directory to use for temporary files during indexing.

int const	WordPercentMaxDefault		= 100;
//		Default maximum percentage of files a word may occur in before
//		it is discarded as being too frequent.

int const	Word_Threshold			= 60000;
//		The word count past which partial indexes are generated and
//		merged

int const	max_columns			= 64;
//		Maximum number of columns in a table.

int const	max_prefix_lists		= 5000;
//		Maximum number of terms considered in prefix search.

int const	Max_CursorAll_Hits		= 20;
//		Maximum number of proximity hits considered by QueryCursorAll

int const	Postings_Segment_Size		= 1024;
//		Size of postings segment which is scanned sequentially
//		This parameter must be less than the following

int const	Min_Postings_Table		= 4096;
//		Minimum number of postings required for the table

} // namespace IXE

#endif	/* IXE_include_config_H */
