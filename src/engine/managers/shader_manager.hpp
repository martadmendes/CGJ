#pragma once

#include <map>
#include <string>

#include "../shader.hpp"

namespace engine {
	namespace managers {
		class shader_manager {
			static shader_manager* instance;
			std::map<std::string, shader*> shaders;

			void destroy();

		public:
			static shader_manager* get_instance();
			static void clean_manager();
			void add_shader(std::string name, shader* shdr);
			shader* get_shader(std::string name);
		};
	}
}