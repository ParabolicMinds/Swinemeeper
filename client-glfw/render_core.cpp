#include "core.hpp"
#include "render.hpp"
#include "render_routine.hpp"

#include "lexicon/timing.hpp"

void rend::render_loop() {
	glfwSwapInterval(1);
	glfwMakeContextCurrent(core::win);
	if (glewInit() != GLEW_OK) {
		cerr("failed to initialize GLEW.");
		return;
	}
	if (!GLEW_VERSION_4_5) {
		cwarn("\n\tYour system does not seem to be fully OpenGL 4.5 compliant. "
			  "\n\tThis module was developed and tested on an OpenGL 4.5 compliant system, and relies on some OpenGL 4.5 functions. "
			  "\n\tYou may experience crashing or total non-function if your driver does not support these functions.");
	}
	if (!rend::routine::initialize()) {
		cerr("failed to initialize render routines.")
		core::should_run.store(false);
		rend::routine::shutdown();
		return;
	}
	lexicon::frame_timer t {60};
	t.start();
	while (core::should_run) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(core::win);
		t.sleep_for_target();
		t.end_frame();
	}
	rend::routine::shutdown();
}
