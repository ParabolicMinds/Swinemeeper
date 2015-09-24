#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <thread>

#define MBUF_SIZE 4096
thread_local char mbuf[MBUF_SIZE];

char const * vas(char const * fmt...) {
	memset(mbuf, 0, MBUF_SIZE);
	va_list va;
	va_start(va, fmt);
	vsnprintf(mbuf, MBUF_SIZE, fmt, va);
	return mbuf;
}

char const * vasa(char const * fmt, va_list & va) {
	memset(mbuf, 0, MBUF_SIZE);
	vsnprintf(mbuf, MBUF_SIZE, fmt, va);
	return mbuf;
}
