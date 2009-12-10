#ifndef __myst_instructions_h_
#define __myst_instructions_h_

#include <myst/exceptions.h>

namespace myst {
  
  class MYST_API Context;
  
  class MYST_API Instruction {
    public:
      Instruction();
      virtual ~Instruction();
      
      virtual void exec(Context *ctx) throw(Exception) = 0;
  };
  
  class MYST_API InstructionList : public std::vector<Instruction*> {
    public:
      InstructionList();
      virtual ~InstructionList();
      
      void exec(Context *ctx) throw(Exception);
  };
  
  class MYST_API Call : public Instruction {
    public:
      Call(const std::string &selector, size_t nargs);
      virtual ~Call();
      
      virtual void exec(Context *ctx) throw(Exception);
      
    protected:
      std::string mSel;
      size_t mArgCount;
  };
  
  class MYST_API PushInt : public Instruction {
    public:
      PushInt(Long val);
      virtual ~PushInt();
      
      virtual void exec(Context *ctx) throw(Exception);
      
    protected:
      Long mVal;
  };
  
  class MYST_API PushReal : public Instruction {
    public:
      PushReal(double val);
      virtual ~PushReal();
      
      virtual void exec(Context *ctx) throw(Exception);
      
    protected:
      double mVal;
  };
  
  class MYST_API PushString : public Instruction {
    public:
      PushString(const std::string &val);
      virtual ~PushString();
      
      virtual void exec(Context *ctx) throw(Exception);
      
    protected:
      std::string mVal;
  };
  
  class MYST_API PushBool : public Instruction {
    public:
      PushBool(bool val);
      virtual ~PushBool();
      
      virtual void exec(Context *ctx) throw(Exception);
      
    protected:
      bool mVal;
  };
  
  class MYST_API SetVar : public Instruction {
    public:
      SetVar(const std::string &name);
      virtual ~SetVar();
      
      virtual void exec(Context *ctx) throw(Exception);
    
    protected:
      std::string mName;
  };
  
  class MYST_API GetVar : public Instruction {
    public:
      GetVar(const std::string &name);
      virtual ~GetVar();
      
      virtual void exec(Context *ctx) throw(Exception);
    
    protected:
      std::string mName;
  };
  
}

#endif
