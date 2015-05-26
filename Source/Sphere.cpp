//
//  Sphere.cpp
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//
#include <math.h>

#include "Sphere.h"

Sphere::Sphere(const Vector3 &c, real r):_c(c), _r(r) {}
Sphere::~Sphere() {}

bool Sphere::intersects(const Ray &r, real &t)
{
    // compute a, b and c coefficients
    real a = r._d.dot();                // a=d.d
    real b = 2 * r._d.dot(r._o);        // b=2(d.o)
    real c = r._o.dot() - _r*_r;        // c=o.o-r*r
    
    // compute discriminant
    real disc = b*b-4*a*c;
    
    //if discriminant is negative there are no real roots: ray misses sphere
    if(disc<0) return false;
    
    // compute q
    real distSqrt = sqrt(disc);
    real q;
    
    if(b<0) q = (-b - distSqrt)/2;
    else    q = (-b + distSqrt)/2;
    
    // compute t0 and t1
    real t0 = q/a;
    real t1 = c/q;
    
    // swap t0 and t1 if t0 is greater than t1
    if(t0>t1) { real temp = t0; t0 = t1; t1=temp; }
    
    // if t1 is negative, both intersections are in the negative ray direction
    if(t1 < 0) return false;
    
    // returns first intersection
    if(t0<0)    t=t1;
    else        t=t0;
    
    return true;
}