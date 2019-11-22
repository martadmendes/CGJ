#pragma once

#include <map>
#include <string>

#include "../scene/scene_graph.hpp"

namespace engine {
	namespace managers {
		class scene_manager {
			static scene_manager* instance;
			std::map<std::string, scene_graph*> scenes;

			void destroy();

		public:
			static scene_manager* get_instance();
			static void clean_manager();
			void add_scene(std::string name, scene_graph* scene);
			scene_graph* get_scene(std::string name);
		};
	}
}