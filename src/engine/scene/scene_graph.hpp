#pragma once
#include "..\include.hpp"
#include "scene_node.hpp"

namespace engine {
	class scene_graph {
	public:
		scene_node* root;

		scene_graph();
		~scene_graph();

		void draw(math::mat4 view, math::mat4 projection);
	};
}