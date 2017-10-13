#pragma once
#ifndef _ABSTRACTMATERIAL__H_
#define _ABSTRACTMATERIAL__H_

#include <glm/glm.hpp>

class AbstractMaterial
{
public:
	AbstractMaterial();
    virtual ~AbstractMaterial();

	glm::vec3 m_reflectivity;
	glm::vec3 m_transmittivity;
	float m_indexOfRefraction;
	
	glm::vec3 m_surfaceColour;
	glm::vec3 m_specularColour;
	float m_specularExp;
};


#endif //_ABSTRACTMATERIAL__H_
