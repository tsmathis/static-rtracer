#include "moving_sphere.h"

#include <cmath>

#include "aabb.h"
#include "ray.h"
#include "vec3.h"

struct hit_record;


bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center(r.time());
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return false;
	auto sqrtd = sqrt(discriminant);

	// Find nearest root that lies in the acceptable range
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center(r.time())) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

	return true;
}

bool moving_sphere::bounding_box(double _time0, double _time1, aabb& output_box) const {
	aabb box0 = aabb(
		center(_time0) - vec3(radius, radius, radius),
		center(_time0) + vec3(radius, radius, radius));
	aabb box1 = aabb(
		center(_time1) - vec3(radius, radius, radius),
		center(_time1) + vec3(radius, radius, radius));
	output_box = surrounding_box(box0, box1);
	return true;
}

point3 moving_sphere::center(double time) const {
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}
