#include "Maths/Transform.h"
#include "Maths/MathPrint.h"

//--------------------------------------------------------------
// Ctors and Dtors
Transform::Transform()
{
	m_transform = glm::mat4(1.0f);
	m_invTrans = glm::inverse(m_transform);

}


Transform::~Transform()
{
}



//--------------------------------------------------------------
// Getters ans Setters

void Transform::SetTransfromMat(const glm::mat4 &_mat)
{
	m_transform = _mat;
	m_invTrans = glm::inverse(m_transform);
}


glm::mat4 Transform::GetTransformMat() const
{
	return m_transform;
}

glm::mat3 Transform::GetTransformDirMat() const
{
	return glm::mat3(m_transform);
}

glm::mat4 Transform::GetInvTransformMat() const
{
	return m_invTrans;
}



//--------------------------------------------------------------
// Member functions

glm::vec3 Transform::TransformPoint(const glm::vec3 &_point)
{
	return glm::vec3(m_transform * glm::vec4(_point,1.0f));
}
glm::vec4 Transform::TransformPoint(const glm::vec4 &_point)
{
	return m_transform * _point;
}

glm::vec3 Transform::TransformPointInverse(const glm::vec3 &_point)
{
	return glm::vec3(m_invTrans * glm::vec4(_point, 1.0f));
}
glm::vec4 Transform::TransformPointInverse(const glm::vec4 &_point)
{
	return m_invTrans * _point;
}


glm::vec3 Transform::TransformDir(const glm::vec3 &_dir)
{
	return glm::mat3(m_transform) * _dir;
}

glm::vec3 Transform::TransformNormal(const glm::vec3 &_normal)
{
	return glm::transpose(glm::mat3(m_invTrans)) * _normal;
}