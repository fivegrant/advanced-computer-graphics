//Feature: Spheres

#define CATCH_CONFIG_MAIN
#include <cmath>
#include <vector>
#include "../../modules/catch2.hpp"
#include "../../mechanics/sphere.hpp"

//TestCasesWeek1.txt
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
TEST_CASE("The normal on a sphere at a point on the x axis"){
  Sphere s = Sphere();
  Tuple n = s.normalAtPoint(point(1, 0, 0));
  REQUIRE(n == vector(1, 0, 0));
}

TEST_CASE("The normal on a sphere at a point on the y axis"){
  Sphere s = Sphere();
  Tuple n = s.normalAtPoint(point(0, 1, 0));
  REQUIRE(n == vector(0, 1, 0));
}

TEST_CASE("The normal on a sphere at a point on the z axis"){
  Sphere s = Sphere();
  Tuple n = s.normalAtPoint(point(0, 0, 1));
  REQUIRE(n == vector(0, 0, 1));
}

TEST_CASE("The normal on a sphere at a nonaxial point"){
  Sphere s = Sphere();
  Tuple n = s.normalAtPoint(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  REQUIRE(n == vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
}

TEST_CASE("The normal is a normalized vector"){
  Sphere s = Sphere();
  Tuple n = s.normalAtPoint(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  REQUIRE(n == normalize(n));
}

TEST_CASE("A sphere may be assigned a material //** NOTE: Some differences from textbook!"){
  Sphere s = Sphere();
  Material m = Material();
  m.surface_color = color(0, 0, 1);
  s.material = m;
  REQUIRE(s.material == m);
}

//TestCasesWeek3.txt
/*TODO
Scenario: A sphere's default transformation
  Given s ← sphere()
  Then s.transform = identity_matrix

Scenario: Changing a sphere's transformation
  Given s ← sphere()
    And t ← translation(2, 3, 4)
  When set_transform(s, t)
  Then s.transform = t

Scenario: Intersecting a scaled sphere with a ray
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And s ← sphere()
  When set_transform(s, scaling(2, 2, 2))
    And xs ← intersect(s, r)
  Then xs.count = 2
    And xs[0].t = 3
    And xs[1].t = 7

Scenario: Intersecting a translated sphere with a ray
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And s ← sphere()
  When set_transform(s, translation(5, 0, 0))
    And xs ← intersect(s, r)
  Then xs.count = 0
*/
