#pragma once
#include "AbstractPrimitive.h"
#include "Materials/BasicMaterial.h"


class SpherePrimitive :	public AbstractPrimitive
{
public:
	SpherePrimitive(glm::vec4 _centre, double _rad, AbstractMaterial *_material, Shader *_shader);
	~SpherePrimitive();

	DistList Intersect(const Ray &_ray);
	bool PointInside(const glm::vec4 &_point);
	glm::vec3 Normal(const glm::vec4 &_point);
	glm::vec3 GetColour(const glm::vec4 &_point);

	//------------------------------------------------------------

	glm::vec4 m_centre;
	double m_radius;
};

