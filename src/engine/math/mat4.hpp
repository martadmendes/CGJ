#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "vec4.hpp"

namespace engine {
	namespace math {

		class mat4 {
		public:
			float data[16];

			mat4();
			mat4(const float k);
			mat4(const float m0, const float m1, const float m2, const float m3,
				const float m4, const float m5, const float m6, const float m7,
				const float m8, const float m9, const float m10, const float m11,
				const float m12, const float m13, const float m14, const float m15);
			mat4(const mat4& m); //row major constructor

			void clean();
			mat4 transpose() const;
			mat4& operator = (const mat4& m);
			mat4& operator += (const mat4& m);
			mat4& operator -= (const mat4& m);
			mat4& operator *= (const float k);
			friend mat4 operator + (const mat4& m1, const mat4& m2);
			friend mat4 operator - (const mat4& m1, const mat4& m2);
			friend mat4 operator * (const mat4& m, const float k);       //matrix * scalar
			friend mat4 operator * (const float k, const mat4& m);       //scalar * matrix
			friend vec4 operator * (const mat4& m, const math::vec4 v);  //matrix * vector
			friend mat4 operator * (const mat4& m1, const mat4& m2);	  //matrix * matrix
			friend bool operator == (const mat4& m1, const mat4& m2);
			friend bool operator != (const mat4& m1, const mat4& m2);
			friend std::ostream& operator << (std::ostream& os, const mat4& m);
		};
	}
}