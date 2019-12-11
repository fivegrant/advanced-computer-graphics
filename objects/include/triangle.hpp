#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "objects/include/shape.hpp"
#include "utilities/include/epsilon.hpp"

class Triangle: public Shape {
  public:
    Tuple origin, axis1, axis2;


    Triangle(Tuple input_a, Tuple input_b, Tuple input_c): 
      origin(input_a), axis1(input_b), axis2(input_c) {
      this->shape_type = "Triangle";
      }

    std::vector<Intersection> intersectionWith(Ray ray);
    Tuple localNormal(Tuple position) const;
};

#endif
