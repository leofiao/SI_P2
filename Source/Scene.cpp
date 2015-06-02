//
//  Scene.cpp
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Scene.h"

void Scene::setBackground(const Color &background)
{
    this->background = background;
}

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
    Instance *obj=NULL;
    HitRecord hitrec;
    // process each primitive instace
    for(std::vector<Instance *>::iterator it=instances.begin(); it!=instances.end(); it++)
    {
        HitRecord hr;
        real t=INFINITE; Instance *ins = *it;
        if(ins->intersects(r, t, hr)) {
            if(t < tmin) {
                tmin = t;
                obj = ins;
                hitrec = hr;
            }
        }
    }
    
    if(tmin!=INFINITE) // We have a hit
    {
        Vector3 l = lights[0]->sampleLight(hitrec.p);
        real dot = MAX(0,hitrec.n.dot(l));
        
        return obj->m.kd * dot + obj->m.ka;
    }
    return background;
}