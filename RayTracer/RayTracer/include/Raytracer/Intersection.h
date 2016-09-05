#pragma once

#include "Geometry/AbstractPrimitive.h"

class Intersection
{
public:
	Intersection();
	~Intersection();

	glm::vec3 m_Point;
	AbstractPrimitive * m_Prim;
	float m_dist;

};

