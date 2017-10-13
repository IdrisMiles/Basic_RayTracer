#pragma once
#ifndef _TRANSFORM__H_
#define _TRANSFORM__H_

#include <glm/glm.hpp>

class Transform
{
public:
	Transform();
	~Transform();

	//--------------------------------------------------------------
	// Getters ans Setters

	// Set Tranformation matrix, and precompute inverse
	void SetTransfromMat(const glm::mat4 &_mat);

	// Get Transformation matrix
	glm::mat4 GetTransformMat() const;

	// Get Transformation matrix
	glm::mat3 GetTransformDirMat() const;

	// Get Inverse Transformation matrix
	glm::mat4 GetInvTransformMat() const;




	//--------------------------------------------------------------
	// Member functions

	// Transforms a point - scale, translation, rotation, shear
	glm::vec3 TransformPoint(const glm::vec3 &_point);
	glm::vec4 TransformPoint(const glm::vec4 &_point);
	
	// Transforms a point - scale, translation, rotation, shear
	glm::vec3 TransformPointInverse(const glm::vec3 &_point);
	glm::vec4 TransformPointInverse(const glm::vec4 &_point);

	// Transform a direction vector - scale, rotation
	glm::vec3 TransformDir(const glm::vec3 &_dir);
	
	// Transform a normal vector - scale, rotation
	glm::vec3 TransformNormal(const glm::vec3 &_normal);

private:
	glm::mat4 m_transform;
	glm::mat4 m_invTrans;
};

#endif //_TRANSFORM__H_
