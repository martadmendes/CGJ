#include "vec2.hpp"
#define LIMIT 0.00001f

engine::math::vec2::vec2() : x(0.0f), y(0.0f) {}

engine::math::vec2::vec2(const float k) : x(k), y(k) {}

engine::math::vec2::vec2(const float x, const float y) : x(x), y(y) {}

engine::math::vec2::vec2(const vec2& v) : x(v.x), y(v.y) {}

engine::math::vec2::~vec2() {}

void engine::math::vec2::clean() {
	if (x <= LIMIT)
		x = 0;
	if (y <= LIMIT)
		y = 0;
}

float* engine::math::vec2::data() {  
	float data[2] = { x, y };
	return data;
}

const float engine::math::vec2::quadrance() const {
	return x*x + y*y;
}

const float engine::math::vec2::magnitude() const {
	return sqrt(quadrance());
}

const engine::math::vec2 engine::math::vec2::normalize() const {
	return *this/(*this).magnitude();
}

const engine::math::vec2 engine::math::vec2::operator-() const {
	return vec2(-x, -y);
}

engine::math::vec2& engine::math::vec2::operator=(const vec2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

engine::math::vec2& engine::math::vec2::operator+=(const vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

engine::math::vec2& engine::math::vec2::operator-=(const vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

engine::math::vec2& engine::math::vec2::operator*=(const vec2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

engine::math::vec2& engine::math::vec2::operator/=(const vec2& v) {
	x /= v.x;
	y /= v.y;
	return *this;
}

const engine::math::vec2 engine::math::operator+(const vec2& v1, const vec2& v2) {
	return vec2(v1.x+v2.x, v1.y+v2.y);
}

const engine::math::vec2 engine::math::operator-(const vec2& v1, const vec2& v2) {
	return vec2(v1.x-v2.x, v1.y-v2.y);
}

const engine::math::vec2 engine::math::operator*(const vec2& v, const float k) {
	return vec2(v.x*k, v.y*k);
}

const engine::math::vec2 engine::math::operator*(const float k, const vec2& v) {
	return v * k;
}

const engine::math::vec2 engine::math::operator/(const vec2& v, const float k) {
	return vec2(v.x / k, v.y / k);
}

const bool engine::math::operator==(const vec2& v1, const vec2& v2) {
	return (abs(v1.x - v2.x) < LIMIT && abs(v1.y - v2.y) < LIMIT);
}

const bool engine::math::operator!=(const vec2& v1, const vec2& v2) {
	return (abs(v1.x - v2.x) >= LIMIT || abs(v1.y - v2.y) >= LIMIT);
}

std::ostream& engine::math::operator<<(std::ostream& os, const vec2& v) {
	os << "vec2[" << v.x << "," << v.y << "]";
	return os;
}

std::istream& engine::math::operator>>(std::istream& is, vec2& v) {
	is >> v.x;
	is >> v.y;
	return is;
}

