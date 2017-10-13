#include "Geometry/PlanePrimitive.h"
#include "Maths/PolynomialSolver.h"


PlanePrimitive::PlanePrimitive(glm::vec3 _centre, glm::vec3 _planeNormal, AbstractMaterial *_material, Shader *_shader)
{
	m_centre = _centre;
	m_planeNormal = glm::normalize(_planeNormal);
	m_material = _material; 
	m_shader = _shader;
	m_colour = m_material->m_surfaceColour;
    m_name = "PlanePrimitive";
}


PlanePrimitive::~PlanePrimitive()
{
}


//----------------------------------------------------------------------------------
bool PlanePrimitive::Intersect(DistList &_distList, const Ray &_ray)
{
	Ray invRay;
	
	// transform ray into sphere space
	invRay.m_point = m_transform.TransformPointInverse(_ray.m_point);
	invRay.m_dir = m_transform.TransformDir(_ray.m_dir);

	float dirDotNorm = glm::dot(invRay.m_dir, m_planeNormal);
	if (dirDotNorm == 0.0f)
	{
		// rays is parallel to plane so will never intersect
		return false;
	}

	float rayPointDotNorm = glm::dot(invRay.m_point, m_planeNormal);
	float planePointDotNorm = glm::dot(m_centre, m_planeNormal);
	float t = -(rayPointDotNorm - planePointDotNorm) / (dirDotNorm);

	_distList.m_dist.push_back(t);

	return true;
}

//----------------------------------------------------------------------------------
bool PlanePrimitive::PointInside(const glm::vec3 &_point)
{
	return false;
}

//----------------------------------------------------------------------------------
glm::vec3 PlanePrimitive::Normal(const glm::vec3 &_point)
{
	return m_planeNormal;
}

//----------------------------------------------------------------------------------
glm::vec3 PlanePrimitive::GetColour(const glm::vec3 &_point)
{
	glm::vec3 col(0.0f);

	int checkSize = 2;
	int x = (int)abs(_point.x/checkSize);
	int z = (int)abs(_point.z/checkSize);

	x += (_point.x < 0) ? 1 : 0;
	z += (_point.z < 0) ? 1 : 0;

	if ((x % 2 == 0 && z % 2 == 0) || (x % 2 == 1 && z % 2 == 1))
	{
		//printf("black\n");
		col =  m_colour;
	}
	else
	{
		col = glm::vec3(1.0f) - m_colour;
	}

	return col;
}
