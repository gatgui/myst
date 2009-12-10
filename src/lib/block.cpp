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
