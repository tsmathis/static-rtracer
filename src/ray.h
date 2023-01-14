#pragma once

#include "vec3.h"


class ray {
public:
	ray() {}
	ray(const point3& origin, const vec3& direction, double time = 0.0)
		: orig(origin), dir(direction), tm(time)
	{}

	point3 origin() const;
	vec3 direction() const;
	double time() const;

	point3 at(double t) const;

public:
	point3 orig;
	vec3 dir;
	double tm;
};
