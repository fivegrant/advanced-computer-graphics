#include "../include/matrix.hpp"

//Operators
bool Matrix::operator==(const Matrix& rhs) const
{
  return this->body == rhs.body;

}

bool Matrix::operator!=(const Matrix& rhs) const
{
  return !(*this == rhs);
}

//Exclusively for 4x4 Matrices
Tuple Matrix::operator*(const Tuple& rhs) const
{
  if(this->size() != 4){
    return rhs;
    }
  return Tuple(
      //Simplifiy with for loop later
	this->retrieve(0,0) * rhs.x + this->retrieve(0,1) * rhs.y + 
	 this->retrieve(0,2) * rhs.z + this->retrieve(0, 3) * rhs.w,
	this->retrieve(1,0) * rhs.x + this->retrieve(1,1) * rhs.y + 
	 this->retrieve(1,2) * rhs.z + this->retrieve(1, 3) * rhs.w,
	this->retrieve(2,0) * rhs.x + this->retrieve(2,1) * rhs.y + 
	 this->retrieve(2,2) * rhs.z + this->retrieve(2, 3) * rhs.w,
	this->retrieve(3,0) * rhs.x + this->retrieve(3,1) * rhs.y + 
	 this->retrieve(3,2) * rhs.z + this->retrieve(3, 3) * rhs.w

 	      );
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
  std::vector<double> body = {};
  for(int row = 0; row < this->size(); row++){
    for(int right_j = 0; right_j < this->size(); right_j++){
      double cell = 0;
      for(int left_j = 0; left_j < this->size(); left_j++){
          cell += this->retrieve(row, left_j) * rhs.retrieve(left_j, right_j);
        }
      body.push_back(cell);
      }
     }

  return Matrix(body);
}

Matrix Matrix::scale(double rhs) const
{
  std::vector<double> body = this->body;
  for(int index = 0; index < body.size(); index++){
    body[index] *= rhs;
   }
  return Matrix(body);
}
double Matrix::retrieve(int i, int j) const 
{
  return body[i * this->size() + j];
}

void Matrix::write(int i, int j, double content) 
{
  body[i * this->size() + j] = content;
}

//Methods
int Matrix::size() const
{
  return sqrt(this->body.size());
}

bool Matrix::approx(Matrix other) const
{
  for(int index = 0; index < body.size(); index++){
    if(abs(abs(this->body[index]) - abs(other.body[index])) > EPSILON){
      return false;
    }
  }
  return true;
}

Matrix Matrix::submatrix(int i, int j) const
{
  std::vector<double> body = {};
  for(int i_index = 0; i_index < this->size(); i_index++){
    for(int j_index = 0; j_index < this->size(); j_index++){
      if(i != i_index && j_index != j){
	body.push_back(this->retrieve(i_index, j_index));
	}
    }
  }

  return Matrix(body);
}

double Matrix::cofactor(int i, int j) const
{
  return  (((i + j) % 2 == 0) ? 1 : -1) * this->minor(i, j); 
}

Matrix Matrix::cofactor_matrix() const
{
  std::vector<double> body = {};
  for(int i_index = 0; i_index < this->size(); i_index++){
    for(int j_index = 0; j_index < this->size(); j_index++){
	body.push_back(this->cofactor(i_index, j_index));
    }
  }

  return Matrix(body);
}

double Matrix::det() const
{
  double result = 0;
  switch(this->size()){
    //1 x 1 Matrix
    case 1: result = this->retrieve(0,0);
      	    break;
    //2 x 2 Matrix
    case 2: result = this->retrieve(0,0) * this->retrieve(1,1) - 
     		     this->retrieve(1,0) * this->retrieve(0,1);
	    break;
    //n x n Matrix
    default: for(int j_index = 0; j_index < this->size(); j_index++){
		result += this->retrieve(0, j_index) * cofactor(0, j_index);
	     }
  }
  return result;
}

double Matrix::minor(int i, int j) const
{
  return this->submatrix(i, j).det();
}

bool Matrix::invertible()
{
  return this->det() != 0;
}

Matrix Matrix::transpose() const
{
  std::vector<double> body ={};
  for(int j_index = 0; j_index < this->size(); j_index++){
    for(int i_index = 0; i_index < this->size(); i_index++){
      body.push_back(this->retrieve(i_index, j_index));
      }
    }
  return Matrix(body);
}

Matrix Matrix::inverse()
{
  if(this->inverse_matrix.size() == 0){
    Matrix result = this->cofactor_matrix().transpose().scale(1.0/this->det());
    this->inverse_matrix = result.body;
    return result;
  }else{
    return Matrix(this->inverse_matrix);
  }
}

Matrix Matrix::get_inverse() const
{
  return this->inverse_matrix;
}

