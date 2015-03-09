/******************************************************
 * utils.h - utility functions for operating systems
 * created 150131 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#include <cstdint>

#if defined(DEBUG) && !__FOR_TESTS
  #include <cstdio>
  #define DLOG(format, ...) printf("[DEBUG] " format "\n", ##__VA_ARGS__)
#else
  #define DLOG(...)
#endif

/* Base data type for word-addressable OS */
typedef std::uint32_t WORD;

/* Register definitions */
#define R(cpu,x) ((WORD *)cpu + x) /* Access register of specific CPU */
