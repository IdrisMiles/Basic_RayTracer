#include "Lights/PointLight.h"


PointLight::PointLight(glm::vec4 _position, glm::vec3 _intensity)
{
	m_position = _position;
	m_intensity = _intensity;
}


PointLight::~PointLight()
{
}
