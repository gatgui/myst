#ifndef __myst_cnil_h_
#define __myst_cnil_h_

#include <myst/class.h>

namespace myst {
  
  class MYST_API NilClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void IsNil(Context *ctx, Long n) throw(Exception);
      // ifNil: block
      // ifNil: block else: block
      
    
    public:
      
      NilClass();
      virtual ~NilClass();
  };
  
}

#endif

