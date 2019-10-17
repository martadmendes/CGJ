#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "vec2.hpp"

namespace math {

	class mat2 {
	public:
		float data[4];

		mat2();
		mat2(const float k);
		mat2(const float m0, const float m1, const float m2, const float m3);
		mat2(const mat2& m); //row major constructor

		void clean();
		float determinant() const;
		mat2 transpose() const;
		mat2 inverse() const;
		mat2& operator = (const mat2& m);
		mat2& operator += (const mat2& m);
		mat2& operator -= (const mat2& m);
		mat2& operator *= (const float k);
		friend mat2 operator + (const mat2& m1, const mat2& m2);
		friend mat2 operator - (const mat2& m1, const mat2& m2);
		friend mat2 operator * (const mat2& m, const float k);       //matrix * scalar
		friend mat2 operator * (const float k, const mat2& m);       //scalar * matrix
		friend vec2 operator * (const mat2& m, const math::vec2 v);  //matrix * vector
		friend mat2 operator * (const mat2& m1, const mat2& m2);     //matrix * matrix
		friend bool operator == (const mat2& m1, const mat2& m2);
		friend bool operator != (const mat2& m1, const mat2& m2);
		friend std::ostream& operator << (std::ostream& os, const mat2& m);

	};
}
