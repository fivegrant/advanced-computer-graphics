#include "../src/shape.cpp"

class Sphere: public Shape {
  public:
    Sphere() {this->shape_type = "Sphere";}

    std::vector<double> pointAtT(Ray ray) const;

};


