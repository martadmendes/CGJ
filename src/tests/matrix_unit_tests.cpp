#include "matrix_unit_tests.hpp"
#include <vector>

#define PI 3.14159265f

////////// MATRIX 2 TESTS //////////
void mat2_tests() {
	std::cout << "*** MATRIX 2 TESTS *** \n" << std::endl;

	engine::math::mat2 m1 = engine::math::mat2(1, 4, 6, 0);
	engine::math::mat2 m2 = engine::math::mat2(4, 3, 2, 1);
	engine::math::vec2 v = engine::math::vec2(1, 2);

	// print identity 2x2 //
	std::cout << "Identity 2x2: " << std::endl;
	std::cout << engine::math::matrix_factory::identity2x2() << "\n" << std::endl;

	// print zero 2x2 //
	std::cout << "Zero 2x2: " << std::endl;
	std::cout << engine::math::matrix_factory::zero2x2() << "\n" << std::endl;
	
	// test determinant //
	std::cout << "Determinant:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m1.determinant() = " << m1.determinant() << "\n" << std::endl;

	// test transpose // 
	std::cout << "Transpose:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m1.transpose() = " << m1.transpose() << "\n" << std::endl;

	// test inverse //
	std::cout << "Inverse:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m1.inverse() = " << m1.inverse() << "\n" << std::endl;

	// test sum //
	std::cout << "Sum:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 + m2 = " << m1 + m2 << "\n" << std::endl;

	// test subtraction //
	std::cout << "Subtraction:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 - m2 = " << m1 - m2 << "\n" << std::endl;

	// test multiplication //
	std::cout << "Multiplication:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "m1 * 3 = " << m1 * 3 << "\n" << std::endl;
	std::cout << "m1 * v = " << m1 * v << "\n" << std::endl;
	std::cout << "m1 * m2 = " << m1 * m2 << "\n" << std::endl;

	// test == //
	std::cout << "Operator == :" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 == m1 ? " << (m1 == m1) << "\n" << std::endl;
	std::cout << "m1 == m2 ? " << (m1 == m2) << "\n" << std::endl;

	// test != //
	std::cout << "Operator != :" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 != m1 ? " << (m1 == m1) << "\n" << std::endl;
	std::cout << "m1 != m2 ? " << (m1 == m2) << "\n\n" << std::endl;
}


////////// MATRIX 3 TESTS //////////
void mat3_tests() {
	std::cout << "*** MATRIX 3 TESTS *** \n" << std::endl;

	engine::math::mat3 m1 = engine::math::mat3(1, 2, 2, 3, 1, 5, 1, 2, 3);
	engine::math::mat3 m2 = engine::math::mat3(3, 2, 1, 3, 2, 1, 3, 2, 1);
	engine::math::vec3 v = engine::math::vec3(1, 2, 3);

	// print identity 3x3 //
	std::cout << "Identity 3x3: " << std::endl;
	std::cout << engine::math::matrix_factory::identity3x3() << "\n" << std::endl;

	// print zero 3x3 //
	std::cout << "Zero 3x3: " << std::endl;
	std::cout << engine::math::matrix_factory::zero3x3() << "\n" << std::endl;

	// test dual matrix //
	std::cout << "Dual Matrix:" << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "dual_matrix(v) = " << engine::math::matrix_factory::dual_matrix(v) << "\n" << std::endl;

	// test determinant //
	std::cout << "Determinant:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m1.determinant() = " << m1.determinant() << "\n" << std::endl;

	// test transpose // 
	std::cout << "Transpose:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m1.transpose() = " << m1.transpose() << "\n" << std::endl;

	// test inverse //
	std::cout << "Inverse:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m1.inverse() = " << m1.inverse() << "\n" << std::endl;

	// test sum //
	std::cout << "Sum:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 + m2 = " << m1 + m2 << "\n" << std::endl;

	// test subtraction //
	std::cout << "Subtraction:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 - m2 = " << m1 - m2 << "\n" << std::endl;

	// test multiplication //
	std::cout << "Multiplication:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "m1 * 3 = " << m1 * 3 << "\n" << std::endl;
	std::cout << "m1 * v = " << m1 * v << "\n" << std::endl;
	std::cout << "m1 * m2 = " << m1 * m2 << "\n" << std::endl;

	// test == //
	std::cout << "Operator == :" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 == m1 ? " << (m1 == m1) << "\n" << std::endl;
	std::cout << "m1 == m2 ? " << (m1 == m2) << "\n" << std::endl;

	// test != //
	std::cout << "Operator != :" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 != m1 ? " << (m1 == m1) << "\n" << std::endl;
	std::cout << "m1 != m2 ? " << (m1 == m2) << "\n" << std::endl;

	// test convert to matrix 4x4 //
	std::cout << "Convert to 4x4:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "mat3_to_mat4(m1) = " << engine::math::matrix_factory::mat3_to_mat4(m1) << "\n\n" << std::endl;

}


