//
//  P3d.cpp
//  RayTracer
//
//  Created by Fernando Birra on 05/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//
#include <cmath>
#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0){}
Vector3::Vector3(const Vector3 &other): x(other.x), y(other.y), z(other.z) {}
Vector3::Vector3(real x, real y, real z): x(x), y(y), z(z) {}
Vector3::~Vector3(){}

// Selectors
real Vector3::dot() const { return x*x + y*y + z*z; }
real Vector3::dot(const Vector3& other) const { return x*other.x + y*other.y + z*other.z; }
Vector3 Vector3::cross(const Vector3 &other) const
{
    Vector3 res;
    
    res.x = y * other.z - z * other.y;
    res.y = z * other.x - x * other.z;
    res.z = x * other.y - y * other.x;
    
    return res;
}

// Modifiers
void Vector3::scale(real s) { x*=s; y*=s; z*=s; }
void Vector3::normalize() { real len = ::sqrt(dot()); x/=len; y/=len; z/=len; }

//Operators
Vector3 operator +(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x+b.x, a.y+b.y, a.z+b.z);
}

Vector3 operator -(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x-b.x, a.y-b.y, a.z-b.z);
}

Vector3& operator +=(Vector3 &a, const Vector3 &b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Vector3 operator *(const Vector3 &a, real s)
{
    return Vector3(a.x*s, a.y*s, a.z*s);
}

Vector3 operator -(const Vector3 &a) {
    return Vector3(-a.x, -a.y, -a.z);
}