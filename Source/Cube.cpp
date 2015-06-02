#include "Cube.h"
#include <math.h>


Cube::Cube(const Vector3 &C, real R){
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

	return true;
}