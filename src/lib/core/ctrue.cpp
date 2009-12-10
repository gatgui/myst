#include <myst/core/ctrue.h>
#include <myst/core/cstring.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void TrueClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  Class *klass = (Class*) ctx->at(-n);
  static Object *sInstance = klass->newInstance();
  ctx->pop(n);
  ctx->push(sInstance);
}

void TrueClass::ToStr(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new String("true"));
}

TrueClass::TrueClass()
  : Class("True", cObject) {
  addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
}

TrueClass::~TrueClass() {
}

}

