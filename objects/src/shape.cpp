#include <iostream>
#include <limits>
#include <numeric>

#include "objects/include/shape.hpp"

bool Shape::operator==(const Shape& rhs) const
{
  bool condition_type = this->shape_type == rhs.shape_type;
  bool condition_center = this->center == rhs.center;
  bool condition_material = this->material == rhs.material;
  bool condition_transform = this->transform_matrix == rhs.transform_matrix;
  return condition_type && condition_center && condition_material;
}


void Shape::set_transform(Matrix operation_matrix)
{
  transform_matrix = operation_matrix * transform_matrix;
  //transform_matrix = transform_matrix * operation_matrix; //delete
  transform_matrix.inverse();
}

Tuple Shape::normalAtPoint(Tuple position)
{
  Tuple local = localNormal(transform_matrix.inverse() * position);
  assert(std::abs(magnitude(local) - 1.0) < std::numeric_limits<double>::epsilon()); 
//return transform_matrix.inverse() * position; //delete
  //Tuple worldNormal = transform_matrix.inverse().transpose() * local ;
  Tuple worldNormal = transform_matrix.inverse().transpose() * local;
  assert(std::abs(magnitude(worldNormal) - 1.0) < std::numeric_limits<double>::epsilon()); 
  worldNormal.w = 0;
  return normalize(worldNormal);
}

//String Conversion
std::ostream& operator << (std::ostream& os, Shape const& shape) {
    os << shape.shape_type + ": (" + std::to_string(shape.center.x) + ", " + std::to_string(shape.center.y) + ", " + std::to_string(shape.center.z) + ")";
    return os;
}

