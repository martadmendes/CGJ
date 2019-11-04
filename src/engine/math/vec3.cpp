#include "vec3.hpp"
#define LIMIT 0.00001f

engine::math::vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {}

engine::math::vec3::vec3(const float k) : x(k), y(k), z(k) {}

engine::math::vec3::vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

engine::math::vec3::vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

engine::math::vec3::~vec3() {}

void engine::math::vec3::clean() {
	if (x <= LIMIT)
		x = 0;
	if (y <= LIMIT)
		y = 0;
	if (z <= LIMIT)
		z = 0;
}

float* engine::math::vec3::data() {
	float data[3] = { x, y, z };
	return data;
}

const float engine::math::vec3::quadrance() const {
	return x*x + y*y + z*z;
}

const float engine::math::vec3::magnitude() const {
	return sqrt(quadrance());
}

const engine::math::vec3 engine::math::vec3::normalize() const {
	return *this/(*this).magnitude();
}

const engine::math::vec3 engine::math::vec3::operator-() const {
	return vec3(-x, -y, -z);
}

engine::math::vec3& engine::math::vec3::operator=(const vec3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

engine::math::vec3& engine::math::vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

engine::math::vec3& engine::math::vec3::operator-=(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

engine::math::vec3& engine::math::vec3::operator*=(const vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

engine::math::vec3& engine::math::vec3::operator/=(const vec3& v) {
	x /= v.x;
	x /= v.y;
	x /= v.z;
	return *this;
}

const engine::math::vec3 engine::math::operator+(const vec3& v1, const vec3& v2) {
	return vec3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

const engine::math::vec3 engine::math::operator-(const vec3& v1, const vec3& v2) {
	return vec3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

const engine::math::vec3 engine::math::operator*(const vec3& v, const float k) {
	return vec3(v.x*k, v.y*k, v.z*k);
}

const engine::math::vec3 engine::math::operator*(const float k, const vec3& v) {
	return v * k;
}

const engine::math::vec3 engine::math::operator/(const vec3& v, const float k) {
	return vec3(v.x / k, v.y / k, v.z / k);
}

const bool engine::math::operator==(const vec3& v1, const vec3& v2) {
	return (abs(v1.x - v2.x) < LIMIT && abs(v1.y - v2.y) < LIMIT && abs(v1.z - v2.z) < LIMIT);
}

const bool engine::math::operator!=(const vec3& v1, const vec3& v2) {
	return (abs(v1.x - v2.x) >= LIMIT || abs(v1.y - v2.y) >= LIMIT || abs(v1.z - v2.z) >= LIMIT);
}

std::ostream& engine::math::operator<<(std::ostream& os, const vec3& v) {
	os << "vec3[" << v.x << "," << v.y << "," << v.z << "]";
	return os;
}

std::istream& engine::math::operator>>(std::istream& is, vec3& v) {
	is >> v.x;
	is >> v.y;
	is >> v.z;
	return is;
}
