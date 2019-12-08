//Feature: Intersections
#include <cmath>
#include <vector>
#include "modules/catch2.hpp"
#include "objects/include/intersection.hpp"
#include "objects/include/sphere.hpp"

std::vector<Intersection> empty = {};
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
  HitRecord hitRecord = i.generateHitRecord(empty);
  REQUIRE(hitRecord.hitPoint == point(0, 0, -1));
  REQUIRE(hitRecord.eye == vector(0, 0, -1));
  REQUIRE(hitRecord.normal == vector(0, 0, -1));
}

TEST_CASE("The hit, when an intersection occurs on the outside"){
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(4, r, &s);
  HitRecord hitRecord = i.generateHitRecord(empty);
  REQUIRE(hitRecord.isInside == false);
}

TEST_CASE("The hit, when an intersection occurs on the inside"){
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  Sphere s = Sphere();
  Intersection i = Intersection(1, r, &s);
  HitRecord hitRecord = i.generateHitRecord(empty);
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
  HitRecord comps = i.generateHitRecord(empty);
  REQUIRE(comps.overpoint.z < -EPSILON/2);
  REQUIRE(comps.hitPoint.z > comps.overpoint.z);
}

// Custom Test Cases
TEST_CASE("Finding n1 and n2 at varios intersections"){
  Sphere a = GlassSphere();
  a.set_transform(scaling(2, 2, 2));
  Sphere b = GlassSphere();
  b.set_transform(translation(0, 0, -0.25));
  b.material.ior = 2;
  Sphere c = GlassSphere();
  c.set_transform(translation(0, 0, 0.25));
  c.material.ior = 2.5;
  Ray r = Ray(point(0, 0, -4), vector(0, 0, 0));
  r.direction = vector(0, 0, 1);
  std::vector<Intersection> xs = { Intersection(2.00, r, &a),
				   Intersection(2.75, r, &b),
				   Intersection(3.25, r, &c),
				   Intersection(4.75, r, &b),
				   Intersection(5.25, r, &c),
				   Intersection(6.00, r, &a),
  						   };
  SECTION("Generate HitRecord for Index 0"){
    HitRecord h = xs[0].generateHitRecord(xs);
    REQUIRE(h.n1 == 1);
    REQUIRE(h.n2 == 1.5);
  }

  SECTION("Generate HitRecord for Index 1"){
    HitRecord h = xs[1].generateHitRecord(xs);
    REQUIRE(h.n1 == 1.5);
    REQUIRE(h.n2 == 2);
  }

  SECTION("Generate HitRecord for Index 2"){
    HitRecord h = xs[2].generateHitRecord(xs);
    REQUIRE(h.n1 == 2);
    REQUIRE(h.n2 == 2.5);
  }

  SECTION("Generate HitRecord for Index 3"){
    HitRecord h = xs[3].generateHitRecord(xs);
    REQUIRE(h.n1 == 2.5);
    REQUIRE(h.n2 == 2.5);
  }

  SECTION("Generate HitRecord for Index 4"){
    HitRecord h = xs[4].generateHitRecord(xs);
    REQUIRE(h.n1 == 2.5);
    REQUIRE(h.n2 == 1.5);
  }

  SECTION("Generate HitRecord for Index 5"){
    HitRecord h = xs[5].generateHitRecord(xs);
    REQUIRE(h.n1 == 1.5);
    REQUIRE(h.n2 == 1);
  }
}
