#ifndef __myst_cmethod_h_
#define __myst_cmethod_h_

#include <myst/core/ccallable.h>

namespace myst {
  
  class MYST_API MethodClass : public Class {
    public:
      
      static void Name(Context *ctx, Long n) throw(Exception);
      
    public:
      
      MethodClass();
      virtual ~MethodClass();
  };
  
}

#endif

