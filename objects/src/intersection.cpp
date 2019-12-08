#include <algorithm>
#include "objects/include/intersection.hpp"
#include "objects/include/shape.hpp"

bool Intersection::operator==(const Intersection& rhs) const{
  return t == rhs.t && ray == rhs.ray && subject == rhs.subject;
}

bool Intersection::operator<(const Intersection& rhs) const{
  return t < rhs.t;
}

HitRecord Intersection::generateHitRecord(std::vector<Intersection> xs) const
{
  HitRecord generated;
  generated.hitPoint = ray.pointAtT(t);
  generated.normal = subject->normalAtPoint(generated.hitPoint);
  generated.eye = normalize(ray.origin - generated.hitPoint);
  generated.isInside = false;
  if(generated.normal.dot(generated.eye) < 0){
    generated.isInside = true;
    generated.normal = generated.normal * -1;
    }
  generated.reflectv = ray.direction.reflect(generated.normal);
  generated.overpoint = generated.hitPoint + (generated.normal * EPSILON);
  generated.underpoint = generated.hitPoint - (generated.normal * EPSILON);
  std::vector<Shape*> containers = {};
  for(auto i: xs){
    if(i == *this){
      if(containers.size() == 0){
	generated.n1 = 1;
      }else{
        generated.n1 = containers.back()->material.ior;
      }
    }

    if(containers.size() == 0){
      containers.push_back(i.subject);
    }
    else{
      if(*(std::find(containers.begin(), containers.end(), i.subject)) == i.subject){
        containers.erase(std::remove(containers.begin(), containers.end(), i.subject));
      }else{
        containers.push_back(i.subject);
      }
    }

    if(i == *this){
      if(containers.size() == 0){
        generated.n2 = 1;
      }else{
        generated.n2 = containers.back()->material.ior;
      }
      break;
    }
  }
  return generated;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Intersection const& intersection) {
    os << "Intersection: " + std::to_string(intersection.t);
    return os;
}
