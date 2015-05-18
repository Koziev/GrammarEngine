/*
**	IXE
**	include/unordered_set.h
** ----------------------------------------------------------------------
**	Copyright (c) 2009  Giuseppe Attardi (attardi@di.unipi.it)
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

#ifndef	IXE_include_unordered_set_H
#define	IXE_include_unordered_set_H

#include "platform.h"

#if defined(HAVE_STD_UNORDERED_SET)

# include <unordered_set>
# include "hash.h"
using std::unordered_set;
# define BEGIN_NAMESPACE_HASH namespace std {
# define END_NAMESPACE_HASH }

#elif defined(HAVE_TR1_UNORDERED_SET)

# if (_MSC_VER >= 1500)
#  include <unordered_set>
# else
#  include <tr1/unordered_set>
# endif

# include "hash.h"
using std::tr1::unordered_set;
# define BEGIN_NAMESPACE_HASH namespace std { namespace tr1 {
# define END_NAMESPACE_HASH }}

#else

# if defined(HAVE_EXT_HASH_MAP_SET)

#  include <ext/hash_set>
#  if __GNUC__ >= 3
using __gnu_cxx::hash_set;
#  define BEGIN_NAMESPACE_HASH namespace __gnu_cxx {
#  define END_NAMESPACE_HASH }

#  else
using std::hash_set;
#  endif
# elif (_MSC_VER >= 1400)
#  include <hash_set>
using stdext::hash_set;
#  define BEGIN_NAMESPACE_HASH namespace stdext {
#  define END_NAMESPACE_HASH }
# else
#  include <hash_set>
using std::hash_set;
#  define BEGIN_NAMESPACE_HASH namespace std {
#  define END_NAMESPACE_HASH }

# endif

# include "hash.h"

namespace Tanl {

template<class _Value,
	 class _Hash = hash<_Value>,
	 class _Pred = std::equal_to<_Value>,
	 class _Alloc = std::allocator<_Value>,
	 bool __cache_hash_code = false>
class unordered_set : public hash_set<_Value, _Hash, _Pred, _Alloc>
{
  typedef hash_set<_Value, _Hash, _Pred, _Alloc>  _Base;

public:
  typedef typename _Base::size_type       size_type;
  typedef typename _Base::hasher          hasher;
  typedef typename _Base::key_equal       key_equal;
  typedef typename _Base::allocator_type  allocator_type;

  explicit
      unordered_set(size_type __n = 10,
		    const hasher& __hf = hasher(),
		    const key_equal& __eql = key_equal(),
		    const allocator_type& __a = allocator_type())
      : _Base(__n, __hf, __eql, __a)
      { }

      template<typename _InputIterator>
        unordered_set(_InputIterator __f, _InputIterator __l, 
		      size_type __n = 10,
		      const hasher& __hf = hasher(), 
		      const key_equal& __eql = key_equal(), 
		      const allocator_type& __a = allocator_type())
	: _Base(__f, __l, __n, __hf, __eql, __a)
        { }
};

} // namespace Tanl

using Tanl::unordered_set;

#endif

#endif // IXE_include_unordered_set_H
