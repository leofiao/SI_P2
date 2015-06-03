#include "Cube.h"

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

Cube::Cube(const Vector3 &C, real R) :c(C), r(R) {
	x_max = C.x + R;
	x_min = C.x - R;
	y_max = C.y + R;
	y_min = C.y - R;
	z_max = C.z + R;
	z_min = C.z - R;
	r = R;
}
Cube::~Cube() {}


bool Cube::intersects(const Ray &ray, real &t, HitRecord &hr) const
{
	/*
	real tFar = FLT_MAX;
	real tNear = FLT_MIN;

	if (ray.d.x != 0.0) {
		double tx1 = (x_min - ray.o.x) / ray.d.x;
		double tx2 = (x_max - ray.o.x) / ray.d.x;

		tNear = max(tNear, min(tx1, tx2));
		tFar = min(tFar, max(tx1, tx2));
	}

	if (ray.d.y != 0.0) {
		double ty1 = (y_min - ray.o.y) / ray.d.y;
		double ty2 = (y_max - ray.o.y) / ray.d.y;

		tNear = max(tNear, min(ty1, ty2));
		tFar = min(tFar, max(ty1, ty2));
	}

	if (tFar <= tNear) return false;

	t = tNear;

	hr.p = ray.o + ray.d * t;
	hr.n = hr.p;
	*/

	return true;
}
