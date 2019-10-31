#ifndef LIGHT_H
#define LIGHT_H
#include "mechanics/include/tuple.hpp"
#include "objects/include/material.hpp"

class Light{
  public:
    Tuple position, intensity;

    Light(Tuple raw_position, Tuple raw_intensity):
      position(raw_position), intensity(raw_intensity) {}

    Light() {
      position = Tuple(0, 0, 0, 1);
      intensity = Tuple(0, 0, 0, 0);
    }

    void point_light(Tuple, Tuple);
    Tuple colorAtPoint(Material material, Tuple position, Tuple normalv);

};

//String Conversion
std::ostream& operator << (std::ostream& os, Light const& light);
#endif
