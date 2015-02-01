/******************************************************
 * utils.h - utility functions for operating systems
 * created 140131 jonathan howard (j@hovverd.com)
 ******************************************************/

#ifndef __OS_UTILS_H__
#define __OS_UTILS_H__

#ifdef DEBUG
  #include <cstdio>
  #define DLOG(format, ...) printf("[DEBUG] " + format, __VA_ARGS__);
#else
  #define DLOG(...)
#endif

#endif