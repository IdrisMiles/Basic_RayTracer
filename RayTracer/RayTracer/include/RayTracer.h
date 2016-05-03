#pragma once

#include "SpherePrimitive.h"


class RayTracer
{
public:
	RayTracer(unsigned int _width = 100, unsigned int _height = 100);
	~RayTracer();

	void Render();

	unsigned int m_width;
	unsigned int m_height;

	glm::vec3 *m_pixels;

	std::vector<AbstractPrimitive*> m_meshes;
	
};

