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

#ifndef __myst_exceptions_h_
#define __myst_exceptions_h_

#include <myst/config.h>

namespace myst {

  class MYST_API Exception : public std::runtime_error {
    public:
      Exception();
      Exception(const std::string &msg);
      virtual ~Exception() throw();
      
      // i'd like to have backtrace here
  };

  class MYST_API CallError : public Exception {
    public:
      CallError();
      CallError(const std::string &msg);
      virtual ~CallError() throw();
  };

  class MYST_API MissingError : public Exception {
    public:
      MissingError();
      MissingError(const std::string &msg);
      virtual ~MissingError() throw();
  };

  class MYST_API IndexError : public Exception {
    public:
      IndexError();
      IndexError(const std::string &msg);
      virtual ~IndexError() throw();
  };

  class MYST_API KeyError : public Exception {
    public:
      KeyError();
      KeyError(const std::string &msg);
      virtual ~KeyError() throw();
  };
  
  class MYST_API TypeError : public Exception {
    public:
      TypeError();
      TypeError(const std::string &msg);
      virtual ~TypeError() throw();
  };
  
  class MYST_API ArgumentError : public Exception {
    public:
      ArgumentError();
      ArgumentError(const std::string &msg);
      virtual ~ArgumentError() throw();
  };
  
  class MYST_API ZeroDivisionError : public Exception {
    public:
      ZeroDivisionError();
      ZeroDivisionError(const std::string &msg);
      virtual ~ZeroDivisionError() throw();
  };

}

#endif
