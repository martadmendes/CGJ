#pragma once
#include <cmath>
#include "mat2.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "qtrn.hpp"

namespace engine {
	namespace math {
		
		//enum class axis {
		//	x, y, z
		//};

		class matrix_factory {

		public:
			const static vec3 x_axis;
			const static vec3 y_axis;
			const static vec3 z_axis;

			const static mat2 identity2x2();
			const static mat3 identity3x3();
			const static mat4 identity4x4();

			const static mat2 zero2x2();
			const static mat3 zero3x3();
			const static mat4 zero4x4();

			static mat3 dual_matrix(const vec3& axis);

			static mat4 mat3_to_mat4(mat3& m);
			static mat3 mat4_to_mat3(mat4& m);

			static mat4 scale(float sx, float sy, float sz);
			static mat4 translate(float dx, float dy, float dz);
			static mat4 rotate(const vec3& axis, float angle);  //just for xyz
			static mat4 rodrigues(const vec3& axis, const float angle);  //any axis

			static mat4 view_matrix(vec3 eye, vec3 center, vec3 up);
			static mat4 ortho_matrix(float left, float right, float top, float bottom, float near, float far);
			static mat4 perspective_matrix(float fovy, float aspect, float near, float far);

			const static mat3 q_gl_matrix(const qtrn& q);

		};
	}
}