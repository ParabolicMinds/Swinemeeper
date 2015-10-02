#include <cstdio>
#include <exception>
#include <mutex>

#include "lexicon/common.hpp"
#include "error.hpp"

static std::mutex print_m;

void gmerror(errlev lev, char const * str) {
	print_m.lock();
	switch(lev) {
	default:
	case errlev::debug: //TODO: DEBUG
	case errlev::log:
		fprintf(stdout, "LOG: %s", str);
		if (str[strlen(str)-1] != '\n') fputc('\n', stdout);
		break;
	case errlev::warning:
		fprintf(stderr, "WARNING: %s", str);
		if (str[strlen(str)-1] != '\n') fputc('\n', stderr);
		break;
	case errlev::error:
		fprintf(stderr, "ERROR: %s", str);
		if (str[strlen(str)-1] != '\n') fputc('\n', stderr);
		break;
	}
	print_m.unlock();
}

void gmterm(char const * str, int code) {
	fprintf(stderr, "FATAL: %s", str);
	if (str[strlen(str)-1] != '\n') fputc('\n', stderr);
	exit(code);
}
