//
//  Ray.cpp
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Ray.h"
#include "TransformSeq.h"

Ray::Ray(const Vector3 &o, const Vector3 &d): _o(o), _d(d)
{
}

Ray::~Ray()
{
}

Ray Ray::worldToLocal(const TransformSeq &ts) const
{
    // Use inverse transformation to go from world to local
    Vector3 o = ts._tinv * this->_o;
    Vector3 d = this->_d * ts._t;
    d.normalize();
    
    return Ray(o,d);
}

Ray Ray::localToWorld(const TransformSeq &ts) const
{
    // Use direct transformation to go from local to world
    Vector3 o = ts._t * this->_o;
    Vector3 d = this->_d * ts._tinv;
    d.normalize();
    
    return Ray(o,d);
}