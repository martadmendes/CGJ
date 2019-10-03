#include "vec2.hpp"

math::vec2::vec2() : x(0.0f), y(0.0f) {} //assim ou construtor vazio mm?

math::vec2::vec2(const float k) : x(k), y(k) {}

math::vec2::vec2(const float x, const float y) : x(x), y(y) {}

math::vec2::vec2(const vec2& v) : x(v.x), y(v.y) {}

math::vec2::~vec2() {}

void math::vec2::clean() {
	x = 0.0f;
	y = 0.0f;
}

float* math::vec2::data() {  //whaaaat
	return nullptr;
}

const float math::vec2::quadrance() const {
	return x*x + y*y;
}

const float math::vec2::magnitude() const {
	return sqrt(quadrance());
}

float math::vec2::dotProduct(vec2 v1, vec2 v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

const vec2 math::vec2::operator-() const {
	return vec2(-x, -y);
}

vec2& math::vec2::operator=(const vec2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

vec2& math::vec2::operator+=(const vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

vec2& math::vec2::operator-=(const vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

vec2& math::vec2::operator*=(const vec2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

const vec2 math::operator+(const vec2& v1, const vec2& v2) {
	return vec2(v1.x+v2.x, v1.y+v2.y);
}

const vec2 math::operator-(const vec2& v1, const vec2& v2) {
	return vec2(v1.x-v2.x, v1.y-v2.y);
}

const vec2 math::operator*(const vec2& v, const float k) {
	return vec2(v.x*k, v.y*k);
}

const vec2 math::operator*(const float k, const vec2& v) {
	return vec2(k*v.x, k*v.y);
}

const bool math::operator==(const vec2& v1, const vec2& v2) {
	if (v1.x == v2.x && v1.y == v2.y)
		return true;
	else
		return false;
}

const bool math::operator!=(const vec2& v1, const vec2& v2) {
	if (v1.x != v2.x || v1.y != v2.y)
		return true;
	else
		return false;
}

std::ostream& math::operator<<(std::ostream& os, const vec2& v) {
	os << "vec2[" << v.x << "," << v.y << "]";
	return os;
}

std::istream& math::operator>>(std::istream& is, vec2& v) {
	in >> v.x;
	in >> v.y;
	return in;
}

