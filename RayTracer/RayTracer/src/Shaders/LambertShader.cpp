#include "Shaders/LambertShader.h"
#include <iostream>

LambertShader::LambertShader(double _ambient) : 
m_ambient(_ambient)
{
}


LambertShader::~LambertShader()
{
}


glm::vec3 LambertShader::Shade(const glm::vec3 &_point,			const glm::vec3 &_surfNormal,	AbstractMaterial *_mat,
								const Ray &_viewRay,			const glm::vec3 &_lightPos,
								const glm::vec3 &_lightColour)
{
	// temporary variables
	glm::vec3 unitEye, unitNorm, unitLight, unitRefL , halfView, finalColour;
	float diffuseIntensity, specularIntensity, nDotV, nDotL;
	glm::vec3 diffuseCol, specularCol, ambientCol;

	// Get unit vectors for shading equations
	unitEye = glm::normalize(-_viewRay.m_dir);
	unitNorm = glm::normalize(_surfNormal);
	
	// Do this for each light:
	unitLight = glm::normalize(_lightPos - _point);
	unitRefL = unitNorm;
	unitRefL *= (2 * glm::dot(unitNorm, unitLight));	// r = (2(L dot N)*N) - L
	unitRefL -= unitLight;

	float normDotView = glm::dot(unitNorm, unitEye);
    float  diffIntensity = glm::dot(unitNorm, unitLight);
	float specIntensity = glm::clamp(glm::dot(unitEye, unitRefL), 0.0f, 1.0f);

	// check view and light vecots ~not on same side
    if ((normDotView > 0.0f && diffIntensity > 0.0f) || (normDotView < 0.0f && diffIntensity < 0.0f))
	{
		// diffuse colour
        diffuseCol += ((_mat->m_surfaceColour * _lightColour) * (float)fabs(diffIntensity) );
		//diffuseCol = glm::clamp(diffuseCol, glm::vec3(0.0f), glm::vec3(1.0f));

		// Specular colour
        specularCol += ((_lightColour) * (float)pow(specIntensity, _mat->m_specularExp));
		//specularCol = glm::clamp(specularCol, glm::vec3(0.0f), glm::vec3(1.0f));
	}		

	// ambient colout
	ambientCol = _mat->m_surfaceColour;
	ambientCol *= m_ambient;

	// final colour
	finalColour = ambientCol + diffuseCol + specularCol;
	finalColour = glm::clamp(finalColour, glm::vec3(0.0f), glm::vec3(1.0f));
	
	
	return finalColour;
}
