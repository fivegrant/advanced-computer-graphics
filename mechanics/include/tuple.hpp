#ifndef TUPLE_H
#define TUPLE_H
#include <cmath>
#include <string>
#include "utilities/include/epsilon.hpp"

class Tuple{

  public:
    // Tuple Initializiation 
    double x, y, z, w;

    //Constructor
    Tuple (double input_x = 0, double input_y = 0, double input_z = 0, 
      double input_w = 0):
        x(input_x), y(input_y), z(input_z), w(input_w) {}

    //Operators
    bool operator==(const Tuple&) const;
    Tuple operator+(const Tuple& rhs) const;
    Tuple operator-(const Tuple& rhs) const;
    Tuple operator*(const Tuple& rhs) const;
    Tuple operator*(double scalar) const;
    Tuple operator/(double scalar) const;

    //Unary Operators
    Tuple operator-() const;

    //Methods
    Tuple reflect(Tuple over) const;
    double dot(const Tuple& other) const;
    double isPoint() const;
    double isVector() const;

};

//Generators
Tuple point(const double x, const double y, const double z);
Tuple vector(const double x, const double y, const double z);
Tuple color(const double x, const double y, const double z);
Tuple color(const double x, const double y, const double z, bool is255);

//Magnitude and Normalization
double magnitude(const Tuple vector);
Tuple normalize(const Tuple vec);
double dot(const Tuple left, const Tuple right);
Tuple cross(const Tuple left, const Tuple right);

//String Conversion
std::ostream& operator << (std::ostream& os, Tuple const& tuple); 
#endif
