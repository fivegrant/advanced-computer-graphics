#ifndef PLANE_H
#define PLANE_H
#include "objects/include/shape.hpp"

class Plane: public Shape {
  public:
    Plane() {this->shape_type = "Plane";}

    std::vector<Intersection> intersectionWith(Ray ray);
    Tuple localNormal(Tuple position) const;

};

#endif
