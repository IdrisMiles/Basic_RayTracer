#include "AbstractPrimitive.h"


AbstractPrimitive::AbstractPrimitive()
{
	m_trans = Transform();
}


AbstractPrimitive::~AbstractPrimitive()
{
}


void AbstractPrimitive::TransformPrim(glm::mat4 &_trans)
{
	glm::mat4 m = m_trans.GetTransformMat();
	m_trans.SetTransfromMat(m * _trans);
}