#include "scene_node.hpp"

engine::scene_node::scene_node() {
	model_matrix = math::matrix_factory::identity4x4();
	q = math::qtrn(1.0f, math::vec3(0.0f, 0.0f, 0.0f));
}

engine::scene_node::~scene_node() {
	shdr = nullptr;
	m = nullptr;
	parent = nullptr;

	while (!children.empty()) {
		scene_node* child = children.back();
		children.pop_back();
		delete child;
	}
}

engine::scene_node* engine::scene_node::create_child() {
	scene_node* child = new scene_node();
	child->shdr = this->shdr;
	child->parent = this;
	child->model_matrix = this->model_matrix;
	children.push_back(child);
	return children.back();
}

void engine::scene_node::draw(math::mat4 view, math::mat4 projection) {
	if (m != nullptr) {
		glUseProgram(shdr->program_id);
		glUniformMatrix4fv(shdr->uniform_ids["model"], 1, GL_FALSE, model_matrix.data);
		glUniformMatrix4fv(shdr->uniform_ids["view"], 1, GL_FALSE, view.data);
		glUniformMatrix4fv(shdr->uniform_ids["projection"], 1, GL_FALSE, projection.data);
		m->draw();
	}
	for (auto& child : children) {
		child->draw(view, projection);
	}
}

void engine::scene_node::destroy() {
	while (children.size() > 0) {
		children.back()->destroy();
		children.pop_back();
	}
	delete(this);
}
