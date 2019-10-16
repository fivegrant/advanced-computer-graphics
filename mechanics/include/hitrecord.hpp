#ifndef HITRECORD_H
#define HITRECORD_H
struct HitRecord {
  Tuple hitPoint;
  Tuple normal;
  Tuple eye;
  bool isInside;
  Tuple overpoint;
  Tuple underpoint;
  //double ior_i
  //double ior_t
}

#endif
