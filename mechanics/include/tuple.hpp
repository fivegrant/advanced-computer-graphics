#ifndef TUPLE_H
#define TUPLE_H
#include <cmath>
#include <string>
#include "utilities/include/epsilon.hpp"

class Tuple{

  public:
    // Tuple Initializiation 
    double x, y, z, w;

    //Constructor
    Tuple (double input_x = 0, double input_y = 0, double input_z = 0, 
      double input_w = 0):
        x(input_x), y(input_y), z(input_z), w(input_w) {}

    //Operators
    bool operator==(const Tuple&) const;
    Tuple operator+(const Tuple& rhs) const;
    Tuple operator-(const Tuple& rhs) const;
    Tuple operator*(const Tuple& rhs) const;
    Tuple operator*(double scalar) const;
    Tuple operator/(double scalar) const;

    //Unary Operators
    Tuple operator-() const;

    //Methods
    Tuple reflect(Tuple over) const;
    double dot(const Tuple& other) const;
    double isPoint() const;
    double isVector() const;

};

//Generators
Tuple point(const double x, const double y, const double z)
{
  return Tuple{x, y, z, 1.0};
}

Tuple vector(const double x, const double y, const double z)
{
  return Tuple{x, y, z, 0.0};
}

Tuple color(const double x, const double y, const double z)
{
  return Tuple{x, y, z, 0.0};
}

Tuple color(const double x, const double y, const double z, bool is255)
{
  if(is255){
    return Tuple{x, y, z, 1.0};
  }else{
   return Tuple{x, y, z, 0.0};
  }
}
//Magnitude and Normalization
double magnitude(const Tuple vector)
{
  return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2) + pow(vector.w, 2));
}

Tuple normalize(const Tuple vec)
{
  double mag = magnitude(vec);
  return vector(vec.x/mag, vec.y/mag, vec.z/mag);
}

double dot(const Tuple left, const Tuple right)
{
  double result = left.x * right.x;
  result += left.y * right.y;
  result += left.z * right.z;
  result += left.w * right.w;
  return result;
}

Tuple cross(const Tuple left, const Tuple right)
{
 return Tuple{(left.y * right.z - left.z * right.y),
              (left.z * right.x - left.x * right.z),
	      (left.x * right.y - left.y * right.x)};
}

//String Conversion
std::ostream& operator << (std::ostream& os, Tuple const& tuple) {
    os << "|" + std::to_string(tuple.x) + "," + std::to_string(tuple.y) + ","+ std::to_string(tuple.z) + "," + std::to_string(tuple.w) + "|";
    return os;
}
#endif
