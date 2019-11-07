#include "camera.hpp"

engine::camera::camera() : width(0),
height(0), fovy(0), near(0), far(0) {}

engine::camera::camera(math::vec3 eye, math::vec3 center, math::vec3 up, int width, int height, float fovy, float near, float far) : eye(eye), center(center), up(up), width(width), 
																																	height(height), fovy(fovy), near(near), far(far) {}

engine::camera::~camera() {}


void engine::camera::move_camera() {}

void engine::camera::look_at(math::vec3& new_eye, math::vec3& new_center, math::vec3& new_up) {
	eye = new_eye;
	center = new_center;
	up = new_up;
}

engine::math::mat4 engine::camera::get_view() {
	return engine::math::matrix_factory::view_matrix(eye, center, up);
}

engine::math::mat4 engine::camera::get_projection() {
	return projection_matrix;
}

void engine::camera::set_orthographic() {
	float left, right, top, bottom;
	if (width > height) {
		top = 1.0f;
		bottom = -1.0f;
		left = -(float)width / (float)height;
		right = (float)width / (float)height;
	}
	else {
		left = -1.0f;
		right = 1.0f;
		top = (float)height / (float)width;
		bottom = -(float)height / (float)width;
	} //width == height a divisão vai ser -1.0f e 1.0f na mesma

	projection_matrix = math::matrix_factory::ortho_matrix(left, right, top, bottom, near, far);
	is_ortho = true;
}

void engine::camera::set_perspective() {
	float aspect = (float)width / (float)height;
	projection_matrix = math::matrix_factory::perspective_matrix(fovy, aspect, near, far);
}

void engine::camera::pitch(float angle) {
	engine::math::vec3 v = (center - eye);
	engine::math::vec3 s = engine::math::vec3::crossProduct(v, up).normalize();

	math::mat4 pitch = math::matrix_factory::rodrigues(s, angle);
	up = math::matrix_factory::mat4_to_mat3(pitch) * up;
	center = eye + (math::matrix_factory::mat4_to_mat3(pitch) * v);
}

void engine::camera::yaw(float angle) {
	engine::math::vec3 v = (center - eye);
	engine::math::vec3 s = engine::math::vec3::crossProduct(v, up).normalize();
	engine::math::vec3 u = engine::math::vec3::crossProduct(s, v).normalize();

	math::mat4 yaw = math::matrix_factory::rodrigues(u, angle);
	center = eye + (math::matrix_factory::mat4_to_mat3(yaw) * v);
}

