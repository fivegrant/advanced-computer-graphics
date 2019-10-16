#ifndef RAY_H
#define RAY_H
#include <string>
#include "./tuple.hpp"
#include "./matrix.hpp"

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
#endif
