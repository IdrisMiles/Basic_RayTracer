#pragma once

#include "AbstractPrimitive.h"

class Intersection
{
public:
	Intersection();
	~Intersection();

	glm::vec4 m_Point;
	AbstractPrimitive * m_Prim;

};

