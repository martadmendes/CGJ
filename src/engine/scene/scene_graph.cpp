#include "scene_graph.hpp"

engine::scene_graph::scene_graph() {
	root = new scene_node();
}

engine::scene_graph::~scene_graph() {
	delete root;
	root = nullptr;
}

void engine::scene_graph::draw(math::mat4 view, math::mat4 projection) {
	root->draw(view, projection);
	glUseProgram(0);
}
