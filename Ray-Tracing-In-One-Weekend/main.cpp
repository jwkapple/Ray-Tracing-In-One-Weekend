#include <iostream>
#include "vec3.h"
#include "ray.h"

double hitSphere(const vec3& center, double radius, const ray& ray)
{
	vec3 oc = ray.origin() - center;
	auto a = dot(ray.direction(), ray.direction());
	auto b = 2.0 * dot(oc, ray.direction());
	auto c = dot(oc, oc) - radius * radius;

	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		return -1;
	}
	else
	{
		return (-b - sqrt(discriminant) / (2.0 * a));
	}
}

vec3 rayColor(const ray &r)
{
	auto t = hitSphere(vec3(0, 0, -1), 0.5, r);
	
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * vec3(N.x() + 1.0, N.y() + 1.0, N.z() + 1.0);
	}

	vec3 unitDirection = unit_vector(r.direction());
	t = 0.5 * (unitDirection.y() + 1.0); 
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
	const int imageWidth = 200;
	const int imageHeight = 100;

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int j = imageHeight-1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			auto u = double(i) / imageWidth;
			auto v = double(j) / imageHeight;

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 color = rayColor(r);

			color.write_color(std::cout);
		}
	}
	std::cerr << "\nDone.\n";
}