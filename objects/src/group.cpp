#include "objects/include/group.hpp"

std::vector<Intersection> Group::intersectionWith(Ray raw_ray)
{
  std::vector<Intersection> intersections = {};
  for(Shape* shape: objects){
    std::vector<Intersection> hits = shape->intersectionWith(raw_ray);
    intersections.insert(intersections.end(), hits.begin(), hits.end());
    sort(intersections.begin(), intersections.end());
  }
  return intersections;
}

Tuple Group::localNormal(Tuple position) const
{
  std::cout << "SOMETHING HAS GONE HORRIBLY WRONG";
  return vector(0, 0, 0);
}

void Group::addShape(Shape* shape){
  shape->parent = this;
  objects.push_back(shape);
}
