#include "vec4.hpp"
#define LIMIT 0.00001f


engine::math::vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

engine::math::vec4::vec4(const float k) : x(k), y(k), z(k), w(1.0f) {}

engine::math::vec4::vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}

engine::math::vec4::vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

engine::math::vec4::~vec4() {}

void engine::math::vec4::clean() {
	if (x <= LIMIT)
		x = 0;
	if (y <= LIMIT)
		y = 0;
	if (z <= LIMIT)
		z = 0;
	if (w <= LIMIT)
		w = 0;
}

float* engine::math::vec4::data() { 
	float data[4] = { x, y, z, w };
	return data;
}

const float engine::math::vec4::quadrance() const {
	return x * x + y * y + z * z + w * w;
}

const float engine::math::vec4::magnitude() const {
	return sqrt(quadrance());
}

const engine::math::vec4 engine::math::vec4::normalize() const {   
	return *this/(*this).magnitude();
}

const engine::math::vec4 engine::math::vec4::operator-() const {
	return vec4(-x, -y, -z, -w);
}

engine::math::vec4& engine::math::vec4::operator=(const vec4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

engine::math::vec4& engine::math::vec4::operator+=(const vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

engine::math::vec4& engine::math::vec4::operator-=(const vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

engine::math::vec4& engine::math::vec4::operator*=(const vec4& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

engine::math::vec4& engine::math::vec4::operator/=(const vec4& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

const engine::math::vec4 engine::math::operator+(const vec4& v1, const vec4& v2) {
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

const engine::math::vec4 engine::math::operator-(const vec4& v1, const vec4& v2) {
	return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

const engine::math::vec4 engine::math::operator*(const vec4& v, const float k) {
	return vec4(v.x * k, v.y * k, v.z * k, v.w * k);
}

const engine::math::vec4 engine::math::operator*(const float k, const vec4& v) {
	return v * k;
}

const engine::math::vec4 engine::math::operator/(const vec4& v, const float k) {
	return vec4(v.x / k, v.y / k, v.z / k, v.w / k);
}

const bool engine::math::operator==(const vec4& v1, const vec4& v2) {
	return (abs(v1.x - v2.x) < LIMIT && abs(v1.y - v2.y) < LIMIT && abs(v1.z - v2.z) < LIMIT && abs(v1.w - v2.z) < LIMIT);
}

const bool engine::math::operator!=(const vec4& v1, const vec4& v2) {
	return (abs(v1.x - v2.x) >= LIMIT || abs(v1.y - v2.y) >= LIMIT || abs(v1.z - v2.z) >= LIMIT || abs(v1.w - v2.w) >= LIMIT);
}

std::ostream& engine::math::operator<<(std::ostream& os, const vec4& v) {
	os << "vec4[" << v.x << "," << v.y << "," << v.z << "," << v.w << "]";
	return os;
}

std::istream& engine::math::operator>>(std::istream& is, vec4& v) {
	is >> v.x;
	is >> v.y;
	is >> v.z;
	is >> v.w;
	return is;
}
