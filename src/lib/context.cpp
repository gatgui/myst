#include <myst/context.h>
#include <myst/builtins.h>

namespace myst {

Context::Context(Context *parent)
  : mParent(parent), mRoot(NULL) {
  if (mParent) {
    mRoot = mParent->mRoot;
  } else {
    mRoot = this;
  }
}

Context::~Context() {
  // free only vars from context ?
  // garbage collect?
  mStack.clear();
}

void Context::mark() {
  Object::Iterator it = mVars.begin();
  while (it != mVars.end()) {
    it->second->mark();
    ++it;
  }
  Stack::iterator i = mStack.begin();
  while (i != mStack.end()) {
    (*i)->mark();
    ++i;
  }
}

Object* Context::get(const std::string &name) throw(Exception) {
  Object::Iterator it = mVars.find(name);
  if (it == mVars.end()) {
    if (mParent) {
      return mParent->get(name);
    } else {
      std::ostringstream oss;
      oss << "No variable named \"" << name << "\" in current context";
      throw MissingError(oss.str());
    }
  } else {
    return it->second;
  }

}

void Context::set(const std::string &name, Object *o) throw(Exception) {
  mVars[name] = (o == NULL ? oNil : o);
}

void Context::_push(Object *o) {
  mStack.push_back(o);
}

void Context::_pop(size_t n) {
  size_t c = (n > mStack.size() ? mStack.size() : n);
  Stack::iterator f = mStack.end() - c;
  Stack::iterator e = mStack.end();
  mStack.erase(f, e);
}

Object* Context::_at(Long pos) throw(Exception) {
  if (pos < 0) {
    if (-pos > Long(mStack.size())) {
      std::ostringstream oss;
      oss << "Invalid stack index: " << pos;
      throw IndexError(oss.str());
    }
    pos = Long(mStack.size()) + pos;
    
  } else if (pos >= Long(mStack.size())) {
    std::ostringstream oss;
    oss << "Invalid stack index: " << pos;
    throw IndexError(oss.str());
  
  }
  return mStack[size_t(pos)];
}

void Context::_insert(Long pos, Object *o) throw(Exception) {
  if (pos < 0) {
    if (-pos > Long(mStack.size())) {
      std::ostringstream oss;
      oss << "Invalid stack index: " << pos;
      throw IndexError(oss.str());
    }
    pos = Long(mStack.size()) + pos;
    
  } else if (pos > Long(mStack.size())) {
    std::ostringstream oss;
    oss << "Invalid stack index: " << pos;
    throw IndexError(oss.str());
  
  }
  Stack::iterator i = mStack.begin() + size_t(pos);
  mStack.insert(i, o);
}

void Context::_remove(Long pos, size_t n) throw(Exception) {
  if (pos < 0) {
    if (-pos > Long(mStack.size())) {
      std::ostringstream oss;
      oss << "Invalid stack index: " << pos;
      throw IndexError(oss.str());
    }
    pos = Long(mStack.size()) + pos;
    
  }
  Stack::iterator f = mStack.begin() + size_t(pos);
  Stack::iterator e = f + n;
  mStack.erase(f, e);
}


}

