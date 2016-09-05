#include "Maths/Ray.h"


Ray::Ray()
{

}

Ray::Ray(glm::vec3 _point, glm::vec3 _dir):
m_point(_point),
m_dir(_dir)
{
	
}


Ray::~Ray()
{
}
