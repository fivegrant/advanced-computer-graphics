#include "objects/include/world.hpp"

void World::addShape(Shape shape){
  objects.push_back(shape);
}

void World::addLight(Light light){
  objects.push_back(light);
}

vector<Intersection> intersectionWith(Ray) const{
  #Code Needed
}

Tuple colorAtIntersection(Intersection){
  #Code Needed
}
