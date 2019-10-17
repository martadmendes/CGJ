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

math::mat4::mat4(const mat4& m) {
	m.transpose();
	for (int i = 0; i <= 15; i++) {
		data[i] = m.data[i];
	}
}

void math::mat4::clean() {
	for (float f : data) {
		if (f <= LIMIT)
			f = 0.0f;
	}
}

math::mat4 math::mat4::transpose() const {
	return mat4(data[0], data[4], data[8], data[12], 
				data[1], data[5], data[9], data[13], 
				data[2], data[6], data[10], data[14], 
				data[3], data[7], data[11], data[15]);
}

math::mat4& math::mat4::operator=(const mat4& m) {
	for (int i = 0; i <= 15; i++) {
		data[i] = m.data[i];
	}
	return *this;
}

math::mat4& math::mat4::operator+=(const mat4& m) {
	for (int i = 0; i <= 15; i++) {
		data[i] += m.data[i];
	}
	return *this;
}

math::mat4& math::mat4::operator-=(const mat4& m) {
	for (int i = 0; i <= 15; i++) {
		data[i] -= m.data[i];
	}
	return *this;
}

math::mat4& math::mat4::operator*=(const float k) {
	for (int i = 0; i <= 15; i++) {
		data[i] *= k;
	}
	return *this;
}

math::mat4 math::operator+(const mat4& m1, const mat4& m2) {
	mat4 result;
	for (int i = 0; i <= 15; i++) {
		result.data[i] = m1.data[i] + m2.data[i];
	}
	return result;
}

math::mat4 math::operator-(const mat4& m1, const mat4& m2) {
	mat4 result;
	for (int i = 0; i <= 15; i++) {
		result.data[i] = m1.data[i] - m2.data[i];
	}
	return result;
}

math::mat4 math::operator*(const mat4& m, const float k) {
	mat4 result;
	for (int i = 0; i <= 15; i++) {
		result.data[i] = m.data[i] * k;
	}
	return result;
}

math::mat4 math::operator*(const float k, const mat4& m) {
	return m * k;
}

math::vec4 math::operator*(const mat4& m, const math::vec4 v) {
	return vec4(m.data[0] * v.x + m.data[4] * v.y + m.data[8] * v.z + m.data[12] * v.w,
				m.data[1] * v.x + m.data[5] * v.y + m.data[9] * v.z + m.data[13] * v.w,
				m.data[2] * v.x + m.data[6] * v.y + m.data[10] * v.z + m.data[14] * v.w,
				m.data[3] * v.x + m.data[7] * v.y + m.data[11] * v.z + m.data[15] * v.w);
}

math::mat4 math::operator*(const mat4& m1, const mat4& m2) {
	mat4 result;
	result.data[0] = m1.data[0] * m2.data[0] + m1.data[4] + m2.data[1] + m1.data[8] * m2.data[2] + m1.data[12] * m2.data[3];
	result.data[1] = m1.data[1] * m2.data[0] + m1.data[5] + m2.data[1] + m1.data[9] * m2.data[2] + m1.data[13] * m2.data[3];
	result.data[2] = m1.data[2] * m2.data[0] + m1.data[6] + m2.data[1] + m1.data[10] * m2.data[2] + m1.data[14] * m2.data[3];
	result.data[3] = m1.data[3] * m2.data[0] + m1.data[7] + m2.data[1] + m1.data[11] * m2.data[2] + m1.data[15] * m2.data[3];
	result.data[4] = m1.data[0] * m2.data[4] + m1.data[4] + m2.data[5] + m1.data[8] * m2.data[6] + m1.data[12] * m2.data[7];
	result.data[5] = m1.data[1] * m2.data[4] + m1.data[5] + m2.data[5] + m1.data[9] * m2.data[6] + m1.data[13] * m2.data[7];
	result.data[6] = m1.data[2] * m2.data[4] + m1.data[6] + m2.data[5] + m1.data[10] * m2.data[6] + m1.data[14] * m2.data[7];
	result.data[7] = m1.data[3] * m2.data[4] + m1.data[7] + m2.data[5] + m1.data[11] * m2.data[6] + m1.data[15] * m2.data[7];
	result.data[8] = m1.data[0] * m2.data[8] + m1.data[4] + m2.data[9] + m1.data[8] * m2.data[10] + m1.data[12] * m2.data[11];
	result.data[9] = m1.data[1] * m2.data[8] + m1.data[5] + m2.data[9] + m1.data[9] * m2.data[10] + m1.data[13] * m2.data[11];
	result.data[10] = m1.data[2] * m2.data[8] + m1.data[6] + m2.data[9] + m1.data[10] * m2.data[10] + m1.data[14] * m2.data[11];
	result.data[11] = m1.data[3] * m2.data[8] + m1.data[7] + m2.data[9] + m1.data[11] * m2.data[10] + m1.data[15] * m2.data[11];
	result.data[12] = m1.data[0] * m2.data[12] + m1.data[4] + m2.data[13] + m1.data[8] * m2.data[14] + m1.data[12] * m2.data[15];
	result.data[13] = m1.data[1] * m2.data[12] + m1.data[5] + m2.data[13] + m1.data[9] * m2.data[14] + m1.data[13] * m2.data[15];
	result.data[14] = m1.data[2] * m2.data[12] + m1.data[6] + m2.data[13] + m1.data[10] * m2.data[14] + m1.data[14] * m2.data[15];
	result.data[15] = m1.data[3] * m2.data[12] + m1.data[7] + m2.data[13] + m1.data[11] * m2.data[14] + m1.data[15] * m2.data[15];
	return result;
}


bool math::operator==(const mat4& m1, const mat4& m2) {
	for (int i = 0; i <= 15; i++) {
		if (abs(m1.data[i] - m2.data[i]) >= LIMIT)
			return false;
	}
	return true;
}

bool math::operator!=(const mat4& m1, const mat4& m2) {
	for (int i = 0; i <= 15; i++) {
		if (abs(m1.data[i] - m2.data[i]) >= LIMIT)
			return true;
	}
	return false;
}

std::ostream& math::operator<<(std::ostream& os, const mat4& m) {
	os << "mat4[" << m.data[0] << " " << m.data[4] << " " << m.data[8] << " " << m.data[12] << "\n";
	os << "     " << m.data[1] << " " << m.data[5] << " " << m.data[9] << " " << m.data[13] << "\n";
	os << "     " << m.data[2] << " " << m.data[6] << " " << m.data[10] << " " << m.data[14] << "\n";
	os << "     " << m.data[3] << " " << m.data[7] << " " << m.data[11] << " " << m.data[15] << "]\n";
	return os;
}
