#ifndef __RayTracer__Plane__
#define __RayTracer__Plane__

#include <iostream>

#include "Primitive.h"

class Plane : public Primitive {

public:
	Plane(const Vector3& p = Vector3(0, 0, 0), Vector3 n = Vector3(0, 1, 0), real r = 0.5);
	virtual ~Plane();
	virtual bool intersects(const Ray &r, real &t, HitRecord &hr) const;

public:
	Vector3 p; //Point in the center of the square
	Vector3 n;
	/*
	Não é usado mas pode ficar, se eventualmente quisermos implementar um quadrado/paralelograma
	é preferivel utilizar um ponto de origem com mais dois Vectors3 que representam a direção a partir desse ponto
	*/
	real r;
};

#endif
