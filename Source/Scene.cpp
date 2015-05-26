//
//  Scene.cpp
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Scene.h"


void Scene::addInstance(Instance *obj)
{
    instances.push_back(obj);
}

void Scene::addLight(Light *light)
{
    lights.push_back(light);
}

Color Scene::traceRay(const Ray &r)
{
    double tmin = INFINITE;
    Instance *obj = NULL;
    
    // process each primitive instace
    for(std::vector<Instance *>::iterator it=instances.begin(); it!=instances.end(); it++)
    {
        real t; Instance *ins = *it;
        if(ins->intersects(r, t)) {
            if(t < tmin) {
                tmin = t;
                obj = ins;
            }
        }
    }
    
    if(tmin!=INFINITE) // We have a hit
    {
        return Color(obj->_m._kd);
    }
    return Color::black;
}