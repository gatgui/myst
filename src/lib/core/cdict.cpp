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

#include <myst/core/cdict.h>
#include <myst/core/cstring.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void DictClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new Dict());
}

void DictClass::ToStr(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new String("<dummy> DictInstance"));
}

DictClass::DictClass()
  : Class("Dict", cObject) {
  addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
}

DictClass::~DictClass() {
}

// ---

Dict::Dict()
  : TObject<std::map<std::string, Object*> >(cDict) {
}

Dict::~Dict() {
}

void Dict::mark() {
  TObject<std::map<std::string, Object*> >::mark();
  std::map<std::string, Object*>::iterator it = data.begin();
  while (it != data.end()) {
    it->second->mark();
    ++it;
  }
}

}
