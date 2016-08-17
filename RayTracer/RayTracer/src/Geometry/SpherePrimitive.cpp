#include "Geometry/SpherePrimitive.h"
#include "Maths/PolynomialSolver.h"
#include "Maths/MathPrint.h"

SpherePrimitive::SpherePrimitive(glm::vec4 _centre, double _rad, AbstractMaterial *_material, Shader *_shader)
{
	m_centre = _centre;
	m_radius = _rad;

	m_material = _material;
	m_shader = _shader;
	m_colour = m_material->m_surfaceColour;
}


SpherePrimitive::~SpherePrimitive()
{
	delete m_material;
	delete m_shader;
}

//----------------------------------------------------------------------------------
DistList SpherePrimitive::Intersect(const Ray &_ray)
{
	DistList result;
	PolyReturn roots;
	glm::vec3 pointToCentre;
	double c[3];

	// get quadratic coefficients
	pointToCentre = glm::vec3(m_centre - _ray.m_point);
	
	float tca = glm::dot(pointToCentre, _ray.m_dir);
	float d2 = glm::dot(pointToCentre, pointToCentre) - (tca*tca);
	if (d2 <= (m_radius*m_radius))
	{
		float thc = sqrt((m_radius * m_radius) - d2);
		
		
		if (tca - thc > 0.0f)
		{
			result.m_dist.push_back(tca - thc);
		}

		if(tca + thc > 0.0f)
		{
			result.m_dist.push_back(tca + thc);
		}
#if _DEBUG
		printf("______________________\n");
		printf("ray point\t: [%f,%f,%f]\n", invRay.m_point.x, invRay.m_point.y, invRay.m_point.z);
		printf("ray dir\t: [%f,%f,%f]\n", invRay.m_dir.x, invRay.m_dir.y, invRay.m_dir.z);
		//printf("centre\t: [%f,%f,%f]\n", m_centre.x, m_centre.y, m_centre.z);
		//printf("rad\t: %f\n", m_radius);
		printf("t0 = %f\n", (tca - thc));
		printf("t1 = %f\n", (tca + thc));
#endif
	}
	
	/*
	c[0] = glm::dot(_ray.m_dir, _ray.m_dir);
	c[1] = 2 * glm::dot(pointToCentre, _ray.m_dir);
	c[2] = glm::dot(pointToCentre, pointToCentre) - (m_radius*m_radius);


	// solve quadratic equation
	PolynomialSolver::QuadraticRoots(roots, c[2], c[1], c[0]);

	// store results
	for (int i = 0; i < roots.m_numVal; i++)
	{
		result.m_dist.push_back(roots.m_values[i]);
		//printf("\troot %d:\t%f", i, roots.m_values[i]);
	}
	//printf("\n");
	*/
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