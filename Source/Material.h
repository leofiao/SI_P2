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
	Material() : ka(0.0, 0.0, 0.0), kd(), ks(0.6, 0.6, 0.6), kt(0.0, 0.0, 0.0), ns(16.0), nt(1.0), ni(1.0) {}; //ks era 1,1,1
	Material(const Color &ka,
		const Color &kd,
		const Color &ks = Color(1.0, 1.0, 1.0),
		const Color &kt = Color(0.0, 0.0, 0.0),
		int ns = 16.0,
		int nt = 1,
		int ni = 1) :
		ka(ka), kd(kd), ks(ks), kt(kt), ns(ns), nt(nt), ni(ni) {};
	virtual ~Material() {};

public:
	const real REFRACTION_AIR = 1.0003;
	const real REFRACTION_ICE = 1.3100;
	const real REFRACTION_WATER = 1.3330;
	const real REFRACTION_GASOLINE = 1.3980;
	const real REFRACTION_GLASS = 1.5500;
	const real REFRACTION_SAPPHIRE = 1.7700;
	const real REFRACTION_DIAMOND = 2.4190;

	Color ka, kd, ks, kt;
	int ns, nt, ni;
};
#endif /* defined(__RayTracer__Material__) */
