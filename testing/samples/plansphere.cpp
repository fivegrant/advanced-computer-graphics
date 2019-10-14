#include <fstream>
#include <string>
#include "../../objects/src/sphere.cpp"
#include "../../components/canvas.hpp"

const std::string filename = "thingysphere.ppm";

int main(){
Canvas canv = Canvas(1000, 1000);

int j = 0;
for(auto row: canv.pixels){
  double y = 2.0 - j / 250.0;
  int i = 0;
  for(auto pixel: row){
    double x = -2.0 + i / 250.0 ; 
    Tuple origin = point(x, y, -5.0);
    Tuple direction = vector(0, 0, 1.0);
    Ray ray = Ray(origin, direction);
    std::vector<double> ts = Sphere().intersectionWith(ray);
    bool wasHit = false;
      for(auto t: ts){
        if(t>0){
	  wasHit = true;
	}
      }
      if (wasHit){
        canv.write_pixel(j, i, color(0.0,0.0,0.0));
      }else{
        canv.write_pixel(j, i, color(1.0,1.0,1.0));
      }
  i++;
  }
  j++;
}
canv.toPPM(filename);
return 0;
}
