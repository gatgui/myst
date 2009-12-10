#ifndef __dummy_unistd_h_
#define __dummy_unistd_h_

// This is a dummy function so we can compile flex output on windows
int isatty(int) {
  return 0;
}

#endif
