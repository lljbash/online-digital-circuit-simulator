/* Definition of useful macros
 */

#pragma once

#include <cstdio>

#ifdef PSJJJJ_ENABLE_DEBUG
#define PSJJJJ_DEBUG(...) \
    do { fprintf(stderr, __VA_ARGS__); } while (0)
#else
#define PSJJJJ_DEBUG(...) \
    do {} while (0)
#endif

#ifdef PSJJJJ_ENABLE_VERBOSE
#define PSJJJJ_SHOW(...) \
    do { fprintf(stdout, __VA_ARGS__); } while (0)
#else
#define PSJJJJ_SHOW(...) \
    do {} while (0)
#endif

