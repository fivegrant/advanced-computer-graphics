//TestCasesWeek3.txt
//Feature: Matrices

#include <cmath>
#include "modules/catch2.hpp"
#include "mechanics/include/matrix.hpp"

TEST_CASE("Constructing and inspecting a 4x4 matrix"){
  Matrix M = Matrix({ 1   ,  2   ,  3   ,  4   ,
    	              5.5 ,  6.5 ,  7.5 ,  8.5 ,
    	              9   , 10   , 11   , 12   ,
    	              0   ,  0   ,  0   ,  1   });
  REQUIRE(M.retrieve(0,0) == 1);
  REQUIRE(M.retrieve(0,3) == 4);
  REQUIRE(M.retrieve(1,0) == 5.5);
  REQUIRE(M.retrieve(1,2) == 7.5);
  REQUIRE(M.retrieve(2,2) == 11);
  REQUIRE(M.retrieve(3,0) == 0);
  REQUIRE(M.retrieve(3,3) == 1);
}

TEST_CASE("A 2x2 matrix ought to be representable"){
  Matrix M = Matrix({ -3 ,  5 ,
    	               1 , -2 });
  REQUIRE(M.retrieve(0,0) == -3);
  REQUIRE(M.retrieve(0,1) == 5);
  REQUIRE(M.retrieve(1,0) == 1);
  REQUIRE(M.retrieve(1,1) == -2);
}

TEST_CASE("A 3x3 matrix ought to be representable"){
  Matrix M = Matrix({ -3 ,  5 ,  0 ,
	               1 , -2 , -7 ,
    	               0 ,  1 ,  1 });
  REQUIRE(M.retrieve(0,0) == -3);
  REQUIRE(M.retrieve(1,1) == -2);
  REQUIRE(M.retrieve(2,2) == 1);
}

TEST_CASE("Matrix equality with identical matrices"){
  Matrix A = Matrix({ 1 , 2 , 3 , 4 ,
      		      5 , 6 , 7 , 8 ,
		      9 , 8 , 7 , 6 ,
      		      0 , 0 , 0 , 1 });

  Matrix B = Matrix({ 1 , 2 , 3 , 4 ,
      	              5 , 6 , 7 , 8 ,
                      9 , 8 , 7 , 6 ,
                      0 , 0 , 0 , 1 });
  REQUIRE(A == B);
}

TEST_CASE("Matrix equality with different matrices"){
  Matrix A = Matrix({ 1 , 2 , 3 , 4 ,
      	              5 , 6 , 7 , 8 ,
      	              9 , 8 , 7 , 6 ,
      	              0 , 0 , 0 , 1 });

  Matrix B = Matrix({ 2 , 3 , 4 , 5 ,
	              6 , 7 , 8 , 9 ,
	              8 , 7 , 6 , 5 ,
	              0 , 0 , 0 , 1 });
  REQUIRE(A != B);
}

TEST_CASE("Multiplying two matrices"){
  Matrix A = Matrix({ 1 , 2 , 3 , 4 ,
	              5 , 6 , 7 , 8 ,
	              9 , 8 , 7 , 6 ,
	              0 , 0 , 0 , 1 });

  Matrix B = Matrix({ -2 , 1 , 2 ,  3 ,
      		       3 , 2 , 1 , -1 ,
                       4 , 3 , 6 ,  5 ,
                       0 , 0 , 0 ,  1 });

  Matrix AstarB = Matrix({ 16 ,  14 ,  22 ,  20 ,
		           36 ,  38 ,  58 ,  52 ,
		           34 ,  46 ,  68 ,  60 ,
		           0 ,   0 ,   0 ,   1 });
  REQUIRE(A * B == AstarB);
}

TEST_CASE("A matrix multiplied by a tuple"){
  Matrix A = Matrix({ 1 , 2 , 3 , 4 ,
                      2 , 4 , 4 , 2 ,
                      8 , 6 , 4 , 1 ,
	              0 , 0 , 0 , 1 });

  Tuple b = Tuple(1, 2, 3, 1);
  REQUIRE(A * b == Tuple(18, 24, 33, 1));
}

TEST_CASE("Multiplying a matrix by the identity matrix"){
  Matrix A = Matrix({ 0 , 1 ,  2 ,  4 ,
    	              1 , 2 ,  4 ,  8 ,
    	              2 , 4 ,  8 , 16 ,
	              0 , 0 ,  0 ,  1 });
  //Default Matrix is Identity Matrix 4x4
  Matrix I = Matrix();
  REQUIRE(A * I == A);
}

