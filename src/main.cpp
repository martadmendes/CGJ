///////////////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a triangle in Modern OpenGL.
// A "hello world" of Modern OpenGL.
//
// Assignment : Create Shader Abstraction 
//					(e.g. check compilation/linkage for errors, read from file) 
//			  : Manage Multiple Drawable Entities (using your vertex and matrix classes)
//              Draw a set of 7 TANs (i.e. TANGRAM shapes) of different colors: 
//              (1) 3 different TAN geometric shapes at the origin:
//					- right triangle
//					- square
//					- parallelogram
//              (2) 7 TANs of different colors put together to form a shape of
//                  your choice through transformation matrices:
//					- 2 big right triangles
//					- 1 medium right triangle
//					- 2 small right triangles
//					- 1 square
//					- 1 parallelogram;
//
// (c)2013-19 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vertices.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/vec4.hpp"
#include "math/mat2.hpp"
#include "math/mat3.hpp"
#include "math/mat4.hpp"
#include "math/matrix_factory.hpp"

#define VERTICES 0
#define COLORS 1
#define NUM_OBJ 7

math::mat4 transformations[NUM_OBJ]; // array que contem as matrizes de transformações por objecto
int num_indices[NUM_OBJ]; // array que contem o nr de indices por objecto
GLuint VaoId[NUM_OBJ], VboId[3];  // 1 vao por obj, 2 vbo por vao (reutilizados)
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;

#define ERROR_CALLBACK
#ifdef  ERROR_CALLBACK

////////////////////////////////////////////////// ERROR CALLBACK (OpenGL 4.3+)

static const std::string errorSource(GLenum source) {
	switch (source) {
	case GL_DEBUG_SOURCE_API:				return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "window system";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "shader compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:		return "third party";
	case GL_DEBUG_SOURCE_APPLICATION:		return "application";
	case GL_DEBUG_SOURCE_OTHER:				return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorType(GLenum type) {
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:				return "error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	return "deprecated behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	return "undefined behavior";
	case GL_DEBUG_TYPE_PORTABILITY:			return "portability issue";
	case GL_DEBUG_TYPE_PERFORMANCE:			return "performance issue";
	case GL_DEBUG_TYPE_MARKER:				return "stream annotation";
	case GL_DEBUG_TYPE_PUSH_GROUP:			return "push group";
	case GL_DEBUG_TYPE_POP_GROUP:			return "pop group";
	case GL_DEBUG_TYPE_OTHER_ARB:			return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorSeverity(GLenum severity) {
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:			return "high";
	case GL_DEBUG_SEVERITY_MEDIUM:			return "medium";
	case GL_DEBUG_SEVERITY_LOW:				return "low";
	case GL_DEBUG_SEVERITY_NOTIFICATION:	return "notification";
	default:								exit(EXIT_FAILURE);
	}
}

static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam) {
	std::cerr << "GL ERROR:" << std::endl;
	std::cerr << "  source:     " << errorSource(source) << std::endl;
	std::cerr << "  type:       " << errorType(type) << std::endl;
	std::cerr << "  severity:   " << errorSeverity(severity) << std::endl;
	std::cerr << "  debug call: " << std::endl << message << std::endl;
	std::cerr << "Press <return>.";
	std::cin.ignore();
}

void setupErrorCallback() {
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(error, 0);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
	// params: source, type, severity, count, ids, enabled
}

#else

///////////////////////////////////////////////// ERROR HANDLING (All versions)

static const std::string errorString(GLenum error) {
	switch (error) {
	case GL_NO_ERROR:
		return "No error has been recorded.";
	case GL_INVALID_ENUM:
		return "An unacceptable value is specified for an enumerated argument.";
	case GL_INVALID_VALUE:
		return "A numeric argument is out of range.";
	case GL_INVALID_OPERATION:
		return "The specified operation is not allowed in the current state.";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "The framebuffer object is not complete.";
	case GL_OUT_OF_MEMORY:
		return "There is not enough memory left to execute the command.";
	case GL_STACK_UNDERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
	case GL_STACK_OVERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
	default: exit(EXIT_FAILURE);
	}
}

static bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		std::cerr << "OpenGL ERROR [" << errorString(errCode) << "]." << std::endl;
	}
	return isError;
}

