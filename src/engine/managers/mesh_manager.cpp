#include "mesh_manager.hpp"

engine::managers::mesh_manager* engine::managers::mesh_manager::instance;

void engine::managers::mesh_manager::destroy() {
	while (!meshes.empty()) {
		auto it = meshes.begin();
		mesh* m = it->second;
		meshes.erase(it);
		delete m;
	}
}

engine::managers::mesh_manager* engine::managers::mesh_manager::get_instance() {
	if (!instance) instance = new mesh_manager();
	return instance;
}

void engine::managers::mesh_manager::clean_manager() {
	if (instance) {
		instance->destroy();
		delete instance;
	}
	instance = nullptr;
}

void engine::managers::mesh_manager::add_mesh(std::string name, mesh* m) {
	meshes[name] = m;
}

engine::mesh* engine::managers::mesh_manager::get_mesh(std::string name) {
	auto it = meshes.find(name);
	if (it == meshes.end()) return nullptr;
	return it->second;
}