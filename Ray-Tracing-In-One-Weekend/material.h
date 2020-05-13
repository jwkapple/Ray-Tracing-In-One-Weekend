#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "ray.h"
#include "hittable.h"

class material
{
public:
	virtual bool scatter
	(
		const ray& r_in, const hitRecord& rec, color& attenuation, ray& scatterd
	) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const color& a) : mAlbedo(a) { }

	virtual bool scatter
	(
		const ray& r_in, const hitRecord& rec, color& attenuation, ray& scatterd
	) const override {
		vec3 scatterDirection = rec.normal + random_unit_vector();
		scatterd = ray(rec.p, scatterDirection);
		attenuation = mAlbedo;
		return true;
	}
	
private:
	color mAlbedo;
};

class metal : public material
{
public:
	metal() = default;
	metal(const color& a) : mAlbedo(a) {}

	virtual bool scatter
	(
		const ray& ray_in, const hitRecord& rec, color& attenuation, ray& scattered
	) const override
	{
		vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
		attenuation = mAlbedo;
		scattered = ray(rec.p, reflected);
		return (dot(scattered.direction(), rec.normal) > 0);
	}

public:
	color mAlbedo;
};
#endif // !MATERIAL_H

