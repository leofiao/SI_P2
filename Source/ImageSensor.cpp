//
//  ImageSensor.cpp
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "ImageSensor.h"

ImageSensor::ImageSensor(): _w(DEFAULT_RES_X), _h(DEFAULT_RES_Y)
{
    allocateStorage();
}

ImageSensor::ImageSensor(int width, int height) : _w(width), _h(height)
{
    allocateStorage();
}

ImageSensor::~ImageSensor()
{
    deallocateStorage();
}

void ImageSensor::allocateStorage()
{
    data = new Color[_w *_h];
}

void ImageSensor::deallocateStorage()
{
    delete data;
}

size_t ImageSensor::indexFor(size_t i, size_t j) const
{
    return j * _w + i;
}

void ImageSensor::addSample(size_t i, size_t j, Color s)
{
    size_t idx = indexFor(i,j);
    data[idx] += s;
}

void ImageSensor::dumpRawData(const char *filename)
{
        // TODO:
}

SimpleImageSensor::SimpleImageSensor() : ImageSensor()
{
};

SimpleImageSensor::SimpleImageSensor(int width, int height) : ImageSensor(width, height)
{
};

SimpleImageSensor::~SimpleImageSensor()
{    
}

void SimpleImageSensor::process()
{
    // Do noting
}
