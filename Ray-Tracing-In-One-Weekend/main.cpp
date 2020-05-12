
#include "rtweekend.h"

#include "hittableList.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include <iostream>



vec3 rayColor(const ray &r, const hittable& world, int depth)
{
	hitRecord rec;
	
	// If we've exceeded the ray bounce limit, no mor light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	// Some of the reflected rays hit the object they are reflecting off of not at exactly t = 0 
	// So we need to ignore hits very near zero
	if (world.hit(r, 0.001, infinity, rec))
	{
		point3 target = rec.p + rec.normal + random_unit_vector();
		return 0.5 * rayColor(ray(rec.p, target - rec.p), world, depth-1);
	}


	vec3 unitDirection = unit_vector(r.direction());
	auto t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 384;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const int samples_per_pixel = 100;
	const int maxDepth = 10;

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	hittableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, vec3(1,0,0)));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, vec3(0,1,0)));

	camera cam;

	for (int j = imageHeight-1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			color pixelColors;
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (double(i) + randomDouble()) / (imageWidth - 1);
				auto v = (double(j) + randomDouble())/ (imageHeight - 1);
				ray r = cam.get_ray(u, v);
				
				pixelColors += rayColor(r, world, maxDepth);
			}
			write_color(std::cout, pixelColors, samples_per_pixel );
		}
	}
	std::cerr << "\nDone.\n";
}