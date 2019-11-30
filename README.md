# Advanced Computer Graphics
- Language: C++
  - Unit Testing: Catch2

# Dependencies
- Catch2: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top 

# TODO
- Test World
- Test Reflection
- Implement `inShadow()`
- Implement Camera class in `components`
  - Include Orthographic
  - Include Perspective
- Finish Triangles

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

# Questions
- Review Refraction
- Review Monte Carlo Integration/Sampling

# Acknowledgements
- Thanks Satchel Baldwin for helping with the `makefile`
