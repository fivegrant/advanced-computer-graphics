#include <cmath>

class Tuple{

  public:
    // Tuple Initializiation 
    float x, y, z, w;

    //Constructor
    Tuple () {};
    Tuple (float input_x = 0, float input_y = 0, float input_z = 0, float input_w = 0):
      x(input_x), y(input_y), z(input_z), w(input_w) {}

    //Operators
    Tuple operator+(const Tuple& rhs) const;
    Tuple operator-(const Tuple& rhs) const;
    Tuple operator*(float scalar) const;
    Tuple operator/(float scalar) const;

    //Unary Operators
    Tuple operator-() const;

    //Methods
    //float dot(const Tuple& other) const;
    float isPoint() const;
    float isVector() const;

};

//Operators
Tuple Tuple::operator+(const Tuple& rhs) const
{
  return Tuple(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Tuple Tuple::operator-(const Tuple& rhs) const
{
  return Tuple(x - rhs.x, y - rhs.y, z - rhs.z, w + rhs.w);
}

Tuple Tuple::operator*(float scalar) const
{
  return Tuple(scalar * x, scalar * y, scalar * z, scalar * w);
}

Tuple Tuple::operator/(float scalar) const
{
  return Tuple((1/scalar) * x, (1/scalar) * y, (1/scalar) * z, (1/scalar) * w);
}

//Unary Operators
Tuple Tuple::operator-() const
{
  return Tuple(-x, -y, -z, -w);
}

//Methods
//float Tuple::dot(const Tuple& other) const
//{
//  float result = this->x * other.x;
//  result += this->y * other.y;
//  result += this->z * other.z;
//  result += this->w * other.w;
//  return result;
//}

float Tuple::isPoint() const
{
  return this->w == 1;
}

float Tuple::isVector() const
{
  return this->w == 0;
}

//FUNCTIONS NOT IN TUPLE CLASS

//Generators
Tuple point(const float x, const float y, const float z)
{
  return Tuple{x, y, z, 1.0};
}

Tuple vector(const float x, const float y, const float z)
{
  return Tuple{x, y, z, 0.0};
}

//Magnitude and Normalization
float magnitude(const Tuple vector)
{
  return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2) + pow(vector.w, 2));
}

Tuple normalize(const Tuple vec)
{
  float mag = magnitude(vec);
  return vector(vec.x, vec.y, vec.z);
}

float dot(const Tuple left, const Tuple right)
{
  float result = left.x * right.x;
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
