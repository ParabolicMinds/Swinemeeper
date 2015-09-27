#ifndef GM_ERROR_HPP
#define GM_ERROR_HPP

enum class errlev : int { debug, log, warning, error, term };
void gmerror(errlev, char const * fmt...);

#define gmerrf(errlev, fmt...) gmerror(errlev, "%s: %s", __PRETTY_FUNCTION__, fmt)

#endif //GM_ERROR_HPP
