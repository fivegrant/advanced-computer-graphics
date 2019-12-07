#include "objects/include/sphere.hpp"

std::vector<Intersection> Sphere::intersectionWith(Ray raw_ray)
{
  Ray ray = transform(raw_ray, this->transform_matrix.get_inverse());
  Tuple o = ray.origin - point(0, 0, 0);
  double a = dot(ray.direction, ray.direction);
  double b = dot(ray.direction, o) * 2;
  double c = dot(o, o) - 1;
  double discriminant = pow(b, 2) - (4 * a * c);

  if (discriminant < 0){
    return std::vector<Intersection> {};
} else if (discriminant == 0){
    double t = -b/(2 * a);
    Intersection result = Intersection(t, raw_ray, this);
    return std::vector<Intersection> {result, result};
} else {
    discriminant = sqrt(discriminant);
    return std::vector<Intersection> {
     Intersection((-b - discriminant)/(2 * a), raw_ray, this), Intersection((-b + discriminant)/(2 * a), raw_ray, this)};
}
}

Tuple Sphere::localNormal(Tuple position) const
{
  return normalize(position - center);
}

Sphere DefaultSphere1(){
  Sphere s = Sphere();
  s.material.surface_color = color(0.8, 1, 0.6);
  s.material.diffuse = 0.7;
  s.material.specular = 0.2;
  s.material.shininess = 200;
  s.material.ambient = 0.1;
  return s;
}

Sphere DefaultSphere2(){
  Sphere s = Sphere();
  s.set_transform(scaling(0.5, 0.5, 0.5));
  s.material.surface_color = color(1, 1, 1);
  s.material.diffuse = 0.9;
  s.material.specular = 0.9;
  s.material.shininess = 200;
  s.material.ambient = 0.1;
  return s;
}

Sphere GlassSphere(){
  Sphere s = Sphere();
  s.material.ior = 1.5;
  s.material.transparency = 1;
  return s;
}
