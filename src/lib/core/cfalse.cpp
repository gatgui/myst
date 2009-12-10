#include <myst/core/cfalse.h>
#include <myst/core/cstring.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void FalseClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  Class *klass = (Class*) ctx->at(-n);
  static Object *sInstance = klass->newInstance();
  ctx->pop(n);
  ctx->push(sInstance);
}

void FalseClass::ToStr(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new String("false"));
}

FalseClass::FalseClass()
  : Class("False", cObject) {
  addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
}

FalseClass::~FalseClass() {
}

}
