#include <fstream>
#include <string>
#include "../../mechanics/sphere.hpp"
#include "../../components/canvas.hpp"

const std::string filename = "first_sphere.ppm";

/*
int main(){
Canvas canv = Canvas(100, 100);

for(int index_j = 0; index_j < canv.w; index_j++){
  double y = 2 - index_j / 25.0;
  for(int index_i = 0; index_i < canv.h; index_i++){
    int x = -2 + index_i / 25.0 ; 
    Tuple origin = point(x, y, -5);
    Tuple direction = vector(0, 0, 1);
    Ray ray = Ray(origin, direction);
    std::vector<double> ts = Sphere().pointAtT(ray);
    bool wasHit = false;
      for(auto t: ts){
        if(t>0){
	  wasHit = true;
	}
      }
      if (wasHit){
        canv.write_pixel(index_j, index_i,color(1,0,0));
      }else{
        canv.write_pixel(index_j, index_i,color(0,0,0));
      }
  }
}
canv.toPPM("first_sphere.ppm");
return 0;
}
*/

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
