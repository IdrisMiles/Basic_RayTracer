#include "Cameras\PinholeCamera.h"


PinholeCamera::PinholeCamera(int _width, int _height, float viewPlaneDist, float _fov, glm::vec4 _viewPoint)
{
	m_width = _width;
	m_height = _height;

	m_aspectRatio = (float)m_width / m_height;

	m_fov = _fov;
	m_tanHalfFov = tan(glm::radians(0.5f * m_fov));

	m_viewPoint = _viewPoint;
}


PinholeCamera::~PinholeCamera()
{
}

Ray PinholeCamera::ComputeRay(const int &_x, const int &_y)
{

	// transform to Normalizedd Device Coordinates [0-1]
	float pixelNDCx = (float)(_x + 0.5f) / m_width;
	float pixelNDCy = (float)(_y + 0.5f) / m_height;

	// transform to screen space [-1 - +1] then correct for aspect ratio and FOV
	float pixelScreenx = ((2.0f * pixelNDCx) - 1.0f) * m_tanHalfFov * m_aspectRatio;
	float pixelScreeny = ((2.0f * pixelNDCy) - 1.0f) * m_tanHalfFov;
		
	glm::vec3 viewPlanePoint = glm::vec3(m_viewPoint)+glm::vec3(pixelScreenx, pixelScreeny, -1.0f);
	glm::vec4 viewPointWorld = m_transform.TransformPoint(m_viewPoint);
	glm::vec4 viewPlanePointWorld = m_transform.TransformPoint(viewPlanePoint);

	// Apply world space transformation here
	Ray cameraRay(viewPointWorld, glm::normalize(glm::vec3(viewPlanePointWorld) - glm::vec3(viewPointWorld)));

	return cameraRay;
}
