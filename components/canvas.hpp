#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "../mechanics/tuple.hpp"

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

Tuple Canvas::colorTo255(Tuple raw_color) const{
  if (raw_color.w != 1.0){
    double red = (round(raw_color.x * 255));
    red = (red<0) ? (0.0) : (red);
    red = (red>255) ? (255.0) : (red);

    double green = (round(raw_color.y * 255));
    green = (green<0) ? (0.0) : (green);
    green = (green>255) ? (255.0) : (green);

    double blue = (round(raw_color.z * 255));
    blue = (blue<0) ? (0.0) : (blue);
    blue = (blue>255) ? (255.0) : (blue);

    return color(red, green, blue, true);

  }else{
    return raw_color; 
  }
}

Tuple Canvas::pixel_at(int x_pos, int y_pos) const{
 Tuple capture = this->pixels[y_pos][x_pos];
 return this->pixels[y_pos][x_pos];
}

void Canvas::write_pixel(int x_pos, int y_pos, Tuple pixel) {
  //this->pixels[x_pos][y_pos] = colorTo255(pixel);
  this->pixels[y_pos][x_pos] = pixel;
}

void Canvas::toPPM(std::string filename) const
{
  std::string output = "P3\n";
  output+= std::to_string(this->w) + ' ' + std::to_string(this->h) + '\n';
  output+= "255\n";
  for(std::vector<Tuple> row: this->pixels){
    for(Tuple pixel: row){
      Tuple show = colorTo255(pixel);
      output+= std::to_string((int)show.x) + " " + 
       std::to_string((int)show.y) + " " + 
       std::to_string((int)show.z) + " ";
      }
    output+= "\n";
    }
  output+= "\n";
  std::ofstream ppm(filename);
  ppm << output;
  ppm.close();
}

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
