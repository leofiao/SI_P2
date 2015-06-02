//
//  HitRecord.h
//  RayTracer
//
//  Created by Fernando Pedro Birra on 29/05/15.
//  Copyright (c) 2015 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__HitRecord__
#define __RayTracer__HitRecord__

#include "Vector3.h"
#include "TransformSeq.h"

class HitRecord {
public:
    Vector3 p;
    Vector3 n;
    
    HitRecord() : p(), n() {};
    HitRecord(const Vector3 &p, const Vector3 &n) : p(p), n(n) {};
    virtual ~HitRecord() {};
    
    HitRecord localToWorld(const TransformSeq &ts) const;
};

#endif /* defined(__RayTracer__HitRecord__) */
