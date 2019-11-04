#pragma once
#include "math/vec3.hpp"
#include "math/mat3.hpp"
#include "math/mat4.hpp"
#include "math/matrix_factory.hpp"

enum class direction {up, down, left, right, forward, backward};

namespace engine {
	
	class camera {
	public:
		
		math::vec3 eye;
		math::vec3 center;
		math::vec3 up;

		math::vec3 position;
		math::vec3 view;
		math::vec3 side;

		float x_rot;
		float y_rot;
		float speed = 0.5f;

		math::mat4 projection_matrix;

		camera();
		camera(math::vec3 position);
		camera(math::vec3 position, math::vec3 center);
		camera(math::vec3 eye, math::vec3 center, math::vec3 up);
		~camera();


		void look_at();
		void move_camera();
		math::mat4 get_camera();

		math::mat4 get_projection_matrix();
		void set_projection_matrix();

		void yaw(float angle);
		void pitch(float angle);
		void invert_pitch();
	};
}