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
#include <math.h> 

#include "Vector3.h"
#include "Ray.h"
#include "Scene.h"
#include "ImageSensor.h"

class Camera {

public:
	Camera();
	Camera(const Vector3 &eye = Vector3(0, 0, 1), const Vector3 &at = Vector3(0, 0, 0), const Vector3 &up = Vector3(0, 1, 0), real fd = 0.050, real w = 0.036, real h = 0.024);
	virtual ~Camera();

	void setSensor(ImageSensor *s);
	void capture(Scene &s);

private:
	void setupAxis();   // sets up the camera coordinate axis
	Color calcAverageColor(Scene &s, Vector3 pixel, Vector3 dx, Vector3 dy); //returns average color of 4 points in pixel

public:
	Vector3 eye;       // camera origin
	Vector3 at;        // target
	Vector3 up;        // up vector
	real fd;       // focal distance
	real width;    // real image width
	real height;   // real image height

	ImageSensor *sensor;

	Vector3 ez;    // Forward direction
	Vector3 ey;    // Up direction
	Vector3 ex;    // Left direction
};

#endif /* defined(__RayTracer__Camera__) */
