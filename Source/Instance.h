//
//  Instance.h
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Instance__
#define __RayTracer__Instance__

#include <iostream>

#include "Primitive.h"
#include "TransformSeq.h"
#include "Material.h"



class Instance {
public:
    Instance(const Primitive *p): p(p), t(), m() {}; // Default constructors
    Instance(const Primitive *p, const TransformSeq &t, const Material &m): p(p), t(t), m(m) {};
    virtual ~Instance() {};
    
    bool intersects(const Ray &r, real &t, HitRecord &hr);
    
    const Primitive *p;    // The primitive
    TransformSeq t;         // The transformation applied to the primite to create the instace
    Material m;            // The material assigned to the primitive
};
#endif /* defined(__RayTracer__Instance__) */
