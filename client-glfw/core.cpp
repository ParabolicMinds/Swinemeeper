#include "lexicon/common.h"
#include "player_api.h"

#include <cstdio>

static handle_t h;

PAPIPUBLIC bool mod_initialize(handle_t handle) {
	h = handle;
	gm_printf(handle, "TEST");
	return true;
}

PAPIPUBLIC void mod_shutdown() {

}

PAPIPUBLIC void mod_game_start() {
}
