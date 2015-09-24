#include <cstdarg>
#include <cstdio>
#include <exception>

#include "lexicon/common.hpp"
#include "error.hpp"

void gmerror(errlev lev, char const * fmt...) {
	va_list va;
	va_start(va, fmt);
	char const * str = vasa(fmt, va);

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
	case errlev::term:
		fprintf(stderr, "FATAL: %s", str);
		if (str[strlen(str)-1] != '\n') fputc('\n', stderr);
		std::terminate();
		break;
	}
}
