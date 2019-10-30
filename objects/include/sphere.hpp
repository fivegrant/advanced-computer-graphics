#ifndef SPHERE_H
#define SPHERE_H
#include "objects/include/shape.hpp"
#include "objects/include/intersection.hpp"

class Sphere: public Shape {
  public:
    Sphere() {this->shape_type = "Sphere";}

    Intersection intersectionWith(Ray ray) const;
    Tuple normalAtPoint(Tuple position) const;
};

#endif
