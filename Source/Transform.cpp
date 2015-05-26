//
//  Transform.cpp
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Transform.h"

#include <cmath>

Transform::Transform() {};
Transform::~Transform() {}

Transform::Transform(real s)
{
    makeScale(s);
}

void Transform::makeZero() {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            _m[i][j] = 0;
}

void Transform::makeIdentity() {
    makeScale(1);
}

void Transform::makeScale(real s) {
    makeScale(s,s,s,1);
}

void Transform::makeScale(real sx, real sy, real sz, real sw) {
    makeZero();
    setDiagonal(sx,sy,sz,sw);
}

void Transform::makeTranslation(real tx, real ty, real tz) {
    makeIdentity();
    setRightSide(tx,ty,tz);
}

void Transform::makeRotx(real angle)
{
    real cosa = cos(angle);
    real sina = sin(angle);
    makeIdentity();
    _m[1][1] = cosa; _m[1][2] = -sina;
    _m[2][1] = sina; _m[2][2] = cosa;
}

void Transform::makeRoty(real angle)
{
    real cosa = cos(angle);
    real sina = sin(angle);
    makeIdentity();
    _m[0][0] = cosa; _m[0][2] = sina;
    _m[2][0] = -sina; _m[2][2] = cosa;
}


void Transform::makeRotz(real angle)
{
    real cosa = cos(angle);
    real sina = sin(angle);
    makeIdentity();
    _m[0][0] = cosa; _m[0][1] = -sina;
    _m[1][0] = sina; _m[1][1] = cosa;
}

void Transform::setRightSide(real tx, real ty, real tz)
{
    _m[0][3] = tx; _m[1][3] = ty; _m[2][3] = tz;
}

void Transform::setDiagonal(real sx, real sy, real sz, real sw)
{
    _m[0][0] = sx;
    _m[1][1] = sy;
    _m[2][2] = sz;
    _m[3][3] = sw;
}


// row vector multiplication by matrix (same as column multiplication by matrix transpose)
Vector3 operator *(const Vector3 &v, const Transform &t)
{
    real w = t._m[0][3] * v.x + t._m[1][3] * v.y + t._m[2][3] * v.z + t._m[3][3];
    Vector3 res(t._m[0][0] * v.x + t._m[1][0] * v.y + t._m[2][0] * v.z + t._m[3][0],
                t._m[0][1] * v.x + t._m[1][1] * v.y + t._m[2][1] * v.z + t._m[3][1],
                t._m[0][2] * v.x + t._m[1][2] * v.y + t._m[2][2] * v.z + t._m[3][2]);
    
    res *= (1/w);
    return res;
}

// Matrix by column vector multiplication
Vector3 operator *(const Transform &t, const Vector3 &v)
{
    real w = t._m[3][0] * v.x + t._m[3][1] * v.y + t._m[3][2] * v.z + t._m[3][3];
    Vector3 res(t._m[0][0] * v.x + t._m[0][1] * v.y + t._m[0][2] * v.z + t._m[0][3],
                t._m[1][0] * v.x + t._m[1][1] * v.y + t._m[1][2] * v.z + t._m[1][3],
                t._m[2][0] * v.x + t._m[2][1] * v.y + t._m[2][2] * v.z + t._m[2][3]);
    
    res *= (1/w);
    return res;
}

