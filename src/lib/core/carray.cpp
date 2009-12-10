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

#include <myst/core/carray.h>
#include <myst/core/cstring.h>
#include <myst/core/cinteger.h>
#include <myst/method.h>
#include <myst/builtins.h>

namespace myst {

void ArrayClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new Array());
}

void ArrayClass::Includes(Context *ctx, Long n) throw(Exception) {
  Array *ary = (Array*) ctx->at(-n);
  Object *val = ctx->at(-n+1);
  ctx->pop(n);
  if (std::find(ary->data.begin(), ary->data.end(), val) != ary->data.end()) {
    ctx->push(oTrue);
  } else {
    ctx->push(oFalse);
  }
}

void ArrayClass::At(Context *ctx, Long n) throw(Exception) {
  Array *ary = (Array*) ctx->at(-n);
  Integer *oIdx = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  Long idx = oIdx->data;
  ctx->pop(n);
  bool error = false;
  if (idx < 0) {
    idx += Long(ary->data.size());
    if (idx < 0) {
      error = true;
    }
  } else if (size_t(idx) >= ary->data.size()) {
    error = true;
  }
  if (error) {
    std::ostringstream oss;
    oss << "Index out of bounds (" << idx << ")";
    throw IndexError(oss.str());
  }
  ctx->push(ary->data[size_t(idx)]);
}

void ArrayClass::Slice(Context *ctx, Long n) throw(Exception) {
  Array *ary = (Array*) ctx->at(-n);
  Long sz = Long(ary->data.size());
  if (sz <= 0) {
    ctx->pop(n);
    ctx->push(new Array());
    return;
  }
  Integer *oFrom = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  Integer *oTo = (Integer*) ctx->at(-n+2)->call(ctx, "toInt");
  Long from = oFrom->data;
  Long to = oTo->data;
  ctx->pop(n);
  if (from < 0) {
    from = sz + from;
    if (from < 0) {
      from = 0;
    }
  }
  if (to < 0) {
    from = sz + to;
    if (to < 0) {
      to = 0;
    }
  }
  if (from <= sz && from < to) {
    Long n = to - from;
    Array *sl = new Array(n);
    for (Long i=from, j=0; i<to; ++i, ++j) {
      sl->data[size_t(j)] = ary->data[size_t(i)];
    }
    ctx->push(sl);
  } else {
    ctx->push(new Array());
  }
}

void ArrayClass::Push(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  Array *ary = (Array*) self;
  Object *val = ctx->at(-n+1);
  ctx->pop(n);
  ary->data.push_back(val == NULL ? oNil : val);
  ctx->push(self);
}

void ArrayClass::Pop(Context *ctx, Long n) throw(Exception) {
  Array *ary = (Array*) ctx->at(-n);
  ctx->pop(n);
  if (ary->data.size() > 0) {
    Object *rv = ary->data.back();
    ary->data.pop_back();
    ctx->push(rv);
  } else {
    ctx->push(oNil);
  }
}

void ArrayClass::InsertAt(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  Object *val = ctx->at(-n+1);
  Integer *oPos = (Integer*) ctx->at(-n+2)->call(ctx, "toInt");
  Array *ary = (Array*) self;
  Long pos = oPos->data;
  ctx->pop(n);
  if (pos < 0) {
    pos += Long(ary->data.size());
    if (pos < 0) {
      pos = 0;
    }
  }
  ary->data.insert(ary->data.begin() + size_t(pos), val);
  ctx->push(self);
}

void ArrayClass::Clear(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  ctx->pop(n);
  Array *ary = (Array*) self;
  ary->data.clear();
  ctx->push(self);
}

void ArrayClass::ToStr(Context *ctx, Long n) throw(Exception) {
  Array *ary = (Array*) ctx->at(-n);
  ctx->pop(n);
  String *rv = new String("[");
  if (ary->data.size() > 0) {
    for (size_t i=0; i<(ary->data.size()-1); ++i) {
      String *es = (String*) ary->data[i]->call(ctx, "toStr");
      rv->data += es->data;
      rv->data += ", ";
    }
    String *es = (String*) ary->data.back()->call(ctx, "toStr");
    rv->data += es->data;
  }
  rv->data += "]";
  ctx->push(rv);
}

void ArrayClass::Length(Context *ctx, Long n) throw(Exception) {
  Array *ary = (Array*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Integer(ary->data.size()));
}

void ArrayClass::SetAt(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  Array *ary = (Array*) self;
  Object *val = ctx->at(-n+1);
  Integer *oIdx = (Integer*) ctx->at(-n+2)->call(ctx, "toInt");
  ctx->pop(n);
  Long idx = oIdx->data;
  if (idx < 0) {
    idx += Long(ary->data.size());
    if (idx < 0) {
      std::ostringstream oss;
      oss << "Index out of bounds (" << idx << ")";
      throw IndexError(oss.str());
    }
  }
  ary->data[size_t(idx)] = val;
  ctx->push(self);
}

//void ArrayClass::ForEach(Context *ctx, Long n) {
//}

ArrayClass::ArrayClass()
  : Class("Array", cObject) {
  addMethod(new CMethod("new", 0, ArrayClass::NewInstance));
  addInstanceMethod(new CMethod("includes:", 1, ArrayClass::Includes));
  addInstanceMethod(new CMethod("at:", 1, ArrayClass::At));
  addInstanceMethod(new CMethod("@", 1, ArrayClass::At));
  addInstanceMethod(new CMethod("sliceFrom:to:", 2, ArrayClass::Slice));
  addInstanceMethod(new CMethod("push:", 1, ArrayClass::Push));
  addInstanceMethod(new CMethod("pop", 0, ArrayClass::Pop));
  addInstanceMethod(new CMethod("insert:at:", 2, ArrayClass::InsertAt));
  addInstanceMethod(new CMethod("clear", 0, ArrayClass::Clear));
  addInstanceMethod(new CMethod("toStr", 0, ArrayClass::ToStr));
  addInstanceMethod(new CMethod("length", 0, ArrayClass::Length));
  addInstanceMethod(new CMethod("set:at:", 2, ArrayClass::SetAt));
  //addInstanceMethod(new CMethod("forEach", 1, ArrayClass::ForEach);
}

ArrayClass::~ArrayClass() {
}

// ---

Array::Array(Long len)
  : TObject<std::vector<Object*> >(cArray) {
  data.resize(size_t(len), oNil);
}

Array::Array(const std::vector<Object*> &rhs)
  : TObject<std::vector<Object*> >(cArray) {
  data = rhs;
}

Array::~Array() {
  data.clear();
}

void Array::mark() {
  TObject<std::vector<Object*> >::mark();
  for (size_t i=0; i<data.size(); ++i) {
    data[i]->mark();
  }
}

}