////////// MATRIX 4 TESTS //////////
void mat4_tests() {
	std::cout << "*** MATRIX 4 TESTS *** \n" << std::endl;

	engine::math::mat4 m1 = engine::math::mat4(1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4);
	engine::math::mat4 m2 = engine::math::mat4(4, 3, 2, 1, 4, 3, 2, 1, 4, 3, 2, 1, 4, 3, 2, 1);
	engine::math::vec4 v = engine::math::vec4(1, 2, 3, 4);
	engine::math::vec3 axis = engine::math::vec3(0, 1, 0);

	// print identity 4x4 //
	std::cout << "Identity 4x4: " << std::endl;
	std::cout << engine::math::matrix_factory::identity4x4() << "\n" << std::endl;

	// print zero 4x4 //
	std::cout << "Zero 4x4: " << std::endl;
	std::cout << engine::math::matrix_factory::zero4x4() << "\n" << std::endl;

	// test scale //
	std::cout << "Scale:" << std::endl;
	std::cout << "scale(1, 2, 3) = " << engine::math::matrix_factory::scale(1, 2, 3) << "\n" << std::endl;

	// test translate //
	std::cout << "Translate:" << std::endl;
	std::cout << "translate(3, 2, 1) = " << engine::math::matrix_factory::translate(3, 2, 1) << "\n" << std::endl;

	// test rotate //
	std::cout << "Rotate:" << std::endl;
	std::cout << "rotate(axis, 90) = " << engine::math::matrix_factory::rotate(axis, 90) << "\n" << std::endl;

	// test transpose // 
	std::cout << "Transpose:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m1.transpose() = " << m1.transpose() << "\n" << std::endl;

	// test sum //
	std::cout << "Sum:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 + m2 = " << m1 + m2 << "\n" << std::endl;

	// test subtraction //
	std::cout << "Subtraction:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 - m2 = " << m1 - m2 << "\n" << std::endl;

	// test multiplication //
	std::cout << "Multiplication:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "m1 * 3 = " << m1 * 3 << "\n" << std::endl;
	std::cout << "m1 * v = " << m1 * v << "\n" << std::endl;
	std::cout << "m1 * m2 = " << m1 * m2 << "\n" << std::endl;

	// test == //
	std::cout << "Operator == :" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 == m1 ? " << (m1 == m1) << "\n" << std::endl;
	std::cout << "m1 == m2 ? " << (m1 == m2) << "\n" << std::endl;

	// test != //
	std::cout << "Operator != :" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "m2: " << m2 << std::endl;
	std::cout << "m1 != m1 ? " << (m1 == m1) << "\n" << std::endl;
	std::cout << "m1 != m2 ? " << (m1 == m2) << "\n" << std::endl;

	// test convert to matrix 3x3 //
	std::cout << "Convert to 3x3:" << std::endl;
	std::cout << "m1: " << m1 << std::endl;
	std::cout << "mat4_to_mat3(m1) = " << engine::math::matrix_factory::mat4_to_mat3(m1) << "\n\n" << std::endl;
}


////////// CLASS EXERCISE //////////
void aula02() {
	std::cout << "***TESTE AULA***\n" << std::endl;
	
	std::vector<engine::math::vec3> vs = { engine::math::vec3(2,0,0), engine::math::vec3(0,3,0), engine::math::vec3(0,0,4) };

	for (engine::math::vec3& v1 : vs) {
		for (engine::math::vec3& v2 : vs) {
			std::cout << engine::math::matrix_factory::rodrigues(v1, 90) * engine::math::vec4(v2.x, v2.y, v2.z, 1.0f) << "\n" << std::endl;
		}
	}

}


///////// VIEW AND PROJECTION TESTS //////////
void test_3d_matrices() {
	std::cout << "view 1" << std::endl;
	std::cout << engine::math::matrix_factory::view_matrix(engine::math::vec3(5.0f, 5.0f, 5.0f), engine::math::vec3(0.0f, 0.0f, 0.0f), engine::math::vec3(0.0f, 1.0f, 0.0f)) << std::endl;

	std::cout << "view 2" << std::endl;
	std::cout << engine::math::matrix_factory::view_matrix(engine::math::vec3(-5.0f, -5.0f, -5.0f), engine::math::vec3(0.0f, 0.0f, 0.0f), engine::math::vec3(0.0f, 1.0f, 0.0f)) << std::endl;

	std::cout << "ortho" << std::endl;
	std::cout << engine::math::matrix_factory::ortho_matrix(-2.0f, 2.0f, 2.0f, -2.0f, 1.0f, 10.0f) << std::endl;

	std::cout << "perspective" << std::endl;
	std::cout << engine::math::matrix_factory::perspective_matrix(30.0f, 640.0f / 480.0f, 1.0f, 10.0f) << std::endl;
}
