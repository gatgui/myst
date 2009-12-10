#include <myst/myst.h>
#include <iostream>

void printOut(myst::Context *ctx, myst::Object *o) {
  myst::String *s = (myst::String*) o->call(ctx, "toStr");
  std::cout << s->data;
}

int main(int, char**) {
  
  
  try {
    
    myst::Context *ctx = myst::Initialize();
    
    myst::Object *ary = ctx->get("Array")->call(ctx, "new");
    
    static const char * items[] = {
      "hello",
      "world",
      "goodbye",
      "see you",
      "poo"
    };
    
    static size_t nitems = sizeof(items) / sizeof(const char*);
    
    for (size_t i=0; i<nitems; ++i) {
      ary->call(ctx, "push:", new myst::String(items[i]));
    }
    
    myst::Object::Iterator it = ctx->begin();
    while (it != ctx->end()) {
      myst::Object *val = it->second;
      if (!val->isKindOf(myst::cClass)) {
        std::cout << "[instance] ";
        val = val->klass();
      }
      std::cout << "\"" + it->first + "\":" << std::endl;
      size_t i = 1;
      while (val != myst::oNil) {
        for (size_t j=0; j<i; ++j) {
          std::cout << "  ";
        }
        printOut(ctx, val);
        val = val->call(ctx, "super");
        ++i;
      }
      std::cout << std::endl;
      ++it;
    }
    
    
    printOut(ctx, ary);
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Array\" object methods: ";
    printOut(ctx, ary->call(ctx, "methods"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Array\" object members: ";
    printOut(ctx, ary->call(ctx, "variables"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Array\": ";
    printOut(ctx, ctx->get("Array"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Array\" methods:" << std::endl << "  ";
    printOut(ctx, ctx->get("Array")->call(ctx, "methods"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Array\" members:" << std::endl << "  ";
    printOut(ctx, ctx->get("Array")->call(ctx, "variables"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Object\": ";
    printOut(ctx, ctx->get("Object"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Class\": ";
    printOut(ctx, ctx->get("Class"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Array\" is a: ";
    printOut(ctx, ctx->get("Array")->call(ctx, "class"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "\"Array\" instance methods: " << std::endl << "  ";
    printOut(ctx, ctx->get("Array")->call(ctx, "instanceMethods"));
    std::cout << std::endl;
    std::cout << std::endl;
    
    
    myst::InstructionList code;
    code.push_back(new myst::PushString("exp(1.5 + (-2.34)) = "));
    code.push_back(new myst::PushReal(1.5));
    code.push_back(new myst::PushReal(-2.34));
    code.push_back(new myst::Call("add:", 1));
    code.push_back(new myst::Call("exp", 0));
    code.push_back(new myst::Call("toStr", 0));
    code.push_back(new myst::Call("+", 1));
    code.push_back(new myst::Call("print", 0));
    code.exec(ctx);
    
    std::cout << "Total allocated objects: " << myst::Object::AllocatedCount() << std::endl;
    
    std::cout << "Garbage collect" << std::endl;
    
    myst::Object::ClearMarks();
    myst::Object::Sweep();
    
    std::cout << "Total allocated objects: " << myst::Object::AllocatedCount() << std::endl;
    
  } catch (myst::Exception &e) {
    std::cout << "*** " << e.what() << std::endl;
  }
  
  return 0;
}

