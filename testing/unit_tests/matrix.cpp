//TestCasesWeek3.txt
//Feature: Matrices

#define CATCH_CONFIG_MAIN
#include <cmath>
#include "../../modules/catch2.hpp"
#include "../../mechanics/matrix.hpp"

TEST_CASE("Constructing and inspecting a 4x4 matrix"){
  Given the following 4x4 matrix M:
    |  1   |  2   |  3   |  4   |
    |  5.5 |  6.5 |  7.5 |  8.5 |
    |  9   | 10   | 11   | 12   |
    |  0   |  0   |  0   |  1   |
  REQUIRE(M[0,0] == 1);
  REQUIRE(M[0,3] == 4);
  REQUIRE(M[1,2] == 5.5);
  REQUIRE(M[1,2] == 7.5);
  REQUIRE(M[2,2] == 11);
  REQUIRE(M[3,0] == 0);
  REQUIRE(M[3,3] == 1);
}

TEST_CASE("A 2x2 matrix ought to be representable"){
  Given the following 2x2 matrix M:
    | -3 |  5 |
    |  1 | -2 |
  REQUIRE(M[0,0] == -3);
  REQUIRE(M[0,1] == 5);
  REQUIRE(M[1,0] == 1);
  REQUIRE(M[1,1] == -2);
}

TEST_CASE("A 3x3 matrix ought to be representable"){
  Given the following 3x3 matrix M:
    | -3 |  5 |  0 |
    |  1 | -2 | -7 |
    |  0 |  1 |  1 |
  REQUIRE(M[0,0] == -3);
  REQUIRE(M[1,1] == -2);
  REQUIRE(M[2,2] == 1);
}

TEST_CASE("Matrix equality with identical matrices"){
  Given the following matrix A:
      | 1 | 2 | 3 | 4 |
      | 5 | 6 | 7 | 8 |
      | 9 | 8 | 7 | 6 |
      | 0 | 0 | 0 | 1 |
    And the following matrix B:
      | 1 | 2 | 3 | 4 |
      | 5 | 6 | 7 | 8 |
      | 9 | 8 | 7 | 6 |
      | 0 | 0 | 0 | 1 |
  REQUIRE(A == B);
}

TEST_CASE("Matrix equality with different matrices"){
  Given the following matrix A:
      | 1 | 2 | 3 | 4 |
      | 5 | 6 | 7 | 8 |
      | 9 | 8 | 7 | 6 |
      | 0 | 0 | 0 | 1 |
    And the following matrix B:
      | 2 | 3 | 4 | 5 |
      | 6 | 7 | 8 | 9 |
      | 8 | 7 | 6 | 5 |
      | 0 | 0 | 0 | 1 |
  REQUIRE(A != B);
}

TEST_CASE("Multiplying two matrices"){
  Given the following matrix A:
      | 1 | 2 | 3 | 4 |
      | 5 | 6 | 7 | 8 |
      | 9 | 8 | 7 | 6 |
      | 0 | 0 | 0 | 1 |
    And the following matrix B:
      | -2 | 1 | 2 |  3 |
      |  3 | 2 | 1 | -1 |
      |  4 | 3 | 6 |  5 |
      |  0 | 0 | 0 |  1 |
  AstarB is the following 4x4 matrix:
      | 16|  14 |  22 |  20 |
      | 36|  38 |  58 |  52 |
      | 34|  46 |  68 |  60 |
      |  0|   0 |   0 |   1 |
  REQUIRE(A * B == AstarB);
}

TEST_CASE("A matrix multiplied by a tuple"){
  Given the following matrix A:
      | 1 | 2 | 3 | 4 |
      | 2 | 4 | 4 | 2 |
      | 8 | 6 | 4 | 1 |
      | 0 | 0 | 0 | 1 |
  Tuple b = Tuple(1, 2, 3, 1);
  REQUIRE(A * b == Tuple(18, 24, 33, 1));
}

TEST_CASE("Multiplying a matrix by the identity matrix"){
  Given the following matrix A:
    | 0 | 1 |  2 |  4 |
    | 1 | 2 |  4 |  8 |
    | 2 | 4 |  8 | 16 |
    | 0 | 0 |  0 |  1 |
  and the following matrix I:
    | 1 | 0 |  0 |  0 |
    | 0 | 1 |  0 |  0 |
    | 0 | 0 |  1 |  0 |
    | 0 | 0 |  0 |  1 |
  REQUIRE(A * I == A);
}

