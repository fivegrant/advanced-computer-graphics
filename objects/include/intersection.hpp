#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "mechanics/include/ray.hpp"
#include "objects/include/shape.hpp"
#include "mechanics/include/hitrecord.hpp"
#include "utilities/include/epsilon.hpp"

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

//String Conversion
std::ostream& operator << (std::ostream& os, Intersection const& intersection) {
    os << "Intersection: " + std::to_string(intersection.t) + " on a " + intersection.subject.shape_type;
    return os;
}
#endif
