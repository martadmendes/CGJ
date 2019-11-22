///////////////////////////////////////////////////////////////////////////////
//
// Assignment consists in the following:
//
// - Create the following changes to your scene:
//   - Make your TANs double-faced, so they can be seen from both sides.
//   - The new face of each TAN should share the same hue as the original top
//     face color but have a different level of saturation and brightness.
//
// - Add the following functionality (consider a Camera class):
//   - Create a View Matrix from (eye, center, up) parameters.
//   - Create an Orthographic Projection Matrix from (left-right, bottom-top, 
//     near-far) parameters.
//   - Create a Perspective Projection Matrix from (fovy, aspect, nearZ, farZ) 
//     parameters.
//
// - Add the following dynamics to the application:
//   - Create a free 3D camera controlled by the mouse (orientation) and 
//     keyboard (movement) allowing to visualize the scene through all its 
//     angles.
//   - Change perspective from orthographic to perspective and back as
//     a response to pressing the key 'p'.
//
// (c) 2013-19 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include "engine/include.hpp"
#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/scene/scene_node.hpp"
#include "tests/vector_unit_tests.hpp"
#include "tests/matrix_unit_tests.hpp"
#include "engine/geometry/colors.hpp"
#include "engine/managers/mesh_manager.hpp"
#include "engine/managers/shader_manager.hpp"
#include "engine/managers/scene_manager.hpp"

engine::camera cam;
int WIDTH = 640, HEIGHT = 640;
float SPEED = 0.1f;

bool mouse_pressed = false;
engine::math::vec2 last_mouse_pos = engine::math::vec2(-1.0f, -1.0f);

bool is_gimbal = false;

#define ERROR_CALLBACK
#ifdef  ERROR_CALLBACK

///////////////////////////////////////////////////////////////////////// ERROR CALLBACK (OpenGL 4.3+)

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

///////////////////////////////////////////////////////////////////////// ERROR HANDLING (All versions)

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

///////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createMeshes() {
	engine::mesh* m = new engine::mesh(sq, indices_sq, lilac);
	engine::managers::mesh_manager::get_instance()->add_mesh("square1", m);
	m = new engine::mesh(sq, indices_sq, blue);
	engine::managers::mesh_manager::get_instance()->add_mesh("square2", m);
	m = new engine::mesh(sq, indices_sq, yellow);
	engine::managers::mesh_manager::get_instance()->add_mesh("square3", m);
	m = new engine::mesh(sq, indices_sq, orange);
	engine::managers::mesh_manager::get_instance()->add_mesh("square4", m);
	m = new engine::mesh(sq, indices_sq, green);
	engine::managers::mesh_manager::get_instance()->add_mesh("square5", m);
	m = new engine::mesh(sq, indices_sq, red);
	engine::managers::mesh_manager::get_instance()->add_mesh("square6", m);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

///////////////////////////////////////////////////////////////////////// SCENE

void setupScenes() {
	engine::math::vec3 z = engine::math::vec3(0, 0, 1);
	engine::math::vec3 y = engine::math::vec3(0, 1, 0);
	engine::math::vec3 x = engine::math::vec3(1, 0, 0);

	engine::scene_graph* main_scene = new engine::scene_graph();

	engine::scene_node* root_node = main_scene->root;
	root_node->shdr = engine::managers::shader_manager::get_instance()->get_shader("main");
	engine::scene_node* child = root_node->create_child();
	child->model_matrix = engine::math::matrix_factory::translate(0.0f, 0.0f, 0.5f);
	child->m = engine::managers::mesh_manager::get_instance()->get_mesh("square1");
	child = root_node->create_child();
	child->model_matrix = engine::math::matrix_factory::translate(0.0f, 0.0f, -0.5f) * engine::math::matrix_factory::rodrigues(x, 180);
	child->m = engine::managers::mesh_manager::get_instance()->get_mesh("square2");
	child = root_node->create_child();
	child->model_matrix = engine::math::matrix_factory::translate(0.0f, 0.5f, 0.0f) * engine::math::matrix_factory::rodrigues(x, -90);
	child->m = engine::managers::mesh_manager::get_instance()->get_mesh("square3");
	child = root_node->create_child();
	child->model_matrix = engine::math::matrix_factory::translate(0.0f, -0.5f, 0.0f) * engine::math::matrix_factory::rodrigues(x, 90);
	child->m = engine::managers::mesh_manager::get_instance()->get_mesh("square4");
	child = root_node->create_child();
	child->model_matrix = engine::math::matrix_factory::translate(0.5f, 0.0f, 0.0f) * engine::math::matrix_factory::rodrigues(y, 90);
	child->m = engine::managers::mesh_manager::get_instance()->get_mesh("square5");
	child = root_node->create_child();
	child->model_matrix = engine::math::matrix_factory::translate(-0.5f, 0.0f, 0.0f) * engine::math::matrix_factory::rodrigues(y, -90);
	child->m = engine::managers::mesh_manager::get_instance()->get_mesh("square6");

	engine::managers::scene_manager::get_instance()->add_scene("main", main_scene);
}


