#include "shader_manager.hpp"

engine::managers::shader_manager* engine::managers::shader_manager::instance;

void engine::managers::shader_manager::destroy() {
	while (!shaders.empty()) {
		auto it = shaders.begin();
		shader* shdr = it->second;
		shaders.erase(it);
		delete shdr;
	}
}

engine::managers::shader_manager* engine::managers::shader_manager::get_instance() {
	if (!instance) instance = new shader_manager();
	return instance;
}

void engine::managers::shader_manager::clean_manager() {
	if (instance) {
		instance->destroy();
		delete instance;
	}
	instance = nullptr;
}

void engine::managers::shader_manager::add_shader(std::string name, shader* shdr) {
	shaders[name] = shdr;
}

engine::shader* engine::managers::shader_manager::get_shader(std::string name) {
	auto it = shaders.find(name);
	if (it == shaders.end()) return nullptr;
	return it->second;
}