//
//  Transform3D.h
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Transform__
#define __RayTracer__Transform__

#include <iostream>

#include "defines.h"
#include "Vector3.h"


class Transform {
public:
    
    Transform();
    explicit Transform(real s);
    virtual ~Transform();
    
    // modifiers
    void makeScale(real sx, real sy, real sz=1, real sw = 1);
    void makeTranslation(real tx, real ty, real tz=0);
    void makeRotx(real angle);
    void makeRoty(real angle);
    void makeRotz(real angle);
    
    // Points, Vectors and Normals transformation
    Vector3 applyToColumnPoint(const Vector3 &v) const;
    Vector3 applyToColumnVector(const Vector3 &v) const;
    Vector3 applyToColumnNormal(const Vector3 &n) const;

    // Points, Vectors and Normals transformation
    Vector3 applyToRowPoint(const Vector3 &v) const;
    Vector3 applyToRowVector(const Vector3 &v) const;
    Vector3 applyToRowNormal(const Vector3 &n) const;
    

    // make Zero matrix
    void makeZero();
    // make Identity matrix
    void makeIdentity();
    // Uniform scale along x, y and z
    void makeScale(real s);
    // Non-uniform scale
    
    void postMultiply(const Transform &t);
    void preMultiply(const Transform &t);

    // partial modifiers
    void setDiagonal(real v);
    void setDiagonal(real sx, real sy, real sz=1, real sw=1);
    void setRightSide(real tx, real ty, real tz);
    
    real m[4][4];
};

// row vector multiplication by matrix (same as column multiplication by matrix transpose)
// Vector3 v is assumed to represent a point (implicit w=1)
Vector3 operator *(const Vector3 &v, const Transform &t);

// Matrix bby column vector multiplication
// Vector3 v is assumed to represent a point (implicit w=1)
Vector3 operator *(const Transform &t, const Vector3 &v);

#endif /* defined(__RayTracer__Transform__) */
