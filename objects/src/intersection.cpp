#include "objects/include/intersection.h"

bool Intersection::operator==(const Intersection& rhs) const{
  return t == rhs.t && ray == rhs.ray && subject == rhs.subject;
}

HitRecord Intersection::generateHitRecord() const
{
  HitRecord generated;
  generated.hitPoint = ray.pointAtT(t);
  generated.normal = subject.normalAt(hitPoint);
  generated.eye = normalize(ray.origin - hitPoint);
  generated.inside = false;
  if(normal.dot(eye) < 0){
    generated.inside = true;
    generated.normal = generated.normal * -1;
    }
  generated.overpoint = hitPoint + normal * EPSILON;
  generated.underpoint = hitPoint - normal * EPSILON;
  return generated;
}
