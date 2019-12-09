#ifndef PATTERN_H
#define PATTERN_H
#include "mechanics/include/matrix.hpp"
#include "utilities/include/pattern_functions.hpp"

class Pattern{
  public:
    Tuple color_a = color(1, 1, 1); 
    Tuple color_b = color(0, 0, 0);
    Matrix transform_matrix = Matrix();
    bool active = false;
    Tuple (*pattern_func)(Tuple, Tuple, Tuple) = &xyz;
    Pattern(){};  

    void set_transform(Matrix);
    Tuple pattern_at(Tuple point);
    Tuple pattern_at_shape(Tuple point_w, Matrix object_transfrom);
};

#endif
