#pragma once
#include "AbstractPrimitive.h"

#include "Materials/BasicMaterial.h"


class PlanePrimitive : public AbstractPrimitive
{
public:
	PlanePrimitive(glm::vec3 _centre, glm::vec3 _planeNormal, AbstractMaterial *_material, Shader *_shader);
	~PlanePrimitive();

	bool Intersect(DistList &_distList, const Ray &_ray);
	bool PointInside(const glm::vec3 &_point);
	glm::vec3 Normal(const glm::vec3 &_point);
	glm::vec3 GetColour(const glm::vec3 &_point);

	//------------------------------------------------------------

	glm::vec3 m_centre;
	glm::vec3 m_planeNormal;	

};

