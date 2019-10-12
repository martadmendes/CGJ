#include "mat4.hpp"
#define LIMIT 0.00001f

math::mat4::mat4() : data{ 0.0f } {}

math::mat4::mat4(const float k) : data{ k, 0.0f, 0.0f, 0.0f,
										0.0f, k, 0.0f, 0.0f, 
										0.0f, 0.0f, k, 0.0f,
										0.0f, 0.0f, 0.0f, k } {}

math::mat4::mat4(const float m0, const float m1, const float m2, const float m3, 
				 const float m4, const float m5, const float m6, const float m7, 
				 const float m8, const float m9, const float m10, const float m11,
				 const float m12, const float m13, const float m14, const float m15) : data{ m0, m1, m2, m3, 
																							 m4, m5, m6, m7, 
																							 m8, m9, m10, m11, 
																							 m12, m13, m14, m15 } {}

math::mat4::mat4(const mat4& m) : data{ m.data[0], m.data[1], m.data[2], m.data[3], 
										m.data[4], m.data[5], m.data[6], m.data[7], 
										m.data[8], m.data[9], m.data[10], m.data[11],
										m.data[12], m.data[13], m.data[14], m.data[15] } {}

void math::mat4::clean() {
	for (float f : data) {
		if (f <= LIMIT)
			f = 0.0f;
	}
}

float math::mat4::determinant() const {
	return 0.0f;
}

math::mat4& math::mat4::operator=(const mat4& m) {
	// TODO: insert return statement here
}

math::mat4& math::mat4::operator+=(const mat4& m) {
	// TODO: insert return statement here
}

math::mat4& math::mat4::operator-=(const mat4& m) {
	// TODO: insert return statement here
}

math::mat4& math::mat4::operator*=(const float k) {
	// TODO: insert return statement here
}

math::mat4 math::transpose(mat4& m) {
	return mat4();
}

math::mat4 math::inverse(mat4& m) {
	return mat4();
}

math::mat4& math::operator+(const mat4& m1, const mat4& m2) {
	// TODO: insert return statement here
}

math::mat4& math::operator-(const mat4& m1, const mat4& m2) {
	// TODO: insert return statement here
}

math::mat4& math::operator*(const mat4& m, const float k) {
	// TODO: insert return statement here
}

math::mat4& math::operator*(const float k, const mat4& m) {
	// TODO: insert return statement here
}

math::mat4& math::operator*(const mat4& m, const math::vec4 v) {
	// TODO: insert return statement here
}

math::mat4& math::operator*(const mat4& m1, const mat4& m2) {
	// TODO: insert return statement here
}

bool math::operator==(const mat4& m1, const mat4& m2) {
	return false;
}

bool math::operator!=(const mat4& m1, const mat4& m2) {
	return false;
}

std::ostream& math::operator<<(std::ostream& os, const mat4& m) {
	// TODO: insert return statement here
}
