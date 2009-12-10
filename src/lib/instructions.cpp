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

#include <myst/instructions.h>
#include <myst/builtins.h>
#include <myst/context.h>
#include <myst/callable.h>
#include <myst/core/cinteger.h>
#include <myst/core/cstring.h>
#include <myst/core/creal.h>
#include <myst/core/ctrue.h>
#include <myst/core/cfalse.h>
#include <myst/core/cnil.h>

namespace myst {

Instruction::Instruction() {
}

Instruction::~Instruction() {
}

// ---

InstructionList::InstructionList() {
}

InstructionList::~InstructionList() {
  for (size_t i=0; i<size(); ++i) {
    delete (*this)[i];
  }
}

void InstructionList::exec(Context *ctx) throw(Exception) {
  for (size_t i=0; i<size(); ++i) {
    (*this)[i]->exec(ctx);
  }
}

// ---

Call::Call(const std::string &sel, size_t nargs)
  : Instruction(), mSel(sel), mArgCount(nargs) {
}

Call::~Call() {
}

void Call::exec(Context *ctx) throw(Exception) {
  if (ctx->stackSize() < (mArgCount + 1)) {
    throw CallError("Not enough objects on stack for Call");
  }
  Object *recv = ctx->at(-(Long(mArgCount)+1));
  Callable *meth = recv->method(mSel);
  if (meth->argCount() != mArgCount) {
    throw CallError("Argument count mismatch");
  }
  meth->call(ctx);
}

// ---

PushInt::PushInt(Long val)
  : Instruction(), mVal(val) {
}

PushInt::~PushInt() {
}

void PushInt::exec(Context *ctx) throw(Exception) {
  ctx->push(new Integer(mVal));
}

// ---

PushReal::PushReal(double val)
  : Instruction(), mVal(val) {
}

PushReal::~PushReal() {
}

void PushReal::exec(Context *ctx) throw(Exception) {
  ctx->push(new Real(mVal));
}

// ---

PushString::PushString(const std::string &val)
  : Instruction(), mVal(val) {
}

PushString::~PushString() {
}

void PushString::exec(Context *ctx) throw(Exception) {
  ctx->push(new String(mVal));
}

// ---

PushBool::PushBool(bool val)
  : Instruction(), mVal(val) {
}

PushBool::~PushBool() {
}

void PushBool::exec(Context *ctx) throw(Exception) {
  ctx->push(mVal ? oTrue : oFalse);
}

// ---

SetVar::SetVar(const std::string &name)
  : Instruction(), mName(name) {
}

SetVar::~SetVar() {
}

void SetVar::exec(Context *ctx) throw(Exception) {
  if (ctx->stackSize() == 0) {
    throw Exception("No variable on stack");
  }
  ctx->set(mName, ctx->at(-1));
  ctx->pop(1);
}

// ---

GetVar::GetVar(const std::string &name)
  : Instruction(), mName(name) {
}

GetVar::~GetVar() {
}

void GetVar::exec(Context *ctx) throw(Exception) {
  ctx->push(ctx->get(mName));
}

}
