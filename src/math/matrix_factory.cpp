#include "matrix_factory.hpp"

const math::mat2 math::matrix_factory::identity2() {
	return mat2(1.0, 0.0, 0.0, 1.0);
}

const math::mat3 math::matrix_factory::identity3() {
	return mat3();
}

const math::mat4 math::matrix_factory::identity4() {
	return mat4();
}

const math::mat2 math::matrix_factory::zero2() {
	return mat2(0.0, 0.0, 0.0, 0.0);
}

const math::mat3 math::matrix_factory::zero3() {
	return mat3();
}

const math::mat4 math::matrix_factory::zero4() {
	return mat4();
}

math::mat3 math::matrix_factory::mat4_to_mat3(mat4& m) {
	return mat3();
}

math::mat4 math::matrix_factory::mat3_to_mat4(mat3& m) {
	return mat4();
}

math::mat4 math::matrix_factory::scale() {
	return mat4();
}

math::mat4 math::matrix_factory::rotate() {
	return mat4();
}

math::mat4 math::matrix_factory::translate() {
	return mat4();
}
