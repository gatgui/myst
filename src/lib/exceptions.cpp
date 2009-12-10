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


