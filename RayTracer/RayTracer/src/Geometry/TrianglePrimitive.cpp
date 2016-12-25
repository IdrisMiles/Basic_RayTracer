#include "Geometry/TrianglePrimitive.h"


TrianglePrimitive::TrianglePrimitive(glm::vec3 _verts[3], AbstractMaterial *_material, Shader *_shader)
{
	m_verts[0] = _verts[0];
	m_verts[1] = _verts[1];
	m_verts[2] = _verts[2];
	m_centre = (m_verts[0] + m_verts[1] + m_verts[2])/3.0f;
	m_faceNormal = glm::cross((m_verts[1] - m_verts[0]), (m_verts[2] - m_verts[0]));
	m_area = glm::length(m_faceNormal);
	m_faceNormal = glm::normalize(m_faceNormal);

	m_material = _material;

	m_shader = _shader;

}


TrianglePrimitive::~TrianglePrimitive()
{
}


bool TrianglePrimitive::Intersect(DistList &_distList, const Ray &_ray)
{
	Ray invRay;

	// transform ray into sphere space
	invRay.m_point = m_transform.TransformPointInverse(_ray.m_point);
	invRay.m_dir = m_transform.TransformDir(_ray.m_dir);

	float dirDotNorm = glm::dot(invRay.m_dir, m_faceNormal);
	if (abs(dirDotNorm) < 0.001f)
	{
		// rays is parallel to plane so will never intersect
		return false;
	}

	float rayPointDotNorm = glm::dot(invRay.m_point, m_faceNormal);
	float planePointDotNorm = glm::dot(m_centre, m_faceNormal);
	float t = -(rayPointDotNorm - planePointDotNorm) / (dirDotNorm);

	glm::vec3 hitPoint = _ray.m_point + (_ray.m_dir * t);

	if (PointInside(hitPoint))
	{
		_distList.m_dist.push_back(t);
		return true;
	}

	return false;
}


bool TrianglePrimitive::PointInside(const glm::vec3 &_point)
{
	/*
	glm::vec3 AP = _point - m_verts[0];
	glm::vec3 AB = m_verts[1] - m_verts[0];
	glm::vec3 AC = m_verts[2] - m_verts[0];

	float areaABC = glm::length(glm::cross(AB, AC));
	float alpha = glm::length(glm::cross(AP,AB)) / areaABC;
	float beta = glm::length(glm::cross(AP, AC)) / areaABC;

	if ( (alpha >= 0.0f) && (beta >= 0.0f) && (alpha + beta <= 1.0f) )
	{
		return true;
	}
	*/

	glm::vec3 c;
	
	glm::vec3 edge01 = m_verts[1] - m_verts[0];
	glm::vec3 edge0P = _point - m_verts[0];
	c = glm::cross(edge01, edge0P);
	if (glm::dot(m_faceNormal, c) < 0)
	{
		return false;
	}

	glm::vec3 edge12 = m_verts[2] - m_verts[1];
	glm::vec3 edge1P = _point - m_verts[1];
	c = glm::cross(edge12, edge1P);
	if (glm::dot(m_faceNormal, c) < 0)
	{
		return false;
	}

	glm::vec3 edge20 = m_verts[0] - m_verts[2];
	glm::vec3 edge2P = _point - m_verts[2];
	c = glm::cross(edge20, edge2P);
	if (glm::dot(m_faceNormal, c) < 0)
	{
		return false;
	}


	return true;
}


glm::vec3 TrianglePrimitive::Normal(const glm::vec3 &_point)
{
	return m_faceNormal;
}


glm::vec3 TrianglePrimitive::GetColour(const glm::vec3 &_point)
{
	return m_material->m_surfaceColour;
}
