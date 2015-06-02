//
//  Ray.cpp
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Ray.h"
#include "TransformSeq.h"

Ray::Ray(const Vector3 &o, const Vector3 &d): o(o), d(d)
{
}

Ray::~Ray()
{
}

Ray Ray::worldToLocal(const TransformSeq &ts) const
{
    // Use inverse transformation to go from world to local
    //    Vector3 ori = ts.tinv.applyToPoint(this->o);
    //    Vector3 dir = ts.tinv.applyToVector(this->d);
    Vector3 ori = ts.applyInverseToPoint(this->o);
    Vector3 dir = ts.applyInverseToVector(this->d);

    return Ray(ori,dir);
}
