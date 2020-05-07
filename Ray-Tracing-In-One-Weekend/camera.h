#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera
{
public:
	camera()
	{
		mLowerLeftCorner = point3(-2.0, -1.0, -1.0);
		mHorizontal = vec3(4.0, 0.0, 0.0);
		mVertical = vec3(0.0, 2.0, 0.0);
		mOrigin = point3(0.0, 0.0, 0.0);
	}

	ray get_ray(double u, double v) const
	{
		return ray(mOrigin, mLowerLeftCorner + u * mHorizontal + v * mVertical - mOrigin);
	}

private:
	point3 mOrigin;
	point3 mLowerLeftCorner;
	vec3 mVertical;
	vec3 mHorizontal;
};
#endif // !CAMERA_H
