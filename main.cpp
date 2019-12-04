#include "build/raytracer.hpp"

int main(){


Camera cam = Camera(150, 150);
World w = World();

//Scene Contents
Light light = Light(point(-10, 10, -10), color(.5, 0, .8));
Sphere s1 = Sphere();
Material m = Material(color(0.8, 1.0, 0.6), 0.7);
m.specular = 0.2;
s1.material = m;
Sphere s2 = Sphere();
s2.set_transform(scaling(25, 25, 25));
w.addShape(&s1);
w.addShape(&s2);
w.addLight(light);

Canvas image = cam.render(w);
image.toPPM("main.ppm");


  return 0;
}
