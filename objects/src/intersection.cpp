#include "objects/include/intersection.hpp"
#include "objects/include/shape.hpp"

bool Intersection::operator==(const Intersection& rhs) const{
  return t == rhs.t && ray == rhs.ray && subject == rhs.subject;
}

bool Intersection::operator<(const Intersection& rhs) const{
  return t < rhs.t;
}

HitRecord Intersection::generateHitRecord() const
{
  HitRecord generated;
  generated.hitPoint = ray.pointAtT(t);
  generated.normal = subject->normalAtPoint(generated.hitPoint);
  generated.eye = normalize(ray.origin - generated.hitPoint);
  generated.isInside = false;
  if(generated.normal.dot(generated.eye) < 0){
    generated.isInside = true;
    generated.normal = generated.normal * -1;
    }
  generated.overpoint = generated.hitPoint + (generated.normal * EPSILON);
  generated.underpoint = generated.hitPoint - (generated.normal * EPSILON);
  return generated;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Intersection const& intersection) {
    os << "Intersection: " + std::to_string(intersection.t);
    return os;
}
