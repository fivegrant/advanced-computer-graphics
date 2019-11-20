#include "objects/include/material.hpp"

bool Material::operator==(const Material& rhs) const
{
  bool condition_1 = this->surface_color == rhs.surface_color;
  bool condition_2 = this->diffuse == rhs.diffuse;
  return condition_1 && condition_2;
}

Tuple Material::colorAtPoint(Light light, Tuple position, Tuple normalv)
{
  //normalv = normal
  //hitPoint = position
  Tuple vectorToLight = light.position - position;
  Tuple unitVectorToLight = normalize(vectorToLight);
  double lightIntensity = normalv.dot(unitVectorToLight);
  Tuple result = light.intensity * lightIntensity * surface_color;
  result.x = (result.x >= 0) ? result.x : 0;
  result.y = (result.y >= 0) ? result.y : 0;
  result.z = (result.z >= 0) ? result.z : 0;
  return result;
}

std::ostream& operator << (std::ostream& os, Material const& material) {
    os << "M[surface_color: " + 
     std::to_string(material.surface_color.x) + 
     std::to_string(material.surface_color.y) +
     std::to_string(material.surface_color.z) +
     std::to_string(material.surface_color.w) +

          ", diffuse" +
     std::to_string(material.diffuse);
    return os;
}

