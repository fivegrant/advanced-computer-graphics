//Feature: Planes

#include <cmath>
#include <vector>
#include "modules/catch2.hpp"
#include "objects/include/plane.hpp"

//TestCasesWeek6.txt
TEST_CASE("The normal of a plane is constant everywhere"){
  Plane p = Plane();
  Tuple n1 = p.normalAtPoint(point(0, 0, 0));
  Tuple n2 = p.normalAtPoint(point(10, 0, -10));
  Tuple n3 = p.normalAtPoint(point(-5, 0, 150));
  REQUIRE(n1 == vector(0, 1, 0));
  REQUIRE(n2 == vector(0, 1, 0));
  REQUIRE(n3 == vector(0, 1, 0));
}

TEST_CASE("Intersect with a ray parallel to the plane"){
  Plane p = Plane();
  Ray r = Ray(point(0, 10, 0), vector(0, 0, 1));
  std::vector<Intersection> xs = p.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("Intersect with a coplanar ray"){
  Plane p = Plane();
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  std::vector<Intersection> xs = p.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray intersecting a plane from above"){
  Plane p = Plane();
  Ray r = Ray(point(0, 1, 0), vector(0, -1, 0));
  std::vector<Intersection> xs = p.intersectionWith(r);
  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t == 1);
  REQUIRE(xs[0].subject == &p);
}

TEST_CASE("A ray intersecting a plane from below"){
  Plane p = Plane();
  Ray r = Ray(point(0, -1, 0), vector(0, 1, 0));
  std::vector<Intersection> xs = p.intersectionWith(r);
  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t == 1);
  REQUIRE(xs[0].subject == &p);
}
