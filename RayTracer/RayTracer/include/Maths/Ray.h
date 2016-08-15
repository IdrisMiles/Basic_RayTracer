#pragma once

#include <glm\glm.hpp>

class Ray
{
public:
	Ray();
	Ray(glm::vec4 _point, glm::vec3 _dir);
	~Ray();
	
	glm::vec4 m_point;
	glm::vec3 m_dir;
};

