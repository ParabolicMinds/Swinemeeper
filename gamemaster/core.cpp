#include <cstdio>
#include <cstring>

#include "lexicon/common.hpp"
#include "module.hpp"
#include "error.hpp"

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
    return 0;
}
