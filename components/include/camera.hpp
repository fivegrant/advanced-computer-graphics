#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "mechanics/include/matrix.hpp"
#include "mechanics/include/ray.hpp"
#include "components/include/canvas.hpp"
#include "objects/include/world.hpp"
#include "utilities/include/pi.hpp"

const double REC_DEPTH = 5;

class Camera{
  private:
    double field_of_view = PI/2;
    Matrix transform_matrix = Matrix();
    double pixel = 0;
    double half_w, half_h;
  public:
    int w, h;
 
  Camera (int input_w, int input_h):
    w(input_w), h(input_h){}

  void set_transform(Matrix reset);
  void set_fov(double value);
  double get_fov();
  Matrix get_transform();
  double pixel_size();
  Ray ray_at_pixel(int x, int y);
  Canvas render(World world);
};

//String Conversion
std::ostream& operator << (std::ostream& os, Camera const& camera);

#endif

