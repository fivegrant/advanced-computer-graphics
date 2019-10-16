#include <fstream>
#include <string>
#include "objects/include/sphere.hpp"
#include "components/include/canvas.hpp"

const std::string filename = "first_sphere.ppm";

int main(){
Canvas canv = Canvas(100, 100);

int j = 0;
for(auto row: canv.pixels){
  double y = 2.0 - j / 25.0;
  int i = 0;
  for(auto pixel: row){
    double x = -2.0 + i / 25.0 ; 
    Tuple origin = point(x, y, -5.0);
    Tuple direction = vector(0, 0, 1.0);
    Ray ray = Ray(origin, direction);
    std::vector<double> ts = Sphere().pointAtT(ray);
    bool wasHit = false;
      for(auto t: ts){
        if(t>0){
	  wasHit = true;
	}
      }
      if (wasHit){
        canv.write_pixel(j, i, color(1.0,0.0,0.0));
      }else{
        canv.write_pixel(j, i, color(0.0,0.0,0.0));
      }
  i++;
  }
  j++;
}
canv.toPPM("first_sphere.ppm");
return 0;
}
