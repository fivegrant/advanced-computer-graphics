#include "../include/tuple.hpp"

//Operators
bool Tuple::operator==(const Tuple& rhs) const
{
  bool condition_x = abs(x - rhs.x) < EPSILON;
  bool condition_y = abs(y - rhs.y) < EPSILON;
  bool condition_z = abs(z - rhs.z) < EPSILON;
  bool condition_w = abs(w - rhs.w) < EPSILON;
  return condition_x && condition_y && condition_z && condition_w;
}

Tuple Tuple::operator+(const Tuple& rhs) const
{
  return Tuple(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Tuple Tuple::operator-(const Tuple& rhs) const
{
  return Tuple(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Tuple Tuple::operator*(const Tuple& rhs) const
{
  return Tuple(rhs.x * x, rhs.y * y, rhs.z * z, rhs.w * w);
}

Tuple Tuple::operator*(double scalar) const
{
  return Tuple(scalar * x, scalar * y, scalar * z, scalar * w);
}

Tuple Tuple::operator/(double scalar) const
{
  return Tuple((1/scalar) * x, (1/scalar) * y, (1/scalar) * z, (1/scalar) * w);
}

//Unary Operators
Tuple Tuple::operator-() const
{
  return Tuple(-x, -y, -z, -w);
}

//Methods
Tuple Tuple::reflect(Tuple over) const
{
  return -this + 2 * (this * over) * over;
}

double Tuple::dot(const Tuple& other) const
{
  double result = this->x * other.x;
  result += this->y * other.y;
  result += this->z * other.z;
  result += this->w * other.w;
  return result;
}

double Tuple::isPoint() const
{
  return this->w == 1;
}

double Tuple::isVector() const
{
  return this->w == 0;
}




