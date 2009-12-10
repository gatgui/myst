#include <myst/core/cnil.h>
#include <myst/core/cstring.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void NilClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  Class *klass = (Class*) ctx->at(-n);
  static Object *sInstance = klass->newInstance();
  ctx->pop(n);
  ctx->push(sInstance);
}

void NilClass::ToStr(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new String("nil"));
}

void NilClass::IsNil(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(oTrue);
}

NilClass::NilClass()
  : Class("Nil", cObject) {
  addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
  addInstanceMethod(new CMethod("isNil", 0, &IsNil));
}

NilClass::~NilClass() {
}

}
