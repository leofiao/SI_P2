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

#include "Instance.h"
#include "Light.h"

class Scene {
    
public:
    Scene() {};
    virtual ~Scene() {};
    
    virtual void addInstance(Instance *obj);
    virtual void addLight(Light *light);
    
    Color traceRay(const Ray &r);
    
    // data members
    std::vector<Instance *> instances;
    std::vector<Light *> lights;
};

#endif /* defined(__RayTracer__Scene__) */
