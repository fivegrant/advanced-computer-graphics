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
  transform_matrix.inverse();
}



// Computes the normal to this shape at the point p_W in the world frame, W.
Tuple Shape::normalAtPoint(Tuple point_WorldFrame)
{
  // position = point_WorldFrame
  // localNormal() requires the point to be in the body frame (B). So transform
  // the point from Frame W to Frame B.
  Tuple point_BodyFrame = transform_matrix.inverse() * point_WorldFrame;  
  Tuple normal_BodyFrame = localNormal(point_BodyFrame);

  // Transform the normal from Frame B back to Frame W. To do this, we need
  // the rotational component of X_WB because we want to change the normal to 
  // a different basis (W instead of B). We mimic this operation by zeroing the
  // w component of normal_B.
  normal_BodyFrame.w = 0;
  Tuple normal_WorldFrame = transform_matrix * normal_BodyFrame;

  // Since scaling can be incorporated into the transformation matrix, we have
  // to renormalize this vector.
  return normalize(normal_WorldFrame);
}

//String Conversion
std::ostream& operator << (std::ostream& os, Shape const& shape) {
    os << shape.shape_type + ": (" + std::to_string(shape.center.x) + ", " + std::to_string(shape.center.y) + ", " + std::to_string(shape.center.z) + ")";
    return os;
}

/*
#include <iostream>
#include <limits>
#include <numeric>
// Computes the normal to this shape at the point p_W in the world frame, W.
Tuple Shape::normalAtPoint(Tuple p_W)
{
  // Get the 4x4 matrix that transforms points from the body frame to the world
  // frame.
  Matrix X_WB = transform_matrix;

  // localNormal() requires the point to be in the body frame (B). So transform
  // the point from Frame W to Frame B.
  Tuple p_B = X_WB.inverse() * p_W;  
  Tuple normal_B = localNormal(p_B);
  assert(std::abs(magnitude(normal_B) - 1.0) < std::numeric_limits<double>::epsilon()); 

  // Transform the normal from Frame B back to Frame W. To do this, we need
  // the rotational component of X_WB because we want to change the normal to 
  // a different basis (W instead of B). We mimic this operation by zeroing the
  // w component of normal_B.
  normal_B.w = 0;
  Tuple normal_W = X_WB * normal_B;

  // Since scaling can be incorporated into the transformation matrix, we have
  // to renormalize this vector.
  return normalize(normal_W);
}

//String Conversion
std::ostream& operator << (std::ostream& os, Shape const& shape) {
    os << shape.shape_type + ": (" + std::to_string(shape.center.x) + ", " + std::to_string(shape.center.y) + ", " + std::to_string(shape.center.z) + ")";
    return os;
}
*/
