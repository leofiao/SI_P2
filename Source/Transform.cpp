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
            m[i][j] = 0;
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
    m[1][1] = cosa; m[1][2] = -sina;
    m[2][1] = sina; m[2][2] =  cosa;
}

void Transform::makeRoty(real angle)
{
    real cosa = cos(angle);
    real sina = sin(angle);
    makeIdentity();
    m[0][0] =  cosa; m[0][2] = sina;
    m[2][0] = -sina; m[2][2] = cosa;
}


void Transform::makeRotz(real angle)
{
    real cosa = cos(angle);
    real sina = sin(angle);
    makeIdentity();
    m[0][0] = cosa; m[0][1] = -sina;
    m[1][0] = sina; m[1][1] =  cosa;
}

void Transform::setRightSide(real tx, real ty, real tz)
{
    m[0][3] = tx; m[1][3] = ty; m[2][3] = tz;
}

void Transform::setDiagonal(real sx, real sy, real sz, real sw)
{
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    m[3][3] = sw;
}


// row vector multiplication by matrix (same as column multiplication by matrix transpose)
Vector3 operator *(const Vector3 &v, const Transform &t)
{
    real w = t.m[0][3] * v.x + t.m[1][3] * v.y + t.m[2][3] * v.z + t.m[3][3];
    Vector3 res(t.m[0][0] * v.x + t.m[1][0] * v.y + t.m[2][0] * v.z + t.m[3][0],
                t.m[0][1] * v.x + t.m[1][1] * v.y + t.m[2][1] * v.z + t.m[3][1],
                t.m[0][2] * v.x + t.m[1][2] * v.y + t.m[2][2] * v.z + t.m[3][2]);
    
    res *= (1/w);
    return res;
}

// Matrix by column vector multiplication
Vector3 operator *(const Transform &t, const Vector3 &v)
{
    return t.applyToColumnPoint(v);
}

Vector3 Transform::applyToColumnPoint(const Vector3 &v) const
{
    real w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
    Vector3 res(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]);
    
    res *= (1/w);
    return res;
}

Vector3 Transform::applyToRowPoint(const Vector3 &v) const
{
    real w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3];
    Vector3 res(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z+m[3][0],
                m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z+m[3][1],
                m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z+m[3][2]);
    
    res *= (1/w);
    return res;
}

