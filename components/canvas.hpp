#include <vector>
#include <string>
#include <cmath>
#include "../mechanics/tuple.hpp"

class Canvas{

  public:
  double w, h;
  std::vector<std::vector<Tuple>> pixels;

  Canvas (double input_w, double input_h, std::vector<std::vector<Tuple>> input_pixels):
    w(input_w), h(input_h), pixels(input_pixels) {}
  
  Tuple colorTo255(Tuple color) const; 
  Tuple pixel_at(int x_pos, int y_pos) const;
  void write_pixel(int x_pos, int y_pos, Tuple);
  std::string toPPM() const;
};

Tuple Canvas::colorTo255(Tuple raw_color) const{
  if (raw_color.w != 1.0){
    double red = (round(raw_color.x * 255));
    red = (red<0) ? (0.0) : (red);
    red = (red>0) ? (255.0) : (red);

    double green = (round(raw_color.y * 255));
    green = (green<0) ? (0.0) : (green);
    green = (green>0) ? (255.0) : (green);

    double blue = (round(raw_color.z * 255));
    blue = (blue<0) ? (0.0) : (blue);
    blue = (blue>0) ? (255.0) : (blue);

    return color(red, green, blue, true);

  }else{
    return raw_color; 
  }
}

Tuple Canvas::pixel_at(int x_pos, int y_pos) const{
 Tuple capture = this->pixels[x_pos][y_pos];
 return this->pixels[x_pos][y_pos];
}

void Canvas::write_pixel(int x_pos, int y_pos, Tuple pixel) {
  this->pixels[x_pos][y_pos] = colorTo255(pixel);
}

std::string Canvas::toPPM() const
{
  std::string output = "P3\n";
  output+= std::to_string(this->w) + ' ' + std::to_string(this->h) + '\n';
  output+= "255\n";
  for(std::vector<Tuple> width: this->pixels){
    for(Tuple pixel: width){
      output+= std::to_string(int (pixel.x)) + " " + std::to_string(int (pixel.y)) + " " + std::to_string(int (pixel.z)) + " ";
    output+= '\n';
      }
    }
  return output;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Canvas const& canvas) {
    os << "CANVAS:: w: " +std::to_string(canvas.w) + ", h: " +
     std::to_string(canvas.h);
    return os;
}
