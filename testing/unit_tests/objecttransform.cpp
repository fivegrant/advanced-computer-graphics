//Feature: Objection Transformation

#include <cmath>
#include <vector>
#include "modules/catch2.hpp"
#include "mechanics/include/matrix.hpp"
#include "objects/include/sphere.hpp"
#include "objects/include/plane.hpp"
#include "objects/include/group.hpp"
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

//Custom Test Cases
TEST_CASE("Translating a shape"){
  Matrix translate = translation(1, 2, 3);
  Sphere s = Sphere();
  Plane p = Plane();
  s.set_transform(translate);
  p.set_transform(translate);
  std::vector<double> test_content = { 1, 0, 0, 1,
  				       0, 1, 0, 2,
				       0, 0, 1, 3,
				       0, 0, 0, 1 };
  REQUIRE(s.transform_matrix == Matrix(test_content));
  REQUIRE(p.transform_matrix == Matrix(test_content));
}

TEST_CASE("Scaling a plane"){
  Matrix scale = scaling(1, 2, 3);
  Sphere s = Sphere();
  Plane p = Plane();
  s.set_transform(scale);
  p.set_transform(scale);
  std::vector<double> test_content = { 1, 0, 0, 0,
  				       0, 2, 0, 0,
				       0, 0, 3, 0,
				       0, 0, 0, 1 };
  REQUIRE(s.transform_matrix == Matrix(test_content));
  REQUIRE(p.transform_matrix == Matrix(test_content));
}

TEST_CASE("Rotating a plane and a sphere"){
  Matrix xrotate = rotationx(0.25);
  Matrix yrotate = rotationy(0.50);
  Matrix zrotate = rotationz(0.75);
  Sphere s = Sphere();
  Plane p = Plane();
  s.set_transform(zrotate);s.set_transform(yrotate);s.set_transform(xrotate);
  p.set_transform(xrotate);p.set_transform(yrotate);p.set_transform(zrotate);
  Matrix sphere_test = (xrotate * yrotate) * zrotate;
  Matrix plane_test = (zrotate * yrotate) * xrotate;
  REQUIRE(s.transform_matrix.approx(sphere_test));
  REQUIRE(p.transform_matrix.approx(plane_test));
}

// Custom Test Cases
TEST_CASE("Converting a point from world to object space"){
  Group g1 = Group();
  g1.set_transform(rotationy(PI/2));
  Group g2 = Group();
  g2.set_transform(scaling(2, 2, 2));
  g1.addShape(&g2);
  Sphere s = Sphere();
  s.set_transform(translation(5, 0, 0));
  g2.addShape(&s);
  Tuple p = s.world_to_object(point(-2, 0, -10));
  REQUIRE(p == point(0, 0, -1));

}
TEST_CASE("Converting a normal from object to world space"){
  Group g1 = Group();
  g1.set_transform(rotationy(PI/2));
  Group g2 = Group();
  g2.set_transform(scaling(1, 2, 3));
  g1.addShape(&g2);
  Sphere s = Sphere();
  s.set_transform(translation(5, 0, 0));
  g2.addShape(&s);
  Tuple n = s.normal_to_world(vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  REQUIRE(g2.parent == &g1);
  REQUIRE(n == vector(.2857, .4286, -.8571));

}
TEST_CASE("Finding the normal on a child object"){
  Group g1 = Group();
  g1.shape_type = "DOOM";
  g1.set_transform(rotationy(PI/2));
  Group g2 = Group();
  g2.shape_type = "EMMA";
  g2.set_transform(scaling(1, 2, 3));
  g1.addShape(&g2);
  Sphere s = Sphere();
  s.set_transform(translation(5, 0, 0));
  g2.addShape(&s);
  Tuple n = s.normalAtPoint(point(1.7321, 1.1547, -5.5774));
  REQUIRE(g2.parent == &g1);
  REQUIRE(n == vector(.2857, .4286, -.8571));

}
