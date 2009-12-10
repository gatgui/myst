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

#include <myst/block.h>
#include <myst/context.h>
#include <myst/builtins.h>

namespace myst {

Block::Block(Context *, size_t nargs)
  : Callable(cBlock, nargs) {
  mArgNames.resize(nargs);
}

Block::~Block() {
}

void Block::setArgName(size_t idx, const std::string &str) {
  if (idx < argCount()) {
    mArgNames[idx] = str;
  }
}

void Block::addBlockTemp(const std::string &str) {
  if (std::find(mBlockTemp.begin(), mBlockTemp.end(), str) == mBlockTemp.end()) {
    mBlockTemp.push_back(str);
  }
}

void Block::call(Context *ctx) throw(Exception) {
  Context local(ctx);
  // there's not necessarily a self, this is true only for block
  // that defines methods
  Long iarg = - Long(argCount());
  for (size_t i=0; i<argCount(); ++i) {
    if (mArgNames[i].length() == 0) {
      throw CallError("Block arguments must all be named");
    }
    local.set(mArgNames[i], ctx->at(iarg));
    ++iarg;
  }
  for (size_t i=0; i<mBlockTemp.size(); ++i) {
    local.set(mBlockTemp[i], oNil);
  }
  mCode.exec(&local);
}

}
