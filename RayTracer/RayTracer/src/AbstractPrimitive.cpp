#include "AbstractPrimitive.h"


AbstractPrimitive::AbstractPrimitive()
{
}


AbstractPrimitive::~AbstractPrimitive()
{
}


void AbstractPrimitive::TransformPrim(glm::mat4 &_trans)
{
	glm::mat4 m = m_trans.GetTransformMat();
	m_trans.SetTransfromMat(m * _trans);
}