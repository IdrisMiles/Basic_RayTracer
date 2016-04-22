#pragma once
#include "AbstractPrimitive.h"
class SpherePrimitive :	public AbstractPrimitive
{
public:
	SpherePrimitive(glm::vec4 _centre, double _rad);
	~SpherePrimitive();

	DistList Intersect(Ray &_ray);
	int PointInside(glm::vec4 &_point);
	glm::vec3 Normla(glm::vec4 &_point);
	glm::vec3 GetColour(glm::vec4 &_point);
	
	glm::vec4 m_centre;
	double m_radius;
	glm::vec3 m_colour;
};

