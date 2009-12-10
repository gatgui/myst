/*

Copyright (C) 2009  Gaetan Guidet

This file is part of myst.

myst is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

myst is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

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
