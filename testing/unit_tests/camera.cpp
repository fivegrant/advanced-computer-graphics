//Custom Test Cases
//Feature: Camera

#include <cmath>
#include <string>
#include "modules/catch2.hpp"
#include "components/include/camera.hpp"
#include "objects/include/sphere.hpp"
#include "utilities/include/pi.hpp"
#include "utilities/include/epsilon.hpp"

TEST_CASE("The transformation matrix for the default orientation"){
   Tuple f = point(0, 0, 0);
   Tuple t = point(0, 0, -1);
   Tuple u = point(0, 1, 0);
   Matrix x = view_transform(f, t, u);
   REQUIRE(x == Matrix());
}

TEST_CASE("A view transformation matrix looking in positive z direction"){
   Tuple f = point(0, 0, 0);
   Tuple t = point(0, 0, 1);
   Tuple u = point(0, 1, 0);
   Matrix x = view_transform(f, t, u);
   REQUIRE(x == scaling(-1, 1, -1));
}

TEST_CASE("The view transformation moves the world"){
   Tuple f = point(0, 0, 8);
   Tuple t = point(0,0, 0);
   Tuple u = point(0, 1, 0);
   Matrix x = view_transform(f, t, u);
   REQUIRE(x == translation(0, 0, -8));
}

TEST_CASE("An arbitrary view transformation"){
   Tuple f = point(1, 3, 2);
   Tuple t = point(4,-2, 8);
   Tuple u = point(1, 1, 0);
   Matrix x = view_transform(f, t, u);
   REQUIRE(x.approx(Matrix({  -0.50709,  -0.50709,  0.67612,  -2.36643,
   			       0.76772,   0.60609,  0.12122,  -2.82843,
   			      -0.35857,   0.59761, -0.71714,   0.00000,
   			       0.00000,   0.00000,  0.00000,   1.00000,
			          })));
}

TEST_CASE("Constructing a camera"){
  Camera c = Camera(160, 120);
  c.set_fov(PI/3);
  REQUIRE(c.w == 160);
  REQUIRE(c.h == 120);
  REQUIRE(c.get_fov() ==  PI/3);
  REQUIRE(c.get_transform() == Matrix());
}

TEST_CASE("The pixel size for a horizontal canvas"){
  Camera c = Camera(200, 125);
  REQUIRE(abs(c.pixel_size() - 0.01) < EPSILON);
}

TEST_CASE("The pixel size for a vertical canvas"){
  Camera c = Camera(125, 200);
  REQUIRE((c.pixel_size() - 0.01) < EPSILON);
}

TEST_CASE("Constructing a ray through the center of the canvas"){
  Camera c = Camera(201, 101);
  Ray r = c.ray_at_pixel(100, 50);
  REQUIRE(r.origin == point(0, 0, 0));
  REQUIRE(r.direction == vector(0, 0, -1));
}

TEST_CASE("Constructing a ray through a corner of the canvas"){
  Camera c = Camera(201, 101);
  Ray r = c.ray_at_pixel(0, 0);
  REQUIRE(r.origin == point(0, 0, 0));
  REQUIRE(r.direction == vector(0.66519, 0.33259, -0.66851));
}

TEST_CASE("Constructing a ray when the camera is transformed"){
  Camera c = Camera(201, 101);
  c.set_transform(rotationy(PI/4) * translation(0, -2, 5));
  Ray r = c.ray_at_pixel(100, 50);
  REQUIRE(r.origin == point(0, 2, -5));
  REQUIRE(r.direction == vector(sqrt(2)/2, 0, -sqrt(2)/2));
}
TEST_CASE("Rendering a world with a camera"){
  World w = World();
  Sphere shape1 = DefaultSphere1();
  Sphere shape2 = DefaultSphere2();
  Camera c = Camera(11, 11);
  Tuple f = point(0, 0, -5);
  Tuple t = point(0, 0, 0);
  Tuple u = vector(0, 1, 0);
  c.set_transform(view_transform(f, t, u));
  Canvas image = c.render(w);
  REQUIRE(image.pixel_at(5, 5) == color(0.3806, 0.47583, 0.2855));
  
}
