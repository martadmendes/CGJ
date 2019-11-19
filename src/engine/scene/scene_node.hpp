#pragma once
#include <vector>
#include "..\geometry\mesh.hpp"
#include "..\math\vec3.hpp"
#include "..\math\vec4.hpp"
#include "..\math\mat4.hpp"
#include "..\math\qtrn.hpp"

namespace engine {

	class scene_node {
	public:
		bool is_active = true;

		scene_node* parent;
		engine::mesh* mesh;
		engine::math::qtrn q;
		engine::math::mat4 model_matrix;
		std::vector <scene_node*> children;

		scene_node();
		~scene_node();

		void change_dir(float angle, engine::math::vec3 axis);
		void set_active(bool b);

		engine::mesh* get_mesh();
		void set_mesh(engine::mesh* new_mesh);

		engine::math::mat4 get_model_matrix();
		void set_model_matrix(engine::math::mat4 new_matrix);

		void set_shader(shader* shader);

		scene_node* create_child();
		
		void draw();
		void update();
		void release();
		void destroy();


	};
}