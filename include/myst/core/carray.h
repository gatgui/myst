#ifndef __myst_carray_h_
#define __myst_carray_h_

#include <myst/class.h>
#include <myst/context.h>
#include <myst/core/cobject.h>

namespace myst {
  
  class MYST_API ArrayClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void Includes(Context *ctx, Long n) throw(Exception);
      static void At(Context *ctx, Long n) throw(Exception);
      static void Slice(Context *ctx, Long n) throw(Exception);
      static void Push(Context *ctx, Long n) throw(Exception);
      static void Pop(Context *ctx, Long n) throw(Exception);
      static void InsertAt(Context *ctx, Long n) throw(Exception);
      static void Clear(Context *ctx, Long n) throw(Exception);
      static void ToStr(Context *ctx, Long n) throw(Exception);
      static void Length(Context *ctx, Long n) throw(Exception);
      static void SetAt(Context *ctx, Long n) throw(Exception);
      //static void ForEach(Context *ctx, Long n) throw(Exception);
      
    public:

      ArrayClass();
      virtual ~ArrayClass();
  };
  
  
  class MYST_API Array : public TObject<std::vector<Object*> > {
    public:
      
      Array(Long len=0);
      Array(const std::vector<Object*> &rhs);
      virtual ~Array();
      
      virtual void mark();
  };
  
}

#endif
