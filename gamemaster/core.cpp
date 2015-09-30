#include <cstdio>
#include <cstring>

#include "lexicon/common.h"
#include "lexicon/timing.h"
#include "module.hpp"
#include "error.hpp"

char com_str[1024];

int command_loop() {
	timing_t t;
	timing_setup(&t, 125);
	timing_start(&t);
	for (;;) {
		module::signal_update();
		gmerrf(errlev::log, "Frame: Impulse (%f s), Game Time(%i ms)", t.impulse, t.gametime);
		timing_end_frame(&t);
	}
}

int main(int argc, char * * argv) {
	if (argc == 1) {
		printf("Cannot start game with no players.\n");
		return 1;
	} else {
		for (int argi = 1; argi < argc; argi++) {
			char const * arg = argv[argi];
			if (!module::load(arg)) gmerrf(errlev::term, "failed to load requested modules.");
		}
	}
	return command_loop();
}
