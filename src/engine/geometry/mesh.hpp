#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "..\include.hpp"
#include "..\shader.hpp"
#include "../geometry/vertices.hpp"

namespace engine {
	class mesh {
	public:
		std::vector<math::vec3> vertices;
		std::vector<math::vec3> normals;
		std::vector<math::vec2> texels;
		GLuint vaoid;

		template<std::size_t SIZE_V, std::size_t SIZE_I>
		mesh(const Vertex(&vertices)[SIZE_V], const GLushort(&indices)[SIZE_I], const math::vec4 color);
		mesh(std::string file, math::vec4 color);
		~mesh();

		void draw();
	private:
		std::vector<math::vec3> vert_data;
		std::vector<math::vec3> norm_data;
		std::vector<math::vec2> tex_data;
		std::vector<unsigned int> v_idx, n_idx, t_idx;
		bool normals_loaded, texels_loaded, elements_loaded;
		int num_indices;

		void parse_vertex(std::stringstream& sin);
		void parse_normal(std::stringstream& sin);
		void parse_texcoord(std::stringstream& sin);
		void parse_face(std::stringstream& sin);
		void parse_line(std::stringstream& sin);

		void load_mesh_data(std::string file);
		void process_mesh_data();
		void free_mesh_data();
		void crete_buffer_objects(math::vec4 color);
	};
	template<std::size_t SIZE_V, std::size_t SIZE_I>
	inline mesh::mesh(const Vertex(&vertices)[SIZE_V],
		const GLushort(&indices)[SIZE_I], const math::vec4 color) :
		elements_loaded(true), normals_loaded(false), texels_loaded(false) {
		GLuint VboId[3];
		num_indices = SIZE_I;
		std::vector<math::vec4> colors(SIZE_V);
		for (int i = 0; i < colors.size(); i++)
			colors[i] = color;
		glGenVertexArrays(1, &vaoid);
		glBindVertexArray(vaoid);
		{
			glGenBuffers(3, VboId);

			glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
			{
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glEnableVertexAttribArray(VERTICES);
				glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, 0, 0);
			}
			glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
			{
				glGenBuffers(1, &VboId[1]);
				glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
				glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(math::vec4), &colors[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(COLORS);
				glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(math::vec4), 0);
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
			{
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			}
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}