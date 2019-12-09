#include "objects/include/plane.hpp"

std::vector<Intersection> Plane::intersectionWith(Ray raw_ray)
{
  Ray ray = transform(raw_ray, transform_matrix.get_inverse());
  if(ray.direction.y == 0){
    return {};
  }else{
    double t = -ray.origin.y/ray.direction.y;
    return {Intersection(t, raw_ray, this)};
  }
}

Tuple Plane::localNormal(Tuple position) const
{
  return vector(0, 1, 0);
}


