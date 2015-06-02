//
//  Instance.cpp
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Instance.h"

// TODO: This method should probably return in (in-out) parameter,
// a record with some relevant information regarding the hit (Position, Normal, ...)

bool Instance::intersects(const Ray &r, real &t, HitRecord &hr)
{
    HitRecord hrlocal;
    
    // Transform the ray to the local coordinate system
    Ray rl = r.worldToLocal(this->t);
    
    // Compute intersection in primitive local space
    bool hit = this->p->intersects(rl, t, hrlocal);
    
    // Transform hit record (position and normal) back to world
    if(hit)
        hr = hrlocal.localToWorld(this->t);
    return hit;
}