#ifndef HITRECORD_H
#define HITRECORD_H
struct HitRecord {
  Tuple hitPoint;
  Tuple normal;
  Tuple eye;
  Tuple overpoint;
  bool isInside;
}

#endif
