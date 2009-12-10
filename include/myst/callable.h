#ifndef __myst_callable_h_
#define __myst_callable_h_

#include <myst/object.h>

namespace myst {
  
  class MYST_API Context;
  
  class MYST_API Callable : public Object {
    public:
      
      typedef std::map<std::string, Callable*> Map;
      typedef Map::iterator Iterator;
      typedef Map::const_iterator ConstIterator;
      
    public:
      
      Callable(Class *klass, size_t nargs);
      virtual ~Callable();
      
      inline size_t argCount() {
        return mArgCount;
      }
      
      Object* call(Context *ctx, Object *s) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4,
                                            Object *o5) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4,
                                            Object *o5,
                                            Object *o6) throw(Exception);
      
      Object* call(Context *ctx, Object *s, Object *o0,
                                            Object *o1,
                                            Object *o2,
                                            Object *o3,
                                            Object *o4,
                                            Object *o5,
                                            Object *o6,
                                            Object *o7) throw(Exception);
      
      Object* call(Context *ctx, Object *s, size_t nargs, Object **args) throw(Exception);
      
      // after call, all arguments should have been popped off the stack
      // and the return value pushed on
      virtual void call(Context *ctx) throw(Exception) = 0;
      
      
    protected:
      
      size_t mArgCount;
  };
  
}


#endif
