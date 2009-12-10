#include <myst/method.h>
#include <myst/builtins.h>

namespace myst {

// class should be set to myst::builtins::cMethod
// and this should wrap up things properly
// yield: arg0
// yield: (arg0, arg1)

Method::Method(const std::string &name, size_t nargs)
  : Callable(cMethod, nargs), mName(name) {
}

Method::~Method() {
}

// ---

CMethod::CMethod(const std::string &name, size_t nargs,
                 CMethod::Pointer ptr)
  : Method(name, nargs), mPtr(ptr) {
}

CMethod::~CMethod() {
}

void CMethod::call(Context *ctx) throw(Exception) {
  Method::call(ctx);
  (*mPtr)(ctx, argCount()+1);
}

// ---

GetVarMethod::GetVarMethod(const std::string &varName)
  : Method(varName, 0) {
}

GetVarMethod::~GetVarMethod() {
}

void GetVarMethod::call(Context *ctx) throw(Exception) {
  Method::call(ctx); // raise exception if insufficient objects on stack
  Object *self = ctx->at(-1);
  ctx->pop(1);
  ctx->push(self->getVar(name()));
}

// ---

SetVarMethod::SetVarMethod(const std::string &varName)
  : Method(varName+":", 1), mVarName(varName) {
}

SetVarMethod::~SetVarMethod() {
}

void SetVarMethod::call(Context *ctx) throw(Exception) {
  Method::call(ctx);
  Object *self = ctx->at(-2);
  Object *val = ctx->at(-1);
  ctx->pop(2);
  self->setVar(mVarName, val);
  // return self? or val?
  ctx->push(self);
}

}
