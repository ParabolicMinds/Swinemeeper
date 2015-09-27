#ifndef GM_ERROR_HPP
#define GM_ERROR_HPP

enum class errlev : int { debug, log, warning, error, term };
void gmerror(errlev, char const * str);

#define gmerrv(errlev, fmt ...) gmerror(errlev, vas(fmt))
#define gmerrf(errlev, fmt ...) gmerror(errlev, vas("%s: %s", __PRETTY_FUNCTION__, vas(fmt)))

#endif //GM_ERROR_HPP
