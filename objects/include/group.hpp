#ifndef GROUP_H
#define GROUP_H
#include <vector> 
#include <cmath> 
#include "objects/include/shape.hpp"

class Group: public Shape{
  public:
    std::vector<Shape*> objects; 

    Group() {this->shape_type = "Group";}

    std::vector<Intersection> intersectionWith(Ray ray);
    Tuple localNormal(Tuple position) const;
    void addShape(Shape*);

};

#endif
