#ifndef __myst_block_h_
#define __myst_block_h_

#include <myst/exceptions.h>
#include <myst/callable.h>
#include <myst/instructions.h>

namespace myst {
  
  class MYST_API Context;
  
  class MYST_API Block : public Callable {
    public:
      
      Block(Context *ctx, size_t nargs);
      virtual ~Block();
      
      virtual void call(Context *ctx) throw(Exception);
      
      void setArgName(size_t idx, const std::string &str);
      void addBlockTemp(const std::string &str);
      
    protected:
      
      Context *mCtx;
      InstructionList mCode;
      std::vector<std::string> mArgNames;
      std::vector<std::string> mBlockTemp;
  };
  
}

#endif
