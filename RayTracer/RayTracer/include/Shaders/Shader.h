#pragma once

#include <glm/glm.hpp>
#include "Maths/Ray.h"
#include "Materials/BasicMaterial.h"


class Shader
{
public:
	Shader();
	~Shader();


	virtual glm::vec3 Shade(const glm::vec3 &_point, const glm::vec3 &_surfNormal, AbstractMaterial *_mat,
							const Ray &_viewRay,	 const glm::vec3 &_lightPos,
							const glm::vec3 &_lightColour) = 0;
};

