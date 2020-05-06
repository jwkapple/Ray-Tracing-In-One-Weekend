#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hitRecord
{
	double t;
	point3 p;
	vec3 normal;
	bool frontFace;

	inline void setFaceNormal(const ray& r, const vec3& outwardNormal)
	{
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class hittable
{
public:
	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const = 0;
	// tMin & tMax set for limitation of ray distance
};

#endif // !HITTABLE_H

