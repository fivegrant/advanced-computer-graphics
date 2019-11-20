#include "objects/include/light.hpp"

bool Light::operator==(const Light& rhs) const
{
  return position == rhs.position && intensity == rhs.intensity;
}
void Light::point_light(Tuple new_position, Tuple new_intensity)
{
  this->position = new_position;
  this->intensity = new_intensity;
}



//String Conversion
std::ostream& operator << (std::ostream& os, Light const& light) {
    os << "L[intensity: " + 
     std::to_string(light.intensity.x) + 
     std::to_string(light.intensity.y) +
     std::to_string(light.intensity.z) +
     std::to_string(light.intensity.w) +
     ", position: " + 
     std::to_string(light.position.x) + 
     std::to_string(light.position.y) +
     std::to_string(light.position.z) +
     std::to_string(light.position.w);
    return os;
}


