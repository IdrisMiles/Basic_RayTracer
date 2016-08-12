#pragma once

#include "Scene.h"


class RayTracer
{
public:
	RayTracer(unsigned int _width = 100, unsigned int _height = 100);
	~RayTracer();

	void Render();
	glm::vec3 TraceRay(const Ray &_sourceRay);

	unsigned int m_width;
	unsigned int m_height;

	std::vector<glm::vec3> m_pixels;
	

	Scene *m_scene;
	
};

