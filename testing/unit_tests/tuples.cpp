//TestCasesWeek1.txt
//Feature: Tuples, Vectors, and Points

#include <cmath>
#include "modules/catch2.hpp"
#include "mechanics/include/tuple.hpp"

TEST_CASE("A tuple with w=1.0 is a point"){
  Tuple a{4.3, -4.2, 3.1, 1.0};
  REQUIRE(a.x == (double) 4.3);
  REQUIRE(a.y == (double) -4.2);
  REQUIRE(a.z == (double) 3.1);
  REQUIRE(a.w == (double) 1.0);
  REQUIRE(a.isPoint());
  REQUIRE(!a.isVector());
}

TEST_CASE("A tuple with w=0.0 is a vector"){
  Tuple a{4.3, -4.2, 3.1, 0.0};
  REQUIRE(a.x == (double) 4.3);
  REQUIRE(a.y == (double) -4.2);
  REQUIRE(a.z == (double) 3.1);
  REQUIRE(a.w == (double) 0.0);
  REQUIRE(!a.isPoint());
  REQUIRE(a.isVector());
}

TEST_CASE("point() creates tuples with w=1"){
  Tuple p{4, -4, 3, 1};
  REQUIRE(point(4, -4, 3) == p);
}

TEST_CASE("vector() creates tuples with w=0"){
  Tuple v{4, -4, 3, 0};
  REQUIRE(vector(4, -4, 3) == v);
}

TEST_CASE("Adding two tuples"){
  Tuple a1{3, -2, 5, 1};
  Tuple a2{-2, 3, 1, 0};
  REQUIRE(a1 + a2 == Tuple{1, 1, 6, 1});
}

TEST_CASE("Subtracting two points"){
  Tuple p1 = point(3, 2, 1);
  Tuple p2 = point(5, 6, 7);
  REQUIRE(p1 - p2 == vector(-2, -4, -6));
}

TEST_CASE("Subtracting a vector from a point"){
  Tuple p = point(3, 2, 1);
  Tuple v = vector(5, 6, 7);
  REQUIRE(p - v == point(-2, -4, -6));
}

TEST_CASE("Subtracting two vectors"){
  Tuple v1 = vector(3, 2, 1);
  Tuple v2 = vector(5, 6, 7);
  REQUIRE(v1 - v2 == vector(-2, -4, -6));
}

TEST_CASE("Subtracting a vector from the zero vector"){
  Tuple zero = vector(0, 0, 0);
  Tuple v = vector(1, -2, 3);
  REQUIRE(zero - v == vector(-1, 2, -3));
}

TEST_CASE("Negating a tuple"){
  Tuple a{1, -2, 3, -4};
  REQUIRE(-a == Tuple{-1, 2, -3, 4});
}

TEST_CASE("Multiplying a tuple by a scalar"){
  Tuple a{1, -2, 3, -4};
  REQUIRE(a * 3.5 == Tuple{3.5, -7, 10.5, -14});
}

TEST_CASE("Multiplying a tuple by a fraction"){
Tuple a{1, -2, 3, -4};
REQUIRE(a * .5 == Tuple{0.5, -1, 1.5, -2});
}

TEST_CASE("Dividing a tuple by a scalar"){
  Tuple a{1, -2, 3, -4};
  REQUIRE(a / 2 == Tuple{0.5, -1, 1.5, -2});
}

TEST_CASE("Computing the magnitude of vector(1, 0, 0)"){
  Tuple v = vector(1, 0, 0);
  REQUIRE(magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 1, 0)"){
  Tuple v = vector(0, 1, 0);
  REQUIRE(magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 0, 1)"){
  Tuple v = vector(0, 0, 1);
  REQUIRE(magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(1, 2, 3)"){
  Tuple v = vector(1, 2, 3);
  REQUIRE(magnitude(v) == (double) sqrt(14));
}

TEST_CASE("Computing the magnitude of vector(-1, -2, -3)"){
  Tuple v = vector(-1, -2, -3);
  REQUIRE(magnitude(v) == (double) sqrt(14));
}

TEST_CASE("Normalizing vector(4, 0, 0) gives (1, 0, 0)"){
  Tuple v = vector(4, 0, 0);
  REQUIRE(normalize(v) == vector(1, 0, 0));
}

TEST_CASE("Normalizing vector(1, 2, 3)"){
  Tuple v = vector(1, 2, 3);
  double s14 = sqrt(14);
  REQUIRE(normalize(v) == vector(1 / s14, 2 / s14, 3 / s14));
}

TEST_CASE("The magnitude of a normalized vector"){
  Tuple v = vector(1, 2, 3);
  Tuple norm = normalize(v);
  REQUIRE((double) magnitude(norm) == (double) 1);
}

TEST_CASE("The dot product of two tuples"){
  Tuple a = vector(1, 2, 3);
  Tuple b = vector(2, 3, 4);
  REQUIRE(dot(a, b) == 20);
}

TEST_CASE("The cross product of two vectors"){
  Tuple a = vector(1, 2, 3);
  Tuple b = vector(2, 3, 4);
  REQUIRE(cross(a, b) == vector(-1, 2, -1));
  REQUIRE(cross(b, a) == vector(1, -2, 1));
}

TEST_CASE("Adding colors"){
  Tuple c1 = color(0.9, 0.6, 0.75);
  Tuple c2 = color(0.7, .1, 0.25);
  REQUIRE(c1 + c2 == color(1.6, 0.7, 1.0));
}

TEST_CASE("Subtracting colors"){
  Tuple c1 = color(0.9, 0.6, 0.75);
  Tuple c2 = color(0.7, .1, 0.25);
  REQUIRE(c1 - c2 == color(0.2, 0.5, 0.5));
}

TEST_CASE("Multiplying a color by a scalar"){
  Tuple c = color(0.2, 0.3, 0.4);
  REQUIRE(c * 2 == color(0.4, 0.6, 0.8));
}

TEST_CASE("Multiplying colors"){
  Tuple c1 = color(1, 0.2, 0.4);
  Tuple c2 = color(0.9, 1, 0.1);
  REQUIRE(c1 * c2 == color(0.9, 0.2, 0.04));
}

// Custom Test Cases

TEST_CASE("Reflecting a vector approaching at 45 degrees"){
  Tuple v = vector(1, -1, 0);
  Tuple n = vector(0, 1, 0);
  Tuple r = v.reflect(n);
  REQUIRE(r == vector(1, 1, 0));
}

TEST_CASE("Reflecting a vector off a slanted surface"){
  Tuple v = vector(0, -1, 0);
  Tuple n = vector(sqrt(2)/2, sqrt(2)/2, 0);
  Tuple r = v.reflect(n);
  REQUIRE(r == vector(1, 0, 0));
}
