#include <myst/core/cclass.h>
#include <myst/core/cstring.h>
#include <myst/core/carray.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {
  
void ClassClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  String *oName = (String*) ctx->at(-n+1)->call(ctx, "toStr");
  ctx->pop(n);
  ctx->push(new Class(oName->data, cObject));
}

void ClassClass::NewUnder(Context *ctx, Long n) throw(Exception) {
  String *oName = (String*) ctx->at(-n+1)->call(ctx, "toStr");
  Object *oClass = ctx->at(-n+2);
  if (!oClass->isKindOf(cClass)) {
    throw ArgumentError("Expected a Class instance for under: argument");
  }
  ctx->pop(n);
  ctx->push(new Class(oName->data, (Class*) oClass));
}

void ClassClass::GetInstanceVariables(Context *ctx, Long n) throw(Exception) {
  Class *c = (Class *) ctx->at(-n);
  StringList names;
  c->instanceVariables(names);
  Array *ary = new Array(names.size());
  for (size_t i=0; i<names.size(); ++i) {
    ary->data[i] = new String(names[i]);
  }
  ctx->pop(n);
  ctx->push(ary);
}

void ClassClass::GetInstanceMethods(Context *ctx, Long n) throw(Exception) {
  Class *c = (Class *) ctx->at(-n);
  StringList names;
  c->instanceMethods(names);
  Array *ary = new Array(names.size());
  for (size_t i=0; i<names.size(); ++i) {
    ary->data[i] = new String(names[i]);
  }
  ctx->pop(n);
  ctx->push(ary);
}

void ClassClass::GetSuper(Context *ctx, Long n) throw(Exception) {
  Class *c = (Class *) ctx->at(-n);
  Class *s = c->super();
  ctx->pop(n);
  ctx->push(s == NULL ? oNil : s);
}

void ClassClass::Subclass(Context *ctx, Long n) throw(Exception) {
  Class *c = (Class *) ctx->at(-n);
  String *oName = (String*) ctx->at(-n+1)->call(ctx, "toStr");
  ctx->pop(n);
  ctx->push(c->subclass(oName->data));
}

void ClassClass::GetName(Context *ctx, Long n) throw(Exception) {
  Class *c = (Class*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new String(c->name()));
}

void ClassClass::ToStr(Context *ctx, Long n) throw(Exception) {
  Class *c = (Class *) ctx->at(-n);
  std::ostringstream oss;
  oss << "<Class: \"" << c->name() << "\">" << std::endl;
  ctx->pop(n);
  ctx->push(new String(oss.str()));
}

ClassClass::ClassClass()
  : Class("Class", cObject) {
  addMethod(new CMethod("new:", 1, &NewInstance));
  addMethod(new CMethod("new:under:", 2, &NewUnder));
  addInstanceMethod(new CMethod("instanceVariables", 0, &GetInstanceVariables));
  addInstanceMethod(new CMethod("instanceMethods", 0, &GetInstanceMethods));
  addInstanceMethod(new CMethod("super", 0, &GetSuper));
  addInstanceMethod(new CMethod("subclass:", 1, &Subclass));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
}

ClassClass::~ClassClass() {
}

}
