#ifndef __RayTracer__Torus__
#define __RayTracer__Torus__

#include <iostream>

#include "Primitive.h"
#include "poly34.h"
#include "QuarticSolver.h"

class Torus : public Primitive {

public:
	Torus(const Vector3& c = Vector3(0, 0, 0), real outer_r = 0.4, real inner_r = 1.0);
	virtual ~Torus();
	virtual bool intersects(const Ray &r, real &t, HitRecord &hr) const;

public:
	Vector3 c;
	real outer_r;
	real inner_r;
};

#endif
