#pragma once
#ifndef _SHADER__H_
#define _SHADER__H_

#include <glm/glm.hpp>
#include "Maths/Ray.h"
#include "Materials/BasicMaterial.h"


class Shader
{
public:
	Shader();
    virtual ~Shader();


	virtual glm::vec3 Shade(const glm::vec3 &_point, const glm::vec3 &_surfNormal, AbstractMaterial *_mat,
							const Ray &_viewRay,	 const glm::vec3 &_lightPos,
							const glm::vec3 &_lightColour) = 0;
};


#endif //_SHADER__H_
