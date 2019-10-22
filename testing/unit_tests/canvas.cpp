//TestCasesWeek1.txt
//Feature: Canvas

#include <cmath>
#include <string>
#include "modules/catch2.hpp"
#include "components/include/canvas.hpp"
#include "utilities/include/ppmname.hpp"

//Sample File

TEST_CASE("Creating a canvas"){
  Canvas c = Canvas(10, 20);
  REQUIRE(c.w == 10);
  REQUIRE(c.h == 20);
  for(auto column: c.pixels){
    for(auto pixel: column){
    REQUIRE(pixel == color(0, 0, 0));}
    }
}

TEST_CASE("Writing pixels to a canvas"){
  Canvas c = Canvas(10, 20);
  Tuple red = color(1, 0, 0);
  c.write_pixel(2, 3, red); 
  REQUIRE(c.pixel_at(2, 3) == red);
}

TEST_CASE("Constructing the PPM header"){
  Canvas c = Canvas(5, 3);
  c.toPPM(SAMPLE_PPM);
  std::vector<std::string> ppm = ppmByLine(SAMPLE_PPM);
  REQUIRE(ppm[0] == "P3");
  REQUIRE(ppm[1] == "5 3");
  REQUIRE(ppm[2] == "255");
}


TEST_CASE("Constructing the PPM pixel data"){
  Canvas c = Canvas(5, 3);
  Tuple c1 = color(1.5, 0, 0);
  Tuple c2 = color(0, 0.5, 0);
  Tuple c3 = color(-0.5, 0, 1);
  c.write_pixel(0, 0, c1);
  c.write_pixel(2, 1, c2);
  c.write_pixel(4, 2, c3);
  c.toPPM(SAMPLE_PPM);
  std::vector<std::string> ppm = ppmByLine(SAMPLE_PPM);
  REQUIRE(ppm[3] == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
  REQUIRE(ppm[4] == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
  REQUIRE(ppm[5] == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

TEST_CASE("Splitting long lines in PPM files"){
  Tuple standard_color = color(1, 0.8, 0.6);
  Canvas c = Canvas(10, 2, standard_color);
  //c.toPPM(SAMPLE_PPM);
  //std::vector<std::string> ppm = ppmByLine(SAMPLE_PPM);
  c.toPPM(SAMPLE_PPM);
  std::vector<std::string> ppm = ppmByLine(SAMPLE_PPM);
  REQUIRE(ppm[3] == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
  REQUIRE(ppm[4] == "153 255 204 153 255 204 153 255 204 153 255 204 153");
  REQUIRE(ppm[5] == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
  REQUIRE(ppm[6] == "153 255 204 153 255 204 153 255 204 153 255 204 153");
}

TEST_CASE("PPM files are terminated by a newline character"){
  Canvas c = Canvas(5, 3);
  c.toPPM(SAMPLE_PPM);
  std::vector<std::string> ppm = ppmByLine(SAMPLE_PPM);
  REQUIRE(ppm[6] == "");
}
