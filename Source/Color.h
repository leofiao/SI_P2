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
    
    real _r, _g, _b;
};

Color& operator +=(Color &a, const Color &b);

#endif /* defined(__RayTracer__RGB__) */
