#include "..\include\Scene.h"


Scene::Scene()
{
	m_meshes.push_back(new SpherePrimitive(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0));
}


Scene::~Scene()
{
}
