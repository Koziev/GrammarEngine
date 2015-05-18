/*
**  DeSR
**  src/Enumerator.i
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

%{
#include "Enumerator.h"
%}

%include "Enumerator.h"

#ifdef SWIGPYTHON

// Instantiate template and provide iterator interface.
// Prefix is added to 'Enumerator' for generating the SWIG name.
%define EnumeratorInterface(Prefix, Item)

%template(Enumerator ## Prefix) Tanl::Enumerator<Item>;

// Decrease the reference to the embedded enumerator object.
%feature("unref") Tanl::Enumerator<Item> "$this->Dispose();"

// Wonderful SWIG magic to turn a C++ method into a Python iterator.
%allowexception;
%exception Tanl::Enumerator<Item>::next() {
  $action
    if (!result) {
      /* Throw a StopIteration exception. */
      PyErr_SetObject(PyExc_StopIteration, Py_None);
      return NULL;
    }
};

%newobject Tanl::Enumerator<Item>::next();

%extend Tanl::Enumerator<Item> {
  Tanl::Enumerator<Item>* __iter__() {
    return $self;
  }

  Item next() {
    return $self->MoveNext() ? $self->Current() : NULL;
  }
};
%enddef

#endif // SWIGPYTHON

#ifdef SWIGJAVA
// Instantiate template and provide iterator interface.
// Prefix is added to 'Enumerator' for generating the SWIG name.
%define EnumeratorInterface(Prefix, Item)

%template(Enumerator ## Prefix) Tanl::Enumerator<Item>;

%newobject Tanl::Enumerator<Item>::next();

%extend Tanl::Enumerator<Item> {

  Item next() {
    return $self->Current();
  }

  bool hasNext() { return $self->MoveNext(); }
};
%enddef

#endif // SWIGJAVA
