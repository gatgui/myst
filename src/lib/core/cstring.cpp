#include <myst/core/cstring.h>
#include <myst/core/cinteger.h>
#include <myst/core/creal.h>
#include <myst/builtins.h>
#include <myst/method.h>

namespace myst {

void StringClass::NewInstance(Context *ctx, Long n) throw(Exception) {
  ctx->pop(n);
  ctx->push(new String());
}

void StringClass::Length(Context *ctx, Long n) throw(Exception) {
  String *s = (String*) ctx->at(-n);
  ctx->pop(n);
  ctx->push(new Integer(Long(s->data.length())));
}

void StringClass::Concat(Context *ctx, Long n) throw(Exception) {
  String *s = (String*) ctx->at(-n);
  String *rhs = (String*) ctx->at(-n+1)->call(ctx, "toStr");
  ctx->pop(n);
  ctx->push(new String(s->data + rhs->data));
}

void StringClass::At(Context *ctx, Long n) throw(Exception) {
  String *s = (String*) ctx->at(-n);
  Integer *oIdx = (Integer*) ctx->at(-n+1)->call(ctx, "toInt");
  Long idx = oIdx->data;
  if (idx < 0) {
    idx += Long(s->data.length());
    if (idx < 0) {
      std::ostringstream oss;
      oss << "Index out of bounds: " << idx;
      throw IndexError(oss.str());
    }
  }
  ctx->pop(n);
  ctx->push(new String(s->data.substr(size_t(idx), 1)));
}

void StringClass::SetAt(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  String *s = (String*) self;
  String *val = (String*) ctx->at(-n+1)->call(ctx, "toStr");
  Integer *oIdx = (Integer*) ctx->at(-n+2)->call(ctx, "toInt");
  Long idx = oIdx->data;
  if (idx < 0) {
    idx += Long(s->data.length());
    if (idx < 0) {
      std::ostringstream oss;
      oss << "Index out of bounds: " << idx;
      throw IndexError(oss.str());
    }
  }
  s->data[size_t(idx)] = val->data[0];
  ctx->pop(n);
  ctx->push(self);
}

void StringClass::ToStr(Context *ctx, Long n) throw(Exception) {
  Object *self = ctx->at(-n);
  ctx->pop(n);
  ctx->push(self);
}

void StringClass::ToInt(Context *ctx, Long n) throw(Exception) {
  String *s = (String*) ctx->at(-n);
  Long val;
  #if LONG_IS_64BITS == 1
  if (sscanf(s->data.c_str(), "%ld", &val) != 1) {
  #else
  if (sscanf(s->data.c_str(), "%lld", &val) != 1) {
  #endif
    throw Exception("String is not convertible to Integer");
  }
  ctx->pop(n);
  ctx->push(new Integer(val));
}

void StringClass::ToReal(Context *ctx, Long n) throw(Exception) {
  String *s = (String*) ctx->at(-n);
  double val;
  if (sscanf(s->data.c_str(), "%lf", &val) != 1) {
    throw Exception("String is not convertible to Real");
  }
  ctx->pop(n);
  ctx->push(new Real(val));
}

StringClass::StringClass()
  : Class("String", cObject) {
  addMethod(new CMethod("new", 0, &NewInstance));
  addInstanceMethod(new CMethod("concat:", 1, &Concat));
  addInstanceMethod(new CMethod("+", 1, &Concat));
  addInstanceMethod(new CMethod("length", 0, &Length));
  addInstanceMethod(new CMethod("at:", 1, &At));
  addInstanceMethod(new CMethod("@", 1, &At));
  addInstanceMethod(new CMethod("set:at:", 2, &SetAt));
  addInstanceMethod(new CMethod("toStr", 0, &ToStr));
  addInstanceMethod(new CMethod("toInt", 0, &ToInt));
  addInstanceMethod(new CMethod("toReal", 0, &ToReal));
}

StringClass::~StringClass() {
}

// ---

String::String()
  : TObject<std::string>(cString) {
}

String::String(const std::string &str)
  : TObject<std::string>(cString) {
  data = str;
}

String::~String() {
}

}