TEST_CASE("Multiplying the identity matrix by a tuple"){
  Tuple a = Tuple(1, 2, 3, 4);
  and the following matrix I:
    | 1 | 0 |  0 |  0 |
    | 0 | 1 |  0 |  0 |
    | 0 | 0 |  1 |  0 |
    | 0 | 0 |  0 |  1 |

  REQUIRE(I * a == a);
}

TEST_CASE("Calculating the determinant of a 2x2 matrix"){
  Given the following 2x2 matrix A:
    |  1 | 5 |
    | -3 | 2 |
  REQUIRE(determinant(A) == 17);
}

TEST_CASE("A submatrix of a 3x3 matrix is a 2x2 matrix"){
  Given the following 3x3 matrix A:
    |  1 | 5 |  0 |
    | -3 | 2 |  7 |
    |  0 | 6 | -3 |
  Then submatrix(A, 0, 2) is the following 2x2 matrix:
    | -3 | 2 |
    |  0 | 6 |
}

TEST_CASE("Calculating a minor of a 3x3 matrix"){
  Given the following 3x3 matrix A:
      |  3 |  5 |  0 |
      |  2 | -1 | -7 |
      |  6 | -1 |  5 |
    And B ← submatrix(A, 1, 0)
  REQUIRE(determinant(B) == 25);
  REQUIRE(minor(A, 1, 0) == 25);
}

TEST_CASE("Calculating a cofactor of a 3x3 matrix"){
  Given the following 3x3 matrix A:
      |  3 |  5 |  0 |
      |  2 | -1 | -7 |
      |  6 | -1 |  5 |
  REQUIRE(minor(A, 0, 0) == -12);
  REQUIRE(cofactor(A, 0, 0) == -12);
  REQUIRE(minor(A, 1, 0) == 25);
  REQUIRE(cofactor(A, 1, 0) == -25);
}

TEST_CASE("Calculating the determinant of a 3x3 matrix"){
  Given the following 3x3 matrix A:
    |  1 |  2 |  6 |
    | -5 |  8 | -4 |
    |  2 |  6 |  4 |
  REQUIRE(cofactor(A, 0, 0) == 56);
  REQUIRE(cofactor(A, 0, 1) == 12);
  REQUIRE(cofactor(A, 0, 2) == -46);
  REQUIRE(determinant(A) == -196);
}

TEST_CASE("Calculating the determinant of a 4x4 matrix"){
  Given the following 4x4 matrix A:
    | -2 | -8 |  3 |  5 |
    | -3 |  1 |  7 |  3 |
    |  1 |  2 | -9 |  6 |
    |  0 |  0 |  0 |  1 |
  REQUIRE(determinant(A) == 185);
}

TEST_CASE("Testing an invertible matrix for invertibility"){
  Given the following 4x4 matrix A:
    |  6 |  4 |  4 |  4 |
    |  5 |  5 |  7 |  6 |
    |  4 | -9 |  3 | -7 |
    |  0 |  0 |  0 |  1 |
  REQUIRE(determinant(A) == -2120);
  REQUIRE(A.invertible());
}

TEST_CASE("Testing a noninvertible matrix for invertibility"){
  Given the following 4x4 matrix A:
    | -4 |  2 |  0 | -3 |
    |  9 |  6 |  0 |  6 |
    |  0 | -5 |  0 | -5 |
    |  0 |  0 |  0 |  1 |
  REQUIRE(determinant(A) == 0);
  REQUIRE(!A.invertible());
}

TEST_CASE("Calculating the inverse of a matrix"){
  Given the following 4x4 matrix A:
      | -5 |  2 |  6 | -8 |
      |  1 | -5 |  1 |  8 |
      |  7 |  7 | -6 | -7 |
      |  0 |  0 |  0 |  1 |
    And B ← inverse(A)
  Then B is the following 4x4 matrix:
      |  0.14110 |  0.33129 |  0.19632 | -0.14724 |
      |  0.07975 | -0.07362 |  0.06748 |  1.69939 |
      |  0.25767 |  0.30061 |  0.14110 |  0.64417 |
      |  0.0     |  0.0     |  0.0     |  1.0     |
}

TEST_CASE("Multiplying a product by its inverse"){
  Given the following 4x4 matrix A:
      |  3 | -9 |  7 |  3 |
      |  3 | -8 |  2 | -9 |
      | -4 |  4 |  4 |  1 |
      |  0 |  0 |  0 |  1 |
    And the following 4x4 matrix B:
      |  8 |  2 |  2 |  2 |
      |  3 | -1 |  7 |  0 |
      |  7 |  0 |  5 |  4 |
      |  0 |  0 |  0 |  1 |
    And C ← A * B
  Then C * inverse(B) = A
}
