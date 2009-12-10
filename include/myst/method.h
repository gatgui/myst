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

#ifndef __myst_method_h_
#define __myst_method_h_

#include <myst/exceptions.h>
#include <myst/callable.h>

namespace myst {
  
  
  class MYST_API Method : public Callable {
    public:
      
      Method(const std::string &name, size_t nargs);
      virtual ~Method();
      
      inline const std::string& name() {
        return mName;
      }
      
    protected:
      
      std::string mName;
  };
  
  class MYST_API CMethod : public Method {
    public:
      
      //typedef Object* (*Pointer)(Object *, size_t, Object **);
      typedef void (*Pointer)(Context *, Long n);
      
    public:
      
      CMethod(const std::string &name, size_t nargs, Pointer ptr);
      virtual ~CMethod();
      
      //virtual Object* call(Object *self,
      //                     size_t n, Object **args) throw(Exception);
      virtual void call(Context *ctx) throw(Exception);
      
    protected:
      
      Pointer mPtr;
  };
  
  class MYST_API GetVarMethod : public Method {
    public:
      
      GetVarMethod(const std::string &varName);
      virtual ~GetVarMethod();
      
      //virtual Object* call(Object *self,
      //                     size_t n, Object **args) throw(Exception);
      virtual void call(Context *ctx) throw(Exception);
  };
  
  class MYST_API SetVarMethod : public Method {
    public:
      
      SetVarMethod(const std::string &varName);
      virtual ~SetVarMethod();
      
      //virtual Object* call(Object *self,
      //                     size_t n, Object **args) throw(Exception);
      virtual void call(Context *ctx) throw(Exception);
    
    protected:
      std::string mVarName;
  };
  
}

#endif
