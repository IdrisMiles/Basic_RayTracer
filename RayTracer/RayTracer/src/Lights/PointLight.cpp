#include "Lights/PointLight.h"


PointLight::PointLight(glm::vec3 _position, glm::vec3 _intensity, float _attenuation)
{
	m_position = _position;
	m_intensity = _intensity;
	m_attenuation = _attenuation;

}


PointLight::~PointLight()
{
}
