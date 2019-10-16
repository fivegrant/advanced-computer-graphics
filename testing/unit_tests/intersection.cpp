//Feature: Intersections
#define CATCH_CONFIG_MAIN
#include <cmath>
#include <vector>
#include "../../modules/catch2.hpp"

//TestCasesWeek5.txt
TEST_CASE("An intersection encapsulates t and object"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(3.5, r, s);
  REQUIRE(i.t == 3.5);
  REQUIRE(i.object == s);
  REQUIRE(i.ray == r);
}

TEST_CASE("Precomputing the state of an intersection"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = intersection(4, s);
  HitRecord hitRecord = i.generateHitRecord();
  REQUIRE(hitRecord.point = point(0, 0, -1));
  REQUIRE(hitRecord.eye = vector(0, 0, -1));
  REQUIRE(hitRecord.normal = vector(0, 0, -1));
}

TEST_CASE("The hit, when an intersection occurs on the outside"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(4, r, s);
  HitRecord hitRecord = generateHitRecord(i, r);
  REQUIRE(hitRecord.isInside = false);
}

TEST_CASE("The hit, when an intersection occurs on the inside"){
  Given r ← ray(point(0, 0, 0), vector(0, 0, 1))
    And shape ← sphere()
    And i ← intersection(1, shape)
  When hitRecord ← calculateHitRecord(i, r)
  Then hitRecord.point = point(0, 0, 1)
    And hitRecord.eye = vector(0, 0, -1)
    And hitRecord.isInside = true
      # normal would have been (0, 0, 1), but is inverted!
    And hitRecord.normal = vector(0, 0, -1)
}

//TestCasesWeek6.txt
TEST_CASE("The hit should offset the point"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  s.transform(translation(0, 0, 1));
  Intersection i = intersection(5, shape)
  When comps ← prepare_computations(i, r)
  Then comps.over_point.z < -EPSILON/2
    And comps.point.z > comps.over_point.z
}

