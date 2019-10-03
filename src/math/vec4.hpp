#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace math {

	class vec4 {
	public:
		//attributes
		float x, y, z, w;

		//methods
		vec4();
		vec4(const float k);
		vec4(const float x, const float y, const float z, const float w);
		vec4(const vec4& v);
		~vec4();

		void clean();
		float* data();
		const float quadrance() const;
		const float magnitude() const;
		const vec4 normalize() const;
		static float dotProduct(vec4 v1, vec4 v2);
		static vec4 crossProduct(vec4 v1, vec4 v2);

		const vec4 operator - () const;
		vec4& operator = (const vec4& v);
		vec4& operator += (const vec4& v);
		vec4& operator -= (const vec4& v);
		vec4& operator *= (const vec4& v);
		vec4& operator /= (const vec4& v);
		friend const vec4 operator + (const vec4& v1, const vec4& v2);
		friend const vec4 operator - (const vec4& v1, const vec4& v2);
		friend const vec4 operator * (const vec4& v, const float k);
		friend const vec4 operator * (const float k, const vec4& v);
		friend const vec4 operator / (const vec4& v, const float k);
		friend const bool operator == (const vec4& v1, const vec4& v2);
		friend const bool operator != (const vec4& v1, const vec4& v2);
		friend std::ostream& operator << (std::ostream& os, const vec4& v);
		friend std::istream& operator >> (std::istream& is, vec4& v);

	};

}
