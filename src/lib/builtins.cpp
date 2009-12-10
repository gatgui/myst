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

#include <myst/builtins.h>
#include <myst/object.h>
#include <myst/class.h>

#include <myst/core/cobject.h>
#include <myst/core/cclass.h>
#include <myst/core/cinteger.h>
#include <myst/core/creal.h>
#include <myst/core/cstring.h>
#include <myst/core/carray.h>
#include <myst/core/cdict.h>
#include <myst/core/ctrue.h>
#include <myst/core/cfalse.h>
#include <myst/core/cnil.h>
#include <myst/core/ccallable.h>
#include <myst/core/cmethod.h>

namespace myst {

Object *oNil = 0;
Object *oTrue = 0;
Object *oFalse = 0;

Class *cObject = 0;
Class *cClass = 0;
Class *cInteger = 0;
Class *cReal = 0;
Class *cString = 0;
Class *cArray = 0;
Class *cDict = 0;
Class *cTrue = 0;
Class *cFalse = 0;
Class *cNil = 0;
Class *cCallable = 0;
Class *cMethod = 0;
Class *cBlock = 0;

Context* Initialize() {
  
  Context *ctx = new Context();
  
  // ObjectClass requires cClass to be defined
  // cClass is an instance of ClassClass
  // ClassClass needs cObject to be defined
  // ClassClass also needs cClass to be defined
  // -> circularity
  // 
  // Same problem with cCallable and cMethod
  // But cMethod is used for each object method created...
  // (including the one in cCallable)
  
  if (!cObject) {
    cObject = new ObjectClass();
  }
  ctx->set("Object", cObject);
  
  if (!cClass) {
    cClass = new ClassClass();
  }
  ctx->set("Class", cClass);
  
  if (!cCallable) {
    cCallable = new CallableClass();
  }
  ctx->set("Callable", cCallable);
  
  if (!cMethod) {
    cMethod = new MethodClass();
  }
  ctx->set("Method", cMethod);
  
  //if (!cBlock) {
  //  cBlock = new BlockClass();
  //}
  //ctx->set("Block", cBlock);
  
  //// Bootstrap to get out of the cicrularity problem exposed above
  //cObject->mClass = cClass;
  //cClass->mClass = cClass;
  
  // all methods created in cObject, cClass, cCallable and cMethods
  // needs to be bootstrapped also
  // because cCallable and cMethods where still == 0 at that time
  cObject->_fixClass();
  cClass->_fixClass();
  cObject->_fixAllMethodsClass();
  cClass->_fixAllMethodsClass();
  cCallable->_fixAllMethodsClass();
  cMethod->_fixAllMethodsClass();
  
  if (!cTrue) {
    cTrue = new TrueClass();
  }
  ctx->set("True", cTrue);
  if (!oTrue) {
    oTrue = cTrue->newInstance();
  }
  ctx->set("true", oTrue);
  
  if (!cFalse) {
    cFalse = new FalseClass();
  }
  ctx->set("False", cFalse);
  if (!oFalse) {
    oFalse = cFalse->newInstance();
  }
  ctx->set("false", oFalse);
  
  if (!cNil) {
    cNil = new NilClass();
  }
  ctx->set("Nil", cNil);
  if (!oNil) {
    oNil = cNil->newInstance();
  }
  ctx->set("nil", oNil);
  
  if (!cInteger) {
    cInteger = new IntegerClass();
  }
  ctx->set("Integer", cInteger);
  
  if (!cReal) {
    cReal = new RealClass();
  }
  ctx->set("Real", cReal);
  
  if (!cString) {
    cString = new StringClass();
  }
  ctx->set("String", cString);
  
  if (!cArray) {
    cArray = new ArrayClass();
  }
  ctx->set("Array", cArray);
  
  if (!cDict) {
    cDict = new DictClass();
  }
  ctx->set("Dict", cDict);
  
  return ctx;
}

}

