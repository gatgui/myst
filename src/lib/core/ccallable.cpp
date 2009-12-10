#include <myst/core/ccallable.h>
#include <myst/core/cinteger.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void CallableClass::ArgCount(Context *ctx, Long n) throw(Exception) {
  Callable *c = (Callable*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Integer(c->argCount()));
}

CallableClass::CallableClass()
  : Class("Callable", cObject) {
  addInstanceMethod(new CMethod("argCount", 0, &ArgCount));
}

CallableClass::~CallableClass() {
}

}
