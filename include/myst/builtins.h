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
