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

#ifndef __myst_object_h_
#define __myst_object_h_

#include <myst/exceptions.h>

namespace myst {
  
  class MYST_API Class;
  class MYST_API Callable;
  class MYST_API Method;
  class MYST_API Context;
  
  class MYST_API Object {
    
    // Object tracking (and garbage collection then maybe?)
    // For now, do it dumb, this will blow the memory in the long term
    
    private:
      
      static std::vector<Object*> msAllObjects;
      
    public:
      
      static void ClearMarks();
      static size_t Sweep();
      static size_t AllocatedCount();
      
    public:
      
      typedef std::map<std::string, Object*> Map;
      typedef Map::iterator Iterator;
      typedef Map::const_iterator ConstIterator;
      
      Object(Class *klass);
      virtual ~Object();
      
      void initialize();
      
      void setVar(const std::string &name, Object *o);
      Object* getVar(const std::string &name) throw(Exception);
      
      void addMethod(const std::string &name, Callable *m);
      void addMethod(Method *m);
      Callable* method(const std::string &name) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0,
                                                       Object *o1) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0,
                                                       Object *o1,
                                                       Object *o2) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0,
                                                       Object *o1,
                                                       Object *o2,
                                                       Object *o3) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0,
                                                       Object *o1,
                                                       Object *o2,
                                                       Object *o3,
                                                       Object *o4) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0,
                                                       Object *o1,
                                                       Object *o2,
                                                       Object *o3,
                                                       Object *o4,
                                                       Object *o5) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0,
                                                       Object *o1,
                                                       Object *o2,
                                                       Object *o3,
                                                       Object *o4,
                                                       Object *o5,
                                                       Object *o6) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n, Object *o0,
                                                       Object *o1,
                                                       Object *o2,
                                                       Object *o3,
                                                       Object *o4,
                                                       Object *o5,
                                                       Object *o6,
                                                       Object *o7) throw(Exception);
      
      Object* call(Context *ctx, const std::string &n,
                   size_t nargs, Object **args) throw(Exception);
      
      inline Class* klass() {
        return mClass;
      }
      
      bool isKindOf(Class *);
      bool isA(Class *);
      bool respondsTo(const std::string &);
      size_t methods(StringList &names);
      size_t variables(StringList &names);
      
      inline void clearMark() {
        mMark = false;
      }
      
      inline bool isMarked() {
        return mMark;
      }
      
      virtual void mark();
      
      friend class MYST_API Class;
      
    protected:
      
      Class *mClass;
      std::map<std::string, Callable*> mMethods;
      Object::Map mVars;
      bool mMark;
  };
  
}

#endif

