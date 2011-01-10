/*

Copyright (C) 2010  Gaetan Guidet

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

#ifndef __myst_symbol_h_
#define __myst_symbol_h_

#include <myst/config.h>

namespace myst
{
  
  class MYST_API Symbol
  {
    public:
    
      Symbol();
      Symbol(size_t v);
      Symbol(const std::string &s);
      Symbol(const Symbol &rhs);
      ~Symbol();
    
      Symbol& operator=(const Symbol &rhs);
      bool operator==(const Symbol &rhs) const;
      bool operator!=(const Symbol &rhs) const;
    
      bool valid() const;
      size_t id() const;
    
      friend bool operator<(const Symbol &s0, const Symbol &s1);
      friend std::ostream& operator<<(std::ostream &os, const Symbol &s);
    
    protected:
    
      size_t mID;
  };
  
  class MYST_API SymbolTable
  {
    public:
      
      typedef std::map<std::string, size_t> HashType;
      
    public:
      
      static void Clear();
      static const char* GetString(const Symbol &s);
      static Symbol GetSymbol(const std::string &name);
      
      ~SymbolTable();
      
    protected:
      
      SymbolTable();
      
      Symbol getSymbol(const std::string &name);
      const char* getString(const Symbol &s);
      
    protected:
      
      HashType mSyms;
      std::vector<std::string> mStrs;
  };
  
  // ---
  
  inline Symbol::Symbol()
    : mID(size_t(-1))
  {
  }
  
  inline Symbol::Symbol(size_t v)
    : mID(v)
  {
  }
  
  inline Symbol::Symbol(const std::string &s)
    : mID(size_t(-1))
  {
    Symbol sym = SymbolTable::GetSymbol(s);
    mID = sym.mID;
  }
  
  inline Symbol::Symbol(const Symbol &rhs)
    : mID(rhs.mID)
  {
  }
  
  inline Symbol::~Symbol()
  {
  }
  
  inline Symbol& Symbol::operator=(const Symbol &rhs)
  {
    mID = rhs.mID;
    return *this;
  }
  
  inline bool Symbol::operator==(const Symbol &rhs) const
  {
    return (mID == rhs.mID);
  }
  
  inline bool Symbol::operator!=(const Symbol &rhs) const
  {
    return (mID != rhs.mID);
  }
  
  inline bool Symbol::valid() const
  {
    return (mID != size_t(-1));
  }
  
  inline size_t Symbol::id() const
  {
    return mID;
  }
  
  inline bool operator<(const Symbol &s0, const Symbol &s1)
  {
    return (s0.mID < s1.mID);
  }
  
  inline std::ostream& operator<<(std::ostream &os, const Symbol &s)
  {
    const char *cs = SymbolTable::GetString(s);
    os << (cs == 0 ? "" : cs);
    return os;
  }
}

#endif
