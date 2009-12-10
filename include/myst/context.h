#ifndef __myst_context_h_
#define __myst_context_h_

#include <myst/exceptions.h>
#include <myst/object.h>

namespace myst {
  
  typedef std::vector<Object*> Stack;
  
  class MYST_API Context {
    public:
      
      Context(Context *parent=0);
      ~Context();
      
      // named values
      Object* get(const std::string &name) throw(Exception);
      void set(const std::string &name, Object *o) throw(Exception);
      
      // stack handling
      inline void push(Object *o) {
        mRoot->_push(o);
      }
      inline void pop(size_t n) {
        mRoot->_pop(n);
      }
      inline Object* at(Long pos) throw(Exception) {
        return mRoot->_at(pos);
      }
      inline void insert(Long pos, Object *o) throw(Exception) {
        mRoot->_insert(pos, o);
      }
      inline void remove(Long pos, size_t n) throw(Exception) {
        mRoot->_remove(pos, n);
      }
      inline size_t stackSize() {
        return mRoot->_stackSize();
      }
      
      void mark();
      
      inline Object::Iterator begin() {
        return mVars.begin();
      }
      
      inline Object::Iterator end() {
        return mVars.end();
      }
      
      inline size_t numVars() {
        return mVars.size();
      }
      
      inline Context* parent() {
        return mParent;
      }
      
    protected:
      
      void _push(Object *);
      void _pop(size_t n);
      Object* _at(Long pos) throw(Exception);
      void _insert(Long pos, Object *) throw(Exception);
      void _remove(Long pos, size_t n) throw(Exception);
      inline size_t _stackSize() {
        return mStack.size();
      }
      
    protected:
      
      Context *mParent;
      Context *mRoot;
      Object::Map mVars;
      Stack mStack;
  };
}

#endif
