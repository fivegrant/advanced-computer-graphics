//TestCasesWeek1.txt
//Feature: Canvas

#define CATCH_CONFIG_MAIN
#include <cmath>
#include <string>
#include <fstring>
#include "../../modules/catch2.hpp"
#include "../../components/canvas.hpp"
//Sample File
const string SAMPLE_PPM = "feature_canvas.ppm"

TEST_CASE("Creating a canvas"){
  Canvas c ← Canvas(10, 20);
  REQUIRE(c.width = 10);
  REQUIRE(c.height = 20);
  for(Tuple pixel: c){
  REQUIRE(pixel == color(0, 0, 0));}
}

TEST_CASE("Writing pixels to a canvas"){
  Canvas c = Canvas(10, 20);
  Tuple red = color(1, 0, 0);
  c.write_pixel(2, 3, red); 
  REQUIRE(c.pixel_at(2, 3) == red);
}

TEST_CASE("Constructing the PPM header"){
  Canvas c = Canvas(5, 3)
  std::string ppm = c.toPPM()
  std::ifstream infile(SAMPLE_PPM);
  std::getLine(infile, life)
  //TODO:Fix
  Then lines 1-3 of ppm are
  ppm
    REQUIRE("P3");
    REQUIRE("5 3");
    REQUIRE("255");
}

TEST_CASE("Constructing the PPM pixel data"){
  Canvas c = Canvas(5, 3);
  Tuple c1 = color(1.5, 0, 0);
  Tuple c2 = color(0, 0.5, 0);
  Tuple c3 ← color(-0.5, 0, 1);
  write_pixel(c, 0, 0, c1);
  write_pixel(c, 2, 1, c2);
  write_pixel(c, 4, 2, c3);
  std:string ppm = c.toPPM()
  Then lines 4-6 of ppm are
    """
    255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
    """
}

TEST_CASE("Splitting long lines in PPM files"){
  Canvas c = Canvas(10, 2);
  When every pixel of c is set to color(1, 0.8, 0.6)
    And ppm ← c.toPPM()
  Then lines 4-7 of ppm are
    """
    255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
    153 255 204 153 255 204 153 255 204 153 255 204 153
    255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
    153 255 204 153 255 204 153 255 204 153 255 204 153
    """
}

TEST_CASE("PPM files are terminated by a newline character"){
  Canvas c = Canvas(5, 3);
  std:string ppm = c.toPPM();
  Then ppm ends with a newline character
}
