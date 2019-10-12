#include "vec2.hpp"
#define LIMIT 0.00001f

math::vec2::vec2() : x(0.0f), y(0.0f) {}

math::vec2::vec2(const float k) : x(k), y(k) {}

math::vec2::vec2(const float x, const float y) : x(x), y(y) {}

math::vec2::vec2(const vec2& v) : x(v.x), y(v.y) {}

math::vec2::~vec2() {}

void math::vec2::clean() {
	if (x <= LIMIT)
		x = 0;
	if (y <= LIMIT)
		y = 0;
}

float* math::vec2::data() {  
	float data[2] = { x, y };
	return data;
}

const float math::vec2::quadrance() const {
	return x*x + y*y;
}

const float math::vec2::magnitude() const {
	return sqrt(quadrance());
}

const math::vec2 math::vec2::normalize() const {
	return *this/(*this).magnitude();
}

const math::vec2 math::vec2::operator-() const {
	return vec2(-x, -y);
}

math::vec2& math::vec2::operator=(const vec2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

math::vec2& math::vec2::operator+=(const vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

math::vec2& math::vec2::operator-=(const vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

math::vec2& math::vec2::operator*=(const vec2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

math::vec2& math::vec2::operator/=(const vec2& v) {
	x /= v.x;
	y /= v.y;
	return *this;
}

const math::vec2 math::operator+(const vec2& v1, const vec2& v2) {
	return vec2(v1.x+v2.x, v1.y+v2.y);
}

const math::vec2 math::operator-(const vec2& v1, const vec2& v2) {
	return vec2(v1.x-v2.x, v1.y-v2.y);
}

const math::vec2 math::operator*(const vec2& v, const float k) {
	return vec2(v.x*k, v.y*k);
}

const math::vec2 math::operator*(const float k, const vec2& v) {
	return v * k;
}

const math::vec2 math::operator/(const vec2& v, const float k) {
	return vec2(v.x / k, v.y / k);
}

const bool math::operator==(const vec2& v1, const vec2& v2) {
	return (abs(v1.x - v2.x) < LIMIT && abs(v1.y - v2.y) < LIMIT);
}

const bool math::operator!=(const vec2& v1, const vec2& v2) {
	return (abs(v1.x - v2.x) >= LIMIT || abs(v1.y - v2.y) >= LIMIT);
}

std::ostream& math::operator<<(std::ostream& os, const vec2& v) {
	os << "vec2[" << v.x << "," << v.y << "]";
	return os;
}

std::istream& math::operator>>(std::istream& is, vec2& v) {
	is >> v.x;
	is >> v.y;
	return is;
}

