//TestCasesWeek2.txt
//Feature: Materials
#include "modules/catch2.hpp"
#include "objects/include/material.hpp"
#include "objects/include/sphere.hpp"
#include "objects/include/light.hpp"
#include <cmath>

Material m = Material();
Tuple position = point(0.0, 0.0, 0.0);

TEST_CASE("The default material"){
  REQUIRE(m.surface_color == color(1.0, 1.0, 1.0));
  REQUIRE(m.diffuse == 0.9);
  REQUIRE(m.ambient == 0.1);
  REQUIRE(m.specular == 0.9);
  REQUIRE(m.shininess == 200);
}

TEST_CASE("Lighting with the eye between the light and the surface"){
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0.0, 0.0, -1.0);
  Light light = Light(point(0.0, 0.0, -10.0), color(1.0, 1.0, 1.0));
  Tuple result = m.colorAtPoint(light, position, eyev, normalv, Matrix(), false);
  REQUIRE(result == color(1, 1, 1));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°"){
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  Light light = Light(point(0, 10, -10), color(1, 1, 1));
  Tuple result = m.colorAtPoint(light, position, eyev, normalv, Matrix(), false);
  REQUIRE(result == color(.7364, .7364, .7364));
}

TEST_CASE("Lighting with the light behind the surface"){
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  Light light = Light(point(0, 0, 10), color(1, 1, 1));
  Tuple result = m.colorAtPoint(light, position, eyev, normalv, Matrix(), false);
  REQUIRE(result == color(0.1, 0.1, 0.1));
}

// Custom Test Cases

TEST_CASE("A pattern with an object transformation"){
  Sphere sphere = Sphere();
  sphere.set_transform(scaling(2, 2, 2));
  sphere.material.pattern.active = true;
  Tuple c = sphere.material.pattern.pattern_at_shape(point(2, 3, 4), sphere.transform_matrix);
  REQUIRE(c == color(1, 1.5, 2));
}

TEST_CASE("A pattern with a pattern transformation"){
  Sphere sphere = Sphere();
  sphere.material.pattern.active = true;
  sphere.material.pattern.set_transform(scaling(2, 2, 2));
  Tuple c = sphere.material.pattern.pattern_at_shape(point(2, 3, 4), sphere.transform_matrix);
  REQUIRE(c == color(1, 1.5, 2));
}

TEST_CASE("A pattern with both a pattern and object transformation"){
  Sphere sphere = Sphere();
  sphere.set_transform(scaling(2, 2, 2));
  sphere.material.pattern.active = true;
  sphere.material.pattern.set_transform(translation(.5, 1, 1.5));
  Tuple c = sphere.material.pattern.pattern_at_shape(point(2.5, 3, 3.5), 
    sphere.transform_matrix);
  REQUIRE(c == color(.75, 0.5, .25));
}

TEST_CASE("Transparency and Refractive Index for the default material"){
  Material m = Material();
  REQUIRE(m.transparency == 0);
  REQUIRE(m.ior == 1);
}
