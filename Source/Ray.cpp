//
//  Ray.cpp
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Ray.h"

Ray::Ray(const Vector3 &o, const Vector3 &d): _o(o), _d(d) {};
Ray::~Ray() {};