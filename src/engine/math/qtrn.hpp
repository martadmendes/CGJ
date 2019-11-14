#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "mat4.hpp"
#include "vec3.hpp"

namespace engine {
	namespace math {
		
		class qtrn {
		public:
			float t;
			vec3 v;

			qtrn();
			qtrn(const float t, const vec3 v);
			qtrn(const vec3 axis, const float theta); //q from angle axis
			~qtrn();

			const float to_angle();
			const vec3 to_axis();

			const void clean();
			const float quadrance();
			const float magnitude();
			const qtrn normalize();
			const qtrn conjugate();
			const qtrn inverse();
	
			qtrn& operator = (const qtrn& q);
			qtrn& operator += (const qtrn& q);
			qtrn& operator -= (const qtrn& q);
			qtrn& operator *= (const qtrn& q);
			qtrn& operator /= (const qtrn& q);

			friend const qtrn operator + (const qtrn& q1, const qtrn& q2);
			friend const qtrn operator - (const qtrn& q1, const qtrn& q2);
			friend const qtrn operator * (const qtrn& q1, const qtrn& q2);
			friend const qtrn operator * (const qtrn& q, const float k);
			friend const qtrn operator * (const float k, const qtrn& q);
			friend const qtrn operator / (const qtrn& q, const float k);
			friend const bool operator == (const qtrn& q1, const qtrn& q2);
			friend const std::ostream& operator << (std::ostream& os, qtrn& q);

			static const qtrn lerp(const qtrn& q1, const qtrn& q2, float k);
			static const qtrn slerp(const qtrn& q1, const qtrn& q2, float k);

		};
	}
}