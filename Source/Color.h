//
//  RGB.h
//  RayTracer
//
//  Created by Fernando Birra on 07/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__RGB__
#define __RayTracer__RGB__

#include <iostream>

#include "defines.h"

class Color {

public:
    
    static Color black;
    
    Color();
    Color(real r,real g,real b);
    virtual ~Color();
    
    real r, g, b;
};

Color operator +(const Color &c1, const Color &c2);
Color& operator +=(Color &c1, const Color &c2);
Color operator -(const Color &c1, const Color &c2);
Color operator *(const Color &c, real f);
Color operator *(const Color &c, Color f);
Color& operator *=(Color &c, real f);
Color operator /(const Color &c, real f);
bool operator !=(const Color &c, const Color &c2);


#endif /* defined(__RayTracer__RGB__) */
