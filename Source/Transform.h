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

class Transform {
public:
    
    Transform();
    explicit Transform(real s);
    virtual ~Transform();
    
    // modifiers
    
    // make Zero matrix
    void makeZero();
    // make Identity matrix
    void makeIdentity();
    // Uniform scale along x, y and z
    void makeScale(real s);
    // Non-uniform scale
    void makeScale(real sx, real sy, real sz=1, real sw = 1);
    void makeTranslation(real tx, real ty, real tz=0);
    void makeRotx(real angle);
    void makeRoty(real angle);
    void makeRotz(real angle);
    
    // partial modifiers
    void setDiagonal(real v);
    void setDiagonal(real sx, real sy, real sz=1, real sw=1);
    void setRightSide(real tx, real ty, real tz);

    void postMultiply(const Transform &t);
    void preMultiply(const Transform &t);
    
    real _m[4][4];
};

#endif /* defined(__RayTracer__Transform__) */
