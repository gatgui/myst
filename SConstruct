# Copyright (C) 2009  Gaetan Guidet
# 
# This file is part of myst.
# 
# myst is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 2.1 of the License, or (at
# your option) any later version.
# 
# myst is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.


import excons
import os, glob

projects = [
  { "name"    : "myst",
    "type"    : "sharedlib",
    "defs"    : ["MYST_BUILD"],
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/lib/*.cpp") + glob.glob("src/lib/core/*.cpp"),
  },
  { "name"    : "tests",
    "type"    : "testprograms",
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/tests/*cpp"),
    "libs"    : ["myst"]
  }
]

env = excons.MakeBaseEnv()

excons.DeclareTargets(env, projects)

