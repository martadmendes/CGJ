#include "vector_unit_tests.hpp"

////////// VECTOR 2 TESTS //////////
void vec2_tests() {	
	std::cout << "VECTOR 2 TESTS: " << std::endl;
	
	math::vec2 v1 = math::vec2(1, 0);
	math::vec2 v2 = math::vec2(0, 2);
	
	// test sum //
	std::cout << "Test Sum:" << std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
	std::cout << "___________" << std::endl;

	// test subtraction //
	std::cout << "Test Subtraction:" << std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v1 - v2 = " << v1 - v2 << std::endl;
	std::cout << "___________" << std::endl;

	// test multiplication
	std::cout << "Test multiplication:" << std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1 * 3 = " << v1 * 3 << std::endl;
	std::cout << "___________" << std::endl;

	// test division
	std::cout << "Test division:" << std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1 / 2 = " << v1 / 2 << std::endl;
	std::cout << "___________" << std::endl;

	// test normalization (which also tests magnitude and quadrance)
	std::cout << "Test normalization:" << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v2 normalized = " << v2.normalize() << std::endl;
	std::cout << "___________" << std::endl;
}

////////// VECTOR 3 TESTS //////////
//void vec3_tests() {
//	math::vec3 v1 = math::vec3(1, 0, 0);
//	math::vec3 v2 = math::vec3(0, 2, 0);
//	math::vec3 v3 = math::vec3(0, 0, 3);
//
//	std::cout << "VECTOR 3 TESTS: " << std::endl;
//
//}

////////// VECTOR 4 TESTS //////////
//void vec4_tests() {
//	math::vec2 v1 = math::vec2(1, 0, 0, 0);
//	math::vec2 v2 = math::vec2(0, 2, 0, 1);
//
//	std::cout << "VECTOR 4 TESTS: " << std::endl;
//
//}
