#ifndef __myst_creal_h_
#define __myst_creal_h_

#include <myst/class.h>
#include <myst/core/cobject.h>

namespace myst {
  
  class MYST_API RealClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void Add(Context *ctx, Long n) throw(Exception);
      static void Sub(Context *ctx, Long n) throw(Exception);
      static void Mult(Context *ctx, Long n) throw(Exception);
      static void Div(Context *ctx, Long n) throw(Exception);
      static void Abs(Context *ctx, Long n) throw(Exception);
      static void Neg(Context *ctx, Long n) throw(Exception);
      static void Pow(Context *ctx, Long n) throw(Exception);
      static void Log(Context *ctx, Long n) throw(Exception);
      static void Exp(Context *ctx, Long n) throw(Exception);
      static void Floor(Context *ctx, Long n) throw(Exception);
      static void Ceil(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void ToInt(Context *ctx, Long n) throw(Exception);
      static void ToReal(Context *ctx, Long n) throw(Exception);
      
    public:
      
      RealClass();
      virtual ~RealClass();
  };
  
  class MYST_API Real : public TObject<double> {
    public:
      Real(double val=0);
      virtual ~Real();
  };
  
}


#endif
