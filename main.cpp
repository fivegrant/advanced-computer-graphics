#include "build/raytracer.hpp"

int main(){


Camera camera = Camera(100, 50);
camera.set_fov(PI/3);
//camera.set_view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
camera.set_view_transform(point(0, 1.5, -5), point(0, -1, 0), vector(0, 1, 0));
World w = World();

//Scene Contents
Tuple ROOM_COLOR = color(1, 0.9, 0.9);
Tuple MIDDLE_COLOR = color(0.1, 1, 0.5);
Tuple LEFT_COLOR = color(1, 0.8, 0.1);
Tuple RIGHT_COLOR = color(0.5, 1, 0.1);
Material SURFACE = Material(); SURFACE.diffuse = 0.7; SURFACE.specular = 0.3;

Plane floor = Plane();
floor.material.surface_color = ROOM_COLOR;
w.addShape(&floor);

Plane leftwall = Plane();
leftwall.material.surface_color = ROOM_COLOR;
leftwall.set_transform(rotationx(PI/2));
leftwall.set_transform(rotationy(-PI/4));
leftwall.set_transform(translation(0, 0, 5));
w.addShape(&leftwall);

Plane rightwall = Plane();
rightwall.material.surface_color = ROOM_COLOR;
rightwall.set_transform(rotationx(PI/2));
rightwall.set_transform(rotationy(PI/4));
rightwall.set_transform(translation(0, 0, 5));
w.addShape(&rightwall);

Sphere middle = Sphere();
middle.set_transform(translation(-0.5, 1, 0.5));
middle.material = SURFACE;
middle.material.surface_color = MIDDLE_COLOR;
w.addShape(&middle);

Sphere right = Sphere();
right.set_transform(scaling(0.5, 0.5, 0.5));
right.set_transform(translation(1.5, 0.5, -0.5));
right.material = SURFACE;
right.material.surface_color = RIGHT_COLOR;
w.addShape(&right);

Sphere left = Sphere();
left.set_transform(scaling(0.33, 0.33, 0.33));
left.set_transform(translation(-1.5, 0.33, -0.75));
left.material = SURFACE;
left.material.surface_color = LEFT_COLOR;
w.addShape(&left);

Light light_source = Light(point(-10, 10, 10), color(1, 1, 1));
w.addLight(light_source);

Canvas image = camera.render(w);
image.toPPM("three_spheres.ppm");


  return 0;
}
