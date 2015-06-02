//
//  ImageSensor.cpp
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include "ImageSensor.h"

ImageSensor::ImageSensor(): w(DEFAULT_RES_X), h(DEFAULT_RES_Y)
{
    allocateStorage();
}

ImageSensor::ImageSensor(int w, int h) : w(w), h(h)
{
    allocateStorage();
}

ImageSensor::~ImageSensor()
{
    deallocateStorage();
}

void ImageSensor::allocateStorage()
{
    data = new Color[w * h];
}

void ImageSensor::deallocateStorage()
{
    delete data;
}

unsigned int ImageSensor::indexFor(unsigned int i, unsigned int j) const
{
    return j * w + i;
}

void ImageSensor::addSample(unsigned int i, unsigned int j, Color s)
{
    size_t idx = indexFor(i,j);
    data[idx] += s;
}

typedef struct {
    unsigned char IDLength;
    unsigned char ColorMapType;
    unsigned char ImgType;
    unsigned char CMapStartLo;
    unsigned char CMapStartHi;
    unsigned char CMapLengthLo;
    unsigned char CMapLengthHi;
    unsigned char CMapDepth;
    unsigned char XOffsetLo;
    unsigned char XOffsetHi;
    unsigned char YOffsetLo;
    unsigned char YOffsetHi;
    unsigned char WidthLo;
    unsigned char WidthHi;
    unsigned char HeightLo;
    unsigned char HeightHi;
    unsigned char PixelDepth;
    unsigned char ImageDescriptor;
} tgaHeader;

void ImageSensor::dumpToTGA(const char *filename) const
{
    tgaHeader hdr;
    
    hdr.IDLength = 0;
    hdr.ColorMapType = 0;
    hdr.ImgType = 2;        // Uncompressed RGB
    hdr.CMapStartLo = 0;
    hdr.CMapStartHi = 0;
    hdr.CMapLengthLo = 0;
    hdr.CMapLengthHi = 0;
    hdr.CMapDepth = 0;
    hdr.XOffsetLo = 0;
    hdr.XOffsetHi = 0;
    hdr.YOffsetLo = 0;
    hdr.YOffsetHi = 0;
    hdr.WidthLo = (w & 0xFF);
    hdr.WidthHi = (w & 0xFF00) >> 8;
    hdr.HeightLo = (h & 0xFF);
    hdr.HeightHi = (h & 0xFF00) >> 8;
    hdr.PixelDepth = 24;
    hdr.ImageDescriptor = 32;
    
    FILE *fp = fopen(filename, "wb");
    fwrite(&hdr, sizeof(hdr), 1, fp);
    
    for(unsigned int j=0; j<h; j++)
        for(unsigned int i=0; i<w; i++) {
            unsigned int idx = indexFor(i, j);
            fputc(MIN(255,data[idx].b * 255), fp);
            fputc(MIN(255,data[idx].g * 255), fp);
            fputc(MIN(255,data[idx].r * 255), fp);
        }
    fclose(fp);
}


SimpleImageSensor::SimpleImageSensor() : ImageSensor()
{
};

SimpleImageSensor::SimpleImageSensor(int w, int h) : ImageSensor(w, h)
{
};

SimpleImageSensor::~SimpleImageSensor()
{    
}

void SimpleImageSensor::process()
{
    // Do noting
}
