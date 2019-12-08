#ifndef WORLD_H
#define WORLD_H
#include <vector> 
#include <cmath> 
#include "objects/include/intersection.hpp"
#include "objects/include/light.hpp"
#include "objects/include/shape.hpp"

class World{
  public:
     std::vector<Shape*> objects; 
     std::vector<Light> lights;
     Light default_light = Light(point(-10,10,-10), color(1, 1, 1));
     double function_depth = 4;
     double remaining = 4;

    std::vector<Intersection> intersectionWith(Ray) const;
    double schlick(HitRecord);
    Tuple effective_reflective(Intersection, HitRecord, int);
    Tuple effective_refraction(Intersection, HitRecord, int);
    Tuple colorAtIntersection(Intersection, HitRecord, int);
    Tuple colorAtRay(Ray ray, int);
    Intersection hit(std::vector<Intersection> hits);
    bool shadow(Light light, Tuple overpoint);
    bool shadow(Tuple overpoint);
    void addShape(Shape*);
    void addLight(Light);

};

#endif  
