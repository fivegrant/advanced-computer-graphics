#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "mechanics/include/ray.hpp"
#include "mechanics/include/hitrecord.hpp"
#include "utilities/include/epsilon.hpp"

class Shape;
class Intersection{
  public:
    double t;
    Ray ray;
    Shape* subject;
    Intersection (double raw_t, Ray raw_ray, Shape *shape):
      t(raw_t), ray(raw_ray), subject(shape) {}

    bool operator==(const Intersection& rhs) const;
    bool operator<(const Intersection& rhs) const;
    HitRecord generateHitRecord(std::vector<Intersection>) const;
};

double schlick(HitRecord hit);

//String Conversion
std::ostream& operator << (std::ostream& os, Intersection const& intersection);
#endif