void drawScene() {
	engine::managers::scene_manager::get_instance()->get_scene("main")->draw(cam.get_view(), cam.get_projection());
#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not draw scene.");
#endif
}

///////////////////////////////////////////////////////////////////////// CALLBACKS

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		if (cam.is_ortho) {
			cam.set_perspective();
			cam.is_ortho = false;
		}
		else {
			cam.set_orthographic();
			cam.is_ortho = true;
		}
	}
	else if (key ==	GLFW_KEY_G && action == GLFW_PRESS) {
		is_gimbal = !is_gimbal;
	}
	else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		engine::math::vec3 viewing_dir = cam.center - cam.eye;
		cam.center += viewing_dir.normalize() * SPEED;
		cam.eye += viewing_dir.normalize() * SPEED;
	}
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		engine::math::vec3 viewing_dir = cam.center - cam.eye;
		engine::math::vec3 moving_dir = engine::math::vec3::crossProduct(viewing_dir.normalize(), cam.up);
		cam.center += moving_dir.normalize() * SPEED;
		cam.eye += moving_dir.normalize() * SPEED;
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		engine::math::vec3 viewing_dir = cam.center - cam.eye;
		cam.center -= viewing_dir.normalize() * SPEED;
		cam.eye -= viewing_dir.normalize() * SPEED;
	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		engine::math::vec3 viewing_dir = cam.center - cam.eye;
		engine::math::vec3 moving_dir = engine::math::vec3::crossProduct(viewing_dir.normalize(), cam.up);
		cam.center -= moving_dir.normalize() * SPEED;
		cam.eye -= moving_dir.normalize() * SPEED;
	}
}

void cursor_position_callback(GLFWwindow* win, double xpos, double ypos) {
	if (mouse_pressed) {
		if (last_mouse_pos.x == -1.0f || last_mouse_pos.y == -1.0f) {
			last_mouse_pos.x = (float)xpos;
			last_mouse_pos.y = (float)ypos;
		}
		else {
			engine::math::vec2 curr_mouse_pos = engine::math::vec2((float)xpos, (float)ypos);
			engine::math::vec2 pos_dif = curr_mouse_pos - last_mouse_pos;

			if (is_gimbal) {
				cam.move_horizontal(pos_dif.x * SPEED);
				cam.move_vertical(pos_dif.y * SPEED);
			}
			else {
				cam.q_horizontal(pos_dif.x * SPEED);
				cam.q_vertical(pos_dif.y * SPEED);
			}

			last_mouse_pos = curr_mouse_pos;
		}

	}
}

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	
	if ((button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_PRESS) {
		mouse_pressed = true;
	}
	else if ((button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_RELEASE) {
		mouse_pressed = false;
		last_mouse_pos.x = -1.0f;
		last_mouse_pos.y = -1.0f;
	}
}

void window_close_callback(GLFWwindow* win) {
	engine::managers::scene_manager::clean_manager();
	engine::managers::mesh_manager::clean_manager();
	engine::managers::shader_manager::clean_manager();
}

void window_size_callback(GLFWwindow* win, int winx, int winy) {
	glViewport(0, 0, winx, winy);
	cam.width = winx;
	cam.height = winy;
	if (cam.is_ortho)
		cam.set_orthographic();
	else
		cam.set_perspective();
}

///////////////////////////////////////////////////////////////////////// SETUP

void setupShaders() {
	engine::shader* s = new engine::shader("resources/shaders/shader.vert",
		"resources/shaders/shader.frag");
	engine::managers::shader_manager::get_instance()->add_shader("main", s);
}

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
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, cursor_position_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
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
	setupShaders();
	createMeshes();
	setupScenes();
	cam = engine::camera::camera(engine::math::vec3::vec3(0.0f, 0.0f, 10.0f), engine::math::vec3::vec3(0.0f, 0.0f, 0.0f), engine::math::vec3::vec3(0.0f, 1.0f, 0.0f), winx, winy, 30, 1, 100);
	cam.set_perspective();

	return win;
}

///////////////////////////////////////////////////////////////////////// RUN

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

///////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		WIDTH, HEIGHT, "Hello Modern 3D World", is_fullscreen, is_vsync);
	test_3d_matrices();
	run(win);
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////// END