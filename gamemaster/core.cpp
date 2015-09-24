#include <cstdio>
#include <cstring>

#include "lexicon/common.hpp"
#include "module.hpp"

int main(int argc, char * * argv) {
	if (argc == 1) {
		printf("Cannot start game with no players.\n");
		return 1;
	} else {
		for (int argi = 1; argi < argc; argi++) {
			char const * arg = argv[argi];
			module::load(arg);
		}
	}
    return 0;
}
