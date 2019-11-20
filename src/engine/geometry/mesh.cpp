#include "mesh.hpp"

engine::mesh::mesh(std::string file, math::vec4 color) : diffuse_color(color) {
	load_mesh_data(file);
	process_mesh_data();
	free_mesh_data();
}

engine::mesh::~mesh() {}

void engine::mesh::draw() {
	glBindVertexArray(vaoid);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
	glBindVertexArray(0);
}

void engine::mesh::parse_vertex(std::stringstream& sin) {
	math::vec3 v;
	sin >> v.x >> v.y >> v.z;
	vert_data.push_back(v);
}

void engine::mesh::parse_normal(std::stringstream& sin) {
	math::vec3 n;
	sin >> n.x >> n.y >> n.z;
	norm_data.push_back(n);
}

void engine::mesh::parse_texcoord(std::stringstream& sin) {
	math::vec2 t;
	sin >> t.x >> t.y;
	tex_data.push_back(t);
}

void engine::mesh::parse_face(std::stringstream& sin) {
	std::string token;
	if (norm_data.empty() && tex_data.empty()) {
		for (int i = 0; i < 3; i++) {
			sin >> token;
			v_idx.push_back(std::stoi(token));
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			std::getline(sin, token, '/');
			if (token.size() > 0) v_idx.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) t_idx.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) n_idx.push_back(std::stoi(token));
		}
	}
}

void engine::mesh::parse_line(std::stringstream& sin) {
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parse_vertex(sin);
	else if (s.compare("vt") == 0) parse_texcoord(sin);
	else if (s.compare("vn") == 0) parse_normal(sin);
	else if (s.compare("f") == 0) parse_face(sin);
}

void engine::mesh::load_mesh_data(std::string file) {
	std::ifstream ifile(file);
	std::string line;
	while (std::getline(ifile, line)) {
		std::stringstream sline(line);
		parse_line(sline);
	}
	texels_loaded = (t_idx.size() > 0);
	normals_loaded = (n_idx.size() > 0);
}

void engine::mesh::process_mesh_data() {
	for (unsigned int i = 0; i < v_idx.size(); i++) {
		unsigned int vi = v_idx[i];
		math::vec3 v = vert_data[vi - 1];
		vertices.push_back(v);
		if (texels_loaded) {
			unsigned int ti = t_idx[i];
			math::vec2 t = tex_data[ti - 1];
			texels.push_back(t);
		}
		if (normals_loaded) {
			unsigned int ni = n_idx[i];
			math::vec3 n = norm_data[ni - 1];
			normals.push_back(n);
		}
	}
}

void engine::mesh::free_mesh_data() {
	vert_data.clear();
	tex_data.clear();
	norm_data.clear();
	v_idx.clear();
	t_idx.clear();
	n_idx.clear();
}

void engine::mesh::crete_buffer_objects() {
	std::vector<math::vec4> colors(vertices.size());
	for (int i = 0; i < colors.size(); i++)
		colors[i] = diffuse_color;
	GLuint v_vbo, c_vbo, n_vbo, t_vbo;
	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);
	{
		glGenBuffers(1, &v_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(math::vec3), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3), 0);
		glGenBuffers(1, &c_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(math::vec4), &colors[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(COLORS);
		glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(math::vec4), 0);
		if (this->normals_loaded) {
			glGenBuffers(1, &n_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, n_vbo);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(math::vec3), &normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3), 0);
		}
		if (this->texels_loaded) {
			glGenBuffers(1, &t_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
			glBufferData(GL_ARRAY_BUFFER, texels.size() * sizeof(math::vec2), &texels[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXELS);
			glVertexAttribPointer(TEXELS, 2, GL_FLOAT, GL_FALSE, sizeof(math::vec2), 0);
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
