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
