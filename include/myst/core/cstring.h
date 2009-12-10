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

#ifndef __myst_cstring_h_
#define __myst_cstring_h_

#include <myst/class.h>
#include <myst/core/cobject.h>

namespace myst {
  
  class MYST_API StringClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void Length(Context *ctx, Long n) throw(Exception);
      static void Concat(Context *ctx, Long n) throw(Exception);
      static void At(Context *ctx, Long n) throw(Exception);
      static void SetAt(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void ToInt(Context *ctx, Long n) throw(Exception);
      static void ToReal(Context *ctx, Long n) throw(Exception);
      
    public:
      StringClass();
      virtual ~StringClass();
  };
  
  class MYST_API String : public TObject<std::string> {
    public:
      String();
      String(const std::string &str);
      virtual ~String();
  };
}

#endif
