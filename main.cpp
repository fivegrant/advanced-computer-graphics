#include <iostream>
#include "build/raytracer.hpp"

int main(){

std::cout << "Start\n";

Camera camera = Camera(1000, 500);
camera.set_fov(PI/2);
camera.set_transform(view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0)));
World w = World();

std::cout << "Set up Camera and World\n";


//Scene Contents
Tuple ROOM_COLOR = color(1, 0.9, 0.9);
Tuple MIDDLE_COLOR = color(0.1, 1, 0.5);
Tuple LEFT_COLOR = color(1, 0.8, 0.1);
Tuple RIGHT_COLOR = color(0.5, 1, 0.1);
Material SURFACE = Material(); SURFACE.reflective = .5;SURFACE.diffuse = 0.3; SURFACE.specular = 0.2;
Material WALL = Material(); WALL.specular = 0.0;
WALL.pattern.active = true;
WALL.pattern.pattern_func = &checker;
WALL.pattern.color_a = color(1, 0, 0);
WALL.pattern.color_b = color(0, 0, 1);
WALL.pattern.set_transform(scaling(2, 2, 2));

Plane floor = Plane();
floor.material = WALL;
floor.material.reflective = .1;
floor.material.diffuse = .4;
floor.material.ambient = .4;

w.addShape(&floor);

Plane leftwall = Plane();
leftwall.material = WALL;
leftwall.set_transform(rotationx(PI/2));
leftwall.set_transform(rotationy(-PI/4));
leftwall.set_transform(translation(0, 0, 5));
//w.addShape(&leftwall);

Plane rightwall = Plane();
rightwall.material = WALL;
rightwall.material.surface_color = ROOM_COLOR;
rightwall.set_transform(rotationx(PI/2));
rightwall.set_transform(rotationy(PI/4));
rightwall.set_transform(translation(0, 0, 5));
//w.addShape(&rightwall);

Plane ceiling = Plane();
ceiling.material = WALL;
rightwall.set_transform(translation(0, 5, 0));
//w.addShape(&ceiling);

Plane leftalt = Plane();
leftalt.material = WALL;
leftalt.set_transform(rotationx(PI/2));
leftalt.set_transform(rotationy(-PI/4));
leftalt.set_transform(translation(0, 0, -5));
//w.addShape(&leftalt);

Plane rightalt = Plane();
rightalt.material = WALL;
rightalt.material.surface_color = ROOM_COLOR;
rightalt.set_transform(rotationx(PI/2));
rightalt.set_transform(rotationy(PI/4));
rightalt.set_transform(translation(0, 0, -5));
rightalt.material = GlassSphere().material;
//w.addShape(&rightalt);


Sphere glass = GlassSphere();
glass.set_transform(translation(-0.5, 1, 0.5));
glass.material.reflective = .5;
glass.material.diffuse = .1;
glass.material.ambient = .1;
//w.addShape(&glass);

Sphere middle = Sphere();
middle.set_transform(translation(-0.5, 1, 0.5));
middle.set_transform(scaling(2, 2, 2));
middle.material = SURFACE;
middle.material.pattern.set_transform(scaling(1, 1.5, 2));
middle.material.surface_color = MIDDLE_COLOR;
middle.material.pattern.active = true;
middle.material.pattern.pattern_func = &ring;
middle.material.pattern.color_a = color(1, 1, 1);
middle.material.pattern.color_b = color(1, 0, 0);
w.addShape(&middle);

Sphere right = Sphere();
right.set_transform(scaling(0.5, 0.5, 0.5));
right.set_transform(translation(1.5, 0.5, 0.5));
right.material = SURFACE;
right.material.surface_color = RIGHT_COLOR;
right.material.pattern.active = true;
right.material.pattern.pattern_func = &ring;
right.material.pattern.color_a = color(1, 1, 1);
right.material.pattern.color_b = color(1, 0, 0);
//w.addShape(&right);

Sphere left = Sphere();
left.set_transform(scaling(0.33, 0.33, 0.33));
left.set_transform(translation(-1.5, 0.33, -0.75));
left.material.surface_color = LEFT_COLOR;
left.material.pattern.active = true;
left.material.pattern.pattern_func = &gradient;
left.material.pattern.color_a = color(0, 1, 0);
left.material.pattern.color_b = color(1, 0, 1);
///w.addShape(&left);

std::cout << "Initialize Scene\n";

Canvas image = camera.render(w);

std::cout << "Render Scene\n";

std::string FILENAME = "portfolio/look_here.ppm";
image.toPPM(FILENAME);

std::cout << "Save to " << FILENAME << "\n";
  return 0;
}
