#pragma once
#include <glm/glm.hpp>

class AbstractLight
{
public:
	AbstractLight();
	~AbstractLight();

	glm::vec3 m_position;
	glm::vec3 m_intensity;
	float m_attenuation;
};

