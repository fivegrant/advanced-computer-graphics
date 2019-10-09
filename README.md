# Advanced Computer Graphics
- Languge: C++
  - Unit Testing: Catch2

# Dependencies
- Catch2: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top 
# TODO
- Implement World class
  - `intersectionWith(Ray)`
  - `addObject(Object)`
  - `addLight(Light)`
  - `colorAtIntersection(Intersection)`
- Implement Intersection Class
  - `double t`
  - `Ray` 
  - `Object`
  - `generateHitRecord()`
    - dont forget to calculate: overpoint = hitPoint + (normal * epsilon)
- Implement `inShadow()`
- Update Matrix to include `rotation()`
- Update Tuple
  - Include Reflection
- Implement Camera class
  - Include Orthographic
  - Include Perspective
- Break up Header Files
- Restructure mechanics/ and components/
- Write Makefile
- Add `red`, `green`, and `blue` to Tuple
- Implement Matrix Storage for `matrix.hpp`

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
## Rotation
- rotate around x:
  ```
    1	  0	     0       0
    0 cos(theta)  sin(theta) 0 
    0 -sin(theta) cos(theta) 0
    0      0         0       1
    ```
- rotate around y:
    ```
    cos(theta)	  0	-sin(theta)  0
        0 	  1          0       0 
    sin(theta) 	  0      cos(theta)  0
        0         0         0        1
    ```
- rotate around z:
   ```
    cos(theta)  sin(theta)     0      0
    -sin(theta) cos(theta)     0      0 
         0          0          1      0
         0          0          0      1
    ```
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

# Questions
- `double magsquare(Tuple vector)`: Return a vector dotted with itself
- Handling error constant in multiple file
