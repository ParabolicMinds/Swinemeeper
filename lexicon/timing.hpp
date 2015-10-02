#ifndef LEXICON_TIMING_HPP
#define LEXICON_TIMING_HPP

#include <chrono>

namespace lexicon {

	typedef double impulse_t;
	typedef unsigned int gametime_t;

	class frame_timer {
	public:
		impulse_t const & impulse;
		gametime_t const & gametime;
		frame_timer(double target_fps = 60.0);
		void start();
		void sleep_for_target();
		void end_frame();
		void stop();
		void reset();
	private:
		impulse_t _impulse = 0;
		impulse_t _impulse_target = 0;
		gametime_t _gametime = 0;
		gametime_t _gametime_perpetual = 0;
		gametime_t _gametime_timescale = 0;
		std::chrono::high_resolution_clock::time_point _start;
		std::chrono::high_resolution_clock::time_point _frame;
	};
}

#endif //LEXICON_TIMING_HPP
