#include "utilities/include/pattern_functions.hpp"

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
  if((((int)floor(point.x) + (int)floor(point.y) + (int)floor(point.z)) % 2) == 0){
    return color_a;
  }else{
    return color_b;
  }
  }
