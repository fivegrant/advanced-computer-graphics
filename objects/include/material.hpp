#ifndef MATERIAL_H
#define MATERIAL_H
#include "mechanics/include/tuple.hpp"
#include "objects/include/light.hpp"

class Material{
  public:
    Tuple surface_color; 
    double diffuse, ambient, shininess, specular, reflective, ior, transparency;

    Material(Tuple r_color, double r_diffuse):
      surface_color(r_color), diffuse(r_diffuse){}

    Material() {
      surface_color = Tuple(1, 1, 1, 0);
      diffuse = .9;
      ambient = .1;
      specular = .9;
      shininess = 200;
      reflective = 0;
      ior = 1;
      transparency  = 0;
    }

    bool operator==(const Material&) const;
    Tuple colorAtPoint(Light light, Tuple position, Tuple eyev, Tuple normalv, bool in_shadow);
};

//String Conversion
std::ostream& operator << (std::ostream& os, Material const& material);
#endif
