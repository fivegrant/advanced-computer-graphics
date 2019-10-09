#include "../include/sphere.hpp"

std::vector<double> Sphere::intersectionWith(Ray raw_ray) const
{
  Ray ray = transform(raw_ray, this->transform_matrix.inverse());
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



