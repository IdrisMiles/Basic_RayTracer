#pragma once
#include "AbstractCamera.h"
class PinholeCamera :
	public AbstractCamera
{
public:
	PinholeCamera(int _width = 600, int _height = 400, glm::vec3 _eye = glm::vec3(0.0f), glm::vec3 _lookAt = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float _vFov = 90.0f, float _aperture = 0.0f, int _numDofSamples = 1);
	~PinholeCamera();

	Ray ComputeRay(const int &_x, const int &_y);
	Ray ComputeRay(const int &_x, const int &_y, const int &_sample);

};

