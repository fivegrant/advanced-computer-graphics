#include "objects/include/material.hpp"
#include <iostream>

bool Material::operator==(const Material& rhs) const
{
  bool condition_1 = this->surface_color == rhs.surface_color;
  bool condition_2 = this->diffuse == rhs.diffuse;
  return condition_1 && condition_2;
}

Tuple Material::colorAtPoint(Light light, Tuple position, Tuple eyev, Tuple normalv, bool in_shadow)
{
  //normalv = normal
  //hitPoint = position

  // combine the surface color with the light's color/intensity
  Tuple effective_color = surface_color * light.intensity;


  // find the direction to the light source
  Tuple vectorToLight = normalize(light.position - position);

  // compute the ambient contribution
  Tuple effective_ambient = effective_color * ambient;

  // set defaults for diffuse and specular contribution
  Tuple effective_diffuse = color(0, 0, 0); 
  Tuple effective_specular = color(0, 0, 0);;

  if (!in_shadow){
  //  light_dot_normal represents the cosine of the angle between the 
  //  light vector and the normal vector. A negative number means the 
  //  light is on the other side of the surface.
  if (vectorToLight.dot(normalv) >= 0){
    // compute the diffuse contribution
    effective_diffuse = effective_color * diffuse * vectorToLight.dot(normalv);

    // reflect_dot_eye represents the cosine of the angle 
    // between the reflection vector and the eye vector. 
    // A negative number means the light reflects away from theeye. 
    // the line below used to read `Tuple reflectv = vectorToLight.reflect(normalv);`
    Tuple reflectv = vectorToLight.reflect(normalv);
    double reflect_dot_eye = reflectv.dot(eyev);
    if (reflect_dot_eye <= 0){
      effective_specular = color(0, 0, 0);
    }else{
      // compute the specular contribution
      double factor = pow(reflect_dot_eye, shininess);
      effective_specular = light.intensity * specular * factor;
    }
  }
  }

  // Add the three contributions together to get the final shading
  return effective_ambient + effective_diffuse + effective_specular;
}

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

