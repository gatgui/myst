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

