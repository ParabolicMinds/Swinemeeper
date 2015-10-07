#ifndef CORE_HPP
#define CORE_HPP

#include "lexicon/common.hpp"
#include "lexicon/player_api.hpp"

#include <atomic>

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace core {

	extern GLFWwindow * win;
	extern handle_t handle;
	extern std::atomic_bool should_run;

}

#define clog(fmt ...) gm_print(core::handle, errlev::log, fmt);
#define cwarn(fmt ...) gm_print(core::handle, errlev::warning, fmt);
#define cerr(fmt ...) gm_print(core::handle, errlev::error, fmt);

#endif //CORE_HPP
