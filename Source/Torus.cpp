
#include <math.h>

#include "Torus.h"

Torus::Torus(const Vector3 &c, real outer_r, real inner_r) :c(c), outer_r(outer_r), inner_r(inner_r) {}
Torus::~Torus() {}

/*
http://www.emeyex.com/site/projects/raytorus.pdf
*/
bool Torus::intersects(const Ray &ray, real &t, HitRecord &hr) const
{
	// compute a, b and c coefficients
	real a = ray.d.dot();                // a=d.d
	real b = 2 * ray.d.dot(ray.o);        // b=2(d.o)
	real c = ray.o.dot() - inner_r*inner_r - outer_r*outer_r;     // c=o.o - inner_r*inner_r - outer_r*outer_r

	//quadratic equation components
	real a4 = a*a;
	real a3 = 2 * a * b;
	real a2 = (b*b) + (2 * a * c) + (4 * inner_r*inner_r * ray.d.z*ray.d.z);
	real a1 = (2 * b * c) + (8 * inner_r*inner_r * ray.o.z * ray.d.z);
	real a0 = (c*c) + (4 * inner_r*inner_r * ray.o.z*ray.o.z) - (4 * inner_r*inner_r * outer_r*outer_r);

	//TODO poly34
	//double solution[4];
	//SolveP4(solution, a3, a2, a1, a0);

	//QuarticSolver
	QuarticEquation equation(a4, a3, a2, a1, a0);
	//numero maximo de raizes/solucoes = 4
	const int maxRoots = 4;
	double solutions[maxRoots] = { -1.0, -1.0, -1.0, -1.0 };
	int rootsCount = equation.Solve(solutions);

	if (rootsCount == 0) {
		return false;
	}

	//get first intersection
	real temp_t = FLT_MAX;
	for (int i = 0; i < maxRoots; i++) {
		if (solutions[i] > 0 && solutions[i] < temp_t) {
			temp_t = solutions[i];
		}
	}

	if (temp_t == FLT_MAX)
		return false;

	t = temp_t;
	hr.p = ray.o + ray.d * t;
	hr.n = hr.p;

	return true;
}