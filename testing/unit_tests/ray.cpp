//Feature: Rays

#define CATCH_CONFIG_MAIN
#include <cmath>
#include "../../modules/catch2.hpp"
#include "../../mechanics/ray.hpp"
#include "../../mechanics/matrix.hpp"

//TestCasesWeek1.txt
TEST_CASE("Scenario: Creating and querying a ray"){
  Tuple origin = point(1, 2, 3);
  Tuple direction = vector(4, 5, 6);
  Ray r = Ray(origin, direction);
  REQUIRE(r.origin == origin);
  //The bottom one doesn't work since I normalize when initialized
  //REQUIRE(r.direction == direction);
}

TEST_CASE("Computing a point from a distance"){
  Ray r = Ray(point(2, 3, 4), vector(1, 0, 0));
    REQUIRE(r.pointAtT(0) == point(2, 3, 4));
    REQUIRE(r.pointAtT(1) == point(3, 3, 4));
    REQUIRE(r.pointAtT(-1) == point(1, 3, 4));
    REQUIRE(r.pointAtT(2.5) == point(4.5, 3, 4));
}


//TestCasesWeek3.txt
TEST_CASE("Translating a ray"){
  Ray r = Ray(point(1, 2, 3), vector(0, 1, 0));
  Matrix m = translation(3, 4, 5);
  Ray r2 = transform(r, m);
  REQUIRE(r2.origin == point(4, 6, 8));
  REQUIRE(r2.direction == vector(0, 1, 0));
}

TEST_CASE("Scaling a ray"){
  Ray r = Ray(point(1, 2, 3), vector(0, 1, 0));
  Matrix m = scaling(2, 3, 4);
  Ray r2 = transform(r, m);
  REQUIRE(r2.origin == point(2, 6, 12));
  REQUIRE(r2.direction == vector(0, 3, 0));
}
