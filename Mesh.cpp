#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"

#include <vector>

using namespace glm;
using namespace std;

Mesh::Mesh( const std::string& fname )
	: m_vertices()
	, m_faces()
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	std::ifstream ifs( fname.c_str() );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
		}
	}
}

Mesh::Mesh( std::vector<glm::vec3>& vertices, const std::vector<Triangle> &faces) :
	m_vertices(vertices), m_faces(faces) {
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";
  out << "}";
  return out;
}

bool Mesh::intersect(Ray &ray, float closet, float fart, Intersection &intersection) {
	float closest = fart;
	vec3 normal = vec3();
    bool intersect = false;

	for ( Triangle triangle : m_faces ) {
        float tmp_t;

		// Möller–Trumbore intersection algorithm
		// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
		vec3 vertex0 = m_vertices[triangle.v1];
		vec3 vertex1 = m_vertices[triangle.v2];
		vec3 vertex2 =  m_vertices[triangle.v3];

		bool doesIntersect = false;

		const float EPSILON = 0.0000001;
		glm::vec3 edge1, edge2, h, s, q;
		float a, f, u, v;
		edge1 = vertex1 - vertex0;
		edge2 = vertex2 - vertex0; 

		h = glm::cross(ray.get_direction(), edge2);
		a = glm::dot(edge1, h);
		if (a > -EPSILON && a < EPSILON) {
			return false;
		}
		f = 1 / a;
		s = ray.get_origin() - vertex0;
		u = f * (glm::dot(s, h));
		if (u > 0.0 && u < 1.0) {
			q = glm::cross(s, edge1);
			v = f * glm::dot(ray.get_direction(), q);
			if (v > 0.0 && u + v < 1.0) {
				float t = f * glm::dot(edge2, q);
				if (t > EPSILON) // ray intersection
				{
					tmp_t = t;
					if ( tmp_t < closest && tmp_t > closet ) {
						intersect = true;
						closest = tmp_t;
						normal = cross(m_vertices[triangle.v1] - m_vertices[triangle.v2], m_vertices[triangle.v2] - m_vertices[triangle.v3]);
					}
				}	
			}
		}
    }

	if ( intersect ) {

		// if orthogonal
		if ( dot( ray.get_direction(), normal ) > 0 ) {
			normal *= -1;
		}

		intersection.t = closest;
		intersection.intersectionPoint = ray.point_at_t(intersection.t);
		intersection.normal = normal;
		intersection.material = nullptr;
		return intersect;
	}
	return false;
}

