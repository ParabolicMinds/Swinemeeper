#ifndef SWINEMEEPER_PLAYER_API_HPP
#define SWINEMEEPER_PLAYER_API_HPP

#include "error.hpp"

#define PAPIPUBLIC extern "C" __attribute__ ((visibility ("default")))
#define GMAPIPUBLIC extern "C" __attribute__ ((visibility ("default")))

typedef void * handle_t;

//REQUIRED
PAPIPUBLIC bool mod_initialize(handle_t); //return false on initialization failure
PAPIPUBLIC bool mod_update(unsigned int gametime, double impulse); //return false for graceful shutdown, mod_shutdown will be called automatically (if present)

//OPTIONAL
PAPIPUBLIC void mod_shutdown();
PAPIPUBLIC void mod_game_start();
PAPIPUBLIC void mod_game_end();

//GAMEMASTER CALLS
GMAPIPUBLIC void gm_print(handle_t, errlev, char const * fmt, ...);

#endif //SWINEMEEPER_PLAYER_API_HPP
