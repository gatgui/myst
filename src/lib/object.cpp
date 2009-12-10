#include <myst/object.h>
#include <myst/class.h>
#include <myst/method.h>
#include <myst/builtins.h>
#include <myst/context.h>
#include <set>

namespace myst {

void Object::ClearMarks() {
  for (size_t i=0; i<msAllObjects.size(); ++i) {
    msAllObjects[i]->clearMark();
  }
}

size_t Object::Sweep() {
  std::vector<Object*> remainings(msAllObjects.size(), NULL);
  
  size_t cnt = 0;
  size_t j = 0;
  
  for (size_t i=0; i<msAllObjects.size(); ++i) {
    if (!msAllObjects[i]->isMarked()) {
      cnt += 1;
      delete msAllObjects[i];
      
    } else {
      remainings[j] = msAllObjects[i];
      ++j;
    }
  }
  
  remainings.resize(j);
  std::swap(remainings, msAllObjects);
  
  return cnt;
}

size_t Object::AllocatedCount() {
  return msAllObjects.size();
}

// ---

std::vector<Object*> Object::msAllObjects;

Object::Object(Class *klass)
  : mClass(klass), mMark(false) {
  msAllObjects.push_back(this);
  initialize();
}

Object::~Object() {
}

void Object::initialize() {
  if (mClass) {
    mClass->populateInstanceVars(this);
  }
}

void Object::mark() {
  if (mMark == true) {
    // already marked
    return;
  }
  mMark = true;
  Object::Iterator vit = mVars.begin();
  while (vit != mVars.end()) {
    vit->second->mark();
    ++vit;
  }
  Callable::Iterator mit = mMethods.begin();
  while (mit != mMethods.end()) {
    mit->second->mark();
    ++mit;
  }
  if (mClass) {
    mClass->mark();
  }
}

void Object::setVar(const std::string &name, Object *o) {
  mVars[name] = (o == NULL ? oNil : o);
}

Object* Object::getVar(const std::string &name) throw(Exception) {
  Object::Iterator it = mVars.find(name);
  if (it == mVars.end()) {
    std::ostringstream oss;
    oss << "Object has no variable named \"" << name << "\"";
    throw MissingError(oss.str());
  } else {
    return (it->second);
  }
}

void Object::addMethod(const std::string &name, Callable *m) {
  if (m != NULL) {
    mMethods[name] = m;
  }
}

void Object::addMethod(Method *m) {
  if (m != NULL) {
    mMethods[m->name()] = m;
  }
}

Callable* Object::method(const std::string &name) throw(Exception) {
#ifdef _DEBUG
  std::cerr << "--- Look for method \"" << name << "\" in object 0x" << std::hex << (void*)this << std::dec;
  if (mClass) {
    std::cerr << " of class \"" << mClass->name() << "\"";
  }
  std::cerr << std::endl;
#endif
  Callable::Iterator m = mMethods.find(name);
  if (m == mMethods.end()) {
    if (mClass) {
      return mClass->instanceMethod(name);
    } else {
      std::ostringstream oss;
      oss << "Object: 0x" << std::hex << (void*)this << std::dec << " does not respond to method \"" << name << "\"";
      throw MissingError(oss.str());
    }
  }
  return m->second;
}

Object* Object::call(Context *ctx, const std::string &n) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0,
                                   Object *o1) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0, o1);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0,
                                   Object *o1,
                                   Object *o2) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0, o1, o2);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0,
                                   Object *o1,
                                   Object *o2,
                                   Object *o3) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0, o1, o2, o3);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0,
                                   Object *o1,
                                   Object *o2,
                                   Object *o3,
                                   Object *o4) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0, o1, o2, o3, o4);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0,
                                   Object *o1,
                                   Object *o2,
                                   Object *o3,
                                   Object *o4,
                                   Object *o5) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0, o1, o2, o3, o4, o5);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0,
                                   Object *o1,
                                   Object *o2,
                                   Object *o3,
                                   Object *o4,
                                   Object *o5,
                                   Object *o6) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0, o1, o2, o3, o4, o5, o6);
}

Object* Object::call(Context *ctx, const std::string &n,
                                   Object *o0,
                                   Object *o1,
                                   Object *o2,
                                   Object *o3,
                                   Object *o4,
                                   Object *o5,
                                   Object *o6,
                                   Object *o7) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, o0, o1, o2, o3, o4, o5, o6, o7);
}

Object* Object::call(Context *ctx, const std::string &n,
                     size_t nargs, Object **args) throw(Exception) {
  Callable *m = method(n);
  return m->call(ctx, this, nargs, args);
}

bool Object::isKindOf(Class *klass) {
  Class *cc = mClass;
  while (cc) {
    if (cc == klass) {
      return true;
    }
    cc = cc->super();
  }
  return false;
}

bool Object::isA(Class *klass) {
  return (klass == mClass);
}

bool Object::respondsTo(const std::string &name) {
  try {
    method(name);
    return true;
  } catch (...) {
    return false;
  }
}

size_t Object::methods(StringList &names) {
  Callable::Iterator it = mMethods.begin();
  while (it != mMethods.end()) {
    if (std::find(names.begin(), names.end(), it->first) == names.end()) {
      names.push_back(it->first);
    }
    ++it;
  }
  if (mClass) {
    mClass->instanceMethods(names);
  }
  return names.size();
}

size_t Object::variables(StringList &names) {
  Object::Iterator it = mVars.begin();
  while (it != mVars.end()) {
    if (std::find(names.begin(), names.end(), it->first) == names.end()) {
      names.push_back(it->first);
    }
    ++it;
  }
  if (mClass) {
    mClass->instanceVariables(names);
  }
  return names.size();
}

}

