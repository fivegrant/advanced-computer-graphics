#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <cmath>
#include "./tuple.hpp"
#include "../../utilities/include/epsilon.hpp"

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
    Matrix operator*(const Matrix& rhs) const;
    Tuple operator*(const Tuple& rhs) const;

    double retrieve(int i, int j) const;
    void write(int i, int j, double content);

    int size() const;
    bool approx(Matrix) const;

    //Linear Algebra
    Matrix scale(double rhs) const;
    Matrix submatrix(int i, int j) const;
    Matrix cofactor_matrix() const;
    Matrix inverse();
    Matrix get_inverse() const;
    Matrix transpose() const;
    double det() const; //determinant
    double minor(int i, int j) const;
    double cofactor(int i, int j) const;
    bool invertible();


};

#endif
