//
//  Camera.cpp
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//


#include "Camera.h"

Camera::Camera(): eye(), at(0,0,-1), up(0,1,0), fd(0.050), width(0.036), height(0.024), sensor(NULL)
{
    setupAxis();
}

Camera::Camera(const Vector3 &eye, const Vector3 &at, const Vector3 &up, real fd, real width, real height):
    eye(eye), at(at), up(up), fd(fd), width(width), height(height), sensor(NULL)
{
    setupAxis();
}

Camera::~Camera()
{
}

void Camera::setSensor(ImageSensor *s)
{
    // Discard previous sensor if it exists
    if(sensor) delete sensor;
    
    // replace with new one
    sensor = s;
}

void Camera::capture(Scene &s)
{
    // No sensor no capture
    if(!sensor) return;
    
    // compute the center of the virtual sensor, placed at the focal distance
    Vector3 center = eye - ez * fd;
    
    // Compute the top left corner of the sensor, in WC
    Vector3 topleft = center - ex * .5 * width + ey * .5 * height;
    
    Vector3 dx = ex * (width / sensor->w); // Horizontal distance between pixels in image sensor
    Vector3 dy = -ey * (height / sensor->h); // Vertical distance between pixels in image sensor
    
    
    Vector3 pixel = topleft + dx * 0.5 - dy * .5;   // Center of the pixel
        
    Vector3 left = pixel;
    for(unsigned int j=0; j<sensor->h; j++) {
        for(unsigned int i=0; i<sensor->w; i++) {
            Vector3 to = pixel - eye; to.normalize();
            Ray r(eye, to);
            Color c = s.traceRay(r);
            sensor->addSample(i,j,c);
            pixel += dx;
        }
        left += dy;
        pixel = left;
    }
    
    this->sensor->dumpToTGA("image.tga");
}

void Camera::setupAxis()
{
    // ez is a unit vector pointing from at to eye
    ez = eye - at;
    ez.normalize();
    
    // ex is orthogonal to the plane formed by up and (at-eye)
    ex = up.cross(ez);
    ex.normalize();
    
    // finally ey is also orthogonal to the plane formed by ey and ez
    ey = ez.cross(ex);
    ey.normalize();    // This shouldn't be necessary
}

