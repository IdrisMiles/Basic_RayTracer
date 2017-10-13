#pragma once
#ifndef _RAY__H_
#define _RAY__H_

#include <glm/glm.hpp>

class Ray
{
public:
	Ray();
	Ray(glm::vec3 _point, glm::vec3 _dir);
	~Ray();
	
	glm::vec3 m_point;
	glm::vec3 m_dir;
};

#endif
