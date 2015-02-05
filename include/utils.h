/******************************************************
 * utils.h - utility functions for operating systems
 * created 140131 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#include <cstdint>

#ifdef DEBUG
  #include <cstdio>
  #define DLOG(format, ...) printf("[DEBUG] " + format, __VA_ARGS__);
#else
  #define DLOG(...)
#endif

/* Base data type for word-addressable OS */
typedef std::uint32_t WORD;

/* Register definitions */
#define R_ACCUMULATOR -2
#define R_ZERO -1
#define R(cpu,x) ((word *)cpu+(word *)(x+2)) /* Access register of specific CPU */
