#include "core.hpp"
#include "input.hpp"
#include "render.hpp"

#include <cstdio>
#include <thread>

GLFWwindow * core::win = nullptr;
handle_t core::handle;
std::atomic_bool core::should_run {true};

static std::thread * input_th = nullptr;
static std::thread * render_th = nullptr;

PAPIPUBLIC bool mod_initialize(handle_t handle) {
	core::handle = handle;

	if (glfwInit() != GL_TRUE) {
		cerr("GLFW Failed to initialize!");
		return false;
	}

	core::win = glfwCreateWindow(800, 600, "TEST", nullptr, nullptr);
	if (!core::win) {
		cerr("GLFW Failed to create a window!");
		return false;
	}

	input_th = new std::thread(input::input_loop);
	render_th = new std::thread(rend::render_loop);

	return true;
}

PAPIPUBLIC bool mod_update(unsigned int gametime, double impulse) {
	if (!core::should_run) glfwSetWindowShouldClose(core::win, true);
	return core::should_run;
}

PAPIPUBLIC void mod_shutdown() {
	core::should_run.store(false);
	if (render_th && render_th->joinable()) {
		render_th->join();
		delete render_th;
	}
	if (input_th && input_th->joinable()) {
		input_th->join();
		delete input_th;
	}
	glfwTerminate();
}

PAPIPUBLIC void mod_game_start() {

}

PAPIPUBLIC void mod_game_end() {

}
