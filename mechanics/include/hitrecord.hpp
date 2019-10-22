#ifndef HITRECORD_H
#define HITRECORD_H
#include "mechanics/include/tuple.hpp"
struct HitRecord {
  Tuple hitPoint;
  Tuple normal;
  Tuple eye;
  bool isInside;
  Tuple overpoint;
  Tuple underpoint;
  //double ior_i
  //double ior_t
};

#endif
