#include "objects/include/shape.hpp"

bool Shape::operator==(const Shape& rhs) const
{
  bool condition_type = this->shape_type == rhs.shape_type;
  bool condition_center = this->center == rhs.center;
  bool condition_material = this->material == rhs.material;
  bool condition_transform = this->transform_matrix == rhs.transform_matrix;
  return condition_type && condition_center && condition_material;
}

Tuple Shape::world_to_object(Tuple point){
  if(parent){
    return transform_matrix.inverse() * parent->world_to_object(point);
  }
  return transform_matrix.inverse() * point;
}

Tuple Shape::normal_to_world(Tuple normal_WorldFrame){
  Tuple point_BodyFrame = transform_matrix.inverse().transpose() * normal_WorldFrame;
  point_BodyFrame.w = 0;
  Tuple normal_BodyFrame = normalize(point_BodyFrame);

  if(parent){
    normal_BodyFrame = parent->normal_to_world(normal_BodyFrame);
    }
  
  return normal_BodyFrame;
 }

void Shape::set_transform(Matrix operation_matrix)
{
  transform_matrix = operation_matrix * transform_matrix;
  transform_matrix.inverse();
}

// Computes the normal to this shape at the point p_W in the world frame, W.
Tuple Shape::normalAtPoint(Tuple point_WorldFrame)
{
  
  Tuple point_BodyFrame = world_to_object(point_WorldFrame);
  Tuple normal_BodyFrame = localNormal(point_BodyFrame);
  return normal_to_world(normal_BodyFrame);
}

//String Conversion
std::ostream& operator << (std::ostream& os, Shape const& shape) {
    os << shape.shape_type + ": (" + std::to_string(shape.center.x) + ", " + std::to_string(shape.center.y) + ", " + std::to_string(shape.center.z) + ")";
    return os;
}

