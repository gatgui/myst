#ifndef __myst_cinteger_h_
#define __myst_cinteger_h_

#include <myst/class.h>
#include <myst/core/cobject.h>

namespace myst {
  
  class MYST_API IntegerClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void Add(Context *ctx, Long n) throw(Exception);
      static void Sub(Context *ctx, Long n) throw(Exception);
      static void Mult(Context *ctx, Long n) throw(Exception);
      static void Div(Context *ctx, Long n) throw(Exception);
      static void Modulo(Context *ctx, Long n) throw(Exception);
      static void LShift(Context *ctx, Long n) throw(Exception);
      static void RShift(Context *ctx, Long n) throw(Exception);
      static void BitOr(Context *ctx, Long n) throw(Exception);
      static void BitAnd(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void ToInt(Context *ctx, Long n) throw(Exception);
      static void ToReal(Context *ctx, Long n) throw(Exception);
      static void Abs(Context *ctx, Long n) throw(Exception);
      static void Neg(Context *ctx, Long n) throw(Exception);
      
    public:
      
      IntegerClass();
      virtual ~IntegerClass();
  };
  
  class MYST_API Integer : public TObject<Long> {
    public:
      Integer(Long val=0);
      virtual ~Integer();
  };
}

#endif
