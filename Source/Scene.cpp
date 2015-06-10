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

	//Este if nao pode ficar assim, apenas calculamos a luz se o objeto nao estiver tapado por outro
	if (tmin != INFINITE) // We have a hit
	{

		Color finalColor(0, 0, 0);
		int remainingRefractions = 3;
		for (int i = 0; i < lights.size(); i++) {

			//lightDir
			//Verificar para a direcional, nao tem origem
			Vector3 l = lights[i]->sampleLight(hitrec.p);

			//Calcular raio refractado
			real cosI = -hitrec.n.dot(r.d);
			Color refractedColor(1.0, 1.0, 1.0);

			

			if (obj->m.kt.r != 0.0 && obj->m.kt.g != 0.0 && obj->m.kt.b != 0.0 && remainingRefractions > 0)
				if (cosI > 0) {
					real sinI = sqrt(1 - pow(cosI, 2));
					Vector3 m = (hitrec.n * cosI - r.d) / sinI;
					real sinT = (obj->m.ni * sinI) / obj->m.nt;
					real cosT = sqrt(1 - pow(sinT, 2));

					Vector3 t = m * sinT - hitrec.n * cosT;
					refractedColor = traceRay(Ray(hitrec.p, t));
					remainingRefractions--;
				}
				else {
					refractedColor = traceRay(Ray(hitrec.p, r.d));
					remainingRefractions--;
				}


				/*
				if (remainingRefractions > 0) {
				remainingRefractions--;
				Ray rRay(hitrec.p, -hitrec.n);
				refractedColor = this->traceRay(rRay);
				}
				*/

				//Diffuse lighting
				real diffuseDot = MAX(0, hitrec.n.normalize().dot(l));

				real specularDot = 0.0;
				if (diffuseDot > 0.0) {
					//Specular lighting
					Vector3 viewDir = (-r.d).normalize();  //N      //correto???    v = ray.inverso
					Vector3 halfDir = (l + viewDir).normalize(); //H
					real specAngle = MAX(hitrec.n.dot(halfDir), 0.0); //N.H
					specularDot = pow(specAngle, 64.0); //(N.H)^n
				}




				finalColor += obj->m.kd * diffuseDot + obj->m.ks * specularDot + obj->m.kt*refractedColor;
		}

		//Verificar se o raio que sai de hitrec.p até à fonte de luz intersecta outro objeto
		//Samplelight pode retornar um ray (origem e direcçao) para podermos saber a distancia entre a luz e  ponto de intersecao
		//cena recebe esse raio, normaliza

		return  obj->m.ka + finalColor; // + kt*Ot (componente de refracçao)
	}

	//Implementear shadows aqui
	/*
	Existe uma primeira intersecao onde se calcula tendo em conta a luz, enviar um raio de hr.p ate ao outro objeto
	a sua origem é hr.p e a sua direcçao é luz - intersecçao
	*/
	//Ray shadowRay(hitrec.p, );

	return background;
}

bool Scene::compareColor(Color rColor){
	return (background.g != rColor.g && background.r != rColor.r && background.b != rColor.b);
}