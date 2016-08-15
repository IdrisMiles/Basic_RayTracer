#pragma once
#include "AbstractPrimitive.h"

#include "Materials/BasicMaterial.h"


class PlanePrimitive : public AbstractPrimitive
{
public:
	PlanePrimitive(glm::vec4 _centre, glm::vec3 _planeNormal, AbstractMaterial *_material, Shader *_shader);
	~PlanePrimitive();

	DistList Intersect(const Ray &_ray);
	bool PointInside(const glm::vec4 &_point);
	glm::vec3 Normal(const glm::vec4 &_point);
	glm::vec3 GetColour(const glm::vec4 &_point);

	//------------------------------------------------------------

	glm::vec4 m_centre;
	glm::vec3 m_planeNormal;	

};

