#ifndef LEXICON_COMMON_H
#define LEXICON_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

typedef unsigned char byte;

char const * vas(char const * fmt, ...);
char const * vasa(char const * fmt, va_list va);

#ifdef __cplusplus
}
#endif

#endif //LEXICON_COMMON_HPP
