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

#include <myst/core/cmethod.h>
#include <myst/core/cstring.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void MethodClass::Name(Context *ctx, Long n) throw(Exception) {
  Method *m = (Method*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new String(m->name()));
}

MethodClass::MethodClass()
  : Class("Method", cCallable) {
  addInstanceMethod(new CMethod("name", 0, &Name));
}

MethodClass::~MethodClass() {
}

}