static void checkOpenGLError(std::string error) {
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

#endif // ERROR_CALLBACK

/////////////////////////////////////////////////////////////////////// SHADERs

const GLchar* VertexShader =
{
	"#version 330 core\n"

	"in vec4 in_Position;\n"
	"in vec4 in_Color;\n"
	"out vec4 ex_Color;\n"

	"uniform mat4 Matrix;\n"

	"void main(void)\n"
	"{\n"
	"	gl_Position = Matrix * in_Position;\n"
	"	ex_Color = in_Color;\n"
	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 330 core\n"

	"in vec4 ex_Color;\n"
	"out vec4 out_Color;\n"

	"void main(void)\n"
	"{\n"
	"	out_Color = ex_Color;\n"
	"}\n"
};

void createShaderProgram() {
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, 0);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(ProgramId, COLORS, "in_Color");

	glLinkProgram(ProgramId);
	UniformId = glGetUniformLocation(ProgramId, "Matrix");

	glDetachShader(ProgramId, VertexShaderId);
	glDeleteShader(VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	glDeleteShader(FragmentShaderId);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create shaders.");
#endif
}

void destroyShaderProgram() {
	glUseProgram(0);
	glDeleteProgram(ProgramId);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not destroy shaders.");
#endif
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void create_triangle(int obj_num, math::vec4 color) {
	num_indices[obj_num] = 3;
	glGenVertexArrays(1, &VaoId[obj_num]);
	glBindVertexArray(VaoId[obj_num]);
	{
		glGenBuffers(3, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(tr), tr, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
		{
			float vertex_color[4][4] = {
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z}
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_color), vertex_color, GL_STATIC_DRAW);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_tr), indices_tr, GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void create_square(int obj_num, math::vec4 color) {
	num_indices[obj_num] = 6;
	glGenVertexArrays(1, &VaoId[obj_num]);
	glBindVertexArray(VaoId[obj_num]);
	{
		glGenBuffers(3, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(sq), sq, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
		{
			float vertex_color[4][4] = {
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z}
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_color), vertex_color, GL_STATIC_DRAW);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_sq), indices_sq, GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void create_parallelogram(int obj_num, math::vec4 color) {
	num_indices[obj_num] = 6;
	glGenVertexArrays(1, &VaoId[obj_num]);
	glBindVertexArray(VaoId[obj_num]);
	{
		glGenBuffers(3, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(pa), pa, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
		{
			float vertex_color[4][4] = {
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z},
				{color.x, color.y, color.z, color.z}
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_color), vertex_color, GL_STATIC_DRAW);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_pa), indices_pa, GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void createBufferObjects() {
	math::vec3 z = math::vec3(0, 0, 1);
	math::mat4 id = math::matrix_factory::identity4x4();
	//final scale if needed
	math::mat4 final_scale = math::matrix_factory::scale(0.5f, 0.5f, 1.0f);

	//triangle 1: rotate + translate
	math::mat4 t1_rotate = math::matrix_factory::rodrigues(180, z);
	math::mat4 t1_translate = math::matrix_factory::translate(1.0f, 0.0f, 0.0f);

	transformations[0] =  t1_translate * t1_rotate;

	//triangle 2: rotate + translate
	math::mat4 t2_rotate = math::matrix_factory::rodrigues(135, z);
	math::mat4 t2_translate = math::matrix_factory::translate(0.35f, -0.35f, 0.0f);

	transformations[1] = t2_translate * t2_rotate;


	//triangle 3: scale + rotate + translate
	math::mat4 t3_scale = math::matrix_factory::scale(sqrt(0.5f), sqrt(0.5f), 1.0);
	math::mat4 t3_rotate = math::matrix_factory::rodrigues(-135, z);
	math::mat4 t3_translate = math::matrix_factory::translate(0.5f, 0.5f, 0.0f);

	transformations[2] = t3_translate * t3_rotate * t3_scale;

	//square 4: rotate + scale + translate
	math::mat4 s4_scale = math::matrix_factory::scale(0.5f, 0.5f, 1.0f);
	math::mat4 s4_rotate = math::matrix_factory::rodrigues(45.0f, z);
	math::mat4 s4_translate = math::matrix_factory::translate(-0.0015f, 0.355f, 0.0f);

	transformations[3] = s4_translate * s4_rotate * s4_scale;


	//parallelogram 5: rotate + scale + translate
	math::mat4 p5_scale = math::matrix_factory::scale(1.0f, 0.35f, 1.0f);
	math::mat4 p5_rotate = math::matrix_factory::rodrigues(90.0f, z);
	math::mat4 p5_translate = math::matrix_factory::translate(-0.53f, 0.0f, 0.0f);

	transformations[4] =  p5_translate * p5_rotate * p5_scale;


	//triangle 6: scale + rotate + translate
	math::mat4 t6_scale = math::matrix_factory::scale(0.5f, 0.5f, 1.0);
	math::mat4 t6_rotate = math::matrix_factory::rodrigues(45, z);
	math::mat4 t6_translate = math::matrix_factory::translate(-0.60f, 0.61f, 0.0f);

	transformations[5] = t6_translate * t6_rotate * t6_scale;


	//triangle 7: scale + rotate + translate
	math::mat4 t7_scale = math::matrix_factory::scale(0.5f, 0.5f, 1.0);
	math::mat4 t7_rotate = math::matrix_factory::rodrigues(-45, z);
	math::mat4 t7_translate = math::matrix_factory::translate(-0.71f, 0.5f, 0.0f);

	transformations[6] = t7_translate * t7_rotate * t7_scale;


	create_triangle(0, white);
	create_triangle(1, lilac);
	create_triangle(2, blue);
	create_square(3, red);
	create_parallelogram(4, orange);
	create_triangle(5, green);
	create_triangle(6, yellow);


#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void destroyBufferObjects() {
	for (int i = 0; i < NUM_OBJ; i++) {
		glBindVertexArray(VaoId[i]);
		glDisableVertexAttribArray(VERTICES);
		glDisableVertexAttribArray(COLORS);
		glDeleteBuffers(3, VboId);
		glDeleteVertexArrays(1, &VaoId[i]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

#ifndef ERROR_CALLBACK
		checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
#endif
	}
}

/////////////////////////////////////////////////////////////////////// SCENE

void drawScene() {
	math::mat4 identity = math::matrix_factory::identity4x4();
	//int i = 0;
	for (int i = 0; i < NUM_OBJ; i++) {
		glBindVertexArray(VaoId[i]);
		glUseProgram(ProgramId);

		glUniformMatrix4fv(UniformId, 1, GL_FALSE, transformations[i].data);
		glDrawElements(GL_TRIANGLES, num_indices[i], GL_UNSIGNED_SHORT, (GLvoid*)0);

		glUseProgram(0);
		glBindVertexArray(0);

#ifndef ERROR_CALLBACK
		checkOpenGLError("ERROR: Could not draw scene.");
#endif
	}
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win) {
	destroyShaderProgram();
	destroyBufferObjects();
}

void window_size_callback(GLFWwindow* win, int winx, int winy) {
	glViewport(0, 0, winx, winy);
}

///////////////////////////////////////////////////////////////////////// SETUP

void glfw_error_callback(int error, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}

GLFWwindow* setupWindow(int winx, int winy, const char* title,
	int is_fullscreen, int is_vsync) {
	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
	if (!win) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(is_vsync);
	return win;
}

void setupCallbacks(GLFWwindow* win) {
	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
	setupCallbacks(win);

#if _DEBUG
	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
	return win;
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	// Allow extension entry points to be loaded even if the extension isn't 
	// present in the driver's extensions string.
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	// You might get GL_INVALID_ENUM when loading GLEW.
}

void checkOpenGLInfo() {
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy) {
#if _DEBUG
	checkOpenGLInfo();
#endif
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glViewport(0, 0, winx, winy);
}

GLFWwindow* setup(int major, int minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
	GLFWwindow* win =
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);
#ifdef ERROR_CALLBACK
	setupErrorCallback();
#endif
	createShaderProgram();
	createBufferObjects();
	return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void display(GLFWwindow* win, double elapsed_sec) {
	drawScene();
}

void run(GLFWwindow* win) {
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win)) {
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(win, elapsed_time);
		glfwSwapBuffers(win);
		glfwPollEvents();
#ifndef ERROR_CALLBACK
		checkOpenGLError("ERROR: MAIN/RUN");
#endif
	}
	glfwDestroyWindow(win);
	glfwTerminate();
}

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		640, 640, "Hello Modern 2D World", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END