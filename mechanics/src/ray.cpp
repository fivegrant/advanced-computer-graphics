#include "../include/ray.hpp"

bool Ray::operator==(const Ray& rhs) const
{
  return origin == rhs.origin && direction == rhs.direction;
}
//Methods
Tuple Ray::pointAtT(float t) const
{
  return direction * t + origin;
}

Ray transform(Ray ray, Matrix matrix)
{
  Ray result = Ray(matrix * ray.origin, vector(0,0,0));
  Tuple direction_transform = (matrix * ray.direction);
  result.direction = direction_transform;
  return result;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Ray const& ray) {
    os << "[[origin: " + 
     std::to_string(ray.origin.x) + 
     std::to_string(ray.origin.y) +
     std::to_string(ray.origin.z) +
     std::to_string(ray.origin.w) +
     ", direction: " + 
     std::to_string(ray.direction.x) + 
     std::to_string(ray.direction.y) +
     std::to_string(ray.direction.z) +
     std::to_string(ray.direction.w);
    return os;
}
