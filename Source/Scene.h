//
//  Scene.h
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Scene__
#define __RayTracer__Scene__

#include <iostream>
#include <vector>
#include <math.h> //pow

#include "Instance.h"
#include "Light.h"

class Scene {

public:
	Scene() : background(0, 0, 0) {};
	virtual ~Scene()  {};

	virtual void addInstance(Instance *obj);
	virtual void addLight(Light *light);

	void setBackground(const Color &background);
	Color traceRay(const Ray &r);
	Color traceRefractionRay(Ray &newRay, Ray r);
	//Ray refraction(Ray &ray, hit_rec h_r, double &R, bool _bump);

	// data members
	Color background;
	std::vector<Instance *> instances;
	std::vector<Light *> lights;
};

#endif /* defined(__RayTracer__Scene__) */
