#include "lexicon/common.h"
#include "player_api.h"

#include <cstdio>

static handle_t h;

PAPIPUBLIC bool mod_initialize(handle_t handle) {
	h = handle;
	return true;
}

PAPIPUBLIC bool mod_update() {
	return false;
}

PAPIPUBLIC void mod_shutdown() {

}

PAPIPUBLIC void mod_game_start() {
}
