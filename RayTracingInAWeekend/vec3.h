#pragma once

#include <cmath>
#include <iostream>


class vec3 {
public:
	vec3() : e{ 0,0,0 } {}
	vec3(double e0, double e1, double e2) : e{ e0,e1,e2 } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const{return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const vec3& v) {
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	vec3& operator/=(const vec3& v) {
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];
		return *this;
	}

	double length() const {
		return std::sqrt(lengt_squared());
	}
	double lengt_squared() const{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
public:
	double e[3];
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
	return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.e[0] + rhs.e[0], lhs.e[1] + rhs.e[1], lhs.e[2] + rhs.e[2]);
}
inline vec3 operator-(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.e[0] - rhs.e[0], lhs.e[1] - rhs.e[1], lhs.e[2] - rhs.e[2]);
}
inline vec3 operator*(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.e[0]*rhs.e[0], lhs.e[1] * rhs.e[1], lhs.e[2] * rhs.e[2]);
}
inline vec3 operator*(double d, const vec3& value) {
	return vec3(d * value.e[0], d * value.e[1], d * value[2]);
}
inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}
inline vec3 operator/(const vec3 v, double t) {
	return (1 / t) * v;
}
inline double dot(const vec3& lhs, const vec3& rhs) {
	return lhs.e[0] * rhs.e[0]
		+ lhs.e[1] * rhs.e[1]
		+ lhs.e[2] * rhs.e[2];
}
inline vec3 cross(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.e[1] * rhs.e[2] - lhs.e[2] * rhs.e[1],
				lhs.e[2] * rhs.e[0] - lhs.e[0] * rhs.e[2],
				lhs.e[0] * rhs.e[1] - lhs.e[1] * rhs.e[0]);
}
inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}
