//Feature: Objection Transformation

#include <cmath>
#include <vector>
#include "modules/catch2.hpp"
#include "mechanics/include/matrix.hpp"
#include "utilities/include/pi.hpp"

//TestCasesWeek6.txt
TEST_CASE("Rotating a point around the x axis"){
  Tuple p = point(0, 1, 0);
  Matrix half_quarter = rotationx(PI / 4);
  Matrix full_quarter = rotationx(PI / 2);
  REQUIRE(half_quarter * p == point(0, sqrt(2)/2, sqrt(2)/2));
  REQUIRE(full_quarter * p == point(0, 0, 1));
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction"){
  Tuple p = point(0, 1, 0); 
  Matrix half_quarter = rotationx(PI / 4);
  Matrix inv = half_quarter.inverse();
  REQUIRE(inv * p == point(0, sqrt(2)/2, -sqrt(2)/2));
}

TEST_CASE("Rotating a point around the y axis"){
  Tuple p = point(0, 0, 1);
  Matrix half_quarter = rotationy(PI / 4);
  Matrix full_quarter = rotationy(PI / 2);
  REQUIRE(half_quarter * p == point(sqrt(2)/2, 0, sqrt(2)/2));
  REQUIRE(full_quarter * p == point(1, 0, 0));
}

TEST_CASE("Rotating a point around the z axis"){
  Tuple p = point(0, 1, 0);
  Matrix half_quarter = rotationz(PI / 4);
  Matrix full_quarter = rotationz(PI / 2);
  REQUIRE(half_quarter * p == point(-sqrt(2)/2, sqrt(2)/2, 0));
  REQUIRE(full_quarter * p == point(-1, 0, 0));
}
// Custom Test Cases
