#include "components/include/camera.hpp"

void Camera::set_fov(double value)
{
  field_of_view = value;
  pixel = pixel_size();
}

double Camera::get_fov(){
  return field_of_view;
}

Matrix Camera::get_transform(){
  return transform_matrix;
}

void Camera::set_transform(Matrix reset){
  transform_matrix = reset;
  transform_matrix.inverse();
}

double Camera::pixel_size()
{
  if (pixel != 0) {
	return pixel;
  }else{
	double half_view = tan(field_of_view/2);
	double aspect = (double)w/(double)h;
	half_w = half_view;
  	half_h = half_view/aspect;
  	if (aspect < 1){
    		half_w = half_view * aspect;
    		half_h = half_view;
  	}
  pixel = (half_w * 2) / (double)w;
  return pixel;
}
}

Ray Camera::ray_at_pixel(int x, int y) {
  //set the value of pixel
  pixel_size();
  // the offset from the edge of the canvas to the pixel's center
  double xoffset = (x + 0.5) * pixel;
  double yoffset = (y + 0.5) * pixel;
  // the untransformed coordinates of the pixel in world space.
  // (remember that the camera looks toward -z, so +x is to the *left*.)
  double world_x = half_w - xoffset;
  double world_y = half_h - yoffset;
  // using the camera matrix, transform the canvas point and the origin,
  // and then compute the ray's direction vector.
  // (remember that the canvas is at z = -1
  Tuple pixel_position = transform_matrix.inverse() * point(world_x, world_y, -1);
  Tuple origin = transform_matrix.inverse() * point(0, 0, 0);
  Tuple direction = pixel_position - origin;
  return Ray(origin, direction);

}

Canvas Camera::render(World world){
  Canvas image = Canvas(w, h);
  for(int y = 0; y < h; y++){
    for(int x = 0; x < w; x++){
      Ray ray = ray_at_pixel(x, y);
      Tuple pixel_color = world.colorAtRay(ray, REC_DEPTH);
      image.write_pixel(x, y, pixel_color);
    }}
  return image;

}

//String Conversion
std::ostream& operator << (std::ostream& os, Camera const& camera) {
    os << "CAMERA:: w: " + std::to_string(camera.w) + ", h: " +
     std::to_string(camera.h);
    return os;
}
