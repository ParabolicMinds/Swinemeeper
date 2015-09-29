#ifndef SWINEMEEPER_PLAYER_API_HPP
#define SWINEMEEPER_PLAYER_API_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define PAPIPUBLIC __attribute__ ((visibility ("default")))

typedef void * handle_t;

PAPIPUBLIC bool mod_initialize(handle_t);
PAPIPUBLIC void mod_shutdown();

#ifdef __cplusplus
}
#endif
#endif //SWINEMEEPER_PLAYER_API_HPP
