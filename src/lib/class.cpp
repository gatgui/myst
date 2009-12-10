/*

Copyright (C) 2009  Gaetan Guidet

This file is part of myst.

myst is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

myst is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

#include <myst/class.h>
#include <myst/method.h>
#include <myst/builtins.h>

namespace myst {


Class::Class(const std::string &name, Class *super)
  : Object(cClass), mName(name), mSuper(super) {
}

Class::~Class() {
}

void Class::addInstanceVar(const std::string &name) {
  StringListIterator it = std::find(mIVars.begin(), mIVars.end(), name);
  if (it == mIVars.end()) {
    mIVars.push_back(name);
    Method *get = new GetVarMethod(name);
    Method *set = new SetVarMethod(name);
    addInstanceMethod(get->name(), get);
    addInstanceMethod(set->name(), set);
  }
}

void Class::addInstanceMethod(const std::string &name, Callable *m) {
  if (m != NULL) {
    mIMethods[name] = m;
  }
}

void Class::addInstanceMethod(Method *m) {
  if (m != NULL) {
    mIMethods[m->name()] = m;
  }
}

Callable* Class::instanceMethod(const std::string &name) {
#ifdef _DEBUG
  std::cerr << "--- Look for method \"" << name << "\" in class \"" << mName << "\" instance methods" << std::endl;
#endif
  Callable::Iterator it = mIMethods.find(name);
  if (it == mIMethods.end()) {
    if (!mSuper) {
      std::ostringstream oss;
      oss << "Object does not respond to method \"" << name << "\"";
      throw MissingError(oss.str());
    } else {
      return mSuper->instanceMethod(name);
    }
  }
  return it->second;
}

void Class::populateInstanceVars(Object *inst) {
  for (size_t i=0; i<mIVars.size(); ++i) {
    inst->setVar(mIVars[i], NULL);
  }
  if (mSuper) {
    mSuper->populateInstanceVars(inst);
  }
}

void Class::mark() {
  Object::mark();
  Callable::Iterator it = mIMethods.begin();
  while (it != mIMethods.end()) {
    it->second->mark();
    ++it;
  }
  if (mSuper) {
    mSuper->mark();
  }
}

Class* Class::subclass(const std::string &name) {
  return new Class(name, this);
}

Object* Class::newInstance() {
  return new Object(this);
}

size_t Class::instanceMethods(StringList &names) {
  Callable::Iterator it = mIMethods.begin();
  while (it != mIMethods.end()) {
    if (std::find(names.begin(), names.end(), it->first) == names.end()) {
      names.push_back(it->first);
    }
    ++it;
  }
  if (mSuper) {
    mSuper->instanceMethods(names);
  }
  return names.size();
}

size_t Class::instanceVariables(StringList &names) {
  for (size_t i=0; i<mIVars.size(); ++i) {
    if (std::find(names.begin(), names.end(), mIVars[i]) == names.end()) {
      names.push_back(mIVars[i]);
    }
  }
  if (mSuper) {
    mSuper->instanceVariables(names);
  }
  return names.size();
}

void Class::_fixClass() {
  if (mClass == 0) {
    //std::cout << "Class " << name() << " class was NULL" << std::endl;
    mClass = cClass;
  }
}

void Class::_fixMethodsClass() {
  Callable::Iterator it;
  it = mMethods.begin();
  while (it != mMethods.end()) {
    if (it->second->mClass == 0) {
      //std::cout << "Found " << name() << " method whose class was NULL" << std::endl;
      it->second->mClass = cMethod;
    }
    ++it;
  }
}

void Class::_fixInstanceMethodsClass() {
  Callable::Iterator it;
  it = mIMethods.begin();
  while (it != mIMethods.end()) {
    if (it->second->mClass == 0) {
      //std::cout << "Found " << name() << " instance method whose class was NULL" << std::endl;
      it->second->mClass = cMethod;
    }
    ++it;
  }
}

void Class::_fixAllMethodsClass() {
  _fixMethodsClass();
  _fixInstanceMethodsClass();
}

}

