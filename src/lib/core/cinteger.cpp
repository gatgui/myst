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

#include <myst/core/cinteger.h>
#include <myst/core/creal.h>
#include <myst/core/cstring.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void IntegerClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new Integer());
}

void IntegerClass::Add(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  ctx->pop(n);
  ctx->push(new Integer(i->data + oRhs->data));
}

void IntegerClass::Sub(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  ctx->pop(n);
  ctx->push(new Integer(i->data - oRhs->data));
}

void IntegerClass::Mult(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  ctx->pop(n);
  ctx->push(new Integer(i->data * oRhs->data));
}

void IntegerClass::Div(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  if (oRhs->data == 0) {
    throw ZeroDivisionError();
  }
  ctx->pop(n);
  ctx->push(new Integer(i->data / oRhs->data));
}

void IntegerClass::Modulo(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  if (oRhs->data == 0) {
    throw ZeroDivisionError();
  }
  ctx->pop(n);
  ctx->push(new Integer(i->data % oRhs->data));
}

void IntegerClass::LShift(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  ctx->pop(n);
  ctx->push(new Integer(i->data << oRhs->data));
}

void IntegerClass::RShift(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  ctx->pop(n);
  ctx->push(new Integer(i->data >> oRhs->data));
}

void IntegerClass::BitOr(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  ctx->pop(n);
  ctx->push(new Integer(i->data | oRhs->data));
}

void IntegerClass::BitAnd(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  Integer *oRhs = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  ctx->pop(n);
  ctx->push(new Integer(i->data & oRhs->data));
}

void IntegerClass::ToStr(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  std::ostringstream oss;
  oss << i->data;
  ctx->pop(n);
  ctx->push(new String(oss.str()));
}

void IntegerClass::ToInt(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  ctx->pop(n);
  ctx->push(self);
}

void IntegerClass::ToReal(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Real(double(i->data)));
}

void IntegerClass::Abs(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Integer(i->data < 0 ? -i->data : i->data));
}

void IntegerClass::Neg(Context *ctx, Long n) throw(Exception) {
  Integer *i = (Integer*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Integer(- i->data));
}

IntegerClass::IntegerClass()
  : Class("Integer", cObject) {
  addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("add:", 1, &Add));
  addInstanceMethod(new CMethod("+", 1, &Add));
  addInstanceMethod(new CMethod("sub:", 1, &Sub));
  addInstanceMethod(new CMethod("-", 1, &Sub));
  addInstanceMethod(new CMethod("times:", 1, &Mult));
  addInstanceMethod(new CMethod("*", 1, &Mult));
  addInstanceMethod(new CMethod("div:", 1, &Div));
  addInstanceMethod(new CMethod("/", 1, &Div));
  addInstanceMethod(new CMethod("modulo:", 1, &Modulo));
  addInstanceMethod(new CMethod("%", 1, &Modulo));
  addInstanceMethod(new CMethod("abs", 0, &Abs));
  addInstanceMethod(new CMethod("neg", 0, &Neg));
  addInstanceMethod(new CMethod("lshift:", 1, &LShift));
  addInstanceMethod(new CMethod("rshift:", 1, &RShift));
  addInstanceMethod(new CMethod("or:", 1, &BitOr));
  addInstanceMethod(new CMethod("|", 1, &BitOr));
  addInstanceMethod(new CMethod("and:", 1, &BitAnd));
  addInstanceMethod(new CMethod("&", 1, &BitAnd));
  addInstanceMethod(new CMethod("lshift:", 1, &LShift));
  addInstanceMethod(new CMethod("toReal", 0, &ToReal));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
  addInstanceMethod(new CMethod("toInt", 0, &ToInt));
  
}

IntegerClass::~IntegerClass() {
}

// ---

Integer::Integer(Long val)
  : TObject<Long>(cInteger) {
  data = val;
}

Integer::~Integer() {
}

}
