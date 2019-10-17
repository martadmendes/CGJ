#include "mat3.hpp"
#define LIMIT 0.00001f

math::mat3::mat3() : data{ 0.0f } {}

math::mat3::mat3(const float k) : data{ k, 0.0f, 0.0f, 0.0f, k, 0.0f, 0.0f, 0.0f, k } {}

math::mat3::mat3(const float m0, const float m1, const float m2, 
	const float m3, const float m4, const float m5, 
	const float m6, const float m7, const float m8) : data{ m0, m1, m2, m3, m4, m5, m6, m7, m8 } {}

math::mat3::mat3(const mat3& m) {
	m.transpose();
	for (int i = 0; i <= 8; i++) {
		data[i] = m.data[i];
 	}
}

void math::mat3::clean() {
	for (float f : data) {
		if (f <= LIMIT)
			f = 0.0f;
	}
}

float math::mat3::determinant() const {
	mat2 a = mat2(data[4], data[5], data[7], data[8]);
	mat2 b = mat2(data[1], data[2], data[7], data[8]);
	mat2 c = mat2(data[1], data[2], data[4], data[5]);
	return data[0] * a.determinant() - data[3] * b.determinant() + data[6] * c.determinant();
}

math::mat3 math::mat3::transpose() const {
	return mat3(data[0], data[3], data[6], 
				data[1], data[4], data[7], 
				data[2], data[5], data[8]);
}

math::mat3 math::mat3::inverse() const {
	float det = determinant();


	if (det == 0) {
		throw std::exception("For the inverse to exist, the determinant can't be 0.");
	}

}

math::mat3 math::mat3::adjugate_matrix(mat3 m) {
	mat2 m0 = mat2(m.data[4], m.data[5], m.data[7], m.data[8]);
	mat2 m1 = mat2(m.data[3], m.data[5], m.data[6], m.data[8]);
	mat2 m2 = mat2(m.data[3], m.data[4], m.data[6], m.data[7]);
	mat2 m3 = mat2(m.data[1], m.data[2], m.data[7], m.data[8]);
	mat2 m4 = mat2(m.data[0], m.data[2], m.data[6], m.data[8]);
	mat2 m5 = mat2(m.data[0], m.data[1], m.data[6], m.data[7]);
	mat2 m6 = mat2(m.data[1], m.data[2], m.data[4], m.data[5]);
	mat2 m7 = mat2(m.data[0], m.data[2], m.data[3], m.data[5]);
	mat2 m8 = mat2(m.data[0], m.data[1], m.data[3], m.data[4]);

	mat3 cofactors = mat3(m0.determinant(), m1.determinant(), m2.determinant(),
								m3.determinant(), m4.determinant(), m5.determinant(),
								m6.determinant(), m7.determinant(), m8.determinant());

	//multiply certain elements by -1 to get the adjugate matrix
	cofactors.data[1] *= -1;
	cofactors.data[3] *= -1;
	cofactors.data[5] *= -1;
	cofactors.data[7] *= -1;

	return cofactors; 
}

math::mat3& math::mat3::operator=(const mat3& m) {
	for(int i = 0; i <= 8; i++){
		data[i] = m.data[i];
	}
	return *this;
}

math::mat3& math::mat3::operator+=(const mat3& m) {
	for (int i = 0; i <= 8; i++) {
		data[i] += m.data[i];
	}
	return *this;
}

math::mat3& math::mat3::operator-=(const mat3& m) {
	for (int i = 0; i <= 8; i++) {
		data[i] -= m.data[i];
	}
	return *this;
}

math::mat3& math::mat3::operator*=(const float k) {
	for (int i = 0; i <= 8; i++) {
		data[i] *= k;
	}
}

math::mat3 math::operator+(const mat3& m1, const mat3& m2) {
	math::mat3 result;
	for (int i = 0; i <= 8; i++) {
		result.data[i] = m1.data[i] + m2.data[i];
	}
	return result;
}

math::mat3 math::operator-(const mat3& m1, const mat3& m2) {
	math::mat3 result;
	for (int i = 0; i <= 8; i++) {
		result.data[i] = m1.data[i] - m2.data[i];
	}
	return result;
}

math::mat3 math::operator*(const mat3& m, const float k) {
	math::mat3 result;
	for (int i = 0; i <= 8; i++) {
		result.data[i] = m.data[i] * k;
	}
	return result;
}

math::mat3 math::operator*(const float k, const mat3& m) {
	return m * k;
}

math::vec3 math::operator*(const mat3& m, const math::vec3 v) {
	return vec3(m.data[0] * v.x + m.data[3] * v.y + m.data[6] * v.z, 
				m.data[1] * v.x + m.data[4] * v.y + m.data[7] * v.z, 
				m.data[2] * v.x + m.data[5] * v.y + m.data[8] * v.z);
}

math::mat3 math::operator*(const mat3& m1, const mat3& m2) {
	math::mat3 result;
	result.data[0] = m1.data[0] * m2.data[0] + m1.data[3] * m2.data[1] + m1.data[6] * m2.data[2];
	result.data[1] = m1.data[1] * m2.data[0] + m1.data[4] * m2.data[1] + m1.data[7] * m2.data[2];
	result.data[2] = m1.data[2] * m2.data[0] + m1.data[5] * m2.data[1] + m1.data[8] * m2.data[2];
	result.data[3] = m1.data[0] * m2.data[3] + m1.data[3] * m2.data[4] + m1.data[6] * m2.data[5];
	result.data[4] = m1.data[1] * m2.data[3] + m1.data[4] * m2.data[4] + m1.data[7] * m2.data[5];
	result.data[5] = m1.data[2] * m2.data[3] + m1.data[5] * m2.data[4] + m1.data[8] * m2.data[5];
	result.data[6] = m1.data[0] * m2.data[6] + m1.data[3] * m2.data[7] + m1.data[6] * m2.data[8];
	result.data[7] = m1.data[1] * m2.data[6] + m1.data[4] * m2.data[7] + m1.data[7] * m2.data[8];
	result.data[8] = m1.data[2] * m2.data[6] + m1.data[5] * m2.data[7] + m1.data[8] * m2.data[8];
	return result;
}

bool math::operator==(const mat3& m1, const mat3& m2) {
	for (int i = 0; i <= 8; i++) {
		if (abs(m1.data[i] - m2.data[i]) >= LIMIT)
			return false;
	}
	return true;
}

bool math::operator!=(const mat3& m1, const mat3& m2) {
	for (int i = 0; i <= 8; i++) {
		if (abs(m1.data[i] - m2.data[i]) >= LIMIT)
			return true;
	}
	return false;
}

std::ostream& math::operator<<(std::ostream& os, const mat3& m) {
	os << "mat3[";
	int i = 0, j = 0;
	while (i<=8) {
		if (i<3) {
			os << "[";
		}
		else if (j == 2) {
			os << m.data[i] << " ";
			i + 3;
		}
		if (i > 8) {
			os << "]\n    ";
			j++;
			i = j;
		}
	}

	/*os << "mat3[" << m.data[0] << " " << m.data[3] << " " << m.data[6] << "\n";
	os << "     " << m.data[1] << " " << m.data[4] << " " << m.data[7] << "\n";
	os << "     " << m.data[2] << " " << m.data[5] << " " << m.data[8] << "]\n";*/
	return os;
}
