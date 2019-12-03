#ifndef RAY_H
#define RAY_H
#include <string>
#include "mechanics/include/tuple.hpp"
#include "mechanics/include/matrix.hpp"

class Ray{
  public:
    //Ray Initialization
    Tuple origin, direction;

    //Constructor
    Ray(Tuple raw_origin, Tuple raw_direction):
      origin(raw_origin), direction(normalize(raw_direction)) {}
    Ray(): origin(point(0, 0, 0)), direction(vector(0, 0, 0)){}
      
    bool operator==(const Ray& rhs) const;
    //Methods
    Tuple pointAtT(float t) const;

};
Ray transform(Ray ray, Matrix matrix);

std::ostream& operator << (std::ostream& os, Ray const& ray);
#endif
