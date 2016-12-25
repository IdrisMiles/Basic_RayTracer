#pragma once
#include <glm/glm.hpp>

class AbstractMaterial
{
public:
	AbstractMaterial();
	~AbstractMaterial();

	glm::vec3 m_reflectivity;
	glm::vec3 m_transmittivity;
	float m_indexOfRefraction;
	
	glm::vec3 m_surfaceColour;
	glm::vec3 m_specularColour;
	float m_specularExp;
};

