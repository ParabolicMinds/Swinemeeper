#ifndef GM_ERROR_HPP
#define GM_ERROR_HPP

enum class errlev : int { debug, log, error, term };
void gmerror(errlev, char const * fmt...);

#endif //GM_ERROR_HPP
