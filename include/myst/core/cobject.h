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

#ifndef __myst_cobject_h_
#define __myst_cobject_h_

#include <myst/class.h>

namespace myst {
  
  class MYST_API ObjectClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void IsKindOf(Context *ctx, Long n) throw(Exception);
      static void IsA(Context *ctx, Long n) throw(Exception);
      static void RespondsTo(Context *ctx, Long n) throw(Exception);
      static void GetVariables(Context *ctx, Long n) throw(Exception);
      static void GetMethods(Context *ctx, Long n) throw(Exception);
      static void GetClass(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void IsNil(Context *ctx, Long n) throw(Exception);
      static void Print(Context *ctx, Long n) throw(Exception);
      //static void Hash(Context *ctx, Long n) throw(Exception);
      //static void Equals(Context *ctx, Long n) throw(Exception);
      
    public:
      
      ObjectClass();
      virtual ~ObjectClass();
  };
  
  template <typename T>
  class TObject : public Object {
    public:
      
      TObject(Class *klass)
        : Object(klass) {
      }
      
      virtual ~TObject() {
      }
      
      T data;
  };
}

#endif

