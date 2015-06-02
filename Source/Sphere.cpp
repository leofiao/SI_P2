//
//  Sphere.cpp
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//
#include <math.h>

#include "Sphere.h"

Sphere::Sphere(const Vector3 &c, real r):c(c), r(r) {}
Sphere::~Sphere() {}

bool Sphere::intersects(const Ray &ray, real &t, HitRecord &hr) const
{
    // compute a, b and c coefficients
    real a = ray.d.dot();                // a=d.d
    real b = 2 * ray.d.dot(ray.o);        // b=2(d.o)
    real c = ray.o.dot() - r*r;        // c=o.o-r*r
    
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
    
    hr.p = ray.o + ray.d * t;
    hr.n = hr.p;
    
    return true;
}