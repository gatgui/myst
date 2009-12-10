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

#ifndef __myst_builtins_h_
#define __myst_builtins_h_

#include <myst/config.h>
#include <myst/context.h>

namespace myst {
  
  class MYST_API Class;
  class MYST_API Object;
  
  
  MYST_DATA_API Object *oNil;
  MYST_DATA_API Object *oTrue;
  MYST_DATA_API Object *oFalse;
  
  MYST_DATA_API Class *cObject;
  MYST_DATA_API Class *cClass;
  MYST_DATA_API Class *cInteger;
  MYST_DATA_API Class *cReal;
  MYST_DATA_API Class *cString;
  MYST_DATA_API Class *cArray;
  MYST_DATA_API Class *cDict;
  MYST_DATA_API Class *cTrue;
  MYST_DATA_API Class *cFalse;
  MYST_DATA_API Class *cNil;
  MYST_DATA_API Class *cCallable;
  MYST_DATA_API Class *cMethod;
  MYST_DATA_API Class *cBlock;
  
  MYST_API Context* Initialize();
  
}

#endif
