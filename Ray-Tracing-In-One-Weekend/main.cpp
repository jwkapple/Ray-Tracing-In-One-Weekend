
#include "rtweekend.h"

#include "hittableList.h"
#include "sphere.h"
#include "color.h"
#include <iostream>



vec3 rayColor(const ray &r, const hittable& world)
{
	hitRecord rec;
	
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + color(1, 1, 1));
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

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";


	point3 origin(0.0, 0.0, 0.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.25, 0.0);
	point3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, 1);


	hittableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	for (int j = imageHeight-1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			auto u = double(i) / (imageWidth-1);
			auto v = double(j) / (imageHeight-1);

			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);

			color pixelColor = rayColor(r, world);
			write_color(std::cout, pixelColor);
		}
	}
	std::cerr << "\nDone.\n";
}