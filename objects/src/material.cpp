#include "objects/include/material.hpp"

bool Material::operator==(const Material& rhs) const
{
  bool condition_1 = this->surface_color == rhs.surface_color;
  bool condition_2 = this->diffuse == rhs.diffuse;
  return condition_1 && condition_2;
}


