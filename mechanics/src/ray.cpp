#include "../include/ray.hpp"

//Methods
Tuple Ray::pointAtT(float t) const
{
  return direction * t + origin;
}

