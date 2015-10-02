#include <csignal>
#include <cstdio>
#include <cstring>

#include "lexicon/common.hpp"
#include "lexicon/timing.hpp"
#include "module.hpp"
#include "error.hpp"

char com_str[1024];

static bool cmd_run = true;

int command_loop() {
	lexicon::frame_timer t {60};
	t.start();
	while (cmd_run) {
		if (!module::signal_update(t.gametime, t.impulse)) {
			gmerrf(errlev::log, "No more modules loaded, shutting down...");
			return 0;
		}
		t.sleep_for_target();
		t.end_frame();
	}
	gmerrf(errlev::log, "Shutting Down...");
	module::shutdown();
	return 0;
}

void interrupt_handler(int) {
	cmd_run = false;
}

int main(int argc, char * * argv) {
	signal (SIGINT, interrupt_handler);
	if (argc == 1) {
		gmerrf(errlev::error, "At least one module required.\n");
		return 1;
	} else {
		for (int argi = 1; argi < argc; argi++) {
			char const * arg = argv[argi];
			if (!module::load(arg)) gmtermf(-1, "failed to load requested modules.");
		}
	}
	int r =  command_loop();
	if (r) gmerrf(errlev::log, "Exiting with error code: %i", r); else gmerrf(errlev::log, "Exiting normally...");
	return r;
}
