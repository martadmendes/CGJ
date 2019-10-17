#include "mat2.hpp"
#define LIMIT 0.00001f

math::mat2::mat2() : data{ 0.0f } {}

math::mat2::mat2(const float k) : data{ k, 0.0f, 0.0f, k } {}

math::mat2::mat2(const float m0, const float m1, const float m2, const float m3) : data{ m0, m1, m2, m3 } {}

math::mat2::mat2(const mat2& m) {
	m.transpose();
	for (int i = 0; i <= 3; i++) {
		data[i] = m.data[i];
	}
}

void math::mat2::clean() {
	for (float f : data) {
		if (f <= LIMIT)
			f = 0.0f;
	}
}

float math::mat2::determinant() const {
	return data[0]*data[3] - data[2]*data[1];
}

math::mat2 math::mat2::transpose() const {
	return mat2(data[0], data[2], 
				data[1], data[3]);
}

math::mat2 math::mat2::inverse() const {
	float det = determinant();

	if (det == 0) {
		throw std::exception("For the inverse to exist, the determinant can't be 0.");
	}
	return mat2(data[3] / det, -data[1] / det, -data[2] / det, data[0] / det);
}

math::mat2& math::mat2::operator=(const mat2& m) {
	for (int i = 0; i <= 3; i++) {
		data[i] = m.data[i];
	}
	return *this;
}

math::mat2& math::mat2::operator+=(const mat2& m) {
	for (int i = 0; i <= 3; i++) {
		data[i] += m.data[i];
	}
	return *this;
}

math::mat2& math::mat2::operator-=(const mat2& m) {
	for (int i = 0; i <= 3; i++) {
		data[i] -= m.data[i];
	}
	return *this;
}

math::mat2& math::mat2::operator*=(const float k) {
	for (int i = 0; i <= 3; i++) {
		data[i] *= k;
	}
	return *this;
}

math::mat2 math::operator+(const mat2& m1, const mat2& m2) {
	mat2 result;
	for (int i = 0; i <= 3; i++) {
		result.data[i] = m1.data[i] + m2.data[i];
	}
	return result;
}

math::mat2 math::operator-(const mat2& m1, const mat2& m2) {
	mat2 result;
	for (int i = 0; i <= 3; i++) {
		result.data[i] = m1.data[i] - m2.data[i];
	}
	return result;
}

math::mat2 math::operator*(const mat2& m, const float k) {
	mat2 result;
	for (int i = 0; i <= 3; i++) {
		result.data[i] = m.data[i] * k;
	}
	return result;
}

math::mat2 math::operator*(const float k, const mat2& m) {
	return m * k;
}

math::vec2 math::operator*(const mat2& m, const math::vec2 v) {
	return vec2(m.data[0] * v.x + m.data[2] * v.y, m.data[1] * v.x + m.data[3] * v.y);
}

math::mat2 math::operator*(const mat2& m1, const mat2& m2) {
	mat2 result;	
	result.data[0] = m1.data[0] * m2.data[0] + m1.data[2] * m2.data[1];
	result.data[1] = m1.data[1] * m2.data[0] + m1.data[3] * m2.data[1];
	result.data[2] = m1.data[0] * m2.data[2] + m1.data[2] * m2.data[3];
	result.data[3] = m1.data[1] * m2.data[2] + m1.data[3] * m2.data[3];
	return result;
}

bool math::operator==(const mat2& m1, const mat2& m2) {
	for (int i = 0; i <= 3; i++) {
		if (abs(m1.data[i] - m2.data[i]) >= LIMIT)
			return false;
	}
	return true;
}

bool math::operator!=(const mat2& m1, const mat2& m2) {
	for (int i = 0; i <= 3; i++) {
		if (abs(m1.data[i] - m2.data[i]) >= LIMIT)
			return true;
	}
	return false;
}

std::ostream& math::operator<<(std::ostream& os, const mat2& m) {
	os << "mat2[" << m.data[0] << " " << m.data[2] << "\n";
	os << "     " << m.data[1] << " " << m.data[3] << "]\n";
	return os;
}
