#include "render_routine.hpp"
#include "render_mesh.hpp"

bool rend::routine::initialize() {
	if (!rend::mesh::initialize()) {
		cerr("failed to initialize meshes.");
	}
	glClearColor(0.25f, 0.0f, 0.0f, 1.0f);
	return true;
}

void rend::routine::shutdown() {
	rend::mesh::shutdown();
}
