#pragma once
#include "AbstractPrimitive.h"


class TrianglePrimitive : public AbstractPrimitive
{
public:
	TrianglePrimitive(glm::vec3 _verts[3], AbstractMaterial *_material, Shader *_shader);
	~TrianglePrimitive();

	bool Intersect(DistList &_distList, const Ray &_ray);
	bool PointInside(const glm::vec3 &_point);
	glm::vec3 Normal(const glm::vec3 &_point);
	glm::vec3 GetColour(const glm::vec3 &_point);

	//------------------------------------------------------------

	glm::vec3 m_verts[3];
	glm::vec3 m_vertNormal[3];
	glm::vec3 m_faceNormal;
	glm::vec3 m_centre;
	float m_area;



};

