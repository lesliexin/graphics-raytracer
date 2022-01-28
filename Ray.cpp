#include "Ray.hpp"

using namespace std;
using namespace glm;

Ray::Ray() {
    origin = vec3();
    direction =  vec3();
}

Ray::Ray(const vec3& o,const vec3& d) {
    origin = o;
    direction = d;
}

vec3 Ray::get_origin() {
    return origin;
}

vec3 Ray::get_direction() {
    return direction;
}

vec3 Ray::point_at_t(float t) {
    return t*direction + origin;
}