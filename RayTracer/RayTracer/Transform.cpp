#include "Transform.h"

//--------------------------------------------------------------
// Ctors and Dtors
Transform::Transform()
{
}


Transform::~Transform()
{
}



//--------------------------------------------------------------
// Getters ans Setters

void Transform::SetTransfromMat(const glm::mat4 &_mat)
{
	m_trans = _mat;
	m_transDir = glm::mat3(m_trans);
	m_invTrans = glm::inverse(m_trans);
}


glm::mat4 Transform::GetTransformMat() const
{
	return m_trans;
}

glm::mat3 Transform::GetTransformDirMat() const
{
	return m_transDir;
}

glm::mat4 Transform::GetInvTransformMat() const
{
	return m_invTrans;
}



//--------------------------------------------------------------
// Member functions

glm::vec4 Transform::TransformPoint(const glm::vec4 &_point)
{
	return m_trans * _point;
}

glm::vec4 Transform::TransformPointInverse(const glm::vec4 &_point)
{
	return m_invTrans * _point;
}


glm::vec3 Transform::TransformDir(const glm::vec3 &_dir)
{
	return m_transDir * _dir;
}

glm::vec3 Transform::TransformNormal(const glm::vec3 &_normal)
{
	return glm::mat3(m_invTrans) * _normal;
}