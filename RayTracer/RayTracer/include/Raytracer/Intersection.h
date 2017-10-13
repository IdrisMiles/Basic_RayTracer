#pragma once
#ifndef _INTERSECTION__H_
#define _INTERSECTION__H_

#include "Geometry/AbstractPrimitive.h"

class Intersection
{
public:
	Intersection();
	~Intersection();

	glm::vec3 m_Point;
    AbstractPrimitive *m_Prim;
	float m_dist;

};


#endif //_INTERSECTION__H_
