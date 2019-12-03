#ifndef WORLD_H
#define WORLD_H
#include <vector> 
#include "objects/include/intersection.hpp"
#include "objects/include/light.hpp"
#include "objects/include/shape.hpp"

class World{
  public:
     std::vector<Shape*> objects; 
     std::vector<Light> lights;

    std::vector<Intersection> intersectionWith(Ray) const;
    Tuple colorAtIntersection(Intersection);
    Tuple colorAtRay(Ray ray);
    void addShape(Shape*);
    void addLight(Light);

};

#endif  
