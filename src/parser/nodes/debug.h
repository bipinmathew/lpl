#ifndef __DEBUG_H___
#define __DEGBUG_H__
  #include <iostream>
  #ifdef DEBUG_BUILD
  #define dbg(x) std::cerr << "dbg: " << x
  #else
  #define dbg(x) do {} while (0)
  #endif
#endif
