#include "qtrn.hpp"

#define PI 3.14159265f
#define LIMIT 0.00001f


engine::math::qtrn::qtrn() : t(0) {}

engine::math::qtrn::qtrn(const float t, const vec3 v) : t(t), v(v) {}

engine::math::qtrn::qtrn(const vec3 axis, const float theta) {
	float radians = theta * PI / 180.0f;

	t = cos(radians / 2);
	v.x = axis.x * sin(radians / 2);
	v.y = axis.y * sin(radians / 2);
	v.z = axis.z * sin(radians / 2);
}

engine::math::qtrn::~qtrn() {}

const float engine::math::qtrn::to_angle() {
	return 2*acos(t);
}

const engine::math::vec3 engine::math::qtrn::to_axis() {
	return (v / sqrt(1 - t * t)).normalize();
}

const void engine::math::qtrn::clean() {
	if (t <= LIMIT)
		t = 0.0f;
	v.clean();
}

const float engine::math::qtrn::quadrance() {
	return t * t + v.x * v.x + v.y * v.y + v.z * v.z;
}

const float engine::math::qtrn::magnitude() {
	return sqrt(quadrance());
}

const engine::math::qtrn engine::math::qtrn::normalize() {
	return *this / (*this).magnitude();
}

const engine::math::qtrn engine::math::qtrn::conjugate() {
	return qtrn(t, -v);
}

const engine::math::qtrn engine::math::qtrn::inverse() {
	return this->conjugate() / this->quadrance();
}


engine::math::qtrn& engine::math::qtrn::operator=(const qtrn& q) {
	t = q.t;
	v.x = q.v.x;
	v.y = q.v.y;
	v.z = q.v.z;
	return *this;
}

engine::math::qtrn& engine::math::qtrn::operator+=(const qtrn& q) {
	t += q.t;
	v.x += q.v.x;
	v.y += q.v.y;
	v.z += q.v.z;
	return *this;
}

engine::math::qtrn& engine::math::qtrn::operator-=(const qtrn& q) {
	t -= q.t;
	v.x -= q.v.x;
	v.y -= q.v.y;
	v.z -= q.v.z;
	return *this;
}

engine::math::qtrn& engine::math::qtrn::operator*=(const qtrn& q) {
	t *= q.t;
	v.x *= q.v.x;
	v.y *= q.v.y;
	v.z *= q.v.z;
	return *this;
}

engine::math::qtrn& engine::math::qtrn::operator/=(const qtrn& q) {
	t /= q.t;
	v.x /= q.v.x;
	v.y /= q.v.y;
	v.z /= q.v.z;
	return *this;
}

const engine::math::qtrn engine::math::operator+(const qtrn& q1, const qtrn& q2) {
	return qtrn(q1.t + q2.t, q1.v + q2.v);
}

const engine::math::qtrn engine::math::operator-(const qtrn& q1, const qtrn& q2) {
	return qtrn(q1.t - q2.t, q1.v - q2.v);
}

const engine::math::qtrn engine::math::operator*(const qtrn& q1, const qtrn& q2) {
	return qtrn();
}

const engine::math::qtrn engine::math::operator*(const qtrn& q, const float k) {
	return qtrn(q.t * k, q.v * k);
}

const engine::math::qtrn engine::math::operator*(const float k, const qtrn& q) {
	return q*k;
}

const engine::math::qtrn engine::math::operator/(const qtrn& q, const float k) {
	return qtrn(q.t / k, q.v / k);
}

const bool engine::math::operator==(const qtrn& q1, const qtrn& q2) {
	return ((abs(q1.t - q2.t) < LIMIT) && (abs(q1.v.x - q2.v.x) < LIMIT) && (abs(q1.v.y - q2.v.y) < LIMIT) && (abs(q1.v.z - q2.v.z) < LIMIT));
}

const std::ostream& engine::math::operator<<(std::ostream& os, qtrn& q) {
	os << "qtrn: \nt = " << q.t << "\nx = " << q.v.x << "\ny = " << q.v.y << "\n z = " << q.v.z << "\n";
	return os;
}

const engine::math::qtrn engine::math::qtrn::lerp(const qtrn& q1, const qtrn& q2, float k) {
	float cos_angle = q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z + q1.t * q2.t;
	float k1 = 1.0f - k;
	float k2 = (cos_angle > 0) ? k : -k;
	qtrn q = k1 * q1 + k2 * q2;
	return q.normalize();
}

const engine::math::qtrn engine::math::qtrn::slerp(const qtrn& q1, const qtrn& q2, float k) {
	float angle = acos(q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z + q1.t * q2.t);
	float k1 = sin((1 - k) * angle) / sin(angle);
	float k2 = sin(k * angle) / sin(angle);
	qtrn q = k1 * q1 + k2 * q2;
	return q.normalize();
}