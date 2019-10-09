#include "../include/plane.hpp"

std::vector<double> Plane::intersectionWith(Ray ray) const
{
  if(ray.direction.y == 0){
    return {}}
  }else{
    
    double t = -ray.origin/ray.direction;
    /*
      intersection.t = t
                  .obj = self
		  .ray = ray
		  return intersection
     */
    return t
  }
}
