//
//  RGB.cpp
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Color.h"

Color::Color():_r(0),_g(0),_b(0) {}
Color::Color(real r, real g, real b):_r(r), _g(g), _b(b) {};
Color::~Color() {};

Color& operator +=(Color &a, const Color &b)
{
    a._r += b._r;
    a._g += b._g;
    a._b += b._b;
    
    return a;
}

Color Color::black(0,0,0);