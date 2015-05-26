#include <iostream>

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"

int main(int argc, char *argv[]) {
    
    Scene s;
    
    Material red(Color(1.0, 0.0, 0.0), Color(1.0, 0.0, 0.0));
    Material green(Color(0.0, 1.0, 0.0), Color(0.0, 1.0, 0.0));
    
    TransformSeq ts; ts.addTranslation(5, 0, 0);
    
    s.addInstance(new Instance(new Sphere(), TransformSeq(), red));
    s.addInstance(new Instance(new Sphere(), ts, green));
    
    s.addLight(new PointLight(Vector3(10,10,10)));
    s.addLight(new DirectionalLight(Vector3(0.0,-1.0, 0.0)));
    
    Camera cam(Vector3(0,0,10));
    ImageSensor *is = new SimpleImageSensor();
    
    cam.setSensor(is);
    cam.capture(s);
    
    return 0;
}




