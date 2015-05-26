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
    
    virtual void addSample(size_t i, size_t j, Color c);
    virtual void dumpRawData(const char *filename);
    
    virtual void process() = 0;
    
private:
    void allocateStorage();
    void deallocateStorage();
    size_t indexFor(size_t i, size_t j) const;
    
public:

    int _w, _h; // Image resolution
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