#include <myst/exceptions.h>

namespace myst {

Exception::Exception()
  : std::runtime_error("Unknown exception") {
}

Exception::Exception(const std::string &msg)
  : std::runtime_error(msg) {
}

Exception::~Exception() throw() {
}

// ---

CallError::CallError()
  : Exception("CallError") {
}

CallError::CallError(const std::string &msg)
  : Exception("CallError: "+msg) {
}

CallError::~CallError() throw() {
}

// ---

MissingError::MissingError()
  : Exception("MissingError") {
}

MissingError::MissingError(const std::string &msg)
  : Exception("MissingError: "+msg) {
}

MissingError::~MissingError() throw() {
}

// ---

IndexError::IndexError()
  : Exception("IndexError") {
}

IndexError::IndexError(const std::string &msg)
  : Exception("IndexError: "+msg) {
}

IndexError::~IndexError() throw() {
}

// ---

KeyError::KeyError()
  : Exception("KeyError") {
}

KeyError::KeyError(const std::string &msg)
  : Exception("KeyError: "+msg) {
}

KeyError::~KeyError() throw() {
}

// ---

TypeError::TypeError()
  : Exception("TypeError") {
}

TypeError::TypeError(const std::string &msg)
  : Exception("TypeError: "+msg) {
}

TypeError::~TypeError() throw() {
}

// ---

ArgumentError::ArgumentError()
  : Exception("ArgumentError") {
}

ArgumentError::ArgumentError(const std::string &msg)
  : Exception("ArgumentError: "+msg) {
}

ArgumentError::~ArgumentError() throw() {
}

// ---

ZeroDivisionError::ZeroDivisionError()
  : Exception("ZeroDivisionError") {
}

ZeroDivisionError::ZeroDivisionError(const std::string &msg)
  : Exception("ZeroDivisionError: "+msg) {
}

ZeroDivisionError::~ZeroDivisionError() throw() {
}

}


