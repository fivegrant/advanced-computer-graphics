//Feature: World

#include <cmath>
#include <vector>
#include <algorithm>
#include "modules/catch2.hpp"
#include "objects/include/world.hpp"
#include "objects/include/sphere.hpp"
#include "objects/include/plane.hpp"


std::vector<Intersection> unfilled = {};
//TestCasesWeek5.txt
TEST_CASE("Creating a world"){
  World w = World();
  REQUIRE(w.objects.size() == 0);
  REQUIRE(w.lights.size() == 0);
}

TEST_CASE("The default world"){
  Light light = Light(point(-10, 10, -10), color(1, 1, 1));
  Sphere s1 = Sphere();
  Material m = Material(color(0.8, 1.0, 0.6), 0.7);
  m.specular = 0.2;
  s1.material = m;
  Sphere s2 = Sphere();
  s2.set_transform(scaling(0.5, 0.5, 0.5));
  World w = World();
  w.addShape(&s1);
  w.addShape(&s2);
  w.addLight(light);
  REQUIRE(w.lights[0] == light);
  REQUIRE(w.objects[0] == &s1);
  REQUIRE(w.objects[1] == &s2);
}

TEST_CASE("Intersect a world with a ray"){
  World w = World();
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));

  //Populate World
  Light light = Light(point(-10, 10, -10), color(1, 1, 1));
  Sphere s1 = Sphere();
  Material m = Material(color(0.8, 1.0, 0.6), 0.7);
  m.specular = 0.2;
  s1.material = m;
  Sphere s2 = Sphere();
  s2.set_transform(scaling(0.5, 0.5, 0.5));
  w.addShape(&s1);
  w.addShape(&s2);
  w.addLight(light);

  std::vector<Intersection> xs = w.intersectionWith(r);
  REQUIRE(xs.size() == 4);
  REQUIRE(xs[0].t == 4);
  REQUIRE(xs[1].t == 4.5);
  REQUIRE(xs[2].t == 5.5);
  REQUIRE(xs[3].t == 6);
}

