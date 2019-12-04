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
    
     Matrix (std::vector<double> content):
      body(content) {}
     Matrix ()
      {
	body = {1, 0, 0, 0,
	        0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1};
      }

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
Matrix translation(double x, double y, double z);

Matrix scaling(double x, double y, double z);

Matrix rotationx(double theta);

Matrix rotationy(double theta);

Matrix rotationz(double theta);

Matrix view_transform(Tuple place, Tuple look, Tuple up);

std::ostream& operator << (std::ostream& os, Matrix const& matrix);
#endif
