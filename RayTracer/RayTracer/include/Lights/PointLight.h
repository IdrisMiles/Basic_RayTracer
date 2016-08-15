#pragma once
#include "AbstractLight.h"


class PointLight :	public AbstractLight
{
public:
	PointLight(glm::vec4 _position, glm::vec3 _intensity);
	~PointLight();
};

