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
