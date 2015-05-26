//
//  Camera.cpp
//  RayTracer
//
//  Created by Fernando Birra on 08/11/13.
//  Copyright (c) 2013 FCT/UNL. All rights reserved.
//


#include "Camera.h"

Camera::Camera() : _eye(), _at(0, 0, -1), _up(0, 1, 0), _fd(0.050), _width(0.036), _height(0.024), sensor(NULL)
{
	setupAxis();
}

Camera::Camera(const Vector3 &eye, const Vector3 &at, const Vector3 &up, real fd, real width, real height) :
_eye(eye), _at(at), _up(up), _fd(fd), _width(width), _height(height), sensor(NULL)
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
	Vector3 center = _eye - _ez * _fd;

	// Compute the top left corner of the sensor, in WC
	Vector3 topleft = center - _ex * .5 * _width + _ey * .5 * _height;

	Vector3 dx = _ex * (_width / sensor->_w); // Horizontal distance between pixels in image sensor
	Vector3 dy = _ey * (_height / sensor->_h); // Vertical distance between pixels in image sensor

	Vector3 pixel = topleft + dx * 0.5 - dy * .5;   // Center of the pixel

	Vector3 left = pixel;
	for (size_t i = 0; i<sensor->_h; i++) {
		for (size_t j = 0; j<sensor->_w; j++) {
			Vector3 to = pixel - _eye; to.normalize();
			Ray r(_eye, to);
			Color c = s.traceRay(r);
			sensor->addSample(j, i, c);
			pixel += dx;
		}
		left += dy;
		pixel = left;
	}
}

void Camera::setupAxis()
{
	// ez is a unit vector pointing from at to eye
	_ez = _eye - _at;
	_ez.normalize();

	// ex is orthogonal to the plane formed by up and (at-eye)
	_ex = _ez.cross(_up);
	_ex.normalize();

	// finally ey is also orthogonal to the plane formed by ey and ez
	_ey = _ez.cross(_ex);
	_ey.normalize();    // This shouldn't be necessary
}