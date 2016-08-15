#pragma once

#include "Maths/Ray.h"
#include "Maths/Transform.h"

class AbstractCamera
{
public:
	AbstractCamera();
	~AbstractCamera();

	virtual Ray ComputeRay(const int &_x, const int &_y) = 0;

	//------------------------------------------------------------
	Transform m_transform;

	glm::vec4 m_viewPoint;
	/*glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_forward;*/

	float m_viewPlaneDist;
	int m_width;
	int m_height;
	float m_aspectRatio;
	float m_fov;
	float m_tanHalfFov;


};

