#include "objects/include/plane.hpp"

std::vector<Intersection> Plane::intersectionWith(Ray ray) //const
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
    return {Intersection(t, ray, this)};
  }

}

Tuple Plane::normalAtPoint(Tuple position) const
{
  return vector(0, 1, 0);
}


