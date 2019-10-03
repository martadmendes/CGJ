#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace math {

	class vec2
	{
	public:
		//attributes
		float x, y;

		//methods
		vec2();
		vec2(const float k);
		vec2(const float x, const float y);
		vec2(const vec2& v);
		~vec2();

		void clean(); 
		float* data();
		const float quadrance() const;
		const float magnitude() const;
		const vec2 normalize() const;
		float dotProduct(vec2 v1, vec2 v2);

		const vec2 operator - () const;
		vec2& operator = (const vec2& v);
		vec2& operator += (const vec2& v);
		vec2& operator -= (const vec2& v);
		vec2& operator *= (const vec2& v);
		vec2& operator /= (const vec2& v);
		friend const vec2 operator + (const vec2& v1, const vec2& v2);
		friend const vec2 operator - (const vec2& v1, const vec2& v2);
		friend const vec2 operator * (const vec2& v, const float k);
		friend const vec2 operator * (const float k, const vec2& v);
		friend const vec2 operator / (const vec2& v, const float k);
		friend const bool operator == (const vec2& v1, const vec2& v2);
		friend const bool operator != (const vec2& v1, const vec2& v2);
		friend std::ostream& operator << (std::ostream& os, const vec2& v);
		friend std::istream& operator >> (std::istream& is, vec2& v);

	};

}
