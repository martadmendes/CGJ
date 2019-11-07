#include "camera.hpp"

engine::camera::camera() {}

engine::camera::camera(math::vec3 eye, math::vec3 center, math::vec3 up) : eye(eye), center(center), up(up) {}

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

void engine::camera::set_orthographic(float left, float right, float top, float bottom, float near, float far) {
	projection_matrix = math::matrix_factory::ortho_matrix(left, right, top, bottom, near, far);
}

void engine::camera::set_perspective(float fovy, float aspect, float near, float far) {
	projection_matrix = math::matrix_factory::perspective_matrix(fovy, aspect, near, far);
}

void engine::camera::yaw(float angle) {
	math::mat4 yaw = math::matrix_factory::rotate(math::matrix_factory::y_axis, angle);
	center = math::matrix_factory::mat4_to_mat3(yaw) * center;
}

void engine::camera::pitch(float angle) {
	math::mat4 pitch = math::matrix_factory::rotate(math::matrix_factory::x_axis, angle);
	center = math::matrix_factory::mat4_to_mat3(pitch) * center;
}

