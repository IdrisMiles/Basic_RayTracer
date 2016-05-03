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
	
	virtual DistList Intersect(Ray &_ray) = 0;
	virtual int PointInside(glm::vec4 &_point) = 0;
	virtual glm::vec3 Normla(glm::vec4 &_point) = 0;
	virtual glm::vec3 GetColour(glm::vec4 &_point) = 0;



	Transform m_trans;

};