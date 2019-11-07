#pragma once
#include "math/vec3.hpp"
#include "math/mat3.hpp"
#include "math/mat4.hpp"
#include "math/matrix_factory.hpp"

enum class direction {left, right, up, down, forward, backward};

namespace engine {
	
	class camera {
	public:
		
		math::vec3 eye;
		math::vec3 center;
		math::vec3 up;

		math::mat4 projection_matrix;

		camera();
		camera(math::vec3 eye, math::vec3 center, math::vec3 up);
		~camera();

		void move_camera();

		void look_at(math::vec3& new_eye, math::vec3& new_center, math::vec3& new_up);

		math::mat4 get_view();
		math::mat4 get_projection();

		void set_orthographic(float left, float right, float top, float bottom, float near, float far);
		void set_perspective(float fovy, float aspect, float near, float far);

		void yaw(float angle);
		void pitch(float angle);
	};
}