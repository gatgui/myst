#ifndef __myst_cobject_h_
#define __myst_cobject_h_

#include <myst/class.h>

namespace myst {
  
  class MYST_API ObjectClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void IsKindOf(Context *ctx, Long n) throw(Exception);
      static void IsA(Context *ctx, Long n) throw(Exception);
      static void RespondsTo(Context *ctx, Long n) throw(Exception);
      static void GetVariables(Context *ctx, Long n) throw(Exception);
      static void GetMethods(Context *ctx, Long n) throw(Exception);
      static void GetClass(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void IsNil(Context *ctx, Long n) throw(Exception);
      static void Print(Context *ctx, Long n) throw(Exception);
      //static void Hash(Context *ctx, Long n) throw(Exception);
      //static void Equals(Context *ctx, Long n) throw(Exception);
      
    public:
      
      ObjectClass();
      virtual ~ObjectClass();
  };
  
  template <typename T>
  class TObject : public Object {
    public:
      
      TObject(Class *klass)
        : Object(klass) {
      }
      
      virtual ~TObject() {
      }
      
      T data;
  };
}

#endif

