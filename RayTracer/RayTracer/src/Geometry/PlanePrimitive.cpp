#include "..\..\include\Geometry\PlanePrimitive.h"
#include "Maths/PolynomialSolver.h"


PlanePrimitive::PlanePrimitive(glm::vec4 _centre, glm::vec3 _planeNormal, AbstractMaterial *_material, Shader *_shader)
{
	m_centre = _centre;
	m_planeNormal = glm::normalize(_planeNormal);
	m_material = _material; 
	m_shader = _shader;
	m_colour = m_material->m_surfaceColour;
}


PlanePrimitive::~PlanePrimitive()
{
}


//----------------------------------------------------------------------------------
DistList PlanePrimitive::Intersect(const Ray &_ray)
{
	DistList result;
	Ray invRay;
	
	// transform ray into sphere space
	invRay.m_point = m_transform.TransformPointInverse(_ray.m_point);
	invRay.m_dir = m_transform.TransformDir(_ray.m_dir);

	float dirDotNorm = glm::dot(invRay.m_dir, m_planeNormal);
	if (dirDotNorm == 0.0f)
	{
		// rays is parallel to plane so will never intersect
		return result;
	}

	float rayPointDotNorm = glm::dot(glm::vec3(invRay.m_point), m_planeNormal);
	float planePointDotNorm = glm::dot(glm::vec3(m_centre), m_planeNormal);
	float t = -(rayPointDotNorm - planePointDotNorm) / (dirDotNorm);

	result.m_dist.push_back(t);

	return result;
}

//----------------------------------------------------------------------------------
bool PlanePrimitive::PointInside(const glm::vec4 &_point)
{
	return false;
}

//----------------------------------------------------------------------------------
glm::vec3 PlanePrimitive::Normal(const glm::vec4 &_point)
{
	return m_planeNormal;
}

//----------------------------------------------------------------------------------
glm::vec3 PlanePrimitive::GetColour(const glm::vec4 &_point)
{

	int checkSize = 2;
	int x = (int)abs(_point.x/checkSize);
	int z = (int)abs(_point.z/checkSize);

	if ((x % 2 == 0 && z % 2 == 0) || (x % 2 == 1 && z % 2 == 1))
	{
		//printf("black\n");
		return m_colour;
	}
	else
	{
		glm::vec3 col = glm::vec3(1.0f) - m_colour;
		//printf("white\n");
		//printf("%f, %f, %f\n", col.x, col.y, col.z);
		return col;
	}
}