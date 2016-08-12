#pragma once
#include "Shader.h"

class LambertShader : public Shader
{
public:
	LambertShader(double _ambient,	double _diffuse, double _specular, double _specularExp);
	~LambertShader();


	glm::vec3 Shade(const glm::vec3 &_point, const glm::vec3 &_surfNormal, const glm::vec3 &_surfColour,
					const glm::vec3 &_warpNormal, const Ray &_viewRay, const glm::vec3 &_lightPos,
					const glm::vec3 &_lightColour, const glm::vec3 &_shadowColour);



	double m_ambient;
	double m_diffuse;
	double m_specular;
	double m_specularExp;
};

