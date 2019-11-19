#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <map>

namespace engine {

	class shader {
	public:
		GLuint program_id = 0;
		std::map<std::string, GLint> uniforms;
		std::map<GLenum, GLuint> shaders;

		shader();
		~shader();

		void prepare();
		void create();
		void bind_attr(GLuint index, const GLchar* name);
		void link();

		void delete_shader(GLenum type);
		void delete_program();
		void detach(GLenum ShaderType);
		void checkOpenGLError(std::string error);
		void Attach(GLenum ShaderType);
		void AddUniform(const char*);
		void AddUniformBlock(const char* UniformBlockName);
		void BindUniformBlock(GLint UboID, const GLuint UboBP);
		void Enable();
		void Disable();
		GLint GetUniform(const char* UniformName);
		GLint getUniform(const char* UniformName);
		GLint GetUniformBlock(const char* UniformBlockName);
		const std::string LoadFromFile(std::string filename);

	private:
		GLuint fragment_shader_id = 0, vertex_shader_id = 0;
	};
}