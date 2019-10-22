#ifndef PLANE_H
#define PLANE_H
#include "objects/include/shape.hpp"

class Plane: public Shape {
  public:
    Plane() {this->shape_type = "Plane";}

    std::vector<double> intersectionWith(Ray ray) const;
    Tuple normalAtPoint(Tuple position) const;

};

#endif
