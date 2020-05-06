#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "color.h"

double hitSphere(const point3& center, double radius, const ray& ray)
{
	vec3 oc = ray.origin() - center;
	auto a = dot(ray.direction(), ray.direction());
	auto b = 2.0 * dot(oc, ray.direction());
	auto c = dot(oc, oc) - radius * radius;

	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

vec3 rayColor(const ray &r)
{
	auto t = hitSphere(point3(0, 0, -1), 0.5, r);
	
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));

		return 0.5 * color(N.x() + 1.0, N.y() + 1.0, N.z() + 1.0);
	}

	vec3 unitDirection = unit_vector(r.direction());
	t = 0.5 * (unitDirection.y() + 1.0); 
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

	for (int j = imageHeight-1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			auto u = double(i) / (imageWidth-1);
			auto v = double(j) / (imageHeight-1);

			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);

			color pixelColor = rayColor(r);
			write_color(std::cout, pixelColor);
		}
	}
	std::cerr << "\nDone.\n";
}