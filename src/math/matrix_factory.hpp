#pragma once

#include "mat2.hpp"
#include "mat3.hpp"
#include "mat4.hpp"

namespace math {
	class matrix_factory {
	
	public:

		const static mat2 identity2();
		const static mat3 identity3();
		const static mat4 identity4();

		const static mat2 zero2();
		const static mat3 zero3();
		const static mat4 zero4();

		static mat3 mat4_to_mat3(mat4& m);
		static mat4 mat3_to_mat4(mat3& m);

		static mat4 scale();
		static mat4 rotate();
		static mat4 translate();

	};
}