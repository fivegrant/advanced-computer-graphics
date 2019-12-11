# Advanced Computer Graphics
- Language: C++
  - Unit Testing: Catch2

# Dependencies
- Catch2: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top 

# TODO
- Finish Triangles
- Load in OBJ
- Implement Antialiasing

# Notes
## More Lighting
```class LightRecord:
  directionToLight
  distanceFromLight
  normalOfTheLight?

in PointLight
  generateLightRecord(hitRecord)
  vectorToLight = position - hitPoint
  direction = vectorToLight.normalized
  distance = vectorToLight.magnitude

in DirectionalLight
  direction = direction
  distance = ##infinite##
in Shape
  castsShadows = False

in colorAtPoint()
  colorsofar = black
  for light in lights
    light.generateLightRecord(HitRecord)
  color t = calculate diffuse
        t =           specular
	t =           ambient
  lightDirectionDotNormal = lightRecord.direction.dot(hitRecord.normal)
  inShadow()?
    shadowRay = Ray(hitRecord.overpoint, light.direction)
    castTheRay
    intersection.pointer(t > 0 and t < LightRecord.distance)
in AreaLight
  generateLightRecord(hitRecord)
  vectorToLight = getNextSample() - hitPoint
  
```
## Textures

Texture is an abstract class

### 3D
SolidColor
  getTextureColor(local -> Point){base color}
    if sin(point.x) < 0
      color 1
    else:
      color2
  FuzzyStripes:
    t = (sin(point.x) + 1)/2
    return color1*t+color2(1-t)
### 2D

```#include <iostream>
#include <limits>
#include <numeric>
// Computes the normal to this shape at the point p_W in the world frame, W.
Tuple Shape::normalAtPoint(Tuple p_W)
{
  // Get the 4x4 matrix that transforms points from the body frame to the world
  // frame.
  Matrix X_WB = transform_matrix;

  // localNormal() requires the point to be in the body frame (B). So transform
  // the point from Frame W to Frame B.
  Tuple p_B = X_WB.inverse() * p_W;  
  Tuple normal_B = localNormal(p_B);
  assert(std::abs(magnitude(normal_B) - 1.0) < std::numeric_limits<double>::epsilon()); 

  // Transform the normal from Frame B back to Frame W. To do this, we need
  // the rotational component of X_WB because we want to change the normal to 
  // a different basis (W instead of B). We mimic this operation by zeroing the
  // w component of normal_B.
  normal_B.w = 0;
  Tuple normal_W = X_WB * normal_B;

  // Since scaling can be incorporated into the transformation matrix, we have
  // to renormalize this vector.
  return normalize(normal_W);
}

//String Conversion
std::ostream& operator << (std::ostream& os, Shape const& shape) {
    os << shape.shape_type + ": (" + std::to_string(shape.center.x) + ", " + std::to_string(shape.center.y) + ", " + std::to_string(shape.center.z) + ")";
    return os;
}```


# Questions
- Review Monte Carlo Integration/Sampling

# Acknowledgements
- Thanks Satchel Baldwin for helping with the `makefile`
- Thanks Evan Drumwright for introducing me to monograph notation
