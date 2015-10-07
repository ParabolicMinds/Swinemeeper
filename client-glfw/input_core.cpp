#include "core.hpp"
#include "input.hpp"

#include "lexicon/timing.hpp"

void input::input_loop() {
	lexicon::frame_timer t {250};
	t.start();
	while (core::should_run) {
		glfwPollEvents();
		if (glfwWindowShouldClose(core::win)) {
			core::should_run.store(false);
			continue;
		}
		t.sleep_for_target();
		t.end_frame();
	}
}
