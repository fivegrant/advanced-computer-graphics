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

double World::schlick(HitRecord hit){
  // find the cosine of the angle beween the eye and normal vectors
  double cosine = hit.eye.dot(hit.normal);

  // total internal reflection can only occur if n1 > n2
  if(hit.n1 > hit.n2){
    double n = hit.n1/hit.n2;
    double sin2_t = pow(n, 2.) * (1 - pow(cosine, 2.));
    if(sin2_t > 1){
      return 1;
    }
  
  // compute cosine of theta_t using trig identity
  double cos_t = sqrt(1 - sin2_t);
  
  // when n1 > n2, use cos(theta_t) instead
  cosine = cos_t;
  }
  double r0 = pow((hit.n1 = hit.n2)/(hit.n1 + hit.n2), 2);
  return r0 + (1 - r0) * pow(1 - cosine, 5);
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
  return color(0, 0, 0);//refraction causes segfault
  if(remaining < 0){
    remaining = 4;
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
    final_color = final_color + intersection.subject->material.colorAtPoint(light, hit.hitPoint, hit.eye, hit.normal, shadow(light, hit.overpoint));
      
}
  if (lights.size() == 0){
    final_color = final_color + intersection.subject->material.colorAtPoint(default_light, hit.hitPoint, hit.eye, hit.normal, shadow(default_light, hit.overpoint));; 
  }
  Tuple reflect_color = effective_reflective(intersection, hit, remaining);
  Tuple refract_color = effective_refraction(intersection, hit, remaining);
  remaining -= 1;

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