Vector3 Transform::applyToColumnVector(const Vector3 &v) const
{
    // Since vectors are represented in homogeneous coordinates with w=0
    // (they are the difference between two points),
    // we ommit the last column (translation part) of the transformation.
    // In fact, translation of a vector doesn't change it!
    Vector3 res(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
    return res;
}

Vector3 Transform::applyToRowVector(const Vector3 &v) const
{
    Vector3 res(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
                m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
                m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
    return res;
}

Vector3 Transform::applyToColumnNormal(const Vector3 &v) const
{
    // TODO: This should compute (t^-1)^T multiplied by v. We will not need it here and thus avoid matrix inversion.
    throw std::string("Unimplemented operation: applyToColumnNormal!");
    return Vector3();
}

Vector3 Transform::applyToRowNormal(const Vector3 &v) const
{
    // TODO: No need to do this, since it would require matrix inversion.
    throw std::string("Unimplemented operation: applyToRowNormal!");
    return Vector3();
}

void Transform::postMultiply(const Transform &t)
{
    real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
    real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
    real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
    real m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

    real t00 = t.m[0][0], t01 = t.m[0][1], t02 = t.m[0][2], t03 = t.m[0][3];
    real t10 = t.m[1][0], t11 = t.m[1][1], t12 = t.m[1][2], t13 = t.m[1][3];
    real t20 = t.m[2][0], t21 = t.m[2][1], t22 = t.m[2][2], t23 = t.m[2][3];
    real t30 = t.m[3][0], t31 = t.m[3][1], t32 = t.m[3][2], t33 = t.m[3][3];
    
    m[0][0] = m00 * t00 + m01 * t10 + m02 * t20 + m03 * t30;
    m[0][1] = m00 * t01 + m01 * t11 + m02 * t21 + m03 * t31;
    m[0][2] = m00 * t02 + m01 * t12 + m02 * t22 + m03 * t32;
    m[0][3] = m00 * t03 + m01 * t13 + m02 * t23 + m03 * t33;
    
    m[1][0] = m10 * t00 + m11 * t10 + m12 * t20 + m13 * t30;
    m[1][1] = m10 * t01 + m11 * t11 + m12 * t21 + m13 * t31;
    m[1][2] = m10 * t02 + m11 * t12 + m12 * t22 + m13 * t32;
    m[1][3] = m10 * t03 + m11 * t13 + m12 * t23 + m13 * t33;
    
    m[2][0] = m20 * t00 + m21 * t10 + m22 * t20 + m23 * t30;
    m[2][1] = m20 * t01 + m21 * t11 + m22 * t21 + m23 * t31;
    m[2][2] = m20 * t02 + m21 * t12 + m22 * t22 + m23 * t32;
    m[2][3] = m20 * t03 + m21 * t13 + m22 * t23 + m23 * t33;
    
    m[3][0] = m30 * t00 + m31 * t10 + m32 * t20 + m33 * t30;
    m[3][1] = m30 * t01 + m31 * t11 + m32 * t21 + m33 * t31;
    m[3][2] = m30 * t02 + m31 * t12 + m32 * t22 + m33 * t32;
    m[3][3] = m30 * t03 + m31 * t13 + m32 * t23 + m33 * t33;
}

void Transform::preMultiply(const Transform &t)
{
    real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
    real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
    real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
    real m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];
    
    real t00 = t.m[0][0], t01 = t.m[0][1], t02 = t.m[0][2], t03 = t.m[0][3];
    real t10 = t.m[1][0], t11 = t.m[1][1], t12 = t.m[1][2], t13 = t.m[1][3];
    real t20 = t.m[2][0], t21 = t.m[2][1], t22 = t.m[2][2], t23 = t.m[2][3];
    real t30 = t.m[3][0], t31 = t.m[3][1], t32 = t.m[3][2], t33 = t.m[3][3];
    
    m[0][0] = t00 * m00 + t01 * m10 + t02 * m20 + t03 * m30;
    m[0][1] = t00 * m01 + t01 * m11 + t02 * m21 + t03 * m31;
    m[0][2] = t00 * m02 + t01 * m12 + t02 * m22 + t03 * m32;
    m[0][3] = t00 * m03 + t01 * m13 + t02 * m23 + t03 * m33;
    
    m[1][0] = t10 * m00 + t11 * m10 + t12 * m20 + t13 * m30;
    m[1][1] = t10 * m01 + t11 * m11 + t12 * m21 + t13 * m31;
    m[1][2] = t10 * m02 + t11 * m12 + t12 * m22 + t13 * m32;
    m[1][3] = t10 * m03 + t11 * m13 + t12 * m23 + t13 * m33;
    
    m[2][0] = t20 * m00 + t21 * m10 + t22 * m20 + t23 * m30;
    m[2][1] = t20 * m01 + t21 * m11 + t22 * m21 + t23 * m31;
    m[2][2] = t20 * m02 + t21 * m12 + t22 * m22 + t23 * m32;
    m[2][3] = t20 * m03 + t21 * m13 + t22 * m23 + t23 * m33;
    
    m[3][0] = t30 * m00 + t31 * m10 + t32 * m20 + t33 * m30;
    m[3][1] = t30 * m01 + t31 * m11 + t32 * m21 + t33 * m31;
    m[3][2] = t30 * m02 + t31 * m12 + t32 * m22 + t33 * m32;
    m[3][3] = t30 * m03 + t31 * m13 + t32 * m23 + t33 * m33;
}