#pragma once

#include <memory>

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class material;


class xy_rect : public hittable {
public:
	xy_rect() {}
	xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<material> mat)
		: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
		output_box = aabb(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
		return true;
	}

public:
	std::shared_ptr<material> mp;
	double x0, x1, y0, y1, k;

};


class xz_rect : public hittable {
public:
	xz_rect() {}
	xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<material> mat)
		: x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
		output_box = aabb(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
		return true;
	}

public:
	std::shared_ptr<material> mp;
	double x0, x1, z0, z1, k;

};



class yz_rect : public hittable {
public:
	yz_rect() {}
	yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<material> mat)
		: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
		output_box = aabb(point3(k - 0.0001, y0, z0), point3(k + 0.0001, y1, z1));
		return true;
	}

public:
	std::shared_ptr<material> mp;
	double y0, y1, z0, z1, k;

};
