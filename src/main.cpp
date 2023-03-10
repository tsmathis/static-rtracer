#include <iostream>
#include <time.h>

#include "common_consts.h"
#include "scenes.h"
#include "vec3.h"


int main() {
	time_t begin, end;
	time(&begin);

	// Image
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int samples_per_pixel = 80;
	int max_depth = 8;

	// World
	hittable_list world;

	point3 lookfrom;
	point3 lookat;
	auto vfov = 40.0;
	auto aperture = 0.0;
	color background (0, 0, 0);

	switch (0) {
	//default:
	case 1:
		world = random_scene();
		background = color(0.70, 0.80, 1.0);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		aperture = 0.1;
		break;

	case 2:
		world = two_spheres();
		background = color(0.70, 0.80, 1.0);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		break;

	default:
	case 3:
		world = two_perlin_spheres();
		background = color(0.70, 0.80, 1.0);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		break;

	//default:
	case 4:
		world = earth();
		background = color(0.70, 0.80, 1.0);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		break;
	
	//default:
	case 5:
		world = simple_light();
		samples_per_pixel = 400;
		background = color(0.0, 0.0, 0.0);
		lookfrom = point3(26, 3, 6);
		lookat = point3(0, 2, 0);
		vfov = 20.0;
		break;

	//default:
	case 6:
		world = cornell_box();
		aspect_ratio = 1.0;
		image_width = 600;
		samples_per_pixel = 800;
		background = color(0, 0, 0);
		lookfrom = point3(278, 278, -1800);
		lookat = point3(278, 278, 0);
		vfov = 40.0;
		break;

	//default:
	case 7:
		world = cornell_smoke();
		aspect_ratio = 1.0;
		image_width = 600;
		samples_per_pixel = 800;
		background = color(0, 0, 0);
		lookfrom = point3(278, 278, -1800);
		lookat = point3(278, 278, 0);
		vfov = 40.0;
		break;

	//default:
	case 8:
		world = feature_ensemble();
		aspect_ratio = 1.0;
		image_width = 800;
		samples_per_pixel = 1800;
		background = color(0, 0, 0);
		lookfrom = point3(478, 278, -1600);
		lookat = point3(278, 278, 0);
		vfov = 40.0;
		break;
	}


	//Camera
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10;
	int image_height = static_cast<int>(image_width / aspect_ratio);

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {

			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, background, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone\n";

	time(&end);
	time_t elapsed = end - begin;

	std::cerr << "Render time: " << elapsed << "\n";
}