TEST_CASE("Shading an intersection"){
  //Light light = Light(point(-10, 10, -10), color(1, 1, 1));
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  //Material m = Material(color(0.8, 1.0, 0.6), 0.7);
  //m.specular = 0.2;
  //shape.material = m;
  //w.addLight(light);
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Intersection i = Intersection(4, r, &shape1);
  Tuple c = w.colorAtIntersection(i, i.generateHitRecord(unfilled), 5);
  REQUIRE(c == color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("Shading an intersection from the inside"){
  World w = World();
  w.addLight(Light(point(0, 0.25, 0), color(1, 1, 1)));
  Sphere shape = Sphere();
  shape.set_transform(scaling(0.5, 0.5, 0.5));
  w.addShape(&shape);
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  Intersection i = Intersection(0.5, r, &shape);
  Tuple c = w.colorAtIntersection(i, i.generateHitRecord(unfilled), 5);
  REQUIRE(c == color(0.90498, 0.90498, 0.90498));
}

TEST_CASE("The color when a ray misses"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Ray r = Ray(point(0, 0, -5), vector(0, 1, 0));
  Tuple c = w.colorAtRay(r, 5);
  REQUIRE(c == color(0, 0, 0));
}

TEST_CASE("The color when a ray hits"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Tuple c = w.colorAtRay(r, 5);
  REQUIRE(c == color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("The color with an intersection behind the ray"){
  World w = World();
  Sphere outer = DefaultSphere1();
  w.addShape(&outer);
  outer.material.ambient = 1;
  Sphere inner = DefaultSphere2();
  w.addShape(&inner);
  inner.material.ambient = 1;
  Ray r = Ray(point(0, 0, 0.75), vector(0, 0, -1));
  Tuple c = w.colorAtRay(r, 5);
  REQUIRE(c == inner.material.surface_color);
}

//TestCasesWeek6.txt

TEST_CASE("There is no shadow when nothing is collinear with point and light"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Tuple p = point(0, 10, 0);
  REQUIRE(!w.shadow(p));
}

TEST_CASE("The shadow when an object is between the point and the light"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Tuple p = point(10, -10, 10);
  REQUIRE(w.shadow(p));
}

TEST_CASE("There is no shadow when an object is behind the light"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Tuple p = point(-20, 20, -20);
  REQUIRE(!w.shadow(p));
}

TEST_CASE("There is no shadow when an object is behind the point"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Tuple p = point(-2, 2, -2);
  REQUIRE(!w.shadow(p));
}

TEST_CASE("shade_hit() is given an intersection in shadow"){
  World w = World();
    w.addLight(Light(point(0, 0, -10), color(1, 1, 1)));
    Sphere ob1 = Sphere();
    w.addShape(&ob1);
    Sphere ob2 = Sphere();
    ob2.set_transform(translation(0, 0, 10));
    w.addShape(&ob2);
    Ray r = Ray(point(0, 0, 5), vector(0, 0, 1));
    Intersection i = Intersection(4, r, &ob2);
    Tuple c = w.colorAtIntersection(i, i.generateHitRecord(unfilled), 5);
    REQUIRE(c == color(0.1, 0.1, 0.1));
}

// Custom Test Cases
TEST_CASE("Reflectivity for the default material"){
   REQUIRE(Material().reflective == 0 );
}

TEST_CASE("Precomputing the reflection vector"){
  Plane shape = Plane();
  Ray r = Ray(point(0, 1, -1), vector(0, -sqrt(2)/2, sqrt(2)/2));
  Intersection i = Intersection(sqrt(2), r, &shape);
  REQUIRE(i.generateHitRecord(unfilled).reflectv == vector(0, sqrt(2)/2, sqrt(2)/2));
}

TEST_CASE("The refracted color of opaque surfaces"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 0));
  r.direction = vector(0, 0, 1);
  std::vector<Intersection> xs = {Intersection(4, r, &shape1), Intersection(6, r, &shape1)};
  Tuple c = w.effective_refraction(xs[0], xs[0].generateHitRecord(xs), 5);
  REQUIRE(c == color(0, 0, 0));
}

TEST_CASE("The refracted color at the maximum recursive depth"){
   World w = World();
  Sphere shape1 = DefaultSphere1();
  shape1.material.transparency = 1;
  shape1.material.ior = 1.5;
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  //w.addShape(&shape2);
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 0));
  r.direction = vector(0, 0, 1);
  std::vector<Intersection> xs = {Intersection(4, r, &shape1), Intersection(6, r, &shape1)};
  Tuple c = w.effective_refraction(xs[0], xs[0].generateHitRecord(xs), 5);
  REQUIRE(c == color(0, 0, 0));

}

TEST_CASE("The refracted color under total internal reflection"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  shape1.material.transparency = 1;
  shape1.material.ior = 1.5;
  w.addShape(&shape1);
  Sphere shape2 = DefaultSphere2();
  w.addShape(&shape2);
  Ray r = Ray(point(0, 0,sqrt(2)/2), vector(0, 0, 0));
  r.direction = vector(0, 1, 0);
  std::vector<Intersection> xs = {Intersection(-sqrt(2)/2, r, &shape1), Intersection(sqrt(2)/2, r, &shape1)};
  Tuple c = w.effective_refraction(xs[1], xs[1].generateHitRecord(xs), 5);
  REQUIRE(c == color(0, 0, 0));
}

TEST_CASE("colorAtIntersection with a transparent material"){
  World w = World();
  Sphere def1 = DefaultSphere1();
  w.addShape(&def1);
  Sphere def2 = DefaultSphere2();
  w.addShape(&def2);

  Plane floor = Plane();
  floor.set_transform(translation(0, -1, 0));
  floor.material.ior = 1.5;
  floor.material.transparency = 0.5;
  w.addShape(&floor);

  Sphere ball = Sphere();
  ball.material.surface_color = color(1, 0, 0);
  ball.material.ambient = .5;
  floor.set_transform(translation(0, -3.5, -0.5));
  w.addShape(&ball);

  Ray r = Ray(point(0, 0, -3), vector(0, 0, 0));
  r.direction = vector(0, -sqrt(2)/2, sqrt(2)/2);
  std::vector<Intersection> xs = {Intersection(sqrt(2), r, &floor)};
  Tuple c = w.colorAtIntersection(xs[0], xs[0].generateHitRecord(xs), 5);
  REQUIRE(c == color(.93642, .68642, .68642));
}
