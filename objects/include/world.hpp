#ifndef WORLD_H
#define WORLD_H
#include <vector> 
#include "objects/include/intersection.hpp"
#include "objects/include/light.hpp"
#include "objects/include/shape.hpp"

class World{
  public:
     vector<Shape> objects; 
     vector<Light> lights;

    vector<intersection> intersectionWith(Ray) const;
    Tuple colorAtIntersection(Intersection);
    void addShape(Shape);
    void addLight(Light);

};

#endif  
