#include "shader.hpp"

engine::shader::shader() {
	uniform_ids = std::map<std::string, GLint>();
	shaders = std::map<GLenum, GLuint>();
}

engine::shader::~shader() {}

void engine::shader::create() {
	load_shader("resources/shaders/shader.vert", GL_VERTEX_SHADER);
	load_shader("resources/shaders/shader.frag", GL_FRAGMENT_SHADER);

	program_id = glCreateProgram();
	glAttachShader(program_id, shaders[GL_VERTEX_SHADER]);
	glAttachShader(program_id, shaders[GL_FRAGMENT_SHADER]);

	glBindAttribLocation(program_id, VERTICES, "in_Position");
	glBindAttribLocation(program_id, COLORS, "in_Color");

	glLinkProgram(program_id);
	uniform_ids["projection"] = glGetUniformLocation(program_id, "ProjectionMatrix");
	uniform_ids["view"] = glGetUniformLocation(program_id, "ViewMatrix");
	uniform_ids["model"] = glGetUniformLocation(program_id, "ModelMatrix");

	glDetachShader(program_id, shaders[GL_VERTEX_SHADER]);
	glDeleteShader(shaders[GL_VERTEX_SHADER]);
	glDetachShader(program_id, shaders[GL_FRAGMENT_SHADER]);
	glDeleteShader(shaders[GL_FRAGMENT_SHADER]);
}

void engine::shader::delete_shader() {
	glUseProgram(0);
	glDeleteProgram(program_id);
}

void engine::shader::load_shader(std::string file_name, GLenum shader_type) {
	shaders[shader_type] = glCreateShader(shader_type);
	std::string shdr = read_from_file(file_name);
	const GLchar* shader_code = shdr.c_str();
	glShaderSource(shaders[shader_type], 1, &shader_code, 0);
	glCompileShader(shaders[shader_type]);
}

const std::string engine::shader::read_from_file(std::string file_name) {
	std::ifstream shader_file;
	std::string src;
	shader_file.open(file_name);

	if (shader_file.is_open() == false) {
		throw std::exception("Can't open file.");
	}

	std::string line_content = "";
	while (!shader_file.eof()) {
		std::getline(shader_file, line_content);
		src.append(line_content + "\n");
	}
	shader_file.close();
	return src;
}
