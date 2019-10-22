//TestCasesWeek2.txt
//Feature: Materials
#include "modules/catch2.hpp"
#include "mechanics/include/material.cpp"
#include "mechanics/include/light.hpp"
#include <cmath>

Material m = Material();
Tuple position = point(0.0, 0.0, 0.0);

TEST_CASE("The default material"){
  REQUIRE(m.surface_color == color(1.0, 1.0, 1.0));
  REQUIRE(m.diffuse == 1);
}

TEST_CASE("Lighting with the eye between the light and the surface"){
  Tuple normalv = vector(0.0, 0.0, -1.0);
  Light light = Light(point(0.0, 0.0, -10.0), color(1.0, 1.0, 1.0));
  Tuple result = light.colorAtPoint(m, position, normalv);
  REQUIRE(result == color(1.0, 1.0, 1.0));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°"){
  Tuple normalv = vector(0, 0, -1);
  Light light = Light(point(0, 10, -10), color(1, 1, 1));
  Tuple result = light.colorAtPoint(m, position, normalv);
  REQUIRE(result == color(sqrt(2)/2, sqrt(2)/2, sqrt(2)/2));
}

TEST_CASE("Lighting with the light behind the surface"){
  Tuple normalv = vector(0, 0, -1);
  Light light = Light(point(0, 0, 10), color(1, 1, 1));
  Tuple result = light.colorAtPoint(m, position, normalv);
  REQUIRE(result == color(0, 0, 0));
}
