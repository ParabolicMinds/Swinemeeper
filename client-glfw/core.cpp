#include "lexicon/common.hpp"
#include "lexicon/player_api.hpp"

#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static handle_t h;

static GLFWwindow * win = nullptr;

PAPIPUBLIC bool mod_initialize(handle_t handle) {
	h = handle;

	if (glfwInit() != GL_TRUE) {
		gm_printf(h, errlev::error, "GLFW Failed to initialize!");
		return false;
	}

	win = glfwCreateWindow(800, 600, "TEST", nullptr, nullptr);
	if (!win) {
		gm_printf(h, errlev::error, "GLFW Failed to create a window!");
		return false;
	}

	glfwSwapInterval(1);

	return true;
}

PAPIPUBLIC bool mod_update(unsigned int gametime, double impulse) {
	glfwPollEvents();
	if (glfwWindowShouldClose(win)) return false;
	gm_printf(h, errlev::debug, "Frame: Impulse (%f s), Game Time(%i ms)", impulse, gametime);
	//glfwSwapBuffers(win);
	return true;
}

PAPIPUBLIC void mod_shutdown() {
	glfwTerminate();
}

PAPIPUBLIC void mod_game_start() {

}
