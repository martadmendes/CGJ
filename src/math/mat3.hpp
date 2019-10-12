#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "vec3.hpp"
#include "mat2.hpp"

namespace math {

	class mat3 {
	public:
		float data[9];

		mat3();
		mat3(const float k);
		mat3(const float m0, const float m1, const float m2,
			const float m3, const float m4, const float m5,
			const float m6, const float m7, const float m8);
		mat3(const mat3& m); //row major constructor

		//clean passa por todos os valores, vê se o valor é menor que o threshold e se sim iguala a zero
		void clean();
		float determinant() const;
		friend mat3 transpose(mat3& m);
		friend mat3 inverse(mat3& m);
		mat3& operator = (const mat3& m);
		mat3& operator += (const mat3& m);
		mat3& operator -= (const mat3& m);
		mat3& operator *= (const float k);
		friend mat3 operator + (const mat3& m1, const mat3& m2);
		friend mat3 operator - (const mat3& m1, const mat3& m2);
		friend mat3 operator * (const mat3& m, const float k);       //matrix * scalar
		friend mat3 operator * (const float k, const mat3& m);       //scalar * matrix
		friend vec3 operator * (const mat3& m, const math::vec3 v);  //matrix * vector
		friend mat3 operator * (const mat3& m1, const mat3& m2);     //matrix * matrix
		friend bool operator == (const mat3& m1, const mat3& m2);
		friend bool operator != (const mat3& m1, const mat3& m2);
		friend std::ostream& operator << (std::ostream& os, const mat3& m);
	};
}