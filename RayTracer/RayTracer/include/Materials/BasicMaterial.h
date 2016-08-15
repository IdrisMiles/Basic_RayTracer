#pragma once
#include "AbstractMaterial.h"

class BasicMaterial : public AbstractMaterial
{
public:

	BasicMaterial(const glm::vec3 _surfaceColour = glm::vec3(255), const float _specularExp = 2.0f, const glm::vec3 m_reflectivity = glm::vec3(0.0f), const glm::vec3 _transmittivity = glm::vec3(0.0f), const float _indexOfRefraction = 1.0f);
	~BasicMaterial();


};

