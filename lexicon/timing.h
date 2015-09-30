#ifndef LEXICON_TIMING_H
#define LEXICON_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

typedef struct timing_s {
	struct timespec start;
	struct timespec pf;
	__syscall_slong_t sleep_target;

	unsigned int gametime;
	double impulse;

} timing_t;

void timing_setup(timing_t *, double target_fps);
void timing_start(timing_t *);
void timing_end_frame(timing_t *);

#ifdef __cplusplus
}
#endif

#endif //LEXICON_TIMING_H
