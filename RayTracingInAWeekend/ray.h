#pragma once

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const point3& origin, const vec3& direction) :origin(origin), dir(direction) {}
	point3 getOrigin()const { return origin; }
	vec3 getDirection()const { return dir; }

	point3 at(double t) {
		return origin + t * dir;
	}

public:
	point3 origin;
	vec3 dir;
};
