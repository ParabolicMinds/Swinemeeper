#include "timing.h"

#include "assert.h"

#define NANO 1000000000

void timing_setup(timing_t * time, double target_fps) {
	time->sleep_target = (1/target_fps) * NANO;
}

void timing_start(timing_t * time) {
	clock_gettime(CLOCK_MONOTONIC, &time->start);
	time->pf = time->start;
}

void timing_end_frame(timing_t * time) {
	struct timespec cf, diff;
	clock_gettime(CLOCK_MONOTONIC, &cf);
	diff.tv_nsec = cf.tv_nsec - time->pf.tv_nsec;
	diff.tv_sec = cf.tv_sec - time->pf.tv_sec;
	while(diff.tv_nsec < 0 || diff.tv_sec > 0) {diff.tv_sec -= 1; diff.tv_nsec += NANO;}
	assert(diff.tv_nsec > 0 && diff.tv_sec == 0);
	if (diff.tv_nsec < time->sleep_target) {
		diff.tv_nsec = time->sleep_target - diff.tv_nsec;
		nanosleep(&diff, NULL);
		clock_gettime(CLOCK_MONOTONIC, &cf);
		diff.tv_nsec = cf.tv_nsec - time->pf.tv_nsec;
		diff.tv_sec = cf.tv_sec - time->pf.tv_sec;
		while(diff.tv_nsec < 0 || diff.tv_sec > 0) {diff.tv_sec -= 1; diff.tv_nsec += NANO;}
	}
	time->impulse = diff.tv_nsec / ((double)NANO);
	diff.tv_nsec = cf.tv_nsec - time->start.tv_nsec;
	diff.tv_sec = cf.tv_sec - time->start.tv_sec;
	while(diff.tv_nsec < 0) {diff.tv_sec -= 1; diff.tv_nsec += NANO;}
	time->gametime = (diff.tv_sec * 1000) + (diff.tv_nsec / (NANO / 1000));
	time->pf = cf;
}
