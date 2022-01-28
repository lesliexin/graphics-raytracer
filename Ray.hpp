#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>

 #include "Material.hpp"
 
class Ray {
public:
	glm::vec3 origin;
	glm::vec3 direction;

    Ray(const glm::vec3& o,const glm::vec3& d);
    Ray();

    glm::vec3 get_origin();
    glm::vec3 get_direction();

    glm::vec3 point_at_t(float t);
};

#ifndef Intersection_hpp
#define Intersection_hpp

class Intersection {
public:
    float t;
    glm::vec3 intersectionPoint;
    glm::vec3 normal;
    Material *material;
};

#endif
