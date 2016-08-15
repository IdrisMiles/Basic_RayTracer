#pragma once

#include "Geometry/SpherePrimitive.h"
#include "Geometry/PlanePrimitive.h"
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

