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
    std::list<double> pointAtT(Ray ray) const;

};

//Methods
std::list<double> Sphere::pointAtT(Ray ray) const
{
  Tuple o = ray.origin - point(0, 0, 0);
  double a = 1;
  double b = dot(ray.direction, o) * 2;
  double c = dot(o, o) - 1;
  double discriminant = pow(b, 2) - (4 * c);

  if (discriminant < 0){
    return std::list<double> {};
} else if (discriminant == 0){
    double t = -b/(2 * a);
    return std::list<double> {t, t};
} else {
    return std::list<double> {(-b - discriminant)/(2 * a), (-b + discriminant)/(2 * a)};
}
}

//String Conversion
std::ostream& operator << (std::ostream& os, Sphere const& sphere) {
    os << "(0)radius =" + std::to_string(sphere.radius) + "(0)";
    return os;
}
