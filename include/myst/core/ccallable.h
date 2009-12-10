#ifndef __myst_ccallable_h_
#define __myst_ccallable_h_

#include <myst/callable.h>
#include <myst/class.h>

namespace myst {
  
  class MYST_API CallableClass : public Class {
    public:
      
      static void ArgCount(Context *ctx, Long n) throw(Exception);
      
    public:
      
      CallableClass();
      virtual ~CallableClass();
  };
  
}

#endif

