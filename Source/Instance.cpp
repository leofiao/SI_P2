//
//  Instance.cpp
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Instance.h"



bool Instance::intersects(const Ray &r, real &t)
{
    // Transform the ray to the local coordinate system
    Ray rl = r.worldToLocal(this->_t);
    
    // Compute intersection
    // TODO:
    
    // Transform the ray back to world
    // TODO:
    return false;
}