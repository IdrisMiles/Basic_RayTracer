#include "LambertShader.h"



LambertShader::LambertShader(double _ambient, double _diffuse, double _specular, double _specularExp) : 
m_ambient(_ambient),
m_diffuse(_diffuse),
m_specular(_specular),
m_specularExp(_specularExp)
{
}


LambertShader::~LambertShader()
{
}


glm::vec3 LambertShader::Shade(const glm::vec3 &_point,			const glm::vec3 &_surfNormal,	const glm::vec3 &_surfColour,
								const glm::vec3 &_warpNormal,	const Ray &_viewRay,			const glm::vec3 &_lightPos,
								const glm::vec3 &_lightColour,	const glm::vec3 &_shadowColour)
{
	// temporary variables
	glm::vec3 unitEye, unitNorm, unitLight, unitRefL , halfView, finalColour;
	double diffuseIntensity, specularIntensity, nDotV, nDotL;
	glm::vec3 diffuseCol, specularCol, ambientCol;

	// Get unit vectors for shading equations
	unitEye = glm::normalize(-_viewRay.m_dir);
	unitNorm = glm::normalize(_surfNormal);
	
	// Do this for each light:
		unitLight = glm::normalize(_lightPos - _point);
		unitRefL = unitNorm;
		unitRefL *= (2 * glm::dot(unitLight, unitNorm));	// r = (2(L dot N)*N) - L
		unitRefL -= unitLight;

		double normDotView = glm::dot(unitNorm, unitEye);
		double diffIntensity = glm::dot(unitNorm, unitLight);
		double specIntensity = glm::dot(unitEye, unitRefL);
		
		// check view and light vecots not on same side
		if ((normDotView > 0 && diffIntensity < 0) || (normDotView < 0 && diffIntensity > 0))
		{
			// diffuse colour
			diffuseCol += ( (_surfColour * _lightColour * _shadowColour) *= fabs(diffIntensity) );

			// specular colour
			specularCol += ( (_surfColour * _lightColour * _shadowColour) *= glm::pow(fabs(specIntensity), m_specularExp) );
		}

	// ambient colout
	ambientCol = _surfColour;
	ambientCol *= m_ambient;

	// final colour
	finalColour = ambientCol + diffuseCol + specularCol;

	return finalColour;
}