//Feature: World

#include <cmath>
#include <vector>
#include <algorithm>
#include "modules/catch2.hpp"
#include "objects/include/world.hpp"
#include "objects/include/sphere.hpp"
#include "objects/include/plane.hpp"


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
  World w = World();
  Sphere shape = Sphere();
  Material m = Material(color(0.8, 1.0, 0.6), 0.7);
  m.specular = 0.2;
  shape.material = m;
  w.addShape(&shape);
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Intersection i = Intersection(4, r, &shape);
  Tuple c = w.colorAtIntersection(i);
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
  Tuple c = w.colorAtIntersection(i);
  REQUIRE(c == color(0.90498, 0.90498, 0.90498));
}

/*
TEST_CASE("The color when a ray misses"){
  World w = World();
  Ray r = Ray(point(0, 0, -5), vector(0, 1, 0));
  Tuple c = color_at(w, r);
  REQUIRE(c == color(0, 0, 0));
}

TEST_CASE("The color when a ray hits"){
  Given w ← default_world()
    And r ← ray(point(0, 0, -5), vector(0, 0, 1))
  When c ← color_at(w, r)
  Then c = color(0.38066, 0.47583, 0.2855)
}

TEST_CASE("The color with an intersection behind the ray"){
  Given w ← default_world()
    And outer ← the first object in w
    And outer.material.ambient ← 1
    And inner ← the second object in w
    And inner.material.ambient ← 1
    And r ← ray(point(0, 0, 0.75), vector(0, 0, -1))
  When c ← color_at(w, r)
  Then c = inner.material.color
}

//TestCasesWeek6.txt

Scenario: There is no shadow when nothing is collinear with point and light
  Given w ← default_world()
    And p ← point(0, 10, 0)
   Then is_shadowed(w, p) is false

Scenario: The shadow when an object is between the point and the light
  Given w ← default_world()
    And p ← point(10, -10, 10)
   Then is_shadowed(w, p) is true

Scenario: There is no shadow when an object is behind the light
  Given w ← default_world()
    And p ← point(-20, 20, -20)
   Then is_shadowed(w, p) is false

Scenario: There is no shadow when an object is behind the point
  Given w ← default_world()
    And p ← point(-2, 2, -2)
   Then is_shadowed(w, p) is false

Scenario: shade_hit() is given an intersection in shadow
  Given w ← world()
    And w.light ← point_light(point(0, 0, -10), color(1, 1, 1))
    And s1 ← sphere()
    And s1 is added to w
    And s2 ← sphere() with:
      | transform | translation(0, 0, 10) |
    And s2 is added to w
    And r ← ray(point(0, 0, 5), vector(0, 0, 1))
    And i ← intersection(4, s2)
  When comps ← prepare_computations(i, r)
    And c ← shade_hit(w, comps)
  Then c = color(0.1, 0.1, 0.1)
*/

