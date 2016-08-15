#pragma once

#include "Scenes/Scene.h"
#include "Cameras/PinholeCamera.h"


class RayTracer
{
public:
	RayTracer();
	~RayTracer();

	void Render();

	glm::vec3 TraceRay(const Ray &_sourceRay, const int &_depth);

	//------------------------------------------------------------

	unsigned int m_width;
	unsigned int m_height;
	std::vector<glm::vec3> m_pixels;

	
	Scene *m_scene;
	
};

