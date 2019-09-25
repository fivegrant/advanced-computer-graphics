#include "./tuple.hpp"

class Material{
  public:
    Tuple surface_color; 
    double diffuse;

    Material(Tuple r_color, double r_diffuse):
      surface_color(r_color), diffuse(r_diffuse) {}

    Material() {
      surface_color = Tuple(1, 1, 1, 0);
      diffuse = 1;
    }

    bool operator==(const Material&) const;

};

bool Material::operator==(const Material& rhs) const
{
  bool condition_1 = this->surface_color == rhs.surface_color;
  bool condition_2 = this->diffuse == rhs.diffuse;
  return condition_1 && condition_2;
}

//String Conversion
std::ostream& operator << (std::ostream& os, Material const& material) {
    os << "M[surface_color: " + 
     std::to_string(material.surface_color.x) + 
     std::to_string(material.surface_color.y) +
     std::to_string(material.surface_color.z) +
     std::to_string(material.surface_color.w) +

          ", diffuse" +
     std::to_string(material.diffuse);
    return os;
}
