/*

Copyright (C) 2009  Gaetan Guidet

This file is part of myst.

myst is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

myst is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

#ifndef __myst_config_h_
#define __myst_config_h_

#ifdef _WIN32
# ifdef MYST_BUILD
#   define MYST_API __declspec(dllexport)
# else
#   define MYST_API __declspec(dllimport)
# endif
#else
# define MYST_API
#endif

#define MYST_DATA_API extern MYST_API

#ifdef _MSC_VER
  // removes visual studio compiler annoying warning about template classes
  // not having dll-interfaces
# pragma warning(disable: 4251 4275)
  // removes another annoying warning because of non supported exception
  // specifications
# pragma warning(disable: 4290)
#endif

#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>

namespace myst {
  
  typedef std::vector<std::string> StringList;
  typedef StringList::iterator StringListIterator;
  typedef StringList::const_iterator StringListConstIterator;
  
#if defined(__LP64__) || defined(_LP64) || (_MIPS_SZLONG == 64) || (__WORDSIZE == 64)
  typedef long Long;
  #define LONG_IS_64BITS 1
#elif defined(_MSC_VER) || (defined(__BCPLUSPLUS__) && __BORLANDC__ > 0x500) || defined(__WATCOM_INT64__)
  typedef __int64 Long;
  #define LONG_IS_64BITS 0
#elif defined(__GNUG__) || defined(__GNUC__) || defined(__SUNPRO_CC) || defined(__MWERKS__) || defined(__SC__) || defined(_LONGLONG)
  typedef long long Long;
  #define LONG_IS_64BITS 0
#else
#error "Integer not defined for this architecture!"
#endif

}

#endif
