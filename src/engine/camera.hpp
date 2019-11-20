#pragma once
#include "include.hpp"

enum class direction {left, right, up, down, forward, backward};

namespace engine {
	
	class camera {
	public:
		
		math::vec3 eye;
		math::vec3 center;
		math::vec3 up;

		int width, height;
		float fovy, near, far;

		math::mat4 projection_matrix;

		bool is_ortho = false;

		camera();
		camera(math::vec3 eye, math::vec3 center, math::vec3 up, int width, int height, float fovy, float near, float far);
		~camera();

		void move_camera();

		void look_at(math::vec3& new_eye, math::vec3& new_center, math::vec3& new_up);

		math::mat4 get_view();
		math::mat4 get_projection();

		void set_orthographic();
		void set_perspective();

		void pitch(float angle);
		void yaw(float angle);

		void move_vertical(float angle);
		void move_horizontal(float angle);

		void q_vertical(float angle);
		void q_horizontal(float angle);

	};
}