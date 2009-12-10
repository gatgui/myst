#include <myst/core/cobject.h>
#include <myst/core/cstring.h>
#include <myst/core/carray.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {
  
//void ObjectClass::NewInstance(Context *ctx, Long n) throw(Exception) {
//  Class *klass = (Class*) ctx->at(-n);
//  ctx->pop(n);
//  ctx->push(klass->newInstance());
//}

void ObjectClass::IsKindOf(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  Object *oClass = ctx->at(-n+1);
  if (!oClass->isKindOf(cClass)) {
    throw TypeError("Expected a Class instance");
  }
  ctx->pop(n);
  ctx->push(self->isKindOf((Class*) oClass) ? oTrue : oFalse);
}

void ObjectClass::IsA(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  Object *oClass = ctx->at(-n+1);
  if (!oClass->isKindOf(cClass)) {
    throw TypeError("Expected a Class instance");
  }
  ctx->pop(n);
  ctx->push(self->isA((Class*) oClass) ? oTrue : oFalse);
}

void ObjectClass::RespondsTo(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  String *s = (String*) ctx->at(-n+1)->call(ctx, "toStr");
  ctx->pop(n);
  ctx->push(self->respondsTo(s->data) ? oTrue : oFalse);
}

void ObjectClass::GetVariables(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  StringList names;
  self->variables(names);
  Array *ary = new Array(names.size());
  for (size_t i=0; i<names.size(); ++i) {
    ary->data[i] = new String(names[i]);
  }
  ctx->pop(n);
  ctx->push(ary);
}

void ObjectClass::GetMethods(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  StringList names;
  self->methods(names);
  Array *ary = new Array(names.size());
  for (size_t i=0; i<names.size(); ++i) {
    ary->data[i] = new String(names[i]);
  }
  ctx->pop(n);
  ctx->push(ary);
}

void ObjectClass::GetClass(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  ctx->pop(n);
  ctx->push(self->klass());
}

void ObjectClass::ToStr(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  std::ostringstream oss;
  oss << "<"  << self->klass()->name() << ": 0x" << std::hex << (void*)self << std::dec << ">";
  ctx->pop(n);
  ctx->push(new String(oss.str()));
}

void ObjectClass::Print(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  ctx->pop(n);
  String *s = (String*) self->call(ctx, "toStr");
  std::cout << s->data << std::endl;
  ctx->push(self);
}

void ObjectClass::IsNil(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(oFalse);
}

ObjectClass::ObjectClass()
  : Class("Object", NULL) {
  //addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("isKindOf:", 1, &IsKindOf));
  addInstanceMethod(new CMethod("isA:", 1, &IsA));
  addInstanceMethod(new CMethod("respondsTo:", 1, &RespondsTo));
  addInstanceMethod(new CMethod("variables", 0, &GetVariables));
  addInstanceMethod(new CMethod("methods", 0, &GetMethods));
  addInstanceMethod(new CMethod("class", 0, &GetClass));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
  addInstanceMethod(new CMethod("isNil", 0, &IsNil));
  addInstanceMethod(new CMethod("print", 0, &Print));
  //addInstanceMethod(new CMethod("hash", 0, &Hash));
}

ObjectClass::~ObjectClass() {
}

}

