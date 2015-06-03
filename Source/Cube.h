#ifndef __RayTracer__Cube__
#define __RayTracer__Cube__

#include <iostream>
#include <cfloat>
#include <math.h>
#include "Primitive.h"

class Cube : public Primitive {
public:
	Cube(const Vector3& c = Vector3(0, 0, 0), real r = 1.0);
	virtual ~Cube();
	virtual bool intersects(const Ray &r, real &t, HitRecord &hr) const;

public:
	real x_max;
	real x_min;
	real y_max;
	real y_min;
	real z_max;
	real z_min;
	Vector3 c;
	real r;
};
#endif 
