#pragma once
#include "AbstractLight.h"


class PointLight :	public AbstractLight
{
public:
	PointLight(glm::vec3 _position, glm::vec3 _intensity, float _attenuation);
	~PointLight();
};

