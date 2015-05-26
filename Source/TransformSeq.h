//
//  TransformSeq.h
//  RayTracer
//
//  Created by Fernando Pedro Birra on 25/05/15.
//  Copyright (c) 2015 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__TransformSeq__
#define __RayTracer__TransformSeq__

#include <stdio.h>

#include "Transform.h"

class TransformSeq {
public:
    TransformSeq() : _t(1.), _tinv(1.) {};
    virtual ~TransformSeq() {};
    
    void addTranslation(real tx, real ty, real tz);
    void addScale(real sx, real sy, real sz);
    void addRotx(real angle);
    void addRoty(real angle);
    void addRotz(real angle);
public:
    Transform _t;
    Transform _tinv;
    
private:
    void applyFromParts(const Transform &t, const Transform &tinv);
};

#endif /* defined(__RayTracer__TransformSeq__) */
