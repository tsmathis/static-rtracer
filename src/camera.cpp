#include "camera.h"

#include "common_consts.h"
#include "vec3.h"
#include "ray.h"



ray camera::get_ray(double s, double t) const {
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x() + v * rd.y();

	return ray(
		origin + offset,
		lower_left_corner + s * horizontal + t * vertical - origin - offset,
		random_double(time0, time1)
	);
}
