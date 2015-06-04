#include <math.h>

#include "Plane.h"

Plane::Plane(const Vector3 &p, Vector3 n, real r) :p(p), n(n), r(r) {}
Plane::~Plane() {}

bool Plane::intersects(const Ray &ray, real &t, HitRecord &hr) const
{
	real denominator = n.dot(ray.d);
	//if (denominator < 0) return false; //Ray and plane are parallel (nao mostra plano :( )

	real intersect = n.dot((p - ray.o)) / denominator;

	if (intersect < 0) 
		return false; //No intersection

	t = intersect;

	hr.p = ray.o + ray.d * t;
	hr.n = hr.p;
	return true;
}