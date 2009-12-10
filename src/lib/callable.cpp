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

#include <myst/callable.h>
#include <myst/context.h>

namespace myst {

Callable::Callable(Class *klass, size_t nargs)
  : Object(klass), mArgCount(nargs) {
}

Callable::~Callable() {
}

Object* Callable::call(Context *ctx, Object *s) throw(Exception) {
  if (mArgCount != 0) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 0";
    throw CallError(oss.str());
  }
  ctx->push(s);
  call(ctx);
  if (ctx->stackSize() == 0) {
    // fall back to s?
    throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0) throw(Exception) {
  if (mArgCount != 1) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 1";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  call(ctx);
  if (ctx->stackSize() == 0) {
    // fall back to s?
    throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0,
                                                Object *o1) throw(Exception) {
  if (mArgCount != 2) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 2";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  ctx->push(o1);
  call(ctx);
  if (ctx->stackSize() == 0) {
    // fall back to s?
    throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0,
                                                Object *o1,
                                                Object *o2) throw(Exception) {
  if (mArgCount != 3) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 3";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  ctx->push(o1);
  ctx->push(o2);
  call(ctx);
  if (ctx->stackSize() == 0) {
    // fall back to s?
    throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0,
                                                Object *o1,
                                                Object *o2,
                                                Object *o3) throw(Exception) {
  if (mArgCount != 4) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 4";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  ctx->push(o1);
  ctx->push(o2);
  ctx->push(o3);
  call(ctx);
  if (ctx->stackSize() == 0) {
   // fall back to s?
   throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0,
                                                Object *o1,
                                                Object *o2,
                                                Object *o3,
                                                Object *o4) throw(Exception) {
  if (mArgCount != 5) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 5";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  ctx->push(o1);
  ctx->push(o2);
  ctx->push(o3);
  ctx->push(o4);
  call(ctx);
  if (ctx->stackSize() == 0) {
   // fall back to s?
   throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0,
                                                Object *o1,
                                                Object *o2,
                                                Object *o3,
                                                Object *o4,
                                                Object *o5) throw(Exception) {
  if (mArgCount != 6) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 6";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  ctx->push(o1);
  ctx->push(o2);
  ctx->push(o3);
  ctx->push(o4);
  ctx->push(o5);
  call(ctx);
  if (ctx->stackSize() == 0) {
   // fall back to s?
   throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0,
                                                Object *o1,
                                                Object *o2,
                                                Object *o3,
                                                Object *o4,
                                                Object *o5,
                                                Object *o6) throw(Exception) {
  if (mArgCount != 7) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 7";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  ctx->push(o1);
  ctx->push(o2);
  ctx->push(o3);
  ctx->push(o4);
  ctx->push(o5);
  ctx->push(o6);
  call(ctx);
  if (ctx->stackSize() == 0) {
   // fall back to s?
   throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, Object *o0,
                                                Object *o1,
                                                Object *o2,
                                                Object *o3,
                                                Object *o4,
                                                Object *o5,
                                                Object *o6,
                                                Object *o7) throw(Exception) {
  if (mArgCount != 8) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got 8";
    throw CallError(oss.str());
  }
  ctx->push(s);
  ctx->push(o0);
  ctx->push(o1);
  ctx->push(o2);
  ctx->push(o3);
  ctx->push(o4);
  ctx->push(o5);
  ctx->push(o6);
  ctx->push(o7);
  call(ctx);
  if (ctx->stackSize() == 0) {
   // fall back to s?
   throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

Object* Callable::call(Context *ctx, Object *s, size_t nargs,
                                                Object **args) throw(Exception) {
  if (mArgCount != nargs) {
    std::ostringstream oss;
    oss << "Invalid argument count, expected " << mArgCount << ", got " << nargs;
    throw CallError(oss.str());
  }
  ctx->push(s);
  for (size_t i=0; i<nargs; ++i) {
    ctx->push(args[i]);
  }
  call(ctx);
  if (ctx->stackSize() == 0) {
   // fall back to s?
   throw CallError("No return value");
  }
  Object *rv = ctx->at(-1);
  ctx->pop(1);
  return rv;
}

void Callable::call(Context *ctx) throw(Exception) {
  if (ctx->stackSize() < (mArgCount + 1)) {
    throw CallError("Not enough object on stack");
  }
}

}
