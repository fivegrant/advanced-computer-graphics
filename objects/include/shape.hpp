#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include <iostream>
#include "mechanics/include/ray.hpp"
#include "objects/include/material.hpp"
#include "objects/include/intersection.hpp"

class Shape{
  public:

    std::string shape_type = "Shape";
    Tuple center = point(0,0,0);
    Matrix transform_matrix = Matrix();
    Material material = Material();
    Shape* parent = NULL;
    
    Shape() {}

    bool operator==(const Shape&) const;
    void set_transform(Matrix);
    
    Tuple world_to_object(Tuple point);
    Tuple normal_to_world(Tuple normal);
    virtual Tuple normalAtPoint(Tuple position);

    virtual std::vector<Intersection> intersectionWith(Ray ray) = 0;
    virtual Tuple localNormal(Tuple position) const = 0;
};

#endif
