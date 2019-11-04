#pragma once
#include <iostream>
#include <sstream>
#include <string>


namespace engine {
	namespace math {

		
		class vec3 {
		public:
			//attributes
			float x, y, z;

			//methods
			vec3();
			vec3(const float k);
			vec3(const float x, const float y, const float z);
			vec3(const vec3& v);
			~vec3();

			void clean();
			float* data();
			const float quadrance() const;
			const float magnitude() const;
			const vec3 normalize() const;

			const vec3 operator - () const;
			vec3& operator = (const vec3& v);
			vec3& operator += (const vec3& v);
			vec3& operator -= (const vec3& v);
			vec3& operator *= (const vec3& v);
			vec3& operator /= (const vec3& v);
			friend const vec3 operator + (const vec3& v1, const vec3& v2);
			friend const vec3 operator - (const vec3& v1, const vec3& v2);
			friend const vec3 operator * (const vec3& v, const float k);
			friend const vec3 operator * (const float k, const vec3& v);
			friend const vec3 operator / (const vec3& v, const float k);
			friend const bool operator == (const vec3& v1, const vec3& v2);
			friend const bool operator != (const vec3& v1, const vec3& v2);
			friend std::ostream& operator << (std::ostream& os, const vec3& v);
			friend std::istream& operator >> (std::istream& is, vec3& v);

			static float dotProduct(vec3 v1, vec3 v2) {
				return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			}
			static vec3 crossProduct(vec3 v1, vec3 v2) {
				return vec3((v1.y * v2.z - v1.z * v2.y), (v1.z * v2.x - v1.x * v2.z), (v1.x * v2.y - v1.y * v2.x));
			}
		};
	}
}
