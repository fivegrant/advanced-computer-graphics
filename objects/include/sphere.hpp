#ifndef SPHERE_H
#define SPHERE_H
#include "objects/include/shape.hpp"

class Sphere: public Shape {
  public:
    Sphere() {this->shape_type = "Sphere";}

    std::vector<double> intersectionWith(Ray ray) const;
    Tuple normalAtPoint(Tuple position) const;
};

#endif
