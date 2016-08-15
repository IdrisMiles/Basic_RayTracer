#pragma once
#include "AbstractCamera.h"
class PinholeCamera :
	public AbstractCamera
{
public:
	PinholeCamera(int _width = 600, int _height = 400, float viewPlaneDist = 1.0f, float _fov = 90.0f, glm::vec4 _viewPoint = glm::vec4(0.0f));
	~PinholeCamera();

	Ray ComputeRay(const int &_x, const int &_y);

};

