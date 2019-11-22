#pragma once
#include <string>
#include <fstream>
#include <map>
#include "include.hpp"

namespace engine {

	class shader {
		void load_shader(std::string file_name, GLenum shader_type);
		const std::string read_from_file(std::string file_name);

	public:
		GLuint program_id = 0;
		std::map<std::string, GLint> uniform_ids;
		std::map<GLenum, GLuint> shaders;

		shader(std::string vertex, std::string fragment);
		~shader();
	};
}