#pragma once
#include "..\include.hpp"

namespace engine {

	class material {
		math::vec3 ambient;
		math::vec3 diffuse;
		math::vec3 specular;
		math::vec3 emissive;
		float shininess;
		
		material();
		~material();

		void load_material(std::string file);
		void parse(std::stringstream& string);

	};
}