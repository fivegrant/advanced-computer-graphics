//Feature: Triangle

#include <vector>
#include "modules/catch2.hpp"
#include "objects/include/triangle.hpp"

// Custom Test Cases
TEST_CASE("A ray strikes a triangle"){
  Ray r = Ray(point(0, 0.5, -2), vector(0, 0, 1));
  Triangle s = Triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
  std::vector<Intersection> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t == 2.0);
}

TEST_CASE("A ray misses the origin-axis1 edge"){
  Ray r = Ray(point(-1, 1, -2), vector(0, 0, 1));
  Triangle s = Triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
  std::vector<Intersection> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the axis1-axis2 edge"){
  Ray r = Ray(point(0, -1, -2), vector(0, 0, 1));
  Triangle s = Triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
  std::vector<Intersection> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the origin-axis2 edge"){
  Ray r = Ray(point(1, 1, -2), vector(0, 0, 1));
  Triangle s = Triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
  std::vector<Intersection> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray parallel to triangle"){
  Ray r = Ray(point(0, -1, -2), vector(0, 1, 0));
  Triangle s = Triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
  std::vector<Intersection> xs = s.intersectionWith(r);
  REQUIRE(xs.size() == 0);
}
