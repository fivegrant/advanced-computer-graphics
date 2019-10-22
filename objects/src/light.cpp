#include "objects/include/light.hpp"

void Light::point_light(Tuple new_position, Tuple new_intensity)
{
  this->position = new_position;
  this->intensity = new_intensity;
}

Tuple Light::colorAtPoint(Material material, Tuple position, Tuple normalv)
{
  //normalv = normal
  //hitPoint = position
  Tuple vectorToLight = this->position - position;
  Tuple unitVectorToLight = normalize(vectorToLight);
  double lightIntensity = normalv.dot(unitVectorToLight);
  Tuple result = this->intensity * lightIntensity * material.surface_color;
  result.x = (result.x >= 0) ? result.x : 0;
  result.y = (result.y >= 0) ? result.y : 0;
  result.z = (result.z >= 0) ? result.z : 0;
  return result;
}


