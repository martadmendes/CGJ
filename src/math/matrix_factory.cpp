#include "matrix_factory.hpp"
#include <cmath>

#define PI 3.14159265f


const math::mat2 math::matrix_factory::identity2x2() {
	return mat2(1.0, 0.0, 0.0, 1.0);
}

const math::mat3 math::matrix_factory::identity3x3() {
	return mat3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

const math::mat4 math::matrix_factory::identity4x4() {
	return mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

const math::mat2 math::matrix_factory::zero2x2() {
	return mat2(0.0, 0.0, 0.0, 0.0);
}

const math::mat3 math::matrix_factory::zero3x3() {
	return mat3(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

const math::mat4 math::matrix_factory::zero4x4() {
	return mat4(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

math::mat3 math::matrix_factory::dual_matrix(vec3& axis) {
	return mat3(0.0f, axis.data[2], -axis.data[1], 
				-axis.data[2], 0.0, axis.data[0], 
				axis.data[1], -axis.data[0], 0.0);
}

math::mat4 math::matrix_factory::mat3_to_mat4(mat3& m) {
	return mat4(m.data[0], m.data[1], m.data[2], 0.0,
				m.data[3], m.data[4], m.data[5], 0.0,
				m.data[6], m.data[7], m.data[8], 0.0,
				0.0, 0.0, 0.0, 1.0);
}

math::mat3 math::matrix_factory::mat4_to_mat3(mat4& m) {
	return mat3(m.data[0], m.data[1], m.data[2], m.data[4], m.data[5], m.data[6], m.data[8], m.data[9], m.data[10]);
}

math::mat4 math::matrix_factory::scale(float sx, float sy, float sz) {
	return mat4(sx, 0.0, 0.0, 0.0,
				0.0, sy, 0.0, 0.0,
				0.0, 0.0, sz, 0.0,
				0.0, 0.0, 0.0, 1.0);
}

math::mat4 math::matrix_factory::translate(float dx, float dy, float dz) {
	return mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, dx, dy, dz, 1.0);
}

math::mat4 math::matrix_factory::rotate(vec3& axis, float angle) {
	float rad = angle * PI / 180.0;
	
	mat3 scale = identity3x3();

	if (axis.x == 1.0) {
		scale = mat3(1.0, 0.0, 0.0, 0.0, cos(rad), sin(rad), 0.0, -sin(rad), cos(rad));
	}
	else if (axis.y == 1.0) {
		scale = mat3(cos(rad), 0.0, -sin(rad), 0.0, 1.0, 0.0, sin(rad), 0.0, cos(rad));
	}
	else if (axis.z == 1.0) {
		scale = mat3(cos(rad), sin(rad), 0.0, -sin(rad), cos(rad), 0.0, 0.0, 0.0, 1.0);
	}

	mat4 result = mat3_to_mat4(scale);
	return result;
}
