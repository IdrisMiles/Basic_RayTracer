
#ifndef _SPHEREPRIMITIVE__H_
#define _SPHEREPRIMITIVE__H_


#include "AbstractPrimitive.h"
#include "Materials/BasicMaterial.h"


class SpherePrimitive :	public AbstractPrimitive
{
public:
	SpherePrimitive(glm::vec3 _centre, double _rad, AbstractMaterial *_material, Shader *_shader);
    virtual ~SpherePrimitive();

    virtual bool Intersect(DistList &_distList, const Ray &_ray);
    virtual bool PointInside(const glm::vec3 &_point);
    virtual glm::vec3 Normal(const glm::vec3 &_point);
    virtual glm::vec3 GetColour(const glm::vec3 &_point);

	//------------------------------------------------------------

	glm::vec3 m_centre;
	double m_radius;
};

#endif //_SPHEREPRIMITIVE__H_
