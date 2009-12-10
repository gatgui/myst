#ifndef __myst_class_h_
#define __myst_class_h_

#include <myst/object.h>

namespace myst {
  
  class MYST_API Context;
  
  class MYST_API Class : public Object {
    public:
      
      // what about meta class?
      
      typedef std::map<std::string, Class*> Map;
      typedef Map::iterator Iterator;
      typedef Map::const_iterator ConstIterator;
      
      Class(const std::string &name, Class *super=0);
      virtual ~Class();
      
      void addInstanceVar(const std::string &name);
      void populateInstanceVars(Object *inst);
      
      void addInstanceMethod(const std::string &name, Callable *m);
      void addInstanceMethod(Method *m);
      Callable* instanceMethod(const std::string &name);
      
      inline const std::string& name() {
        return mName;
      }
      
      inline Class* super() {
        return mSuper;
      }
      
      size_t instanceMethods(StringList &);
      size_t instanceVariables(StringList &v);
      
      Class* subclass(const std::string &name);
      Object* newInstance();
      
      virtual void mark();
      
      // Those functions are here to break circularity when initializing core classes
      void _fixClass();
      void _fixMethodsClass();
      void _fixInstanceMethodsClass();
      void _fixAllMethodsClass();
      
    protected:
      
      std::string mName;
      Class *mSuper;
      std::map<std::string, Callable*> mIMethods;
      StringList mIVars;
  };
  
  
}

#endif
