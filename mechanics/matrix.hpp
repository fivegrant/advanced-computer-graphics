#include <vector>
#include <cmath>
#include "../../mechanics/tuple.hpp"
class Matrix{

  public:
    // Tuple Initializiation 
    int size;
    std::vector<double> body;
    double det = 0;
    Matrix inverse_matrix, transposed_matrix = Matrix();
    bool invertible = false;
    //check to see if calculation has already been performed
    //determinant | inverse | transposed | invertible
    bool check [] = {false, false, false, false};
    
    //Constructor
     Matrix (std::vector<double> content):
      body(content) {
        size = sqrt(body);
      }
     Matrix ():
      {
        size = 2;
	body = {1, 0,
	        0, 1,}
      }

    //Operators
    bool operator==(const Matrix&) const;
    Matrix operator*(const Matrix& rhs) const;
    Tuple operator*(const Tuple& rhs) const;

    //Unary Operators
    //Tuple operator-() const;

    //Methods
    Matrix inverse();
    double det(); //determinant
    Matrix transpose();
    bool invertible();


};

//Operators
bool Matrix::operator==(const Matrix& rhs) const
{
  return this->body && rhs.body ;
}

Tuple Matrix::operator*(const Tuple& rhs) const
{
  return //finish
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
  return //finish
}


//Methods
double Matrix::det()
{
  return //
}

bool Matrix::invertible()
{
  return //
}

Matrix Matrix::transpose()
{
  return //
}

Matrix Matrix::inverse()
{
  return //
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

