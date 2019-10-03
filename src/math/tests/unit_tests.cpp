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

}

////////// VECTOR 3 TESTS //////////
void vec3_tests() {
	math::vec3 v1 = math::vec3(1, 0, 0);
	math::vec3 v2 = math::vec3(0, 2, 0);
	math::vec3 v3 = math::vec3(0, 0, 3);

	std::cout << "VECTOR 3 TESTS: " << std::endl;

}

////////// VECTOR 4 TESTS //////////
void vec4_tests() {
	math::vec2 v1 = math::vec2(1, 0, 0, 0);
	math::vec2 v2 = math::vec2(0, 2, 0, 1);

	std::cout << "VECTOR 4 TESTS: " << std::endl;

}
