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

#ifndef __myst_creal_h_
#define __myst_creal_h_

#include <myst/class.h>
#include <myst/core/cobject.h>

namespace myst {
  
  class MYST_API RealClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void Add(Context *ctx, Long n) throw(Exception);
      static void Sub(Context *ctx, Long n) throw(Exception);
      static void Mult(Context *ctx, Long n) throw(Exception);
      static void Div(Context *ctx, Long n) throw(Exception);
      static void Abs(Context *ctx, Long n) throw(Exception);
      static void Neg(Context *ctx, Long n) throw(Exception);
      static void Pow(Context *ctx, Long n) throw(Exception);
      static void Log(Context *ctx, Long n) throw(Exception);
      static void Exp(Context *ctx, Long n) throw(Exception);
      static void Floor(Context *ctx, Long n) throw(Exception);
      static void Ceil(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void ToInt(Context *ctx, Long n) throw(Exception);
      static void ToReal(Context *ctx, Long n) throw(Exception);
      
    public:
      
      RealClass();
      virtual ~RealClass();
  };
  
  class MYST_API Real : public TObject<double> {
    public:
      Real(double val=0);
      virtual ~Real();
  };
  
}


#endif
