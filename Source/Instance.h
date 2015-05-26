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
    Instance(const Primitive *p): _p(p), _t(), _m() {}; // Default constructors
    Instance(const Primitive *p, const TransformSeq &t, const Material &m): _p(p), _t(t), _m(m) {};
    virtual ~Instance() {};
    
    bool intersects(const Ray &r, real &t);
    
    const Primitive *_p;    // The primitive
    TransformSeq _t;         // The transformation applied to the primite to create the instace
    Material _m;            // The material assigned to the primitive
};
#endif /* defined(__RayTracer__Instance__) */
