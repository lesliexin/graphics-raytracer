#pragma once

#include "SceneNode.hpp"
#include "Primitive.hpp"
#include "Material.hpp"

#include <vector>

class GeometryNode : public SceneNode {
public:
	GeometryNode( const std::string & name, Primitive *prim, 
		Material *mat = nullptr );

	void setMaterial( Material *material );
	virtual bool intersect(Ray &ray, float closet, float fart, Intersection &intersection);
	Material *m_material;
	Primitive *m_primitive;
};
