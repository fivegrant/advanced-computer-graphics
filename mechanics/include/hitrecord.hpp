#ifndef HITRECORD_H
#define HITRECORD_H
#include "mechanics/include/tuple.hpp"
struct HitRecord {
  Tuple hitPoint;
  Tuple normal;
  Tuple eye;
  Tuple reflectv;
  bool isInside;
  Tuple overpoint;
  Tuple underpoint;
  double n1;
  double n2;
};

#endif
