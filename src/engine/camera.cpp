#include "camera.hpp"

engine::camera::camera() {}

engine::camera::camera(math::vec3 position) {

}

engine::camera::camera(math::vec3 position, math::vec3 center) {

}

engine::camera::camera(math::vec3 eye, math::vec3 center, math::vec3 up) {

}

engine::camera::~camera() {}

void engine::camera::look_at() {}

void engine::camera::move_camera() {}

engine::math::mat4 engine::camera::get_camera() {
	return math::mat4();
}

engine::math::mat4 engine::camera::get_projection_matrix() {
	return math::mat4();
}

void engine::camera::set_projection_matrix() {}

void engine::camera::yaw(float angle) {
	math::mat4 yaw = math::matrix_factory::rotate(math::matrix_factory::y_axis, angle);
	view = math::matrix_factory::mat4_to_mat3(yaw) * view;
}

void engine::camera::pitch(float angle) {
	math::mat4 pitch = math::matrix_factory::rotate(math::matrix_factory::x_axis, angle);
	view = math::matrix_factory::mat4_to_mat3(pitch) * view;
}

void engine::camera::invert_pitch() {

}
