//
//  Primitive.h
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Primitive__
#define __RayTracer__Primitive__

#include <iostream>

#include "Ray.h"
#include "Color.h"

class Primitive {

public:
    Primitive();
    virtual ~Primitive();
    
    virtual bool intersects(const Ray &r, real &t) = 0;
};

#endif /* defined(__RayTracer__Primitive__) */
