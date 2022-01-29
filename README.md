# Graphics RayTracer

## Introduction

This project was created as a part of the Computer Graphics (CS488) course at the University of Waterloo. A ray-tracer is a computer program that traces the path of light rays as they bounce around a scene to create a final image, video, or interactive experience.

The main functions of a ray tracer are the following:
- Cast primary rays from the eye position through every pixel in an image plane
- Intersect primary rays with scene geometry
- Cast shadow rays from intersection points to each light source and
- Use the gathered information to perform illumination calculations and choose a colour for the pixels associated with the primary rays

## Features

### 1. Anti-aliasing
The first feature is anti-aliasing through supersampling. During sampling, errors are introduced, one of them being jaggies. Jaggies are the staircase, jagged pattern that appears near edges due to aliasing. To mitigate this, 10x10 (shown below) and 4x4 supersampling was used to approximate the value of a pixel, by averaging the values of 10 and 4 points within the pixel.

<p align="center">
  <img width="300" height="300" src="https://raw.githubusercontent.com/lesliexin/graphics-raytracer/main/Images/antiAliasing.png">
</p>

### 2. Glossy Reflection
Glossy reflection was achieved through tracing multiple rays based on a uniform distribution and subsequently averaging the colour values.

<p align="center">
  <img width="300" height="300" src="https://raw.githubusercontent.com/lesliexin/graphics-raytracer/main/Images/glossyReflection.png">
</p>

### 3. Specular Refraction
The third objective is specular refraction. Refraction was calculated using the surface normals, Snell’s law, and the respective indices of refraction of the two materials. The percentage of reflected light versus refracted light is calculated using Fresnel’s equation. Shown below is the scene in which the largest sphere has a 0.2 refraction index.

<p align="center">
  <img width="300" height="300" src="https://raw.githubusercontent.com/lesliexin/graphics-raytracer/main/Images/refraction02.png">
</p>


### 4. Glossy Refraction
Similarly to glossy reflection, glossy refraction was built upon regular refraction with the addition of secondary rays based on a uniform distribution and then finding the average. Shown below is the same scene as above with a refraction index of 0.2.

<p align="center">
  <img width="300" height="300" src="https://raw.githubusercontent.com/lesliexin/graphics-raytracer/main/Images/glossyRefraction02.png">
</p>

### 5. Soft Shadows
Soft shadows were created through adding area light sources instead of a single ray from a point light source. Similar to glossy reflection and refraction discussed earlier, this was implemented by sending multiple rays from the intersection point to a uniform distribution of points on the area light source. The resulting values were then averaged to create the soft shadows.

<p align="center">
  <img width="300" height="300" src="https://raw.githubusercontent.com/lesliexin/graphics-raytracer/main/Images/softShadows.png">
</p>


### 6. Depth of Field
The last feature is depth of field. This was achieved by swapping the pinhole camera for a square camera lens. The depth of field is determined by the aperture and focal length variables which determines the focal point of where the light rays intersect with each other.

<p align="center">
  <img width="300" height="300" src="https://raw.githubusercontent.com/lesliexin/graphics-raytracer/main/Images/depthOfField.png">
</p>


## Compilation

Run the following commands in the terminal to start the program.

```$ cd cs488
cs488$ premake4 gmake
cs488$ make

$ cd graphics-raytracer
graphics-raytracer$ premake4 gmake
graphics-raytracer$ make
graphics-raytracer$ cd Assets
graphics-raytracer/Assets$ ../A5 nonhier.lua
graphics-raytracer/Assets$ ../A5 finalScene.lua
```

## Specifications

To toggle each feature, the following constants are used:

```
const bool REFLECTION_ON = true;
const bool GLOSSY_REFLECTION_ON = false;
const bool REFRACTION_ON = false;
const bool GLOSSY_REFRACTION_ON = false;
const bool SOFT_SHADOWS_ON = false;
const bool ANTI_ALIASING_ON = false;
const bool DEPTH_OF_FIELD_ON = false;

```

It should be noted that when glossy reflection is true, reflection must be true as well. The same applied to refraction.

In addition, when toggling between reflection and refraction, the reflective and refractive properties can be edited in the `nonhier.lua` file.

To toggle the material for instance of the largest sphere, the last three arguments in the following function call can be changed:
`glass = gr.material( {0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0.9, 0.0, 0.0) `

The first variable is the reflection coefficient, the next is the refraction coefficient, and the last is the ratio of refraction.
