//
//  HitRecord.cpp
//  RayTracer
//
//  Created by Fernando Pedro Birra on 29/05/15.
//  Copyright (c) 2015 FCT/UNL. All rights reserved.
//

#include "HitRecord.h"

HitRecord HitRecord::localToWorld(const TransformSeq &ts) const
{
    HitRecord hr;
    
    hr.p = ts.applyToPoint(this->p);
    hr.n = ts.applyToNormal(this->n);
    hr.n.normalize();
    
    return hr;
}
