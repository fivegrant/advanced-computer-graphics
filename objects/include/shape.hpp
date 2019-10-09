#include <vector>
#include "../../mechanics/ray.hpp"
#include "../../mechanics/material.hpp"
#include "../../mechanics/matrix.hpp"

class Shape{
  public:

    std::string shape_type = "Shape";
    Tuple center = point(0,0,0);
    Matrix transform_matrix = Matrix();
    Material material = Material();
    
    Shape() {}

    bool operator==(const Shape&) const;
    Tuple normalAtPoint(Tuple position) const;
    void set_transform(Matrix);
    
    virtual std::vector<double> pointAtT(Ray ray) const = 0;

};


