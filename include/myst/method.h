#ifndef __myst_method_h_
#define __myst_method_h_

#include <myst/exceptions.h>
#include <myst/callable.h>

namespace myst {
  
  
  class MYST_API Method : public Callable {
    public:
      
      Method(const std::string &name, size_t nargs);
      virtual ~Method();
      
      inline const std::string& name() {
        return mName;
      }
      
    protected:
      
      std::string mName;
  };
  
  class MYST_API CMethod : public Method {
    public:
      
      //typedef Object* (*Pointer)(Object *, size_t, Object **);
      typedef void (*Pointer)(Context *, Long n);
      
    public:
      
      CMethod(const std::string &name, size_t nargs, Pointer ptr);
      virtual ~CMethod();
      
      //virtual Object* call(Object *self,
      //                     size_t n, Object **args) throw(Exception);
      virtual void call(Context *ctx) throw(Exception);
      
    protected:
      
      Pointer mPtr;
  };
  
  class MYST_API GetVarMethod : public Method {
    public:
      
      GetVarMethod(const std::string &varName);
      virtual ~GetVarMethod();
      
      //virtual Object* call(Object *self,
      //                     size_t n, Object **args) throw(Exception);
      virtual void call(Context *ctx) throw(Exception);
  };
  
  class MYST_API SetVarMethod : public Method {
    public:
      
      SetVarMethod(const std::string &varName);
      virtual ~SetVarMethod();
      
      //virtual Object* call(Object *self,
      //                     size_t n, Object **args) throw(Exception);
      virtual void call(Context *ctx) throw(Exception);
    
    protected:
      std::string mVarName;
  };
  
}

#endif
