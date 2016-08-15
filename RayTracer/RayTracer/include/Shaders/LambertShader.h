#pragma once
#include "Shader.h"

class LambertShader : public Shader
{
public:
	LambertShader(double _ambient);
	~LambertShader();


	glm::vec3 Shade(const glm::vec3 &_point, const glm::vec3 &_surfNormal, AbstractMaterial *_mat,
					const Ray &_viewRay, const glm::vec3 &_lightPos,
					const glm::vec3 &_lightColour);



	double m_ambient;
};

