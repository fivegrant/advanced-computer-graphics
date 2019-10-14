#include "../include/plane.hpp"

std::vector<double> Plane::intersectionWith(Ray ray) const
{
  if(ray.direction.y == 0){
    return {};
  }else{
    double t = -ray.origin.y/ray.direction.y;
    /*
      intersection.t = t
                  .obj = self
		  .ray = ray
		  return intersection
     */
    return {t};
  }

}

Tuple Plane::normalAtPoint(Tuple position) const
{
  return vector(0, 1, 0);
}


