//Feature: Intersections
#define CATCH_CONFIG_MAIN
#include <cmath>
#include <vector>
#include "../../modules/catch2.hpp"

//TestCasesWeek5.txt
TEST_CASE("An intersection encapsulates t and object"){
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
	And s ← sphere()
  When i ← intersection(3.5, s, r)
  Then i.t = 3.5
    And i.object = s
}

TEST_CASE("Precomputing the state of an intersection"){
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And shape ← sphere()
    And i ← intersection(4, shape)
  When hitRecord ← i.calculateHitRecord()
  Then hitRecord.point = point(0, 0, -1)
    And hitRecord.eye = vector(0, 0, -1)
    And hitRecord.normal = vector(0, 0, -1)             
}

TEST_CASE("The hit, when an intersection occurs on the outside"){
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And shape ← sphere()
    And i ← intersection(4, shape, r)
  When hitRecord ← calculateHitRecord(i, r)
  Then hitRecord.isInside = false
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
