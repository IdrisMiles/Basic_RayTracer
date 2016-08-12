#include "SpherePrimitive.h"
#include "PolynomialSolver.h"
#include "MathPrint.h"

SpherePrimitive::SpherePrimitive(glm::vec4 _centre, double _rad)
{
	m_centre = _centre;
	m_radius = _rad;
}


SpherePrimitive::~SpherePrimitive()
{
}

//----------------------------------------------------------------------------------
DistList SpherePrimitive::Intersect(const Ray &_ray)
{
	DistList result;
	PolyReturn roots;
	Ray invRay;
	glm::vec3 pointToCentre;
	double c[3];

	// transform ray into sphere space
	invRay.m_point = m_transform.TransformPointInverse(_ray.m_point);
	invRay.m_dir = m_transform.TransformDir(_ray.m_dir);

	// get quadratic coefficients
	pointToCentre = glm::vec3(invRay.m_point - m_centre);
	/*
	float tca = glm::dot(pointToCentre, _ray.m_dir);
	float d2 = glm::dot(pointToCentre, pointToCentre) - (tca*tca);
	if (d2 < (m_radius*m_radius))
	{
		float thc = sqrt((m_radius * m_radius) - d2);
		result.m_dist.push_back(tca - thc);
		result.m_dist.push_back(tca + thc);
*/
#if !_DEBUG
		printf("______________________\n");
		printf("ray point\t: [%f,%f,%f]\n", invRay.m_point.x, invRay.m_point.y, invRay.m_point.z);
		printf("ray dir\t: [%f,%f,%f]\n", invRay.m_dir.x, invRay.m_dir.y, invRay.m_dir.z);
		printf("centre\t: [%f,%f,%f]\n", m_centre.x, m_centre.y, m_centre.z);
		printf("rad\t: %f\n", m_radius);
		//printf("t0 = %f\n", (tca - thc));
#endif
	//}
	
	
	c[2] = glm::dot(invRay.m_dir, invRay.m_dir);
	c[1] = 2 * glm::dot(pointToCentre, invRay.m_dir);
	c[0] = glm::dot(pointToCentre, pointToCentre) - (m_radius*m_radius);


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
bool SpherePrimitive::PointInside(const glm::vec4 &_point)
{
	glm::vec4 invPoint = m_transform.TransformPointInverse(_point);
	return (glm::dot(invPoint, invPoint) < m_radius*m_radius);
}

//----------------------------------------------------------------------------------
glm::vec3 SpherePrimitive::Normal(const glm::vec4 &_point)
{
	glm::vec4 invPoint = m_transform.TransformPointInverse(_point);
	return glm::normalize(m_transform.TransformNormal(glm::vec3(invPoint - m_centre)));
}

//----------------------------------------------------------------------------------
glm::vec3 SpherePrimitive::GetColour(const glm::vec4 &_point)
{
	return m_colour;
}