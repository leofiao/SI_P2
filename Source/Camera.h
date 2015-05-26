//
//  Camera.h
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Camera__
#define __RayTracer__Camera__

#include <iostream>

#include "Vector3.h"
#include "Ray.h"
#include "Scene.h"
#include "ImageSensor.h"

class Camera {

public:
    Camera();
    Camera(const Vector3 &eye=Vector3(0,0,1), const Vector3 &at=Vector3(0,0,0), const Vector3 &up=Vector3(0,1,0), real fd=0.050, real w=0.036, real h=0.024);
    virtual ~Camera();
    
    void setSensor(ImageSensor *s);
    void capture(Scene &s);
    
private:
    void setupAxis();   // sets up the camera coordinate axis

public:
    Vector3 _eye;       // camera origin
    Vector3 _at;        // target
    Vector3 _up;        // up vector
    real _fd;       // focal distance
    real _width;    // real image width
    real _height;   // real image height
    
    ImageSensor *sensor;

    Vector3 _ez;    // Forward direction
    Vector3 _ey;    // Up direction
    Vector3 _ex;    // Left direction
};

#endif /* defined(__RayTracer__Camera__) */
