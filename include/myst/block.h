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
