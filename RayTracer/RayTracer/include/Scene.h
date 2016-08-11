#pragma once

#include "SpherePrimitive.h"

class Scene
{
public:
	Scene();
	~Scene();


	std::vector<AbstractPrimitive*> m_meshes;
};

