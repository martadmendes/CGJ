#include "matrix_unit_tests.hpp"

////////// MATRIX 2 TESTS //////////
void mat2_tests() {
	std::cout << "*** MATRIX 2 TESTS *** \n" << std::endl;

	math::mat2 m1 = math::mat2(1, 2, 3, 4);
	math::mat2 m2 = math::mat2(4, 3, 2, 1);
	math::vec2 v = math::vec2(1, 2);

	// print identity 2x2 //
	std::cout << "Identity 2x2: " << std::endl;
	std::cout << math::matrix_factory::identity2x2 << "\n" << std::endl;

	// print zero 2x2 //
	std::cout << "Identity 2x2: " << std::endl;
	std::cout << math::matrix_factory::zero2x2 << "\n" << std::endl;
	
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

	math::mat3 m1 = math::mat3(1, 2, 3, 1, 2, 3, 1, 2, 3);
	math::mat3 m2 = math::mat3(3, 2, 1, 3, 2, 1, 3, 2, 1);
	math::vec3 v = math::vec3(1, 2, 3);

	// print identity 3x3 //
	std::cout << "Identity 3x3: " << std::endl;
	std::cout << math::matrix_factory::identity3x3 << "\n" << std::endl;

	// print zero 3x3 //
	std::cout << "Identity 3x3: " << std::endl;
	std::cout << math::matrix_factory::zero3x3 << "\n" << std::endl;

	// test dual matrix //
	std::cout << "Dual Matrix:" << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "dual_matrix(v) = " << math::matrix_factory::dual_matrix(v) << "\n" << std::endl;

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
	std::cout << "mat3_to_mat4(m1) = " << math::matrix_factory::mat3_to_mat4(m1) << "\n\n" << std::endl;

}


////////// MATRIX 4 TESTS //////////
void mat4_tests() {
	std::cout << "*** MATRIX 4 TESTS *** \n" << std::endl;

	math::mat4 m1 = math::mat4(1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4);
	math::mat4 m2 = math::mat4(4, 3, 2, 1, 4, 3, 2, 1, 4, 3, 2, 1, 4, 3, 2, 1);
	math::vec4 v = math::vec4(1, 2, 3, 4);
	math::vec3 axis = math::vec3(0, 1, 0);

	// print identity 4x4 //
	std::cout << "Identity 4x4: " << std::endl;
	std::cout << math::matrix_factory::identity4x4 << "\n" << std::endl;

	// print zero 4x4 //
	std::cout << "Identity 4x4: " << std::endl;
	std::cout << math::matrix_factory::zero4x4 << "\n" << std::endl;

	// test scale //
	std::cout << "Scale:" << std::endl;
	std::cout << "scale(1, 2, 3) = " << math::matrix_factory::scale(1, 2, 3) << "\n" << std::endl;

	// test translate //
	std::cout << "Translate:" << std::endl;
	std::cout << "translate(3, 2, 1) = " << math::matrix_factory::translate(3, 2, 1) << "\n" << std::endl;

	// test rotate //
	std::cout << "Rotate:" << std::endl;
	std::cout << "rotate(axis, 90) = " << math::matrix_factory::rotate(axis, 90) << "\n" << std::endl;

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
	std::cout << "mat4_to_mat3(m1) = " << math::matrix_factory::mat4_to_mat3(m1) << "\n\n" << std::endl;
}



////////// CLASS EXERCISE //////////
void aula02() {}
