#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace math {
	
	class matrix3 {
	public:
		float data[9];

		matrix3();
		matrix3(const float k);
		matrix3(const float m0, const float m1, const float m2,
			const float m3, const float m4, const float m5,
			const float m6, const float m7, const float m8);
		matrix3(const matrix3& m); //row major constructor

		//clean passa por todos os valores, vê se o valor é menor que o threshold e se sim iguala a zero
		void clean();
		float determinant() const;
	
	};
}