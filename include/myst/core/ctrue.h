#ifndef __myst_ctrue_h_
#define __myst_ctrue_h_

#include <myst/class.h>

namespace myst {

  class MYST_API TrueClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void ToStr(Context *ctx, Long n) throw(Exception);
      // ifTrue: block
      // ifFalse: block
      // ifTrue: block else: block
      // ifFalse: block else: block
      
    public:
      
      TrueClass();
      virtual ~TrueClass();
  };

}

#endif
