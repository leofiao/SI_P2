//
//  Scene.cpp
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//

#include "Scene.h"

void Scene::setBackground(const Color &background)
{
	this->background = background;
}

void Scene::addInstance(Instance *obj)
{
	instances.push_back(obj);
}

void Scene::addLight(Light *light)
{
	lights.push_back(light);
}

Color Scene::traceRefractionRay(Ray &newRay, Ray r)
{
	double tmin = INFINITE;
	Instance *obj = NULL;
	HitRecord hitrec;
	// process each primitive instace
	for (std::vector<Instance *>::iterator it = instances.begin(); it != instances.end(); it++)
	{
		HitRecord hr;
		real t = INFINITE; Instance *ins = *it;
		if (ins->intersects(r, t, hr)) {
			if (t < tmin) {
				tmin = t;
				obj = ins;
				hitrec = hr;
			}
		}
	}

	if (tmin != INFINITE) // We have a hit
	{
		newRay.o = hitrec.p;
		newRay.d = r.d;

		Vector3 l = lights[0]->sampleLight(hitrec.p);
		real dot = MAX(0, hitrec.n.dot(l));

		return obj->m.kd * dot + obj->m.ka;
	}
	return background;
}

Color Scene::traceRay(const Ray &r)
{
	double tmin = INFINITE;
	Instance *obj = NULL;
	HitRecord hitrec;
	// process each primitive instace
	for (std::vector<Instance *>::iterator it = instances.begin(); it != instances.end(); it++)
	{
		HitRecord hr;
		real t = INFINITE;
		Instance *ins = *it;
		bool isInShadow = false;
		if (ins->intersects(r, t, hr)) {
			if (t < tmin) {
				tmin = t;
				obj = ins;
				hitrec = hr;
			}
		}
	}

	if (tmin != INFINITE) // We have a hit
	{

		Color finalColor(0, 0, 0);
		int remainingRefractions = 5;
		for (int i = 0; i < lights.size(); i++) {

			//lightDir
			Vector3 l = lights[i]->sampleLight(hitrec.p).normalize();

			//Calcular raio refractado
			Color refractedColor(0.0, 0.0, 0.0);

			real cosI = -hitrec.n.dot(r.d);
			while (remainingRefractions > 0) {
				if (obj->m.kt.r != 0.0 && obj->m.kt.g != 0.0 && obj->m.kt.b != 0.0)
					if (cosI > 0) {

						real sinI = sqrt(1 - pow(cosI, 2));
						Vector3 m = (hitrec.n * cosI - r.d) / sinI;
						real sinT = (obj->m.ni * sinI) / obj->m.nt;

						real n = obj->m.ni / obj->m.nt;
						real sinT2 = n * n * (1.0 - cosI * cosI);
						if (sinT2 > 1.0)
							break; //Invalido
						real cosT = sqrt(1 - sinT2);
						Vector3 t = r.d* n + hitrec.n*(n * cosI - cosT);

						//Dos slides
						//real cosT = sqrt(1 - pow(sinT, 2));
						//Vector3 t = m * sinT - hitrec.n * cosT;

						Ray newRay(hitrec.p - hitrec.n / 20.0, t);
						refractedColor += traceRefractionRay(newRay, newRay);
						//refractedColor += traceRay(newRay);
					}
					else {
						Ray newRay(hitrec.p + hitrec.n / 20.0, r.d);
						refractedColor += traceRefractionRay(newRay, newRay);
						//refractedColor += traceRay(newRay);
					}

					remainingRefractions--;
			}
			refractedColor = refractedColor / 4;


			//Diffuse lighting
			real diffuseDot = MAX(0, hitrec.n.normalize().dot(l));

			real specularDot = 0.0;
			if (diffuseDot > 0.0) {
				//Specular lighting
				Vector3 viewDir = (-r.d).normalize();  //N     v = ray.inverso
				Vector3 halfDir = (l + viewDir).normalize(); //H
				real specAngle = MAX(hitrec.n.dot(halfDir), 0.0); //N.H
				specularDot = pow(specAngle, 64.0); //(N.H)^n
			}

			finalColor += obj->m.kd * diffuseDot + obj->m.ks * specularDot + obj->m.kt*refractedColor;
		}

		return  obj->m.ka + finalColor; 
	}

	return background;
}