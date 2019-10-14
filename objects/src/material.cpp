#include "../include/material.hpp"

bool Material::operator==(const Material& rhs) const
{
  bool condition_1 = this->surface_color == rhs.surface_color;
  bool condition_2 = this->diffuse == rhs.diffuse;
  return condition_1 && condition_2;
}

//String Conversion
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
