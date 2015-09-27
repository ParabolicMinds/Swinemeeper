#ifndef SWINEMEEPER_PLAYER_API_HPP
#define SWINEMEEPER_PLAYER_API_HPP

#define PAPIPUBLIC __attribute__ ((visibility ("default")))

#ifdef __cplusplus
extern "C" {
#endif

PAPIPUBLIC void mod_initialize();
PAPIPUBLIC void mod_shutdown();

PAPIPUBLIC void mod_ping();

#ifdef __cplusplus
}
#endif
#endif //SWINEMEEPER_PLAYER_API_HPP
