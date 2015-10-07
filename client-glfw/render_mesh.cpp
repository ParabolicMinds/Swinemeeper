#include "render_mesh.hpp"

static GLuint fullquad_vao;

bool rend::mesh::initialize() {
	glCreateVertexArrays(1, &fullquad_vao);
	return true;
}

void rend::mesh::shutdown() {
	if (fullquad_vao) glDeleteVertexArrays(1, &fullquad_vao);
}
