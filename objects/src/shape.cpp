#include "../include/shape.hpp"

bool Shape::operator==(const Shape& rhs) const
{
  bool condition_type = this->shape_type == rhs.shape_type;
  bool condition_center = this->center == rhs.center;
  bool condition_material = this->material == rhs.material;
  return condition_type && condition_center && condition_material;
}


Tuple Shape::normalAtPoint(Tuple position) const
{
  return position - this->center;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Shape const& shape) {
    os << shape.shape_type + ": (" + std::to_string(shape.center.x) + ", " + std::to_string(shape.center.y) + ", " + std::to_string(shape.center.z) + ")";
    return os;
}

