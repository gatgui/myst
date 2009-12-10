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

#ifndef __myst_callable_h_
#define __myst_callable_h_

#include <myst/object.h>

namespace myst {
  
  class MYST_API Context;
  
  class MYST_API Callable : public Object {
    public:
      
      typedef std::map<std::string, Callable*> Map;
      typedef Map::iterator Iterator;
      typedef Map::const_iterator ConstIterator;
      
    public:
      
      Callable(Class *klass, size_t nargs);
      virtual ~Callable();
      
      inline size_t argCount() {
        return mArgCount;
      }
      
      Object* call(Context *ctx, Object *s) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4,
                                            Object *o5) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4,
                                            Object *o5,
                                            Object *o6) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4,
                                            Object *o5,
                                            Object *o6,
                                            Object *o7) throw(Exception);
      
      Object* call(Context *ctx, Object *s, size_t nargs, Object **args) throw(Exception);
      
      // after call, all arguments should have been popped off the stack
      // and the return value pushed on
      virtual void call(Context *ctx) throw(Exception) = 0;
      
      
    protected:
      
      size_t mArgCount;
  };
  
}


#endif
