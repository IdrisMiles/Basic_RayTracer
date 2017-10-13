#pragma once
#ifndef _SCENE__H_
#define _SCENE__H_

#include "Geometry/SpherePrimitive.h"
#include "Geometry/PlanePrimitive.h"
#include "Geometry/TrianglePrimitive.h"
#include "Lights/PointLight.h"
#include "Cameras/PinholeCamera.h"

class Scene
{
public:
	Scene();
	~Scene();


	std::vector<AbstractPrimitive*> m_meshes;
	std::vector<AbstractLight*> m_lights;
	AbstractCamera *m_camera;
};

#endif //_SCENE__H_
