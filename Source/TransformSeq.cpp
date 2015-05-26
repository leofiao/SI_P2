//
//  TransformSeq.cpp
//  RayTracer
//
//  Created by Fernando Pedro Birra on 25/05/15.
//  Copyright (c) 2015 FCT/UNL. All rights reserved.
//

#include "TransformSeq.h"


void TransformSeq::addTranslation(real tx, real ty, real tz)
{
    Transform t; t.makeTranslation(tx,ty,tz);
    Transform tinv; tinv.makeTranslation(-tx, -ty, -tz);
    
    applyFromParts(t, tinv);
}

void TransformSeq::addScale(real sx, real sy, real sz)
{
    Transform t; t.makeScale(sx,sy,sz);
    Transform tinv; tinv.makeScale(1/sx, 1/sy, 1/sz);

    applyFromParts(t, tinv);
}

void TransformSeq::addRotx(real angle)
{
    Transform t; t.makeRotx(angle);
    Transform tinv; tinv.makeRotx(-angle);

    applyFromParts(t, tinv);
}

void TransformSeq::addRoty(real angle)
{
    Transform t; t.makeRoty(angle);
    Transform tinv; tinv.makeRoty(-angle);

    applyFromParts(t, tinv);
}

void TransformSeq::addRotz(real angle)
{
    Transform t; t.makeRotz(angle);
    Transform tinv; tinv.makeRotz(-angle);
    
    applyFromParts(t, tinv);
}


void TransformSeq::applyFromParts(const Transform &t, const Transform &tinv)
{
    _t.preMultiply(t);
    _tinv.postMultiply(tinv);
}
