//TestCasesWeek1.txt
//Feature: Spheres

#define CATCH_CONFIG_MAIN
#include <cmath>
#include <vector>
#include "../../modules/catch2.hpp"
#include "../../mechanics/sphere.hpp"

TEST_CASE("A ray intersects a sphere at two points"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.pointAtT(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == 4.0);
  REQUIRE(xs[1] == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent"){
  Ray r = Ray(point(0, 1, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.pointAtT(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == 5.0);
  REQUIRE(xs[1] == 5.0);
}

TEST_CASE("A ray misses a sphere"){
  Ray r = Ray(point(0, 2, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.pointAtT(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere"){
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.pointAtT(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == -1.0);
  REQUIRE(xs[1] == 1.0);
}

TEST_CASE("A sphere is behind a ray"){
  Ray r = Ray(point(0, 0, 5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.pointAtT(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == -6.0);
  REQUIRE(xs[1] == -4.0);
}

//TestCasesWeek1.txt
Scenario: The normal on a sphere at a point on the x axis
  Given s ← sphere()
  When n ← normal_at(s, point(1, 0, 0))
  Then n = vector(1, 0, 0)

Scenario: The normal on a sphere at a point on the y axis
  Given s ← sphere()
  When n ← normal_at(s, point(0, 1, 0))
  Then n = vector(0, 1, 0)

Scenario: The normal on a sphere at a point on the z axis
  Given s ← sphere()
  When n ← normal_at(s, point(0, 0, 1))
  Then n = vector(0, 0, 1)

Scenario: The normal on a sphere at a nonaxial point
  Given s ← sphere()
  When n ← normal_at(s, point(√3/3, √3/3, √3/3))
  Then n = vector(√3/3, √3/3, √3/3)

Scenario: The normal is a normalized vector
  Given s ← sphere()
  When n ← normal_at(s, point(√3/3, √3/3, √3/3))
  Then n = normalize(n)

Scenario: A sphere may be assigned a material //** NOTE: Some differences from textbook!
  Given s ← sphere()
    And m ← material()
    And m.color ← color(0, 0, 1)
  When s.material ← m
  Then s.material = m


