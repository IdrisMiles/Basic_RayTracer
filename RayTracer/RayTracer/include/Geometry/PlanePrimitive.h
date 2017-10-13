
#ifndef _PLANEPRIMITIVE__H_
#define _PLANEPRIMITIVE__H_


#include "AbstractPrimitive.h"

#include "Materials/BasicMaterial.h"


class PlanePrimitive : public AbstractPrimitive
{
public:
	PlanePrimitive(glm::vec3 _centre, glm::vec3 _planeNormal, AbstractMaterial *_material, Shader *_shader);
    virtual ~PlanePrimitive();

    virtual bool Intersect(DistList &_distList, const Ray &_ray);
    virtual bool PointInside(const glm::vec3 &_point);
    virtual glm::vec3 Normal(const glm::vec3 &_point);
    virtual glm::vec3 GetColour(const glm::vec3 &_point);

	//------------------------------------------------------------

	glm::vec3 m_centre;
    glm::vec3 m_planeNormal;

};

#endif //_PLANEPRIMITIVE__H_
