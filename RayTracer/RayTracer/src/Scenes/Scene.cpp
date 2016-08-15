#include "Scenes/Scene.h"
#include "Materials/BasicMaterial.h"
#include "Shaders/LambertShader.h"


Scene::Scene()
{
	glm::vec3 col(0.90f, 0.0f, 0.0f);
	glm::vec3 ref(0.1f);
	glm::vec3 trans(0.0f);
	float IoR = 1.33f;
	BasicMaterial *solidMat = new BasicMaterial(col, 4.0f, ref, trans, IoR);
	BasicMaterial *reflectiveMat = new BasicMaterial(glm::vec3(0.2f, 0.2f, 0.2f), 4.0f, glm::vec3(1.0f), glm::vec3(0.0f), IoR);
	BasicMaterial *refractiveMat = new BasicMaterial(glm::vec3(0.2f, 0.2f, 0.3f), 4.0f, glm::vec3(0.0f), glm::vec3(0.7f), IoR);
	
	int numObject = 3;
	for (int i = 0; i < numObject; i++)
	{
		for (int j = 0; j < numObject; j++)
		{
			glm::vec4 pos = glm::vec4((i - (numObject / 2)) * 10.0f, 5.0f, j * -15.0f, 1.0f);
			float rad = 5.0f;

			if (i == 0)
			{
				m_meshes.push_back(new SpherePrimitive(pos, rad, solidMat, new LambertShader(0.1f)));
			}
			else if (i == 1)
			{
				m_meshes.push_back(new SpherePrimitive(pos, rad, refractiveMat, new LambertShader(0.1f)));
			}
			else
			{
				m_meshes.push_back(new SpherePrimitive(pos, rad, reflectiveMat, new LambertShader(0.1f)));
			}
			
		}
	}
	

	BasicMaterial *floorMat = new BasicMaterial(glm::vec3(1.0f), 4.0f, glm::vec3(0.0f), glm::vec3(0.0f), IoR);
	m_meshes.push_back(new PlanePrimitive(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), floorMat, new LambertShader(0.1f)));

	m_lights.push_back(new PointLight(glm::vec4(0.0f, 50.0f, 0.0f, 1.0f), glm::vec3(1.0f)));

	m_camera = new PinholeCamera(600, 400, 1.0f, 90.0f, glm::vec4(0.0f, 15.0f, 25.0f,1.0f));
}


Scene::~Scene()
{
}