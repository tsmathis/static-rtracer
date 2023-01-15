#pragma once

#include <cmath>
#include <memory>

#include "hittable.h"
#include "vec3.h"

class material;


class sphere : public hittable {
public:
	sphere() {}
	sphere(point3 cen, double r, std::shared_ptr<material> m)
		: center(cen), radius(r), mat_ptr(m) {};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
	
public:
	point3 center;
	double radius;
	std::shared_ptr<material> mat_ptr;

private:
	static void get_sphere_uv(const point3& p, double& u, double& v);
};
