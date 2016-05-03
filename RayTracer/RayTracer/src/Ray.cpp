#include "Ray.h"


Ray::Ray()
{

}

Ray::Ray(glm::vec4 _point, glm::vec3 _dir):
m_point(_point),
m_dir(_dir)
{
	glm::mat4 m;
	glm::mat4 inv_m = glm::inverse(m);
	glm::mat3 m_r = glm::mat3(m);
	m_r * m_dir;
	m * m_point;
	
}


Ray::~Ray()
{
}
