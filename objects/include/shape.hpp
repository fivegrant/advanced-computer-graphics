#include <vector>
#include "../../mechanics/ray.hpp"
#include "../../mechanics/material.hpp"

class Shape{
  public:

    std::string shape_type = "Shape";
    Tuple center = point(0,0,0);
    Material material = Material();
    
    Shape() {}

    bool operator==(const Shape&) const;
    virtual std::vector<double> pointAtT(Ray ray) const = 0;
    Tuple normalAtPoint(Tuple position) const;

};


