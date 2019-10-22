#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "mechanics/include/tuple.hpp"

class Canvas{

  public:
  int w, h;
  std::vector<std::vector<Tuple>> pixels;

  Canvas (int input_w, int input_h, std::vector<std::vector<Tuple>> input_pixels):
    w(input_w), h(input_h), pixels(input_pixels) {}

  Canvas (int input_w, int input_h):
    w(input_w), h(input_h) {
    for(int height = 0; height < input_h; height++){
      std::vector<Tuple> column = {};
      for(int width = 0; width < input_w; width++){
        column.push_back(color(0,0,0));
      }
      pixels.push_back(column);
    }
    
    } 
  Canvas (int input_w, int input_h, Tuple default_color):
    w(input_w), h(input_h) {
    for(int height = 0; height < input_h; height++){
      std::vector<Tuple> column = {};
      for(int width = 0; width < input_w; width++){
        column.push_back(default_color);
      }
      pixels.push_back(column);
    }
    
    }

  Tuple colorTo255(Tuple color) const; 
  Tuple pixel_at(int x_pos, int y_pos) const;
  void write_pixel(int x_pos, int y_pos, Tuple);
  void toPPM(std::string filename) const;
};

//String Conversion
std::ostream& operator << (std::ostream& os, Canvas const& canvas) {
    os << "CANVAS:: w: " +std::to_string(canvas.w) + ", h: " +
     std::to_string(canvas.h);
    return os;
}

//File Conversion
std::vector<std::string> ppmByLine(std::string filename)
{
  std::vector<std::string> output = {};
  std::string capture;
  std::ifstream ppm(filename);
  while (std::getline(ppm, capture)){
    output.push_back(capture);
  }
  ppm.close(); 
  return output;
}
#endif

