#define CATCH_CONFIG_MAIN
#include <cmath>
#include "../modules/catch2.hpp"
#include "../mechanics/tuple.hpp"


TEST_CASE("Tuples, Vectors, and Points Functional", "[point, tuple, vector]"){
  SECTION("A tuple with w=1.0 is a point"){
    Tuple a{4.3, -4.2, 3.1, 1.0};
    REQUIRE(a.x == (double) 4.3);
    REQUIRE(a.y == (double) -4.2);
    REQUIRE(a.z == (double) 3.1);
    REQUIRE(a.w == (double) 1.0);
    REQUIRE(a.isPoint());
    REQUIRE(!a.isVector());
    }

  SECTION("A tuple with w=0.0 is a vector"){
    Tuple a{4.3, -4.2, 3.1, 0.0};
    REQUIRE(a.x == (double) 4.3);
    REQUIRE(a.y == (double) -4.2);
    REQUIRE(a.z == (double) 3.1);
    REQUIRE(a.w == (double) 0.0);
    REQUIRE(!a.isPoint());
    REQUIRE(a.isVector());
    }

  SECTION("point() creates tuples with w=1"){
    Tuple p{4, -4, 3, 1};
    REQUIRE(point(4, -4, 3) == p);
    }

  SECTION("vector() creates tuples with w=0"){
    Tuple v{4, -4, 3, 0};
    REQUIRE(vector(4, -4, 3) == v);
    }

  SECTION("Adding two tuples"){
    Tuple a1{3, -2, 5, 1};
    Tuple a2{-2, 3, 1, 0};
    REQUIRE(a1 + a2 == Tuple{1, 1, 6, 1});
    }

  SECTION("Subtracting two points"){
    Tuple p1 = point(3, 2, 1);
    Tuple p2 = point(5, 6, 7);
    REQUIRE(p1 - p2 == vector(-2, -4, -6));
    }

  SECTION("Subtracting a vector from a point"){
    Tuple p = point(3, 2, 1);
    Tuple v = vector(5, 6, 7);
    REQUIRE(p - v == point(-2, -4, -6));
    }

  SECTION("Subtracting two vectors"){
    Tuple v1 = vector(3, 2, 1);
    Tuple v2 = vector(5, 6, 7);
    REQUIRE(v1 - v2 == vector(-2, -4, -6));
    }

  SECTION("Subtracting a vector from the zero vector"){
    Tuple zero = vector(0, 0, 0);
    Tuple v = vector(1, -2, 3);
    REQUIRE(zero - v == vector(-1, 2, -3));
    }

  SECTION("Negating a tuple"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(-a == Tuple{-1, 2, -3, 4});
    }

  SECTION("Multiplying a tuple by a scalar"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(a * 3.5 == Tuple{3.5, -7, 10.5, -14});
    }

  SECTION("Multiplying a tuple by a fraction"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(a * .5 == Tuple{0.5, -1, 1.5, -2});
    }

  SECTION("Dividing a tuple by a scalar"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(a / 2 == Tuple{0.5, -1, 1.5, -2});
    }

  SECTION("Computing the magnitude of vector(1, 0, 0)"){
    Tuple v = vector(1, 0, 0);
    REQUIRE(magnitude(v) == 1);
    }

  SECTION("Computing the magnitude of vector(0, 1, 0)"){
    Tuple v = vector(0, 1, 0);
    REQUIRE(magnitude(v) == 1);
    }

  SECTION("Computing the magnitude of vector(0, 0, 1)"){
    Tuple v = vector(0, 0, 1);
    REQUIRE(magnitude(v) == 1);
    }

  SECTION("Computing the magnitude of vector(1, 2, 3)"){
    Tuple v = vector(1, 2, 3);
    REQUIRE(magnitude(v) == (double) sqrt(14));
    }

  SECTION("Computing the magnitude of vector(1, 2, 3)"){
    Tuple v = vector(1, 2, 3);
    REQUIRE(magnitude(v) == (double) sqrt(14));
    }

  SECTION("Normalizing vector(4, 0, 0) gives (1, 0, 0)"){
    Tuple v = vector(4, 0, 0);
    REQUIRE(normalize(v) == vector(1, 0, 0));
    }

  SECTION("Normalizing vector(1, 2, 3)"){
    Tuple v = vector(1, 2, 3);
    double s14 = sqrt(14);
    REQUIRE(normalize(v) == vector(1 / s14, 2 / s14, 3 / s14));
    }

  SECTION("The magnitude of a normalized vector"){
    Tuple v = vector(1, 2, 3);
    Tuple norm = normalize(v);
    REQUIRE((double) magnitude(norm) == (double) 1);
    }

  SECTION("The dot product of two tuples"){
    Tuple a = vector(1, 2, 3);
    Tuple b = vector(2, 3, 4);
    REQUIRE(dot(a, b) == 20);
    }

  SECTION("The cross product of two vectors"){
    Tuple a = vector(1, 2, 3);
    Tuple b = vector(2, 3, 4);
    REQUIRE(cross(a, b) == vector(-1, 2, -1));
    REQUIRE(cross(b, a) == vector(1, -2, 1));
    }

  SECTION("Adding colors"){
    Tuple c1 = color(0.9, 0.6, 0.75);
    Tuple c2 = color(0.7, .1, 0.25);
    REQUIRE(c1 + c2 == color(1.6, 0.7, 1.0));
    }

  SECTION("Subtracting colors"){
    Tuple c1 = color(0.9, 0.6, 0.75);
    Tuple c2 = color(0.7, .1, 0.25);
    REQUIRE(c1 - c2 == color(0.2, 0.5, 0.5));
    }

  SECTION("Subtracting colors"){
    Tuple c1 = color(0.9, 0.6, 0.75);
    Tuple c2 = color(0.7, .1, 0.25);
    REQUIRE(c1 - c2 == color(0.2, 0.5, 0.5));
    }

  SECTION("Multiplying a color by a scalar"){
    Tuple c = color(0.2, 0.3, 0.4);
    REQUIRE(c * 2 == color(0.4, 0.6, 0.8));
    }

  SECTION("Multiplying colors"){
    Tuple c1 = color(1, 0.2, 0.4);
    Tuple c2 = color(0.9, 1, 0.1);
    REQUIRE(c1 * c2 == color(0.9, 0.2, 0.04));
    }


}
