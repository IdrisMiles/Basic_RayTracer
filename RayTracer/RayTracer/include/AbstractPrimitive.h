#pragma once

#include "Transform.h"
#include "Ray.h"
#include "DistList.h"

class AbstractPrimitive
{
public:
	AbstractPrimitive();
	~AbstractPrimitive();

	void TransformPrim(glm::mat4 &_trans);
	
	virtual DistList Intersect(const Ray &_ray) = 0;
	virtual bool PointInside(const glm::vec4 &_point) = 0;
	virtual glm::vec3 Normal(const glm::vec4 &_point) = 0;
	virtual glm::vec3 GetColour(const glm::vec4 &_point) = 0;

	//------------------------------------------------------------

	Transform m_transform;
	glm::vec3 m_colour;

};