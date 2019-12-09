#include "utilities/include/pattern_functions.hpp"
#include <iostream>

Tuple xyz(Tuple point, Tuple color_a, Tuple color_b){
  return color(point.x, point.y, point.z);
  }

Tuple stripe(Tuple point, Tuple color_a, Tuple color_b){
  if(((int)floor(point.x) % 2) == 0){
    return color_a;
  }else{
    return color_b;
  }
  }

Tuple checker(Tuple point, Tuple color_a, Tuple color_b){
  if(((int)(floor(point.x) + floor(point.y) + floor(point.z)) % 2) == 0){
    return color_a;
  }else{
    return color_b;
  }
  }
