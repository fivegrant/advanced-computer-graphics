//Feature: Planes

#include <cmath>
#include <vector>
#include "modules/catch2.hpp"
#include "objects/include/plane.hpp"

//TestCasesWeek6.txt
/*
TEST_CASE("The normal of a plane is constant everywhere"){
  Plane p = Plane();
  When n1 ← local_normal_at(p, point(0, 0, 0))
    And n2 ← local_normal_at(p, point(10, 0, -10))
    And n3 ← local_normal_at(p, point(-5, 0, 150))
  Then n1 = vector(0, 1, 0)
    And n2 = vector(0, 1, 0)
    And n3 = vector(0, 1, 0)
}

TEST_CASE("Intersect with a ray parallel to the plane"){
  Plane p = Plane();
    And r ← ray(point(0, 10, 0), vector(0, 0, 1))
  When xs ← local_intersect(p, r)
  Then xs is empty
}

TEST_CASE("Intersect with a coplanar ray"){
  Plane p = Plane();
    And r ← ray(point(0, 0, 0), vector(0, 0, 1))
  When xs ← local_intersect(p, r)
  Then xs is empty
}

TEST_CASE("A ray intersecting a plane from above"){
  Plane p = Plane();
    And r ← ray(point(0, 1, 0), vector(0, -1, 0))
  When xs ← local_intersect(p, r)
  Then xs.count = 1
    And xs[0].t = 1
    And xs[0].object = p
}

TEST_CASE("A ray intersecting a plane from below"){
  Plane p = Plane();
    And r ← ray(point(0, -1, 0), vector(0, 1, 0))
  When xs ← local_intersect(p, r)
  Then xs.count = 1
    And xs[0].t = 1
    And xs[0].object = p
}
*/
