#include <list>
#include "./ray.hpp"

class Sphere{
  public:
    //Sphere Initialization
    double radius = 1; 
    ///Assume Sphere is centered out origin
    
    //Constructor
    Sphere() {}

    //Operators
    std::list<double> intersectionsWith(Ray ray) const;

};

//Methods
std::list<double> Sphere::pointAtT(Ray ray) const
{
  o = ray.origin - point(0, 0, 0);
  a = 1;
  b = dot(ray.direction, o) * 2;
  c = dot(o, o) - 1;
  discriminant = pow(b, 2) - (4 * c);

  if (discriminant < 0){
    return [];
} else if (discriminant == 0){
    t = -b/(2 * a)
    return [t, t]
} else {
    return [(-b - discriminant)/(2 * a), (-b + discriminant)/(2 * a)]
}
