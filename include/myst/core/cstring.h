#ifndef __myst_cstring_h_
#define __myst_cstring_h_

#include <myst/class.h>
#include <myst/core/cobject.h>

namespace myst {
  
  class MYST_API StringClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void Length(Context *ctx, Long n) throw(Exception);
      static void Concat(Context *ctx, Long n) throw(Exception);
      static void At(Context *ctx, Long n) throw(Exception);
      static void SetAt(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void ToInt(Context *ctx, Long n) throw(Exception);
      static void ToReal(Context *ctx, Long n) throw(Exception);
      
    public:
      StringClass();
      virtual ~StringClass();
  };
  
  class MYST_API String : public TObject<std::string> {
    public:
      String();
      String(const std::string &str);
      virtual ~String();
  };
}

#endif
