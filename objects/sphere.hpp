#include <vector>
#include "./ray.hpp"
#include "./material.hpp"
#include "./shape.hpp"

class Sphere: public Object{
  public:
    Sphere() {this->object_type = "Sphere"}

    std::vector<double> pointAtT(Ray ray) const;
    Tuple normalAtPoint(Tuple position) const;

};

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

