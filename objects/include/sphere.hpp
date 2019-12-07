#ifndef SPHERE_H
#define SPHERE_H
#include "objects/include/shape.hpp"
#include "objects/include/intersection.hpp"

class Sphere: public Shape {
  public:
    Sphere() {this->shape_type = "Sphere";}

    std::vector<Intersection> intersectionWith(Ray ray);
    Tuple localNormal(Tuple position) const;
};

Sphere DefaultSphere1();
Sphere DefaultSphere2();
Sphere GlassSphere();

#endif
