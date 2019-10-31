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

//String Conversion
std::ostream& operator << (std::ostream& os, Light const& light) {
    os << "L[intensity: " + 
     std::to_string(light.intensity.x) + 
     std::to_string(light.intensity.y) +
     std::to_string(light.intensity.z) +
     std::to_string(light.intensity.w) +
     ", position: " + 
     std::to_string(light.position.x) + 
     std::to_string(light.position.y) +
     std::to_string(light.position.z) +
     std::to_string(light.position.w);
    return os;
}


