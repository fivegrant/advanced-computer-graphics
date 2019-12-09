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


Tuple World::effective_reflective(Intersection i, HitRecord hit, int remaining){
  if (i.subject->material.reflective == 0 || remaining < 1){
    return color(0, 0, 0);
  }
  Ray reflect_ray = Ray(hit.overpoint, vector(0, 0, 0));
  reflect_ray.direction = hit.reflectv;
  Tuple found_color = colorAtRay(reflect_ray, remaining);
  return found_color * i.subject->material.reflective;
}

Tuple World::effective_refraction(Intersection i, HitRecord hit, int remaining){
  if(remaining < 1){
    return color(0, 0, 0);
  }
  if(i.subject->material.transparency == 0){
    return color(0, 0, 0);
  }
  double n_ratio = hit.n1/hit.n2;
  double cos_i = hit.eye.dot(hit.normal);
  double sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));
  if(sin2_t > 1){
    return color(0, 0, 0);
  }
  double cos_t = sqrt(1 - sin2_t);
  Tuple direction = hit.normal * (n_ratio * cos_i - cos_t) - hit.eye * n_ratio;
  Ray refracted_ray = Ray(hit.underpoint, vector(0, 0, 0));
  refracted_ray.direction = direction;
  Tuple refracted_color = colorAtRay(refracted_ray, remaining);

  return refracted_color * i.subject->material.transparency;

}


Tuple World::colorAtIntersection(Intersection intersection, HitRecord hit, int remaining){

  Tuple final_color = color(0, 0, 0);
  for(Light light: lights){
    final_color = final_color + intersection.subject->material.colorAtPoint(light, hit.hitPoint, hit.eye, hit.normal, intersection.subject->transform_matrix, shadow(light, hit.overpoint));
      
}
  if (lights.size() == 0){
    final_color = final_color + intersection.subject->material.colorAtPoint(default_light, hit.hitPoint, hit.eye, hit.normal, intersection.subject->transform_matrix, shadow(default_light, hit.overpoint)); 
  }
  remaining -= 1;
  Tuple reflect_color = effective_reflective(intersection, hit, remaining);
  Tuple refract_color = effective_refraction(intersection, hit, remaining);

  if(intersection.subject->material.reflective > 0 && intersection.subject->material.transparency > 0){
    double reflectance = intersection.schlick(hit);
    reflect_color = reflect_color * reflectance;
    refract_color = refract_color * (1 - reflectance);
  }
  return final_color + reflect_color + refract_color;
}

Tuple World::colorAtRay(Ray ray, int remaining){
  std::vector<Intersection> hits = intersectionWith(ray);
  if (hit(hits).t > 0){
      return colorAtIntersection(hit(hits), hit(hits).generateHitRecord(hits), remaining);
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
  return Intersection(-1, Ray(point(0, 0, 0), vector(0, 0, 0)),NULL);
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

