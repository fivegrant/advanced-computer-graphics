#include <vector>
#include <cmath>
#include "../../mechanics/tuple.hpp"
class Matrix{

  public:
    double body [];
    double det = 0;
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
    double operator [](int location) const {};
    double & operator [](int location) const {};

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
int Matrix::size() const
{
  return sqrt(this->body.size());
}

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

