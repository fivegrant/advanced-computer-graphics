//Feature: Intersections
#include <cmath>
#include <vector>
#include "modules/catch2.hpp"
#include "objects/include/intersection.hpp"
#include "objects/include/sphere.hpp"

//TestCasesWeek5.txt
TEST_CASE("An intersection encapsulates t and object"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(3.5, r, &s);
  REQUIRE(i.t == 3.5);
  REQUIRE(i.subject == &s);
  REQUIRE(i.ray == r);
}

TEST_CASE("Precomputing the state of an intersection"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(4, r, &s);
  HitRecord hitRecord = i.generateHitRecord();
  REQUIRE(hitRecord.hitPoint == point(0, 0, -1));
  REQUIRE(hitRecord.eye == vector(0, 0, -1));
  REQUIRE(hitRecord.normal == vector(0, 0, -1));
}

TEST_CASE("The hit, when an intersection occurs on the outside"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(4, r, &s);
  HitRecord hitRecord = i.generateHitRecord();
  REQUIRE(hitRecord.isInside == false);
}

TEST_CASE("The hit, when an intersection occurs on the inside"){
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(1, r, &s);
  HitRecord hitRecord = i.generateHitRecord();
  REQUIRE(hitRecord.hitPoint == point(0, 0, 1));
  REQUIRE(hitRecord.eye == vector(0, 0, -1));
  REQUIRE(hitRecord.isInside == true);
      //normal would have been (0, 0, 1), but is inverted!
  REQUIRE(hitRecord.normal == vector(0, 0, -1));
}

//TestCasesWeek6.txt
TEST_CASE("The hit should offset the point"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  s.set_transform(translation(0, 0, 1));
  Intersection i = Intersection(5, r, &s);
  HitRecord comps = i.generateHitRecord();
  REQUIRE(comps.overpoint.z < -EPSILON/2);
  REQUIRE(comps.hitPoint.z > comps.overpoint.z);
}
