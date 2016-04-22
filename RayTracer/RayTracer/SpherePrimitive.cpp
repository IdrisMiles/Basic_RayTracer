#include "SpherePrimitive.h"
#include "PolynomialSolver.h"

SpherePrimitive::SpherePrimitive(glm::vec4 _centre, double _rad)
{
	m_centre = _centre;
	m_radius = _rad;
}


SpherePrimitive::~SpherePrimitive()
{
}

//----------------------------------------------------------------------------------
DistList SpherePrimitive::Intersect(Ray &_ray)
{
	DistList result;
	PolyReturn roots;
	Ray invRay;
	glm::vec4 pointMC;
	double c[3];

	// transform ray into sphere space
	invRay.m_point = m_trans.TransformPointInverse(_ray.m_point);
	invRay.m_dir = m_trans.TransformNormal(_ray.m_dir);

	// get quadratic coefficients
	pointMC = invRay.m_point - m_centre;
	pointMC[3] = 0;
	c[2] = glm::dot(invRay.m_dir, invRay.m_dir);
	c[1] = 2 * glm::dot(glm::vec3(pointMC), invRay.m_dir);
	c[0] = glm::dot(pointMC, pointMC) - (m_radius*m_radius);

	// solve quadratic equation
	PolynomialSolver::QuadraticRoots(roots, c[2], c[1], c[0]);

	// store results
	for (int i = 0; i < roots.m_numVal; i++)
	{
		result.m_dist.push_back(roots.m_values[i]);
	}

	return result;
}

//----------------------------------------------------------------------------------
int SpherePrimitive::PointInside(glm::vec4 &_point)
{
	glm::vec4 invPoint = m_trans.TransformPointInverse(_point);
	if (glm::dot(invPoint, invPoint) < m_radius*m_radius)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//----------------------------------------------------------------------------------
glm::vec3 SpherePrimitive::Normla(glm::vec4 &_point)
{
	glm::vec4 invPoint = m_trans.GetInvTransformMat() * _point;
	return glm::normalize(m_trans.TransformNormal(glm::vec3(invPoint - m_centre)));
}

//----------------------------------------------------------------------------------
glm::vec3 SpherePrimitive::GetColour(glm::vec4 &_point)
{
	return m_colour;
}