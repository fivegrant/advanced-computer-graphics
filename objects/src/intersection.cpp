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
        //containers.erase(std::remove(containers.begin(), containers.end(), i.subject));
	std::vector<Shape*> hold = {};
	for(auto shape: containers){
	  if(i.subject != shape){
	    hold.push_back(shape);
	  }
	containers = hold;
	}
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

double schlick(HitRecord hit)
{
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
  double r0 = pow((hit.n1 - hit.n2)/(hit.n1 + hit.n2), 2);
  return r0 + (1 - r0) * pow(1 - cosine, 5);
}
//String Conversion
std::ostream& operator << (std::ostream& os, Intersection const& intersection) {
    os << "Intersection: " + std::to_string(intersection.t);
    return os;
}