TEST_CASE("Multiplying the identity matrix by a tuple"){
  Tuple a = Tuple(1, 2, 3, 4);
  //Default Matrix is Identity Matrix 4x4
  Matrix I = Matrix();
  REQUIRE(I * a == a);
}

TEST_CASE("Calculating the determinant of a 2x2 matrix"){
  Matrix A = Matrix({ 1 , 5 ,
	             -3 , 2 });
  REQUIRE(A.det() == 17);
}


TEST_CASE("A submatrix of a 3x3 matrix is a 2x2 matrix"){
  Matrix A = Matrix({ 1 , 5 ,  0 ,
    	             -3 , 2 ,  7 ,
	              0 , 6 , -3 });
  Matrix Sub = Matrix({ -3 , 2 ,
    		         0 , 6 });

  A.submatrix(0, 2);
  REQUIRE(A.submatrix(0, 2) == Sub);
}

TEST_CASE("Calculating a minor of a 3x3 matrix"){
  Matrix A = Matrix({ 3 ,  5 ,  0 ,
      	              2 , -1 , -7 ,
                      6 , -1 ,  5 });
  Matrix B = A.submatrix(1, 0);
  REQUIRE(B.det() == 25);
  REQUIRE(A.minor(1, 0) == 25);
}

TEST_CASE("Calculating a cofactor of a 3x3 matrix"){
  Matrix A = Matrix({ 3 ,  5 ,  0 ,
  	              2 , -1 , -7 ,
      	              6 , -1 ,  5 });
  REQUIRE(A.minor(0, 0) == -12);
  REQUIRE(A.cofactor(0, 0) == -12);
  REQUIRE(A.minor(1, 0) == 25);
  REQUIRE(A.cofactor(1, 0) == -25);
}

TEST_CASE("Calculating the determinant of a 3x3 matrix"){
  Matrix A = Matrix({  1 ,  2 ,  6 ,
	              -5 ,  8 , -4 ,
	               2 ,  6 ,  4 });
  REQUIRE(A.cofactor(0, 0) == 56);
  REQUIRE(A.cofactor(0, 1) == 12);
  REQUIRE(A.cofactor(0, 2) == -46);
  REQUIRE(A.det() == -196);
}

TEST_CASE("Calculating the determinant of a 4x4 matrix"){
  Matrix A = Matrix({ -2 , -8 ,  3 ,  5 ,
	              -3 ,  1 ,  7 ,  3 ,
	               1 ,  2 , -9 ,  6 ,
 	               0 ,  0 ,  0 ,  1 });
  REQUIRE(A.det() == 185);
}

TEST_CASE("Testing an invertible matrix for invertibility"){
  Matrix A = Matrix({  6 ,  4 ,  4 ,  4 ,
	               5 ,  5 ,  7 ,  6 ,
	               4 , -9 ,  3 , -7 ,
	               0 ,  0 ,  0 ,  1 });
  REQUIRE(A.det() == 260);
  REQUIRE(A.invertible());
}

TEST_CASE("Testing a noninvertible matrix for invertibility"){
  Matrix A = Matrix({ -4 ,  2 ,  0 , -3 ,
	               9 ,  6 ,  0 ,  6 ,
	               0 , -5 ,  0 , -5 ,
	               0 ,  0 ,  0 ,  1 });
  REQUIRE(A.det() == 0);
  REQUIRE(!A.invertible());
}

TEST_CASE("Calculating the inverse of a matrix"){
  Matrix A = Matrix({ -5 ,  2 ,  6 , -8 ,
	               1 , -5 ,  1 ,  8 ,
      	               7 ,  7 , -6 , -7 ,
                       0 ,  0 ,  0 ,  1 });
  Matrix B = A.inverse();
  Matrix check_B = Matrix({ 0.14110 ,  0.33129 ,  0.19632 , -0.14724 ,
	                    0.07975 , -0.07362 ,  0.06748 ,  1.69939 ,
	                    0.25767 ,  0.30061 ,  0.14110 ,  0.64417 ,
	                    0.0     ,  0.0     ,  0.0     ,  1.0     });
  REQUIRE(B.approx(check_B));
}

TEST_CASE("Multiplying a product by its inverse"){
  Matrix A = Matrix({  3 , -9 ,  7 ,  3 ,
                       3 , -8 ,  2 , -9 ,
      	              -4 ,  4 ,  4 ,  1 ,
      	               0 ,  0 ,  0 ,  1 });

  Matrix B = Matrix({  8 ,  2 ,  2 ,  2 ,
      	               3 , -1 ,  7 ,  0 ,
                       7 ,  0 ,  5 ,  4 ,
                       0 ,  0 ,  0 ,  1 });
  Matrix C = A * B;
  REQUIRE((C * B.inverse()).approx(A));
}
