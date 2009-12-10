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

#include <myst/core/creal.h>
#include <myst/core/cinteger.h>
#include <myst/core/cstring.h>
#include <myst/builtins.h>
#include <myst/method.h>
#include <cmath>

namespace myst {

void RealClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new Real());
}

void RealClass::Add(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  Real *oRhs = (Real*) ctx->at(-n+1)->call(ctx, "toReal");
  ctx->pop(n);
  ctx->push(new Real(r->data + oRhs->data));
}

void RealClass::Sub(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  Real *oRhs = (Real*) ctx->at(-n+1)->call(ctx, "toReal");
  ctx->pop(n);
  ctx->push(new Real(r->data - oRhs->data));
}

void RealClass::Mult(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  Real *oRhs = (Real*) ctx->at(-n+1)->call(ctx, "toReal");
  ctx->pop(n);
  ctx->push(new Real(r->data * oRhs->data));
}

void RealClass::Div(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  Real *oRhs = (Real*) ctx->at(-n+1)->call(ctx, "toReal");
  // what about the precision?
  if (oRhs->data > -0.000001 && oRhs->data < 0.000001) {
    throw ZeroDivisionError();
  }
  ctx->pop(n);
  ctx->push(new Real(r->data / oRhs->data));
}

void RealClass::Abs(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Real(r->data < 0 ? -r->data : r->data));
}

void RealClass::Neg(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Real(- r->data));
}

void RealClass::Pow(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  Real *oRhs = (Real*) ctx->at(-n+1)->call(ctx, "toReal");
  ctx->pop(n);
  ctx->push(new Real(pow(r->data, oRhs->data)));
}

void RealClass::Log(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Real(log(r->data)));
}

void RealClass::Exp(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Real(exp(r->data)));
}

void RealClass::Floor(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Real(floor(r->data)));
}

void RealClass::Ceil(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Real(ceil(r->data)));
}

void RealClass::ToStr(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  std::ostringstream oss;
  oss << r->data;
  ctx->pop(n);
  ctx->push(new String(oss.str()));
}

void RealClass::ToInt(Context *ctx, Long n) throw(Exception) {
  Real *r = (Real*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Integer(Long(r->data)));
}

void RealClass::ToReal(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  ctx->pop(n);
  ctx->push(self);
}


RealClass::RealClass()
  : Class("Real", cObject) {
  addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("toReal", 0, &ToReal));
  addInstanceMethod(new CMethod("toInt", 0, &ToInt));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
  addInstanceMethod(new CMethod("ceil", 0, &Ceil));
  addInstanceMethod(new CMethod("floor", 0, &Floor));
  addInstanceMethod(new CMethod("exp", 0, &Exp));
  addInstanceMethod(new CMethod("log", 0, &Log));
  addInstanceMethod(new CMethod("pow:", 1, &Pow));
  addInstanceMethod(new CMethod("^", 1, &Pow));
  addInstanceMethod(new CMethod("neg", 0, &Neg));
  addInstanceMethod(new CMethod("abs", 0, &Abs));
  addInstanceMethod(new CMethod("add:", 1, &Add));
  addInstanceMethod(new CMethod("+", 1, &Add));
  addInstanceMethod(new CMethod("sub:", 1, &Sub));
  addInstanceMethod(new CMethod("-", 1, &Sub));
  addInstanceMethod(new CMethod("times:", 1, &Mult));
  addInstanceMethod(new CMethod("*", 1, &Mult));
  addInstanceMethod(new CMethod("div:", 1, &Div));
  addInstanceMethod(new CMethod("/", 1, &Div));
}

RealClass::~RealClass() {
}

// ---

Real::Real(double val)
  : TObject<double>(cReal) {
  data = val;
}

Real::~Real() {
}

}

