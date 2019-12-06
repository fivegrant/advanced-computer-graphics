# Advanced Computer Graphics
- Language: C++
  - Unit Testing: Catch2

# Dependencies
- Catch2: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top 

# TODO
- Test Reflection and Refraction
- Implement `inShadow()`
- Finish Triangles
- Load in OBJ
- Implement Antialiasing
- Add Scripting Language if time allows?

# Notes
## Object
- material
- transform
### Sphere
- intersectionWith(Ray)
  - `world_ray -> object_ray`
  - `object_ray = transform.inverse() * world_ray`
- normalAt(Point)
  - `object_normal = objPoint - point(0, 0, 0)`
  - `world_normal= transform.inverse().transpose() object_normal`
  - `return normalized(object_normal)`;
### Plane
- y = 0
- intersectionsWith(Ray)
- normalAt(Point)
  - `objectNormal = Vec(0, 1, 0)`
  - `return worldNormal = transform.inverse().transpose() * objectNormal`

## Shadows
- Steps for each pixel:
	- Make a ray
	- Find intersections w/World
	- Asking the Objects(Material)
		- What color is it at the point of intersection
	- ColorAtPoint(HitRecord, World) for light in World.lights
		- ambient
		- inShadow() = true, if true, skip diffuse and specular
		- diffuse
		- specular
- inShadow()
	- `Ray ShadowRay = Ray(overpoint, normalize(light.position - hitpoint));`
	- `world.intersectionsWith(ShadowRay);`
	- 0 < error < magnitude(light.position-hitPoint) or distance from hitpoint to light
## Flow
- Main
- World
- Camera.render(World, MAX_RECURSION) 
- World.colorWithRay(Ray, MAX_RECURSION)
  - world.intersectionsWithRay(Ray)
  - firstIntersectionT > 0
  - colorAtPoint(interception.generateHitRecord, world, mr)
 
## Reflections
- loop for all lights
- `ambientColor = this->color * light.color * this->ambient`
- if not in shadow
- `lightIntensity = normal.dot(unitVectorToLight)`
- `diffuseColor = this->color * light.color + self.diffuse * lightIntensity`
- `specularIntensity = eye.dot(reflectedVectorToLight)`
- `specularColor = light.color * specularIntensity * specular`
- end of not in shadow
- `reflectedRay = Ray(overPoint, eye.reflectedOverNormal())`
- `reflectedColor = world.colorWithRay(reflectedRay, MAX_RECURSION - 1)`
- add the following to collected_colors `reflectedColor * this->reflectivity to colors + `ambientColor` + `diffuseColor` + `specularColor`
- end loop
- return sum(collect_colors)

## Refraction
- index of refraction (n)
- n1 * sin(theta1) = n2 * sin(theta2)
- total internal reflection is true when sin(theta_n) > 1 or < -1
- add this to the loop of all lights:
  - refractedColor = world.colorWithRay(refractedRay, MAX_RECURSION - 1) * self.transparency
- containers = List<Intersections>
```for intersection in intersection
	if intersection is self
	  if containers is empty
	    ior_incoming = 1```
	  else
	    ior_incoming = contains[-1].obj.material.ior
	if containers contains an intersection with same obj as self obj
	  remove that intersection
	else
	  add to containers
	if intersections is self
	  if containers is empty
	    ior_transmitted = 1
	  else
	    ior_transmitted
	    contains[01].obj.material.ior
```	
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
- Review Refraction
- Review Monte Carlo Integration/Sampling

# Acknowledgements
- Thanks Satchel Baldwin for helping with the `makefile`
- Thanks Evan Drumwright for introducing me to monograph notation
