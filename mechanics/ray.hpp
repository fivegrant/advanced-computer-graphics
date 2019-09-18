#include <string>
#include "./tuple.hpp"

class Ray{
  public:
    //Ray Initialization
    Tuple origin, direction;

    //Constructor
    Ray(Tuple raw_origin, Tuple raw_direction):
      origin(raw_origin), direction(normalize(raw_direction)) {}

    //Methods
    Tuple pointAtT(float t) const;

};

//Methods
Tuple Ray::pointAtT(float t) const
{
  return direction * t + origin;
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
