#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <cmath>
#include "mechanics/include/tuple.hpp"
#include "utilities/include/epsilon.hpp"

class Matrix{

  public:
    std::vector<double> body;
    std::vector<double> inverse_matrix = {};
    
    //Constructor
     Matrix (std::vector<double> content):
      body(content) {}
     Matrix ()
      {
	body = {1, 0, 0, 0,
	        0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1};
      }

    //Operators
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Tuple operator*(const Tuple&) const;

    double retrieve(int, int) const;
    void write(int, int, double);

    int size() const;
    bool approx(Matrix) const;

    //Linear Algebra
    Matrix scale(double) const;
    Matrix submatrix(int, int) const;
    Matrix cofactor_matrix() const;
    Matrix inverse();
    Matrix get_inverse() const;
    Matrix transpose() const;
    double det() const; //determinant
    double minor(int, int) const;
    double cofactor(int, int) const;
    bool invertible();


};

//Generate types of matrices
Matrix translation(double x, double y, double z)
{
  std::vector<double> content = { 1, 0, 0, x,
  			          0, 1, 0, y,
			          0, 0, 1, z,
			          0, 0, 0, 1};
  Matrix result = Matrix(content); 
  return result;
}

Matrix scaling(double x, double y, double z)
{
  std::vector<double> content = { x, 0, 0, 0,
  			          0, y, 0, 0,
			          0, 0, z, 0,
			          0, 0, 0, 1};
  Matrix result = Matrix(content); 
  return result;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Matrix const& matrix) {
    std::string output = "Matrix:\n";
    for(unsigned long int counter = 0; counter < matrix.body.size(); counter++){
   	output += std::to_string(matrix.body[counter]);
	output += (((counter + 1) % matrix.size()) == 0) ? "\n" : "\t";
      }
    output += "\n";
    os << output;
    return os;
}
#endif
