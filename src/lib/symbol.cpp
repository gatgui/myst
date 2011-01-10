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

#include <myst/symbol.h>

namespace myst
{

SymbolTable *gInstance = 0;

void SymbolTable::Clear()
{
  if (gInstance)
  {
    delete gInstance;
    gInstance = 0;
  }
}

const char* SymbolTable::GetString(const Symbol &s)
{
  if (!gInstance)
  {
    gInstance = new SymbolTable();
  }
  return gInstance->getString(s);
}

Symbol SymbolTable::GetSymbol(const std::string &name)
{
  if (!gInstance)
  {
    gInstance = new SymbolTable();
  }
  return gInstance->getSymbol(name);
}

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
  mSyms.clear();
  mStrs.clear();
}

Symbol SymbolTable::getSymbol(const std::string &name)
{
  HashType::iterator it = mSyms.find(name);
  if (it != mSyms.end())
  {
    return Symbol(it->second);
  }
  else
  {
    size_t sym = mStrs.size();
    mSyms[name] = sym;
    mStrs.push_back(name);
    return Symbol(sym);
  }
}

const char* SymbolTable::getString(const Symbol &s)
{
  if (s.valid() && s.id() < mStrs.size())
  {
    return mStrs[s.id()].c_str();
  }
  else
  {
    return 0;
  }
}

}
