#include "scene_manager.hpp"

engine::managers::scene_manager* engine::managers::scene_manager::instance;

void engine::managers::scene_manager::destroy() {
	while (!scenes.empty()) {
		auto it = scenes.begin();
		scene_graph* scene = it->second;
		scenes.erase(it);
		delete scene;
	}
}

engine::managers::scene_manager* engine::managers::scene_manager::get_instance() {
	if (!instance) instance = new scene_manager();
	return instance;
}

void engine::managers::scene_manager::clean_manager() {
	if (instance) {
		instance->destroy();
		delete instance;
	}
	instance = nullptr;
}

void engine::managers::scene_manager::add_scene(std::string name, scene_graph* scene) {
	scenes[name] = scene;
}

engine::scene_graph* engine::managers::scene_manager::get_scene(std::string name) {
	auto it = scenes.find(name);
	if (it == scenes.end()) return nullptr;
	return it->second;
}
