#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "mechanics/include/ray.hpp"
#include "objects/include/sphere.hpp"
#include "objects/include/plane.hpp"
#include "mechanics/include/hitrecord.hpp"
#include "utilities/include/epsilon.hpp"

class Intersection{
  public:
    double t;
    Ray ray;
    //Shape *subject; <- I want to make 1 constructor that stores any shape here
    Sphere sphere;
    Plane plane;
    Intersection (double raw_t, Ray raw_ray, Sphere raw_sphere):
      t(raw_t), ray(raw_ray), sphere(raw_sphere) {}

    Intersection (double raw_t, Ray raw_ray, Plane raw_plane):
      t(raw_t), ray(raw_ray), plane(raw_plane) {}

    bool operator==(const Intersection& rhs) const;
    HitRecord generateHitRecord() const;
};

//String Conversion
std::ostream& operator << (std::ostream& os, Intersection const& intersection) {
    os << "Intersection: " + std::to_string(intersection.t);
    return os;
}
#endif
