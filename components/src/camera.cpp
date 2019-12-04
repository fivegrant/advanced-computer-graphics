#include "components/include/camera.hpp"

void Camera::set_view_transform(Tuple place, Tuple look, Tuple up)
{
  Tuple forward = normalize(look - place);
  Tuple up_n = normalize(up);
  Tuple left = cross(forward, up_n);
  Tuple true_up = cross(left, forward);
  Matrix orientation = Matrix({  left.x,     left.y,     left.z,    0,
   				 true_up.x,  true_up.y,  true_up.z, 0,
				-forward.x, -forward.y,  forward.z, 0,
				     0,          0,         0,      1,
  				});
  transform_matrix = orientation * translation(-place.x, -place.y, -place.z);
  transform_matrix.inverse();
}

void Camera::set_fov(double value)
{
  field_of_view = value;
  pixel = pixel_size();
}

Matrix Camera::get_transform(){
  return transform_matrix;
}

double Camera::pixel_size()
{
  if (pixel != 0) {
	return pixel;
  }else{
	double half_view = tan(field_of_view/2);
	double aspect = w/h;
	double half_w = half_view;
  	double half_h = half_view/aspect;
  	if (aspect < 1){
    		half_w = half_view * aspect;
    		half_h = half_view;
  	}
  pixel = (half_w * 2) / h;
  return pixel;
}
}

Ray Camera::ray_at_pixel(int x, int y) {
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
  Tuple direction = normalize(pixel_position - origin);
  return Ray(origin, direction);

}

Canvas Camera::render(World world){
  //set the value of pixel
  pixel_size();

  Canvas image = Canvas(w, h);
  for(int y = 0; y < h; y++){
    for(int x = 0; x < w; x++){
      Ray ray = ray_at_pixel(x, y);
      volatile Ray rr = ray;
      volatile  Ray yeet = Ray(point(1, 1, 1), vector(-.7,-.07, -.7));
      volatile Ray nnn = Ray(point(10, 1, 1), vector(-.7,-.07, -.7));
      Tuple pixel_color = world.colorAtRay(ray);
      volatile Tuple h = pixel_color;
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
