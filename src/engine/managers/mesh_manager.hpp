#pragma once

#include <map>
#include <string>

#include "../geometry/mesh.hpp"

namespace engine {
	namespace managers {
		class mesh_manager {
			static mesh_manager* instance;
			std::map<std::string, mesh*> meshes;

			void destroy();
		public:

			static mesh_manager* get_instance();
			static void clean_manager();
			void add_mesh(std::string name, mesh* m);
			mesh* get_mesh(std::string name);
		};
	}
}