#ifndef MATERIAL_H
#define MATERIAL_H
#include "mechanics/include/tuple.hpp"

class Material{
  public:
    Tuple surface_color; 
    double diffuse, ambient, shininess, specular, reflectivity, ior, transparency;

    Material(Tuple r_color, double r_diffuse):
      surface_color(r_color), diffuse(r_diffuse) {}

    Material() {
      surface_color = Tuple(1, 1, 1, 0);
      diffuse = 1;
      ambient = 1;
      specular = 1;
      shininess = 200;
      reflectivity = 1;
      ior = 1;
      transparency  = 1;
    }

    bool operator==(const Material&) const;

};

//String Conversion
std::ostream& operator << (std::ostream& os, Material const& material);
#endif
