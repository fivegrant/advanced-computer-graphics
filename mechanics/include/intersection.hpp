#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "../../mechanics/include/hitrecord.hpp"
#include "../../utilities/include/epsilon.hpp"

class Intersection{
  public:
    double t;
    Ray ray;
    Shape subject;

    Tuple (double raw_t, Ray raw_ray, Shape raw_shape):
      t(raw_t), ray(raw_ray), subject(raw_shape) {}

    bool operator==(const Intersection& rhs) const;
    HitRecord generateHitRecord() const;
};
#endif
