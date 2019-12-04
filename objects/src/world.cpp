#include "objects/include/world.hpp"

std::vector<Intersection> World::intersectionWith(Ray ray) const{
  std::vector<Intersection> intersections = {};
  for(Shape* shape: objects){
    std::vector<Intersection> hits = shape->intersectionWith(ray);
    intersections.insert(intersections.end(), hits.begin(), hits.end());
    sort(intersections.begin(), intersections.end());
  }
  return intersections;  
}

Tuple World::colorAtIntersection(Intersection intersection){

  HitRecord hit = intersection.generateHitRecord();
  Tuple final_color = color(0, 0, 0);
  for(Light light: lights){
    final_color = final_color + intersection.subject->material.colorAtPoint(light, hit.hitPoint, hit.eye, hit.normal, shadow(light, hit.overpoint));
}
  if (lights.size() == 0){
    final_color = final_color + intersection.subject->material.colorAtPoint(default_light, hit.hitPoint, hit.eye, hit.normal, shadow(default_light, hit.overpoint));; 
  }
  return final_color;
}

Tuple World::colorAtRay(Ray ray){
  if (hit(intersectionWith(ray)).t > 0){
      return colorAtIntersection(hit(intersectionWith(ray)));
      }
  return color(0, 0, 0);
}

//This will probably segfault without objects in world
Intersection World::hit(std::vector<Intersection> hits){
  for(auto i : hits){
  if (i.t > 0){
      return i;
      }
  }
  return Intersection(-1 ,Ray(point(0, 0, 0), vector(0, 0, 0)),NULL);
}

bool World::shadow(Light light, Tuple overpoint) {
  Tuple v = light.position - overpoint;
  double distance = magnitude(v);
  //ray automatically normalizes direction
  Ray r = Ray(overpoint, v);
  Intersection h = hit(intersectionWith(r));
  if(h.t > 0 && h.t < distance){
    return true;
  }else{
    return false; 
  }
}

bool World::shadow(Tuple overpoint) {
  Tuple v = default_light.position - overpoint;
  double distance = magnitude(v);
  //ray automatically normalizes direction
  Ray r = Ray(overpoint, v);
  Intersection h = hit(intersectionWith(r));
  if(h.t > 0 && h.t < distance){
    return true;
  }else{
    return false; 
  }
}
void World::addShape(Shape* shape){
  objects.push_back(shape);
}

void World::addLight(Light light){
  lights.push_back(light);
}

World default_world(){

}

