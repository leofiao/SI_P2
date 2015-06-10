#include <iostream>

#include "Scene.h"
#include "Sphere.h"
#include "Torus.h"
#include "Plane.h"
#include "Cube.h"
#include "Camera.h"

void oneSphereScene()
{
	Scene s;

	Material green(Color(0.0, 0.2, 0.0), Color(0.0, 0.8, 0.0));

	TransformSeq ts1; ts1.addScale(1.2, 1.2, 0.7); ts1.addTranslation(0, 0, -1.2);

	s.addInstance(new Instance(new Sphere(), ts1, green));

	s.addLight(new PointLight(Vector3(10, 10, 10)));

	Camera cam(Vector3(0, 0, 10));
	ImageSensor *is = new SimpleImageSensor(600, 400);

	cam.setSensor(is);
	cam.capture(s);
}

void testTorusScene() {
	Scene s;

	Material green(Color(0.0, 0.2, 0.0), Color(0.0, 0.8, 0.0));
	Material blue(Color(0.0, 0.0, 0.4), Color(0.0, 0.0, 0.5));

	TransformSeq ts1;
	ts1.addScale(1, 1, 1);
	ts1.addRotx(90.0);

	TransformSeq ts2;
	//ts2.addScale(0.7, 0.7, 0.7);
	ts2.addRotx(90);
	ts2.addTranslation(0, 0, -1.5);


	s.addInstance(new Instance(new Torus(), ts1, green));
	//s.addInstance(new Instance(new Plane(), ts2, blue));

	s.addLight(new PointLight(Vector3(0, 10, 0)));
	//s.addLight(new DirectionalLight(Vector3(0, 10, 10)));
	//s.addLight(new DirectionalLight(Vector3(0.0, -1.0, 0.0)));

	s.setBackground(Color(0.7, 0.7, 0.7));

	Camera cam(Vector3(0, 10, 10));
	ImageSensor *is = new SimpleImageSensor(600, 400);

	cam.setSensor(is);
	cam.capture(s);
}

void threeSpheresScene()
{
	Scene s;

	Material red(Color(0.3, 0.0, 0.0), Color(0.5, 0.0, 0.0));
	Material green(Color(0.0, 0.5, 0.0), Color(0.0, 0.4, 0.0));
	Material blue(Color(0.0, 0.0, 0.4), Color(0.0, 0.0, 0.5));

	TransformSeq ts0; ts0.addScale(1.5, 1.5, 1.5); ts0.addTranslation(0, 0, 0);
	TransformSeq ts1; ts1.addScale(0.5, 1.0, 1.0); ts1.addTranslation(0, 0, 1);
	TransformSeq ts2; ts2.addScale(0.5, 0.5, 0.5); ts2.addTranslation(-1.0, 0.0, 1.0);
	TransformSeq ts3; ts3.addScale(0.5, 0.5, 0.5); ts3.addTranslation(1.0, 0.0, 1.0);

	s.addInstance(new Instance(new Sphere(), ts1, green));
	s.addInstance(new Instance(new Sphere(), ts0, red));
	s.addInstance(new Instance(new Sphere(), ts2, blue));
	s.addInstance(new Instance(new Sphere(), ts3, blue));

	s.addLight(new PointLight(Vector3(0, 5, 5)));
	s.addLight(new DirectionalLight(Vector3(0.0, -1.0, 0.0)));

	s.setBackground(Color(0.3, 0.7, 0.8));

	Camera cam(Vector3(0, 0, 10));
	ImageSensor *is = new SimpleImageSensor(600, 400);

	cam.setSensor(is);
	cam.capture(s);
}

int main(int argc, char *argv[])
{
	//oneSphereScene();
	//threeSpheresScene();
	testTorusScene();

	return 0;
}




