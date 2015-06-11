//
//  Camera.cpp
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//


#include "Camera.h"

Camera::Camera() : eye(), at(0, 0, -1), up(0, 1, 0), fd(0.050), width(0.036), height(0.024), sensor(NULL)
{
	setupAxis();
}

Camera::Camera(const Vector3 &eye, const Vector3 &at, const Vector3 &up, real fd, real width, real height) :
eye(eye), at(at), up(up), fd(fd), width(width), height(height), sensor(NULL)
{
	setupAxis();
}

Camera::~Camera()
{
}

void Camera::setSensor(ImageSensor *s)
{
	// Discard previous sensor if it exists
	if (sensor) delete sensor;

	// replace with new one
	sensor = s;
}

void Camera::capture(Scene &s)
{
	// No sensor no capture
	if (!sensor) return;

	// compute the center of the virtual sensor, placed at the focal distance
	Vector3 center = eye - ez * fd;

	// Compute the top left corner of the sensor, in WC
	Vector3 topleft = center - ex * .5 * width + ey * .5 * height;

	Vector3 dx = ex * (width / sensor->w); // Horizontal distance between pixels in image sensor
	Vector3 dy = -ey * (height / sensor->h); // Vertical distance between pixels in image sensor
	Vector3 pixel = topleft + dx * 0.5 - dy * .5;   // Center of the pixel

	unsigned int aaDepth = 4; //How many times the pixels are going to be divided
	double aaThreshold = 0.3; //The maximum difference allowed (???)

	Vector3 left = pixel;
	for (unsigned int j = 0; j < sensor->h; j++) {
		for (unsigned int i = 0; i < sensor->w; i++) {

			Vector3 to = pixel - eye;
			to.normalize();
			Ray r(eye, to);
			Color centerColor = s.traceRay(r);

			Color averageColor = (calcAverageColor(s, pixel, dx, dy) + centerColor*(1.0 / 9.0));

			//std::cout << averageColor.r << ", " << averageColor.g << ", " << averageColor.b << std::endl;
			sensor->addSample(i, j, averageColor);

			pixel += dx;
		}
		left += dy;
		pixel = left;
	}

	this->sensor->dumpToTGA("image.tga");
}

Color Camera::calcAverageColor(Scene &s, Vector3 pixel, Vector3 dx, Vector3 dy) {

	//Canto superior esquerdo
	Vector3 tl = (pixel - dx / 2 + dy / 2);
	Vector3 to_tl = tl - eye;
	to_tl.normalize();
	Ray rtl(eye, to_tl);
	Color ctl = s.traceRay(rtl);

	//Canto superior direito
	Vector3 tr(pixel + dx / 2 + dy / 2);
	Vector3 to_tr = tr - eye;
	to_tr.normalize();
	Ray rtr(eye, to_tr);
	Color ctr = s.traceRay(rtr);

	//Canto inferior esquero
	Vector3 bl(pixel - dx / 2 - dy / 2);
	Vector3 to_bl = bl - eye;
	to_bl.normalize();
	Ray rbl(eye, to_bl);
	Color cbl = s.traceRay(rbl);

	//Canto inferior direito
	Vector3 br(pixel + dx / 2 - dy / 2);
	Vector3 to_br = br - eye;
	to_br.normalize();
	Ray rbr(eye, to_br);
	Color cbr = s.traceRay(rbr);

	//Topo
	Vector3 tm(pixel + dy / 2);
	Vector3 to_tm = tm - eye;
	to_tm.normalize();
	Ray rtm(eye, to_tm);
	Color ctm = s.traceRay(rtm);

	//Meio direito
	Vector3 rm(pixel + dx / 2);
	Vector3 to_rm = rm - eye;
	to_rm.normalize();
	Ray rrm(eye, to_rm);
	Color crm = s.traceRay(rrm);

	//Meio baixo
	Vector3 bm(pixel - dy / 2);
	Vector3 to_bm = bm - eye;
	to_bm.normalize();
	Ray rbm(eye, to_bm);
	Color cbm = s.traceRay(rbm);

	//Meio esquerda
	Vector3 lm(pixel - dx / 2);
	Vector3 to_lm = lm - eye;
	to_lm.normalize();
	Ray rlm(eye, to_lm);
	Color clm = s.traceRay(rlm);

	Color averageColor = (ctl + ctr + cbl + cbr + ctm + crm + cbm + clm) / 9.0;

	return averageColor;
}

void Camera::setupAxis()
{
	// ez is a unit vector pointing from at to eye
	ez = eye - at;
	ez.normalize();

	// ex is orthogonal to the plane formed by up and (at-eye)
	ex = up.cross(ez);
	ex.normalize();

	// finally ey is also orthogonal to the plane formed by ey and ez
	ey = ez.cross(ex);
	ey.normalize();    // This shouldn't be necessary
}

