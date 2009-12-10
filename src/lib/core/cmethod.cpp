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
