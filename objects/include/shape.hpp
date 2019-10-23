#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include "mechanics/include/ray.hpp"
#include "objects/include/material.hpp"

class Shape{
  public:

    std::string shape_type = "Shape";
    Tuple center = point(0,0,0);
    Matrix transform_matrix = Matrix();
    Material material = Material();
    
    Shape() {}

    bool operator==(const Shape&) const;
    void set_transform(Matrix);
    
    virtual std::vector<double> intersectionWith(Ray ray) const = 0;

    virtual Tuple normalAtPoint(Tuple position) const = 0;
};

#endif
