#pragma once

#include "Maths/Transform.h"
#include "Maths/Ray.h"
#include "Raytracer/DistList.h"
#include "Materials/AbstractMaterial.h"
#include "Shaders/Shader.h"

class AbstractPrimitive
{
public:
	AbstractPrimitive();
	~AbstractPrimitive();

	void TransformPrim(glm::mat4 &_trans);
	
	virtual bool Intersect(DistList &_distList, const Ray &_ray) = 0;
	virtual bool PointInside(const glm::vec3 &_point) = 0;
	virtual glm::vec3 Normal(const glm::vec3 &_point) = 0;
	virtual glm::vec3 GetColour(const glm::vec3 &_point) = 0;

	//------------------------------------------------------------

	Transform m_transform;
	glm::vec3 m_colour;
	AbstractMaterial *m_material;
	Shader *m_shader;
};