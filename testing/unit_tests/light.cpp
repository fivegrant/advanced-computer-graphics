//TestCasesWeek2.txt
//Feature: Lights
#define CATCH_CONFIG_MAIN
#include "modules/catch2.hpp"
#include "objects/include/light.hpp"

TEST_CASE("A point light has a position and intensity"){
  Tuple intensity = color(1, 1, 1);
  Tuple position = point(0, 0, 0);
  Light light = Light(); 
  light.point_light(position, intensity);
  REQUIRE(light.position == position);
  REQUIRE(light.intensity == intensity);

}
