//
//  Ray.h
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Ray__
#define __RayTracer__Ray__

#include <iostream>

#include "Vector3.h"
#include "TransformSeq.h"

class Ray {
public:
    Ray(const Vector3 &o, const Vector3 &d);
    virtual ~Ray();
  
    Ray worldToLocal(const TransformSeq &ts) const;
    Ray localToWorld(const TransformSeq &ts) const;
    
    Vector3 _o, _d;
};

#endif /* defined(__RayTracer__Ray__) */
