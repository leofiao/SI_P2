//
//  P3d.h
//  RayTracer
//
//  Created by Fernando Birra on 05/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__P3d__
#define __RayTracer__P3d__

#include <iostream>

#include "defines.h"

class Vector3 {
public:
    
    Vector3();
    Vector3(const Vector3& other);
    Vector3(real x, real y, real z);
    virtual ~Vector3();
    
    // selectors
    real dot() const;
    real dot(const Vector3& other) const;
    Vector3 cross(const Vector3 &other) const;
    
    // modifiers
    void scale(real s);
    void normalize();
    
    union {
        struct { real  x, y, z; };
        real  v[3];
    };
};

Vector3 operator -(const Vector3 &a);

Vector3 operator +(const Vector3 &a, const Vector3& b);
Vector3 operator -(const Vector3 &a, const Vector3& b);
Vector3 operator *(const Vector3 &a, real s);

Vector3& operator +=(Vector3 &a, const Vector3 &b);
Vector3& operator -=(Vector3 &a, const Vector3 &b);
Vector3& operator *=(Vector3 &a, real s);


#endif /* defined(__RayTracer__P3d__) */

