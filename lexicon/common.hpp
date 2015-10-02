#ifndef LEXICON_COMMON_HPP
#define LEXICON_COMMON_HPP

#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

typedef unsigned char byte;

char const * vas(char const * fmt, ...);
char const * vasa(char const * fmt, va_list va);

#endif //LEXICON_COMMON_HPP
