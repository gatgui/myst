#ifndef __myst_cclass_h_
#define __myst_cclass_h_

#include <myst/class.h>

namespace myst {
  
  class MYST_API ClassClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      static void NewUnder(Context *ctx, Long n) throw(Exception);
      
      static void GetInstanceVariables(Context *ctx, Long n) throw(Exception);
      static void GetInstanceMethods(Context *ctx, Long n) throw(Exception);
      static void GetSuper(Context *ctx, Long n) throw(Exception);
      static void GetName(Context *ctx, Long n) throw(Exception);
      static void Subclass(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      
    public:
      
      ClassClass();
      virtual ~ClassClass();
  };
  
}

#endif