void Transform::postMultiply(const Transform &t)
{
    real m00 = _m[0][0], m01 = _m[0][1], m02 = _m[0][2], m03 = _m[0][3];
    real m10 = _m[1][0], m11 = _m[1][1], m12 = _m[1][2], m13 = _m[1][3];
    real m20 = _m[2][0], m21 = _m[2][1], m22 = _m[2][2], m23 = _m[2][3];
    real m30 = _m[3][0], m31 = _m[3][1], m32 = _m[3][2], m33 = _m[3][3];

    real t00 = t._m[0][0], t01 = t._m[0][1], t02 = t._m[0][2], t03 = t._m[0][3];
    real t10 = t._m[1][0], t11 = t._m[1][1], t12 = t._m[1][2], t13 = t._m[1][3];
    real t20 = t._m[2][0], t21 = t._m[2][1], t22 = t._m[2][2], t23 = t._m[2][3];
    real t30 = t._m[3][0], t31 = t._m[3][1], t32 = t._m[3][2], t33 = t._m[3][3];
    
    _m[0][0] = m00 * t00 + m01 * t10 + m02 * t20 + m03 * t30;
    _m[0][1] = m00 * t01 + m01 * t11 + m02 * t21 + m03 * t31;
    _m[0][2] = m00 * t02 + m01 * t12 + m02 * t22 + m03 * t32;
    _m[0][3] = m00 * t03 + m01 * t13 + m02 * t23 + m03 * t33;
    
    _m[1][0] = m10 * t00 + m11 * t10 + m12 * t20 + m13 * t30;
    _m[1][1] = m10 * t01 + m11 * t11 + m12 * t21 + m13 * t31;
    _m[1][2] = m10 * t02 + m11 * t12 + m12 * t22 + m13 * t32;
    _m[1][3] = m10 * t03 + m11 * t13 + m12 * t23 + m13 * t33;
    
    _m[2][0] = m20 * t00 + m21 * t10 + m22 * t20 + m23 * t30;
    _m[2][1] = m20 * t01 + m21 * t11 + m22 * t21 + m23 * t31;
    _m[2][2] = m20 * t02 + m21 * t12 + m22 * t22 + m23 * t32;
    _m[2][3] = m20 * t03 + m21 * t13 + m22 * t23 + m23 * t33;
    
    _m[3][0] = m30 * t00 + m31 * t10 + m32 * t20 + m33 * t30;
    _m[3][1] = m30 * t01 + m31 * t11 + m32 * t21 + m33 * t31;
    _m[3][2] = m30 * t02 + m31 * t12 + m32 * t22 + m33 * t32;
    _m[3][3] = m30 * t03 + m31 * t13 + m32 * t23 + m33 * t33;
    
}

void Transform::preMultiply(const Transform &t)
{
    real m00 = _m[0][0], m01 = _m[0][1], m02 = _m[0][2], m03 = _m[0][3];
    real m10 = _m[1][0], m11 = _m[1][1], m12 = _m[1][2], m13 = _m[1][3];
    real m20 = _m[2][0], m21 = _m[2][1], m22 = _m[2][2], m23 = _m[2][3];
    real m30 = _m[3][0], m31 = _m[3][1], m32 = _m[3][2], m33 = _m[3][3];
    
    real t00 = t._m[0][0], t01 = t._m[0][1], t02 = t._m[0][2], t03 = t._m[0][3];
    real t10 = t._m[1][0], t11 = t._m[1][1], t12 = t._m[1][2], t13 = t._m[1][3];
    real t20 = t._m[2][0], t21 = t._m[2][1], t22 = t._m[2][2], t23 = t._m[2][3];
    real t30 = t._m[3][0], t31 = t._m[3][1], t32 = t._m[3][2], t33 = t._m[3][3];
    
    _m[0][0] = t00 * m00 + t01 * m10 + t02 * m20 + t03 * m30;
    _m[0][1] = t00 * m01 + t01 * m11 + t02 * m21 + t03 * m31;
    _m[0][2] = t00 * m02 + t01 * m12 + t02 * m22 + t03 * m32;
    _m[0][3] = t00 * m03 + t01 * m13 + t02 * m23 + t03 * m33;
    
    _m[1][0] = t10 * m00 + t11 * m10 + t12 * m20 + t13 * m30;
    _m[1][1] = t10 * m01 + t11 * m11 + t12 * m21 + t13 * m31;
    _m[1][2] = t10 * m02 + t11 * m12 + t12 * m22 + t13 * m32;
    _m[1][3] = t10 * m03 + t11 * m13 + t12 * m23 + t13 * m33;
    
    _m[2][0] = t20 * m00 + t21 * m10 + t22 * m20 + t23 * m30;
    _m[2][1] = t20 * m01 + t21 * m11 + t22 * m21 + t23 * m31;
    _m[2][2] = t20 * m02 + t21 * m12 + t22 * m22 + t23 * m32;
    _m[2][3] = t20 * m03 + t21 * m13 + t22 * m23 + t23 * m33;
    
    _m[3][0] = t30 * m00 + t31 * m10 + t32 * m20 + t33 * m30;
    _m[3][1] = t30 * m01 + t31 * m11 + t32 * m21 + t33 * m31;
    _m[3][2] = t30 * m02 + t31 * m12 + t32 * m22 + t33 * m32;
    _m[3][3] = t30 * m03 + t31 * m13 + t32 * m23 + t33 * m33;
    
}