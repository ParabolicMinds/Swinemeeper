#include <cstring>
#include <cstdarg>
#include <cstdio>

#include "common.hpp"

#define MBUF_SIZE 1024
#define MBUF_NUM 8
__thread char mbuf[MBUF_NUM][MBUF_SIZE];
__thread int mbufn = 0;

#define MBUF_INCR mbufn++; if (mbufn >= MBUF_NUM) mbufn = 0
#define MBUF_CUR mbuf[mbufn]

char const * vas(char const * fmt, ...) {
	MBUF_INCR;
	memset(MBUF_CUR, 0, MBUF_SIZE);
	va_list va;
	va_start(va, fmt);
	vsnprintf(MBUF_CUR, MBUF_SIZE, fmt, va);
	return MBUF_CUR;
}

char const * vasa(char const * fmt, va_list va) {
	MBUF_INCR;
	memset(MBUF_CUR, 0, MBUF_SIZE);
	vsnprintf(MBUF_CUR, MBUF_SIZE, fmt, va);
	return MBUF_CUR;
}
