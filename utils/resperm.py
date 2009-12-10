#!/usr/bin/env python

import sys
import os
import glob
import stat
import re


startdir = os.path.abspath(".")
if len(sys.argv) == 2:
  startdir = os.path.abspath(sys.argv[1])

#print(startdir)

filemode = stat.S_IWUSR|stat.S_IRUSR|stat.S_IRGRP|stat.S_IROTH
dirmode  = filemode|stat.S_IXUSR|stat.S_IXUSR|stat.S_IXOTH

filepattern = re.compile(r"(^(README|COPYING|SConstruct|Makefile.*)$)|(\.(txt|l|y|lua|js|py|rb|st|c|cc|cxx|cpp|h|hh|hxx|hpp)$)")

# Selective Recursive chmod
def srchmod(curdir, filespattern):
  #print("os.chmod(\"%s\", %d)" % (curdir, dirmode))
  os.chmod(curdir, dirmode)
  for f in glob.glob(os.path.join(curdir, "*")):
    if os.path.isdir(f):
      srchmod(f, filepattern)
    else:
      if filespattern.search(os.path.basename(f)):
        #print("os.chmod(\"%s\", %d)" % (f, filemode))
        os.chmod(f, filemode)
      else:
        print("Skip \"%s\"" % f)


srchmod(startdir, filepattern)
