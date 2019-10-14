//Feature: Spheres

#define CATCH_CONFIG_MAIN
#include <cmath>
#include <vector>
#include "../../modules/catch2.hpp"
#include "../../objects/include/sphere.hpp"

//TestCasesWeek1.txt
TEST_CASE("A ray intersects a sphere at two points"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == 4.0);
  REQUIRE(xs[1] == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent"){
  Ray r = Ray(point(0, 1, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == 5.0);
  REQUIRE(xs[1] == 5.0);
}

TEST_CASE("A ray misses a sphere"){
  Ray r = Ray(point(0, 2, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere"){
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == -1.0);
  REQUIRE(xs[1] == 1.0);
}

TEST_CASE("A sphere is behind a ray"){
  Ray r = Ray(point(0, 0, 5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<double> xs = s.intersectionWith(r);
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
TEST_CASE("A sphere's default transformation"){
  Sphere s = Sphere();
  REQUIRE(s.transform_matrix == Matrix());
}

TEST_CASE("Changing a sphere's transformation"){
  Sphere s = Sphere();
  Matrix t = translation(2, 3, 4);
  s.set_transform(t);
  REQUIRE(s.transform_matrix == t);
}

TEST_CASE("Intersecting a scaled sphere with a ray"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  s.set_transform(scaling(2, 2, 2));
  std::vector<double> xs = s.intersectionWith(r);
  REQUIRE(xs == std::vector<double> {3, 7});
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0] == 3);
  REQUIRE(xs[1] == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  s.set_transform(translation(5, 0, 0));
  std::vector<double> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}
