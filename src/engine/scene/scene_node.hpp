#pragma once
#include <vector>
#include "..\include.hpp"
#include "..\geometry\mesh.hpp"
#include "../shader.hpp"

namespace engine {

	class scene_node {
	public:
		bool is_active = true;

		scene_node* parent;
		engine::mesh* m;
		engine::shader* shdr;
		engine::math::qtrn q;
		engine::math::mat4 model_matrix;
		std::vector <scene_node*> children;

		scene_node();
		~scene_node();

		scene_node* create_child();
		
		void draw(math::mat4 view, math::mat4 projection);
		void destroy();
	};
}