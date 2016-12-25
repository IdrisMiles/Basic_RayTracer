#include "Materials/BasicMaterial.h"


BasicMaterial::BasicMaterial(const glm::vec3 _surfaceColour, const float _specularExp, const glm::vec3 _reflectivity, const glm::vec3 _transmittivity, const float _IndexOfRefraction)
{
	m_surfaceColour = _surfaceColour;
	m_specularExp = _specularExp;

	m_reflectivity = _reflectivity;
	m_transmittivity = _transmittivity;
	m_indexOfRefraction = _IndexOfRefraction;
}


BasicMaterial::~BasicMaterial()
{
}
