//
//  ImageSensor.h
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__ImageSensor__
#define __RayTracer__ImageSensor__

#include <iostream>

#include "Color.h"

class ImageSensor {
public:
    static const int DEFAULT_RES_X = 320;
    static const int DEFAULT_RES_Y = 240;

    ImageSensor();
    ImageSensor(int width, int height);
    virtual ~ImageSensor();
    
    virtual void addSample(unsigned int i, unsigned int j, Color c);
    virtual void dumpToTGA(const char *filename) const;
    
    virtual void process() = 0;
    
private:
    void allocateStorage();
    void deallocateStorage();
    unsigned int indexFor(unsigned int i, unsigned int j) const;
    
public:

    int w, h; // Image resolution
    Color *data;
};
#endif /* defined(__RayTracer__ImageSensor__) */

class SimpleImageSensor : public ImageSensor {
public:
    SimpleImageSensor();
    SimpleImageSensor(int width, int height);
    virtual ~SimpleImageSensor();
    
    virtual void process();
};