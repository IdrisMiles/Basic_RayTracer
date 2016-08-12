#include "AbstractPrimitive.h"


AbstractPrimitive::AbstractPrimitive()
{
	m_transform = Transform();
}


AbstractPrimitive::~AbstractPrimitive()
{
}


void AbstractPrimitive::TransformPrim(glm::mat4 &_trans)
{
	glm::mat4 m = m_transform.GetTransformMat();
	m_transform.SetTransfromMat(m * _trans);
}