#include <glm/glm.hpp>
#include "GeometryNode.hpp"

using namespace std;
using namespace glm;

#include <vector>

//---------------------------------------------------------------------------------------
GeometryNode::GeometryNode(
	const std::string & name, Primitive *prim, Material *mat )
	: SceneNode( name )
	, m_material( mat )
	, m_primitive( prim )
{
	m_nodeType = NodeType::GeometryNode;
};

void GeometryNode::setMaterial( Material *mat )
{
	// Obviously, there's a potential memory leak here.  A good solution
	// would be to use some kind of reference counting, as in the 
	// C++ shared_ptr.  But I'm going to punt on that problem here.
	// Why?  Two reasons:
	// (a) In practice we expect the scene to be constructed exactly
	//     once.  There's no reason to believe that materials will be
	//     repeatedly overwritten in a GeometryNode.
	// (b) A ray tracer is a program in which you compute once, and 
	//     throw away all your data.  A memory leak won't build up and
	//     crash the program.

	m_material = mat;
};

//---------------------------------------------------------------------------------------
bool GeometryNode::intersect(Ray &ray, float closet, float fart, Intersection &intersection) {

	vec4 oAug = vec4(ray.origin, 1.0);
	vec4 dAug = vec4(ray.direction, 1.0);
	Ray transformRay(vec3(invtrans*oAug), vec3(invtrans*dAug));

	Intersection tempIntersection;
	float closest = fart;

	bool didPrimativeIntersect = m_primitive->intersect(transformRay, closet, fart, tempIntersection);
	if ( didPrimativeIntersect ) {
		tempIntersection.material = m_material;
		closest = tempIntersection.t;
		intersection = tempIntersection;
	}

	bool didSceneIntersect = SceneNode::intersect(ray, closet, closest, tempIntersection);
	if ( didSceneIntersect ) intersection = tempIntersection;

	if (didPrimativeIntersect || didSceneIntersect) {
		intersection.normal = mat3(transpose(invtrans))*intersection.normal;
		intersection.intersectionPoint = vec3(trans*vec4(intersection.intersectionPoint, 1.0));
		return true;
	}

	return false;
};