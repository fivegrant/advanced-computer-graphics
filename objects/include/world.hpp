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
     Light default_light = Light(point(0,0,-10), color(1, 1, 1));

    std::vector<Intersection> intersectionWith(Ray) const;
    Tuple colorAtIntersection(Intersection);
    Tuple colorAtRay(Ray ray);
    Intersection hit(std::vector<Intersection> hits);
    bool shadow(Light light, Tuple overpoint);
    bool shadow(Tuple overpoint);
    void addShape(Shape*);
    void addLight(Light);

};

#endif  
