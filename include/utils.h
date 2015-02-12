/******************************************************
 * utils.h - utility functions for operating systems
 * created 140131 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#include <cstdint>

#ifdef DEBUG
  #include <cstdio>
  #define DLOG(format, ...) printf("[DEBUG] " format "\n", ##__VA_ARGS__);
#else
  #define DLOG(...)
#endif

/* Base data type for word-addressable OS */
typedef std::uint32_t WORD;

/* Register definitions */
#define R(cpu,x) ((WORD *)cpu+(WORD *)x) /* Access register of specific CPU */
