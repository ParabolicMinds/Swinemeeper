#ifndef GM_ERROR_HPP
#define GM_ERROR_HPP

#include "lexicon/error.hpp"

void gmerror(errlev, char const * str);
void gmterm(char const * str, int code);

#define gmerrv(errlev, fmt ...) gmerror(errlev, vas(fmt))
#define gmerrf(errlev, fmt ...) gmerror(errlev, vas("%s: %s", __PRETTY_FUNCTION__, vas(fmt)))
#define gmtermf(code, fmt ...) gmterm(vas("%s: %s", __PRETTY_FUNCTION__, vas(fmt)), code)

#endif //GM_ERROR_HPP
