# Graphics RayTracer

---

## Introduction

This project was created as a part of the Computer Graphics (CS488) course at the University of Waterloo.

---

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

---

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

## Objectives

- Additional primitive
- Anti-aliasing
- Glossy Reflection
- Specular Refraction
- Glossy Refraction
- Soft Shadows
- Depth of Field
- Texture Mapping
- Animation
- Final scene
