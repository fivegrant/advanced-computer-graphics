#ifndef MATERIAL_H
#define MATERIAL_H
#include "../mechanics/include/tuple.hpp"

class Material{
  public:
    Tuple surface_color; 
    double diffuse, ambient, shininess, specular;

    Material(Tuple r_color, double r_diffuse):
      surface_color(r_color), diffuse(r_diffuse) {}

    Material() {
      surface_color = Tuple(1, 1, 1, 0);
      diffuse = 1;
      ambient = 1;
      specular = 1;
      shininess = 200;
    }

    bool operator==(const Material&) const;

};


#endif
