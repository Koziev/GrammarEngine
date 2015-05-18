/*
**  IXE C++ Library
**  ixe/include/error.h
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

#ifndef IXE_ERROR_H
#define IXE_ERROR_H

// Settings
#include "platform.h"

// standard
#include <stdexcept>

namespace IXE {

/// Base class for all errors reported
class Error : public std::exception
{
private:
  std::string msg;

  /// assignment operator private and unimplemented
  void operator=(const Error &copyme);
protected:
  /** constructors are protected, since they can only
   * be used by derived classes anyway.
   */
  Error(std::string const& error_msg) : msg(error_msg) {}
  Error(const Error &copyme) : msg(copyme.msg) {}
public:
  /** Return a message describing the error.
   *  This is in a human readable form.
   */
  std::string message() { return msg; }

  virtual ~Error() throw() { }
};

//----------------------------------------------------------------------

/** Base class for errors due to programming errors.
 *  An exception derived from LogicError is thrown when a misuse
 *  of the API is detected.
 */
class LogicError : public Error {
    protected:
        LogicError(std::string const& msg) : Error(msg) {}
};

/** Base class for errors due to run time problems.
 *  An exception derived from RuntimeError is thrown when an
 *  error is caused by problems with the data or environment rather
 *  than a programming mistake.
 */
class RuntimeError : public Error {
    protected:
        RuntimeError(std::string const& msg) : Error(msg) {}
};

//----------------------------------------------------------------------

/** Thrown if an internal consistency check fails.
 *  This represents a bug. */
class AssertionError : public LogicError {
public:
  AssertionError(std::string const& msg) :
#   ifdef _MSC_VER     
    LogicError(msg/* + " - assertion failed"*/) {}
#   else
    LogicError(msg + " - assertion failed") {}
#   endif
};

/** Thrown when an attempt to use an unimplemented feature is made. */
class UnimplementedError : public LogicError {
public:
  UnimplementedError(std::string const& msg) : LogicError(msg) {}
};

/** Thrown when an invalid argument is supplied to the API. */
class InvalidArgumentError : public LogicError {
public:
  InvalidArgumentError(std::string const& msg) : LogicError(msg) {}
};

//----------------------------------------------------------------------

/** Thrown when reading a configuration file fails. */
class ConfigFileError : public RuntimeError {
public:
  ConfigFileError(std::string const& msg) : RuntimeError(msg) {}
};

/** Thrown when opening a file fails. */
class FileError : public RuntimeError {
public:
  FileError(std::string const& msg) : RuntimeError(msg) {}
};

/** Thrown when mmap fails mapping a file to memory. */
class MmapError : public RuntimeError {
public:
  MmapError(std::string const& msg) : RuntimeError(msg) {}
};

/** Wrong index format file. */
class FormatError : public RuntimeError {
public:
  FormatError(std::string const& msg) : RuntimeError(msg) {}
};

/** Thrown when an attempt is made to access a document which is not in the
 *  collection.  This could occur either due to a programming error, or
 *  because the collection has changed since running the query. */
class DocNotFoundError : public RuntimeError {
public:
  DocNotFoundError(std::string const& msg) : RuntimeError(msg) {}
};

/** thrown when an internal inconsistency occurs. */
class InternalError : public RuntimeError {
public:
  InternalError(std::string const& msg) : RuntimeError(msg) {}
};

/** thrown during indexing. */
class IndexingError : public RuntimeError {
public:
  IndexingError(std::string const& msg) : RuntimeError(msg) {}
};

/** thrown when an element is out of range. */
class RangeError : public RuntimeError {
public:
  RangeError(std::string const& msg) : RuntimeError(msg) {}
};

/** Thrown when reader fails interpreting document format. */
class ReaderError : public RuntimeError {
public:
  ReaderError(std::string const& msg) : RuntimeError(msg) {}
};

/** thrown for miscellaneous collection errors. */
class CollectionError : public RuntimeError {
public:
  CollectionError(std::string const& msg) : RuntimeError(msg) {}
};

/** thrown when there is a communications problem with
 *  a remote collection.
 */
class NetworkError : public RuntimeError {
public:
  NetworkError(std::string const& msg) : RuntimeError(msg) {}
};

/** thrown when there is a communications problem with
 *  a remote collection.
 */
class MemoryError : public RuntimeError {
public:
  MemoryError(std::string const& msg) : RuntimeError(msg) {}
};

/** Thrown when opening a collection fails. */
class OpeningError : public CollectionError {
public:
  OpeningError(std::string const& msg) : CollectionError(msg) {}
};

/** Thrown when accessing a database Table fails. */
class TableError : public CollectionError {
public:
  TableError(std::string const& msg) : CollectionError(msg) {}
};

class ParserError : public RuntimeError {
public:
  ParserError(char const* msg) : RuntimeError(msg) {}
};

/** Thrown when an SQL query fails. */
class QueryError : public RuntimeError {
public:
  QueryError(std::string const& msg) : RuntimeError(msg) {}
};

/** Thrown when trying to access invalid data. */
class InvalidResultError : public RuntimeError {
public:
  InvalidResultError(std::string const& msg) : RuntimeError(msg) {}
};

/** Thrown when a system call fails. */
class SystemError : public RuntimeError {
public:
  SystemError(std::string const& msg) : RuntimeError(msg) {}
};

class IOError : public RuntimeError {
public:
  IOError(std::string const& msg) : RuntimeError(msg) {}
  IOError(char const* msg) : RuntimeError(msg) {}
};

///////////////////////////////////////////////////////////////////////////////
// System errors

#define SYS_CALL(method, args) \
  if (!(method args)) \
    throw SystemError(std::string("*** SystemError at  " __FILE__ ":") \
    + __LINE__ +  ". Failed: " #method #args)

} // namespace IXE

#endif /* IXE_ERROR_H */
