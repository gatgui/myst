#ifndef __myst_cdict_h_
#define __myst_cdict_h_

#include <myst/class.h>
#include <myst/core/cobject.h>

namespace myst {
  
  class MYST_API DictClass : public Class {
    public:
      
      static void NewInstance(Context *ctx, Long n) throw(Exception);
      
      static void ToStr(Context *ctx, Long n) throw(Exception);
      
    public:
      DictClass();
      virtual ~DictClass();
  };
  
  class MYST_API Dict : public TObject<std::map<std::string, Object*> > {
    public:
      Dict();
      virtual ~Dict();
      
      virtual void mark();
  };
  
}

#endif
