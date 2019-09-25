#include <vector>
#include "./ray.hpp"

class Sphere{
  public:
    //Sphere Initialization
    double radius = 1; 
    Tuple center = point(0,0,0);
    ///Assume Sphere is centered out origin
    
    //Constructor
    Sphere() {}

    //Operators
    std::vector<double> pointAtT(Ray ray) const;
    Tuple normalAtPoint(Tuple position) const;

};

//Methods
std::vector<double> Sphere::pointAtT(Ray ray) const
{
  Tuple o = ray.origin - point(0, 0, 0);
  double a = 1;
  double b = dot(ray.direction, o) * 2;
  double c = dot(o, o) - 1;
  double discriminant = pow(b, 2) - (4 * c);

  if (discriminant < 0){
    return std::vector<double> {};
} else if (discriminant == 0){
    double t = -b/(2 * a);
    return std::vector<double> {t, t};
} else {
    discriminant = sqrt(discriminant);
    return std::vector<double> {(-b - discriminant)/(2 * a), (-b + discriminant)/(2 * a)};
}
}

Tuple Sphere::normalAtPoint(Tuple position) const
{
  return position - this->center;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Sphere const& sphere) {
    os << "(0)radius =" + std::to_string(sphere.radius) + "(0)";
    return os;
}
