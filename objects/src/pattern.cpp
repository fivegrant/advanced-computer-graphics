#include "objects/include/pattern.hpp"

void Pattern::set_transform(Matrix operation_matrix)
{
  transform_matrix = operation_matrix * transform_matrix;
  transform_matrix.inverse();
}

Tuple Pattern::pattern_at(Tuple point){
  return pattern_func(point, color_a, color_b);

}

//Takes point from world frame and returns color
Tuple Pattern::pattern_at_shape(Tuple point_w, Matrix object_transform){
  Tuple point_o = object_transform.inverse() * point_w;
  Tuple point_p = transform_matrix.inverse() * point_o;
  return pattern_at(point_p);
}
