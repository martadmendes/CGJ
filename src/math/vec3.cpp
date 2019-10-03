#include "vec3.hpp"

math::vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {} //assim ou construtor vazio mm?

math::vec3::vec3(const float k) : x(k), y(k), z(k) {}

math::vec3::vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

math::vec3::vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

math::vec3::~vec3() {}

void math::vec3::clean() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

float* math::vec3::data() {   //what is thisssss
	return nullptr;
}

const float math::vec3::quadrance() const {
	return x*x + y*y + z*z;
}

const float math::vec3::magnitude() const {
	return sqrt(quadrance());
}

float math::vec3::dotProduct(vec3 v1, vec3 v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

vec3 math::vec3::crossProduct(vec3 v1, vec3 v2) {
	return vec3((v1.y*v2.z - v1.z*v2.y), (v1.z*v2.x - v1.x*v2.z), (v1.x*v2.y - v1.y*v2.x));
}

const vec3 math::vec3::operator-() const {
	return vec3(-x, -y, -z);
}

vec3& math::vec3::operator=(const vec3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

vec3& math::vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec3& math::vec3::operator-=(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec3& math::vec3::operator*=(const vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

const vec3 math::operator+(const vec3& v1, const vec3& v2) {
	return vec3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

const vec3 math::operator-(const vec3& v1, const vec3& v2) {
	return vec3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

const vec3 math::operator*(const vec3& v, const float k) {
	return vec3(v.x*k, v.y*k, v.z*k);  //nao basta return v*k ou k*v ?
}

const vec3 math::operator*(const float k, const vec3& v) {
	return vec3(k*v.x, k*v.y, k*v.z);
}

const bool math::operator==(const vec3& v1, const vec3& v2) {
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return true;
	else
		return false;
}

const bool math::operator!=(const vec3& v1, const vec3& v2) {
	if (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z)
		return true;
	else
		return false;
}

std::ostream& math::operator<<(std::ostream& os, const vec3& v) {
	os << "vec3[" << v.x << "," << v.y << "," << v.z << "]";
	return os;
}

std::istream& math::operator>>(std::istream& is, vec3& v) {
	in >> v.x;
	in >> v.y;
	in >> v.z;
	return in;
}
