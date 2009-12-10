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

class Parser {
  public:
    Parser();
    ~Parser();
    
    void parseFile(const char *s) {
      yyin = fopen(s, "r");
      YY_NEW_FILE //?
      YY_BUFFER_STATE oldState = YY_CURRENT_BUFFER;
      YY_BUFFER_STATE state = yy_create_buffer(yyin, YY_BUF_SIZE);
      yy_switch_to_buffer(state);
      yylex();
      yy_switch_to_buffer(oldState);
      yy_delete_buffer(state);
      // if done -> yyterminate()
      // what about BEGIN(INITIAL)
      // need to do switch back stuff in the <<EOF>> rule
    }
};
