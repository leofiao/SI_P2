//
//  Material.h
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Material__
#define __RayTracer__Material__

#include <iostream>

#include "defines.h"

#include "Color.h"

class Material {

public:
    Material() : _ka(), _kd(), _ks(1.0, 1.0, 1.0), _kt(0.0, 0.0, 0.0), _ns(0.0), _nt(1.0) {};
    Material(const Color &ka, const Color &kd, const Color &ks = Color(1.0, 1.0, 1.0), const Color &kt=Color(0.0, 0.0, 0.0), int ns=0, int nt=1):
        _ka(ka), _kd(kd), _ks(ks), _kt(kt), _ns(ns), _nt(nt) {};
    virtual ~Material() {};
    
public:
    Color _ka, _kd, _ks, _kt;
    int _ns, _nt;
};
#endif /* defined(__RayTracer__Material__) */
