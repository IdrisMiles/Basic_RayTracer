#include "..\include\Scene.h"


Scene::Scene()
{
	m_meshes.push_back(new SpherePrimitive(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), 2.0f));
}


Scene::~Scene()
{
}
