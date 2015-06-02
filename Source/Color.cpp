//
//  RGB.cpp
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Color.h"

Color::Color():r(0),g(0),b(0) {}
Color::Color(real r, real g, real b):r(r), g(g), b(b) {};
Color::~Color() {};

Color operator +(const Color &c1, const Color &c2)
{
    return Color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
}

Color& operator +=(Color &c1, const Color &c2)
{
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    
    return c1;
}

Color operator *(const Color &c, real f)
{
    return Color(c.r * f, c.g * f, c.b * f);
}

Color& operator *=(Color &c, real f)
{
    c.r *= f;
    c.g *= f;
    c.b *= f;
    
    return c;
}


Color Color::black(0,0,0);