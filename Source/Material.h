//
//  Material.h
//  RayTracer
//
//  Created by Fernando Birra on 24/12/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#ifndef __RayTracer__Material__
#define __RayTracer__Material__

#include <iostream>

#include "defines.h"

#include "Color.h"

class Material {

public:
	Material() : ka(0.0, 0.0, 0.0), kd(), ks(0.6, 0.6, 0.6), kt(0.0, 0.0, 0.0), ns(16.0), nt(1.0) {}; //ks era 1,1,1
	Material(const Color &ka,
		const Color &kd,
		const Color &ks = Color(1.0, 1.0, 1.0),
		const Color &kt = Color(0.0, 0.0, 0.0),
		int ns = 16.0,
		int nt = 1) :
		ka(ka), kd(kd), ks(ks), kt(kt), ns(ns), nt(nt) {};
	virtual ~Material() {};

public:
	Color ka, kd, ks, kt;
	int ns, nt;
};
#endif /* defined(__RayTracer__Material__) */
