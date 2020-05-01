#include <iostream>
#include "vec3.h"

int main()
{
	const int imageWidth = 200;
	const int imageHeight = 100;

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	
	for (int j = imageHeight-1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			vec3 color{ double(i) / imageWidth, double(j) / imageHeight, 0.2 };
			color.write_color(std::cout);
		}
	}
	std::cerr << "\nDone.\n";
}