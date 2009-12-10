#ifndef __myst_cfalse_h_
#define __myst_cfalse_h_

#include <myst/class.h>

namespace myst {
  
  class MYST_API FalseClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void ToStr(Context *ctx, Long n) throw(Exception);
      // ifTrue: block
      // ifFalse: block
      // ifTrue: block else: block
      // ifFalse: block else: block
      
    public:
      
      FalseClass();
      virtual ~FalseClass();
  };

}

#endif


