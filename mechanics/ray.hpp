#include "./tuple.hpp"

class Ray{
  public:
    //Ray Initialization
    Tuple origin, direction;

    //Constructor
    Ray(Tuple raw_origin, Tuple raw_direction):
      origin(raw_origin), direction(normalize(raw_direction)) {}

    //Operators
    Tuple pointAtT(float t) const;

};

//Methods
Tuple Ray::pointAtT(float t) const
{
  return direction * t + origin;
}
