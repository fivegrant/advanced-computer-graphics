#include "objects/include/triangle.hpp"

std::vector<Intersection> Triangle::intersectionWith(Ray raw_ray)
{
  double beta, gamma, t;
  //Matrix answer = a - raw_ray; <- Tuple and Ray TODO: FIX THIS
  //Cramer's Rule
  Matrix denominator_matrix = Matrix({a.x - b.x, a.x - c.x, raw_ray.direction.x,
    				      a.y - b.y, a.y - c.y, raw_ray.direction.y,
    				      a.z - b.z, a.z - c.z, raw_ray.direction.z,
				     });
  double denominator_det = denominator_matrix.det();
  Matrix beta_matrix = denominator_matrix;
  beta_matrix.write(0, 0, denominator_matrix.retrieve(0, 0));
  beta_matrix.write(0, 1, denominator_matrix.retrieve(0, 1));
  beta_matrix.write(0, 2, denominator_matrix.retrieve(0, 2));

  Matrix gamma_matrix = denominator_matrix;
  gamma_matrix.write(1, 0, denominator_matrix.retrieve(1, 0));
  gamma_matrix.write(1, 1, denominator_matrix.retrieve(1, 1));
  gamma_matrix.write(1, 2, denominator_matrix.retrieve(1, 2));

  Matrix t_matrix = denominator_matrix;
  t_matrix.write(2, 0, denominator_matrix.retrieve(2, 0));
  t_matrix.write(2, 1, denominator_matrix.retrieve(2, 1));
  t_matrix.write(2, 2, denominator_matrix.retrieve(2, 2));
  
  beta = beta_matrix.det()/denominator_det;
  gamma = gamma_matrix.det()/denominator_det;
  t = t_matrix.det()/denominator_det;
  return {};
}

Tuple Triangle::localNormal(Tuple position) const
{
  return (b - a) * (c - a);
}

