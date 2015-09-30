#ifndef SWINEMEEPER_PLAYER_API_HPP
#define SWINEMEEPER_PLAYER_API_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define PAPIPUBLIC __attribute__ ((visibility ("default")))
#define GMAPIPUBLIC __attribute__ ((visibility ("default"))) extern

typedef void * handle_t;

//REQUIRED
PAPIPUBLIC bool mod_initialize(handle_t); //return false on initialization failure
PAPIPUBLIC bool mod_update(); //return false for graceful shutdown, mod_shutdown will be called automatically (if present)

//OPTIONAL
PAPIPUBLIC void mod_shutdown();
PAPIPUBLIC void mod_game_start();

//GAMEMASTER CALLS
GMAPIPUBLIC void gm_printf(handle_t, char const * fmt, ...);

#ifdef __cplusplus
}
#endif
#endif //SWINEMEEPER_PLAYER_API_HPP
