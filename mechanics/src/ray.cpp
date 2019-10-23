#include "../include/ray.hpp"

bool Ray::operator==(const Ray& rhs) const
{
  return origin == rhs.origin && direction == rhs.direction;
}
//Methods
Tuple Ray::pointAtT(float t) const
{
  return direction * t + origin;
}

