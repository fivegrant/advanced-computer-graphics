#define CATCH_CONFIG_MAIN
#include <cmath>
#include "../modules/catch2.hpp"
#include "../mechancis/tuple.h"


TEST_CASE("Tuples, Vectors, and Points Functional", "[point, tuple, vector]"){
  SECTION("A tuple with w=1.0 is a point"){
    Tuple a{4.3, -4.2, 3.1, 1.0};
    REQUIRE(a.x == 4.3);
    REQUIRE(a.y == -4.2);
    REQUIRE(a.z == 3.1);
    REQUIRE(a.w == 1.0);
    REQUIRE(a.isPoint());
    REQUIRE(!a.isVector());
    }

  SECTION("A tuple with w=0.0 is a vector"){
    Tuple a{4.3, -4.2, 3.1, 0.0};
    REQUIRE(a.x == 4.3);
    REQUIRE(a.y == -4.2);
    REQUIRE(a.z == 3.1);
    REQUIRE(a.w == 0.0);
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
    p1 = point(3, 2, 1);
    p2 = point(5, 6, 7);
    REQUIRE(p1 - p2 == vector(-2, -4, -6)});
    }

  SECTION("Subtracting a vector from a point"){
    p = point(3, 2, 1);
    v = vector(5, 6, 7);
    REQUIRE(p - v == point(-2, -4, -6)});
    }

  SECTION("Subtracting two vectors"){
    v1 = vector(3, 2, 1);
    v2 = vector(5, 6, 7);
    REQUIRE(v1 - v2 == vector(-2, -4, -6)});
    }

  SECTION("Subtracting a vector from the zero vector"){
    zero = vector(0, 0, 0);
    v = vector(1, -2, 3);
    REQUIRE(zero - v == vector(-1, 2, -3)});
    }

//Def not gonna work
  SECTION("Negating a tuple"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(-a == Tuple{-1, 2, -3, -4});
    }

  SECTION("Multiplying a tuple by a scalar"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(a * 3.5 == Tuple{3.5, -7, 10.5, -14});
    }


  SECTION("Multiplying a tuple by a fraction"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(a * .5 == Tuple{0.5, 1, 1.5, -2});
    }

//Def not gonna work
  SECTION("Dividing a tuple by a scalar"){
    Tuple a{1, -2, 3, -4};
    REQUIRE(a / 2 == Tuple{0.5, 1, 1.5, -2});
    }

//Def not gonna work
  SECTION("Computing the magnitude of vector(1, 0, 0)"){
    v = vector(1, 0, 0);
    REQUIRE(magnitude(v) == 1;
    }

//Def not gonna work
  SECTION("Computing the magnitude of vector(0, 1, 0)"){
    v = vector(0, 1, 0);
    REQUIRE(magnitude(v) == 1;
    }

//Def not gonna work
  SECTION("Computing the magnitude of vector(0, 0, 1)"){
    v = vector(0, 0, 1);
    REQUIRE(magnitude(v) == 1;
    }

//Def not gonna work
  SECTION("Computing the magnitude of vector(1, 2, 3)"){
    v = vector(1, 2, 3);
    REQUIRE(magnitude(v) == sqrt(14);
    }

//Def not gonna work
  SECTION("Computing the magnitude of vector(1, 2, 3)"){
    v = vector(1, 2, 3);
    REQUIRE(magnitude(v) == sqrt(14);
    }

//Def not gonna work
  SECTION("Normalizing vector(4, 0, 0) gives (1, 0, 0)"){
    v = vector(4, 0, 0);
    REQUIRE(normalize(v) == vector(1, 0, 0));
    }

//Def not gonna work
  SECTION("Normalizing vector(1, 2, 3)"){
    v = vector(1, 2, 3);
    s14 = sqrt(14)
    REQUIRE(normalize(v) == vector(s14, 2 * s14, 3 * s14));
    }

//Def not gonna work
  SECTION("The magnitude of a normalized vector"){
    v = vector(1, 2, 3);
    norm = normalize(v);
    REQUIRE(magnitude(norm) == 1));
    }

//Def not gonna work
  SECTION("The dot product of two tuples"){
    a = vector(1, 2, 3);
    b = vector(2, 3, 4);
    REQUIRE(dot(a, b) == 20));
    }

//Def not gonna work
  SECTION("The cross product of two vectors"){
    a = vector(1, 2, 3);
    b = vector(2, 3, 4);
    REQUIRE(cross(a, b) == vector(-1, 2, -1));
    REQUIRE(cross(b, a) == vector(1, -2, 1));
    }

}
