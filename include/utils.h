/******************************************************
 * utils.h - utility functions for operating systems
 * created 140131 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#ifdef DEBUG
  #include <cstdio>
  #define DLOG(format, ...) printf("[DEBUG] " + format, __VA_ARGS__);
#else
  #define DLOG(...)
#endif
