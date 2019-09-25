#include <vector>
#include <cmath>
#include "../../mechanics/tuple.hpp"
class Matrix4x4{

  public:
    double body [];
    double determinant = 0;
    Matrix inverse_matrix, transposed_matrix = Matrix();
    bool invertible = false;
    //check to see if calculation has already been performed
    //determinant | inverse | transposed | invertible
    bool check [] = {false, false, false, false};
    
    //Constructor
     Matrix (std::vector<double> content):
      body(content) {}
     Matrix ():
      {
	body = {1, 0, 0, 0,
	        0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1}
      }

    //Operators
    bool operator==(const Matrix&) const;
    Matrix operator*(const Matrix& rhs) const;
    Tuple operator*(const Tuple& rhs) const;
    //source for bracket overloading: https://stackoverflow.com/questions/11066564/overload-bracket-operators-to-get-and-set
    //index min: 1 & index max:4
    double operator [](int location [2]) const {};
    double & operator [](int location [2]) {};

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

double Matrix::operator [](int location [2]) const 
{
  return body[(location[0] - 1) * 4 + location[1] - 1]
}

double & operator [](int location [2]) 
{
  return body[(location[0] - 1) * 4 + location[1] - 1]
}

//Methods
int Matrix::size() const
{
  return sqrt(this->body.size());
}

double Matrix::det()
{
  //check if det is stored
  if(this->check[0])
  {
    return this->determinant;
  }
  else{
  double determinant = 0;
  //item in 3rd column * (ac - bd)
  sub_a = this[{3, 1}] * (this[{1, 2}] * this[{2, 3}] - this[{1, 3}] * this[{2, 2}]);
  sub_b = -(this[{3, 2}] * (this[{1, 1}] * this[{2, 3}] - this[{1, 3}] * this[{2, 1}]));
  sub_c = this[{3, 3}] * (this[{1, 1}] * this[{2, 2}] - this[{1, 2}] * this[{2, 1}]);
  result = this[{4,4}] * (sub_a + sub_b + sub_c);
  this->check[0] = true;
  this->determinant = result;
  if(result ==0)
  {
    check[1] = true;
    check[3] = true;
  }
  return result;
  }
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

//String Conversion
std::ostream& operator << (std::ostream& os, Matrix const& matrix) {
    std::string output = "";
    output = "|" + matrix.body[0] +  matrix.body[1] + matrix.body[2] + matrix.body[3] + "\n"
		+ matrix.body[4] +  matrix.body[5] + matrix.body[6] + matrix.body[7] + "\n"
		+ matrix.body[8] +  matrix.body[9] + matrix.body[10] + matrix.body[11] + "\n"
		+ matrix.body[12] +  matrix.body[13] + matrix.body[14] + matrix.body[15] + "\n"
                + "|";
    os << output;
    return os;
}

