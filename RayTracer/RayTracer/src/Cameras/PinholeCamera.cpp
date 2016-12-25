#include "Cameras/PinholeCamera.h"
#include <iostream>
#include <glm/gtc/random.hpp>

PinholeCamera::PinholeCamera(int _width, int _height, glm::vec3 _eye, glm::vec3 _focalPoint, glm::vec3 _up, float _vFov, float _aperture, int _numDofSamples)
{
	m_width = _width;
	m_height = _height;

	m_aspectRatio = (float)m_width / m_height;

	m_fov = _vFov;
	m_tanHalfFov = tan(glm::radians(0.5f * m_fov));


	m_eye = _eye;
	m_focalPoint = _focalPoint;
	m_worldUp = glm::normalize(_up);

	m_forward = glm::normalize(m_focalPoint - m_eye);
	m_right = glm::cross(m_forward, m_worldUp);
	m_up = glm::cross(m_right, m_forward);
	m_focalLength = glm::length(m_focalPoint - m_eye);

	m_aperture = _aperture;
	m_numDofSamples = _numDofSamples;

}

PinholeCamera::~PinholeCamera()
{
}

Ray PinholeCamera::ComputeRay(const int &_x, const int &_y)
{

	// transform to Normalizedd Device Coordinates [0-1]
	float pixelNDCx = (float)(_x + 0.5f) / m_width;
	float pixelNDCy = (float)(_y + 0.5f) / m_height;

	// transform to screen space [-1 - +1] then correct for aspect ratio and FOV and focal length
	float pixelScreenx = ((2.0f * pixelNDCx) - 1.0f) * m_tanHalfFov * m_focalLength * m_aspectRatio;
	float pixelScreeny = ((2.0f * pixelNDCy) - 1.0f) * m_tanHalfFov * m_focalLength;

	glm::vec3 rayDir = glm::normalize((pixelScreenx*m_right) + (pixelScreeny*m_up) + (m_focalLength*m_forward));
	glm::vec3 transformedRayDir = m_transform.TransformDir(rayDir);
	glm::vec3 transformedEye = m_transform.TransformPoint(m_eye);
	Ray cameraRay(transformedEye, transformedRayDir);


	return cameraRay;
}


Ray PinholeCamera::ComputeRay(const int &_x, const int &_y, const int &_sample)
{

	// transform to Normalizedd Device Coordinates [0-1]
	float pixelNDCx = (float)(_x + 0.5f) / m_width;
	float pixelNDCy = (float)(_y + 0.5f) / m_height;

	// transform to screen space [-1 - +1] then correct for aspect ratio and FOV and focal length
	float pixelScreenx = ((2.0f * pixelNDCx) - 1.0f) * m_tanHalfFov * m_focalLength * m_aspectRatio;
	float pixelScreeny = ((2.0f * pixelNDCy) - 1.0f) * m_tanHalfFov * m_focalLength;

	glm::vec3 forward = m_forward;
	glm::vec3 right = m_right;
	glm::vec3 up = m_up;
	glm::vec3 apertureOffset(0.0f);

	if (_sample != 0)
	{
		apertureOffset = glm::vec3(glm::diskRand(m_aperture), 0.0f);
		forward = glm::normalize(m_focalPoint - (m_eye + apertureOffset));
		right = (glm::cross(m_forward, m_worldUp));
		up = (glm::cross(m_right, m_forward));
	}

		
	glm::vec3 rayDir = glm::normalize((pixelScreenx*right) + (pixelScreeny*up) + (m_focalLength*forward));
	glm::vec3 transformedRayDir = m_transform.TransformDir(rayDir);
	glm::vec3 transformedEye = m_transform.TransformPoint(m_eye+apertureOffset);
	Ray cameraRay(transformedEye, transformedRayDir);


	return cameraRay;
}
