#include "matrix_factory.hpp"
#include <cmath>

#define PI 3.14159265f

const engine::math::vec3 engine::math::matrix_factory::x_axis = engine::math::vec3(1.0f, 0.0f, 0.0f);  //x_axis constant
const engine::math::vec3 engine::math::matrix_factory::y_axis = engine::math::vec3(0.0f, 1.0f, 0.0f);  //y_axis constant
const engine::math::vec3 engine::math::matrix_factory::z_axis = engine::math::vec3(0.0f, 0.0f, 1.0f);  //z_axis constant


const engine::math::mat2 engine::math::matrix_factory::identity2x2() {
	return mat2(1.0, 0.0, 0.0, 1.0);
}

const engine::math::mat3 engine::math::matrix_factory::identity3x3() {
	return mat3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

const engine::math::mat4 engine::math::matrix_factory::identity4x4() {
	return mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

const engine::math::mat2 engine::math::matrix_factory::zero2x2() {
	return mat2(0.0, 0.0, 0.0, 0.0);
}

const engine::math::mat3 engine::math::matrix_factory::zero3x3() {
	return mat3(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

const engine::math::mat4 engine::math::matrix_factory::zero4x4() {
	return mat4(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

engine::math::mat3 engine::math::matrix_factory::dual_matrix(const vec3& axis) {
	return mat3(0.0f, axis.z, -axis.y, 
				-axis.z, 0.0, axis.x, 
				axis.y, -axis.x, 0.0);
}

engine::math::mat4 engine::math::matrix_factory::mat3_to_mat4(mat3& m) {
	return mat4(m.data[0], m.data[1], m.data[2], 0.0,
				m.data[3], m.data[4], m.data[5], 0.0,
				m.data[6], m.data[7], m.data[8], 0.0,
				0.0, 0.0, 0.0, 1.0);
}

engine::math::mat3 engine::math::matrix_factory::mat4_to_mat3(mat4& m) {
	return mat3(m.data[0], m.data[1], m.data[2], m.data[4], m.data[5], m.data[6], m.data[8], m.data[9], m.data[10]);
}

engine::math::mat4 engine::math::matrix_factory::scale(float sx, float sy, float sz) {
	return mat4(sx, 0.0, 0.0, 0.0,
				0.0, sy, 0.0, 0.0,
				0.0, 0.0, sz, 0.0,
				0.0, 0.0, 0.0, 1.0);
}

engine::math::mat4 engine::math::matrix_factory::translate(float dx, float dy, float dz) {
	return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, dz, 1.0f);
}

engine::math::mat4 engine::math::matrix_factory::rotate(const vec3& axis, float angle) {
	float rad = angle * PI / 180.0f;
	
	mat3 rotate = identity3x3();

	if (axis == x_axis) {
		rotate = mat3(1.0, 0.0, 0.0, 0.0, cos(rad), sin(rad), 0.0, -sin(rad), cos(rad));
	}
	else if (axis == y_axis) {
		rotate = mat3(cos(rad), 0.0, -sin(rad), 0.0, 1.0, 0.0, sin(rad), 0.0, cos(rad));
	}
	else if (axis == z_axis) {
		rotate = mat3(cos(rad), sin(rad), 0.0, -sin(rad), cos(rad), 0.0, 0.0, 0.0, 1.0);
	}

	mat4 result = mat3_to_mat4(rotate);
	return result;
}

engine::math::mat4 engine::math::matrix_factory::rodrigues(const vec3& axis, const float angle) {
	float rad = angle * PI / 180.0f;

	mat3 a = dual_matrix(axis.normalize());
	
	mat3 result = identity3x3() + sin(rad) * a + (1 - cos(rad)) * (a * a);

	return mat3_to_mat4(result);
}

engine::math::mat4 engine::math::matrix_factory::view_matrix(vec3 eye, vec3 center, vec3 up) {
	vec3 v = (center - eye).normalize();
	vec3 s = vec3::crossProduct(v, up).normalize();
	vec3 u = vec3::crossProduct(s, v).normalize();
	return mat4(s.x, u.x, -v.x, 0,
		s.y, u.y, -v.y, 0,
		s.z, u.z, -v.z, 0,
		vec3::dotProduct(-s, eye), vec3::dotProduct(-u, eye), vec3::dotProduct(v, eye), 1);
}

engine::math::mat4 engine::math::matrix_factory::ortho_matrix(float left, float right, float top, float bottom, float near, float far) {
	return mat4(2 / (right - left), 0.0f, 0.0f, 0.0f,
		0.0f, 2 / (top - bottom), 0.0f, 0.0f,
		0.0f, 0.0f, 2 / (near - far), 0.0f,
		(left + right) / (left - right), (top + bottom) / (top - bottom), (near + far) / (near - far), 1.0f);
}

engine::math::mat4 engine::math::matrix_factory::perspective_matrix(float fovy, float aspect, float near, float far) {
	float rad = ( fovy * PI / 180.0f ) / 2;
	float d = 1 / tan(rad);
	return mat4(d / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, d, 0.0f, 0.0f,
		0.0f, 0.0f, (near + far) / (near - far), -1.0f,
		0.0f, 0.0f, (2 * far * near) / (near - far), 0.0f);
}

const engine::math::mat3 engine::math::matrix_factory::q_gl_matrix(const qtrn& q) {
	return mat3(1.0f - 2.0f * q.v.y * q.v.y - 2.0f * q.v.z * q.v.z, 2.0f * q.v.x * q.v.y + 2.0f * q.t * q.v.z, 2.0f * q.v.x * q.v.z - 2.0f * q.t * q.v.y,
		2.0f * q.v.x * q.v.y - 2.0f * q.t * q.v.z, 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.z * q.v.z, 2.0f * q.v.y * q.v.z + 2.0f * q.t * q.v.x,
		2.0f * q.v.x * q.v.z + 2.0f * q.t * q.v.y, 2.0f * q.v.y * q.v.z - 2.0f * q.t * q.v.x, 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.y * q.v.y);
}
