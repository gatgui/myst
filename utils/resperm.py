#!/usr/bin/env python

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
