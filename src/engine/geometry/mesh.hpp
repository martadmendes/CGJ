#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "..\include.hpp"
#include "..\shader.hpp"

namespace engine {
	class mesh {
	public:
		std::vector<math::vec3> vertices;
		std::vector<math::vec3> normals;
		std::vector<math::vec2> texels;
		math::vec4 diffuse_color;
		GLuint vaoid;

		mesh(std::string file, math::vec4 color);
		~mesh();

		void draw();
	private:
		std::vector<math::vec3> vert_data;
		std::vector<math::vec3> norm_data;
		std::vector<math::vec2> tex_data;
		std::vector<unsigned int> v_idx, n_idx, t_idx;
		bool normals_loaded, texels_loaded;

		void parse_vertex(std::stringstream& sin);
		void parse_normal(std::stringstream& sin);
		void parse_texcoord(std::stringstream& sin);
		void parse_face(std::stringstream& sin);
		void parse_line(std::stringstream& sin);

		void load_mesh_data(std::string file);
		void process_mesh_data();
		void free_mesh_data();
		void crete_buffer_objects();
	};
}