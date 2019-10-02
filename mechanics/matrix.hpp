#include <vector>
#include <cmath>
#include "./tuple.hpp"

//`-=>` indicates implement in matrix storage update

const double ERROR = 0.000001;

class Matrix{

  public:
    std::vector<double> body;
    double determinant = 0;
    //-=>int dimension; //Size of Matrix
    //-=>Matrix* inverse_matrix, transposed_matrix;
    bool can_invert = false;
    //check to see if calculation has already been performed
    //determinant | -=>inverse | -=>transposed | invertible | -=>size
    //     0             1              2            3         4
    bool check [5] = {false, false, false, false, false};
    
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

    //Accessing individual Elements
    //index min: 1 & index max:size()
    double retrieve(int i, int j) const;
    void write(int i, int j, double content);

    int size() const;
    bool approx(Matrix) const;

    //Linear Algebra
    Matrix scale(double rhs) const;
    Matrix submatrix(int i, int j) const;
    Matrix cofactor_matrix() const;
    Matrix inverse();
    Matrix transpose() const;
    double det(); //determinant
    double minor(int i, int j) const;
    double cofactor(int i, int j) const;
    bool invertible();


};

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
  /*
  if (!this->check[4]){
    this->dimension = sqrt(this->body.size());
    check[4] = true;
  }
    return this->dimension;
  */
  return sqrt(this->body.size());
}

bool Matrix::approx(Matrix other) const
{
  for(int index = 0; index < body.size(); index++){
    if(abs(abs(this->body[index]) - abs(other.body[index])) > ERROR){
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

double Matrix::det()
{
  //check if det is stored
  if(this->check[0])
  {
    return this->determinant;
  }
  else{
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

  this->check[0] = true;
  this->determinant = result;

  if(result != 0)
  {
    this->check[1] = true;
    this->check[3] = true;
  }
  return result;
  }
}

double Matrix::minor(int i, int j) const
{
  return this->submatrix(i, j).det();
}

bool Matrix::invertible()
{
  /* -=>
  if(this->check[3]){
    this->det();
   }
  return this->can_invert;
  */
  return this->det() != 0;
}

Matrix Matrix::transpose() const
{
  //-=>if(!this->check[2]){
  std::vector<double> body ={};
  for(int j_index = 0; j_index < this->size(); j_index++){
    for(int i_index = 0; i_index < this->size(); i_index++){
      body.push_back(this->retrieve(i_index, j_index));
      }
    }
  //-=>   this->transposed_matrix = &Matrix(body);
  //-=>}
  //-=>return *this->transposed_matrix;
  return Matrix(body);
}

Matrix Matrix::inverse()
{
  /*-=>
  if(!check[0]){
    this->inverse_matrix = &(this * (1/this->transpose().cofactor().det()));
  }
  return *this->inverse_matrix
  */
  return this->cofactor_matrix().transpose().scale((double) 1.0/this->det());
}

//String Conversion
std::ostream& operator << (std::ostream& os, Matrix const& matrix) {
    std::string output = "Matrix:\n";
    for(int counter = 0; counter < matrix.body.size(); counter++){
   	output += std::to_string(matrix.body[counter]);
	output += (((counter + 1) % matrix.size()) == 0) ? "\n" : "\t";
      }
    output += "\n";
    os << output;
    return os;
}

