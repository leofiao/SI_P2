//
//  Light.h
//  RayTracer
//
//  Created by Fernando Pedro Birra on 25/05/15.
//  Copyright (c) 2015 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Light__
#define __RayTracer__Light__

#include <stdio.h>

#include "Color.h"
#include "Vector3.h"

class Light {
  
public:
    Light(): _col(1.0, 1.0, 1.0) {};
    Light(const Color &col) : _col(col) {};
    virtual ~Light() {};

    virtual Vector3 sampleLight(const Vector3 &from) const = 0; // Returns a direction to look for the light
    
public:
    Color _col;

};

class PointLight : public Light {
public:
    PointLight() : Light(), _pos() { };
    PointLight(const Vector3 &pos) : Light(), _pos(pos) {};
    PointLight(const Vector3 &pos, const Color &col) : Light(col), _pos(pos) {};
    virtual ~PointLight() {};
    
    virtual Vector3 sampleLight(const Vector3 &from) const { return _pos - from; }
    
public:
    Vector3 _pos;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(): Light(), _dir() {};
    DirectionalLight(const Vector3 &dir) : Light(), _dir(dir) {};
    virtual ~DirectionalLight() {};
    
    virtual Vector3 sampleLight(const Vector3 &from) const { return - _dir; }
public:
    Vector3 _dir;
};
#endif /* defined(__RayTracer__Light__) */
