#include "build/raytracer.hpp"

int main(){


Camera camera = Camera(1000, 500);
camera.set_fov(PI/2);
//camera.set_transform(view_transform(point(0, 1.5, -5), point(0, 2.5, 0), vector(0, 1, 0)));
camera.set_transform(view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0)));
World w = World();

//Scene Contents
Tuple ROOM_COLOR = color(1, 0.9, 0.9);
Tuple MIDDLE_COLOR = color(0.1, 1, 0.5);
Tuple LEFT_COLOR = color(1, 0.8, 0.1);
Tuple RIGHT_COLOR = color(0.5, 1, 0.1);
Material SURFACE = Material(); SURFACE.reflective = .5;SURFACE.diffuse = 0.3; SURFACE.specular = 0.2;
Material WALL = Material(); WALL.specular = 0.0;

Plane floor = Plane();
floor.material = WALL;
w.addShape(&floor);

Plane leftwall = Plane();
leftwall.material = WALL;
leftwall.set_transform(rotationx(PI/2));
leftwall.set_transform(rotationy(-PI/4));
leftwall.set_transform(translation(0, 0, 5));
w.addShape(&leftwall);

Plane rightwall = Plane();
rightwall.material = WALL;
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

Canvas image = camera.render(w);
image.toPPM("reflect_sphere.ppm");


  return 0;
}
