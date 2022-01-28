#include <glm/glm.hpp>
#include <vector>

#include <iostream>
#include "Ray.hpp"
#include "Primitive.hpp"
#include "polyroots.hpp"
#include "Mesh.hpp"

#include <vector>


using namespace glm;
using namespace std;


Primitive::~Primitive()
{
}

bool Primitive::intersect( Ray &ray, float closet, float fart, Intersection &intersection) {
    return false;
}

Sphere::Sphere() {
    primative = new NonhierSphere(vec3(0.0, 0.0, 0.0), 1.0);
}

Sphere::~Sphere()
{
}

bool Sphere::intersect( Ray &ray, float closet, float fart, Intersection &intersection) {
    return primative->intersect(ray, closet, fart, intersection);
}

Cube::Cube() {
    primative = new NonhierBox(vec3(0.0, 0.0, 0.0), 1.0);
}
Cube::~Cube()
{
}

bool Cube::intersect(Ray &ray, float closet, float fart, Intersection &intersection) {
    return primative->intersect(ray, closet, fart, intersection);
}

NonhierSphere::~NonhierSphere()
{
}

bool NonhierSphere::intersect(Ray &ray, float closet, float fart, Intersection &intersection) {
   vec3 oc = ray.get_origin() - position;
   vec3 r = ray.get_direction();

   double A = dot(r, r);
   double B = 2*dot(r, oc);
   double C = dot(oc, oc) - pow(rad, 2);

    double roots[2] = {0,0};
    int numOfRoots =  quadraticRoots(A, B, C, roots);

    float t = 0;

    if (numOfRoots >= 2) {
        t = glm::min(roots[0], roots[1]);
    } else if (numOfRoots == 1) {
        t = roots[0];
    } else {
        return false;
    }

    if ( t > closet && t < fart ) {
        intersection.t = t;
        intersection.intersectionPoint = ray.point_at_t(t);
        intersection.normal = intersection.intersectionPoint - position;
        return true;
    }
    return false;
}

NonhierBox::NonhierBox(const glm::vec3& pos, double size)
    : position(pos), m_size(size)
{
    std::vector<glm::vec3> vertices = {
        position + glm::vec3(0.0, 0.0, 0.0),
        position + glm::vec3(0.0, m_size, 0.0),
        position + glm::vec3(m_size, 0.0, 0.0),
        position + glm::vec3(m_size, m_size, 0.0),
        position + glm::vec3(0.0, 0.0, m_size),
        position + glm::vec3(0.0, m_size, m_size),
        position + glm::vec3(m_size, 0.0, m_size),
        position + glm::vec3(m_size, m_size, m_size),
    };
    
    std::vector<glm::vec3> indicies = {
      glm::vec3(0, 1, 2),
      glm::vec3(1, 3, 2),
      glm::vec3(4, 5, 6),
      glm::vec3(5, 7, 6),
      glm::vec3(4, 5, 0),
      glm::vec3(5, 1, 0),
      glm::vec3(6, 7, 2),
      glm::vec3(7, 3, 2),
      glm::vec3(1, 5, 3),
      glm::vec3(5, 7, 3),
      glm::vec3(0, 4, 2),
      glm::vec3(4, 1, 2)
    };

    std::vector<Triangle> faces(indicies.size());
    for (int i = 0; i < indicies.size(); i++) {
		Triangle triangle((size_t)indicies[i].x, (size_t)indicies[i].y, (size_t)indicies[i].z);

		faces[i] = triangle;
	}
    m_mesh = new Mesh(vertices, faces);
}

NonhierBox::~NonhierBox()
{
}

bool NonhierBox::intersect(Ray &ray, float closet, float fart, Intersection &intersection) {
   return m_mesh->intersect(ray, closet, fart, intersection);
}


NonhierCone::NonhierCone(const glm::vec3& pos, double size)
    : position(pos), m_size(size) {

    std::vector<glm::vec3> vertices = {
        position + glm::vec3(0.0, 0.0, 0.0),
        position + glm::vec3(size, 0.0, 0.0),
        position + glm::vec3(size/2, 0.0, size * sqrt(3) / 2),
        position + glm::vec3(size/2, size, size/2),
    };
    
    std::vector<glm::vec3> indicies = {
      glm::vec3(0, 1, 2),
      glm::vec3(0, 1, 3),
      glm::vec3(1, 2, 3),
      glm::vec3(0, 2, 3)
    };

    std::vector<Triangle> faces(indicies.size());
    for (int i = 0; i < indicies.size(); i++) {
		Triangle triangle((size_t)indicies[i].x, (size_t)indicies[i].y, (size_t)indicies[i].z);

		faces[i] = triangle;
	}
    m_mesh = new Mesh(vertices, faces);
}

NonhierCone::~NonhierCone()
{
    delete m_mesh;
}

bool NonhierCone::intersect(Ray &ray, float closet, float fart, Intersection &intersection) {
   return m_mesh->intersect(ray, closet, fart, intersection);
}