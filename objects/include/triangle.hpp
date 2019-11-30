#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "objects/include/shape.hpp"

class Triangle: public Shape {
  public:
    Tuple a, b, c;
    Tuple origin, axis1, axis2;


    Triangle(Tuple input_a, Tuple input_b, Tuple input_c): 
      a(input_a), b(input_b), c(input_c) {
      this->shape_type = "Triangle";
      origin = a;
      axis1 = b - origin;
      axis2 = a - origin;
      }

    std::vector<double> intersectionWith(Ray ray) const;
    Tuple localNormal(Tuple position) const;
};

#endif
