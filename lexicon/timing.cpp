#include "timing.hpp"

#include <thread>

typedef std::chrono::duration<lexicon::impulse_t, std::ratio<1, 1>> impulse_dur_t;
typedef std::chrono::duration<lexicon::gametime_t, std::milli> gametime_dur_t;

typedef std::chrono::high_resolution_clock hc;
typedef hc::time_point tp_t;

#define NOW std::chrono::high_resolution_clock::now()

lexicon::frame_timer::frame_timer(float target_fps) : impulse(_impulse), gametime(_gametime), _impulse_target(1.0 / target_fps) {}

void lexicon::frame_timer::start() {
	_start = NOW;
	_frame = _start;
	running = true;
}

void lexicon::frame_timer::sleep_for_target() {
	tp_t c = NOW;
	impulse_dur_t diffi = std::chrono::duration_cast<impulse_dur_t>(c - _frame);
	impulse_t span = _impulse_target - diffi.count();
	if (span > 0) std::this_thread::sleep_for(impulse_dur_t(span));
}

void lexicon::frame_timer::end_frame() {
	if (!running) return;
	tp_t c = NOW;
	impulse_dur_t diffi = std::chrono::duration_cast<impulse_dur_t>(c - _frame);
	gametime_dur_t diffg = std::chrono::duration_cast<gametime_dur_t>(c - _start);
	_impulse = diffi.count();
	_gametime_timescale = diffg.count();
	_gametime = _gametime_perpetual + _gametime_timescale;
	_frame = c;

}

void lexicon::frame_timer::stop() {
	this->end_frame();
	_gametime_perpetual = _gametime;
	_impulse = 0;
	running = false;
}

void lexicon::frame_timer::reset() {
	_start = NOW;
	_frame = _start;
	_gametime = 0;
	_gametime_perpetual = 0;
	_gametime_timescale = 0;
	_impulse = 0;
}
