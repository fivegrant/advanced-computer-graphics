#include <cmath>
#include <string>

const double EPSILON = .00001;

class Tuple{

  public:
    // Tuple Initializiation 
    double x, y, z, w;

    //Constructor
    Tuple () {};
    Tuple (double input_x = 0, double input_y = 0, double input_z = 0, double input_w = 0):
      x(input_x), y(input_y), z(input_z), w(input_w) {}

    //Operators
    bool operator==(const Tuple&) const;
    Tuple operator+(const Tuple& rhs) const;
    Tuple operator-(const Tuple& rhs) const;
    Tuple operator*(double scalar) const;
    Tuple operator/(double scalar) const;

    //Unary Operators
    Tuple operator-() const;

    //Methods
    //double dot(const Tuple& other) const;
    double isPoint() const;
    double isVector() const;

};

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
//double Tuple::dot(const Tuple& other) const
//{
//  double result = this->x * other.x;
//  result += this->y * other.y;
//  result += this->z * other.z;
//  result += this->w * other.w;
//  return result;
//}

double Tuple::isPoint() const
{
  return this->w == 1;
}

double Tuple::isVector() const
{
  return this->w == 0;
}

//FUNCTIONS NOT IN TUPLE CLASS

//Generators
Tuple point(const double x, const double y, const double z)
{
  return Tuple{x, y, z, 1.0};
}

Tuple vector(const double x, const double y, const double z)
{
  return Tuple{x, y, z, 0.0};
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
std::ostream& operator << ( std::ostream& os, Tuple const& tuple ) {
    os << "|" + std::to_string(tuple.x) + "," + std::to_string(tuple.y) + ","+ std::to_string(tuple.z) + "," + std::to_string(tuple.w) + "|";
    return os;
}
