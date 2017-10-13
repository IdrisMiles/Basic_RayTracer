#include "Scenes/Scene.h"
#include "Materials/BasicMaterial.h"
#include "Shaders/LambertShader.h"


Scene::Scene()
{
	glm::vec3 col(0.90f, 0.0f, 0.0f);
	glm::vec3 ref(0.1f);
	glm::vec3 trans(0.0f);
	float IoR = 1.3f;
	BasicMaterial *solidMat = new BasicMaterial(col, 4.0f, ref, trans, 1.0f);
	BasicMaterial *reflectiveMat = new BasicMaterial(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, glm::vec3(1.0f), glm::vec3(0.0f), 1.0f);
	BasicMaterial *refractiveMat = new BasicMaterial(glm::vec3(0.0f, 0.0f, 0.0f), 8.0f, glm::vec3(0.0f), glm::vec3(0.6f,0.6f,0.9f), IoR);

	
    int numObject = 3;
    for (int i = 0; i < numObject; i++)
    {
        for (int j = 0; j < numObject; j++)
        {
            for (int k = 0; k < 1; k++)
            {
                float rad = 5.0f;
                glm::vec3 pos = glm::vec3((i - (numObject / 2)) * 15.0f, 5.0f + (k*15.0f), j * -15.0f);
                glm::vec3 triVerts[3] = { pos + glm::vec3(-2.0f, 5.0f, -4.0f), pos + glm::vec3(2.0f, 5.0f, -4.0f), pos + glm::vec3(0.0f, 10.0f, -4.0f) };

                if (i %3 == 0)
                {
                    m_meshes.push_back(new SpherePrimitive(pos, rad, solidMat, new LambertShader(0.1f)));
                    m_meshes.push_back(new TrianglePrimitive(triVerts, reflectiveMat, new LambertShader(0.1f)));
                }
                else if (i%3 == 1)
                {
                    m_meshes.push_back(new SpherePrimitive(pos, rad, refractiveMat, new LambertShader(0.1f)));
                    m_meshes.push_back(new TrianglePrimitive(triVerts, solidMat, new LambertShader(0.1f)));
                }
                else
                {
                    m_meshes.push_back(new SpherePrimitive(pos, rad, reflectiveMat, new LambertShader(0.1f)));
                    m_meshes.push_back(new TrianglePrimitive(triVerts, refractiveMat, new LambertShader(0.1f)));
                }

            }
			
        }
    }
	
	
	// Floor
    BasicMaterial *floorMat = new BasicMaterial(glm::vec3(1.0f), 8.0f, glm::vec3(0.02f), glm::vec3(0.0f), IoR);
    m_meshes.push_back(new PlanePrimitive(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), floorMat, new LambertShader(0.1f)));


	// Lights
	m_lights.push_back(new PointLight(glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(1.0f), 1.0f));


	// Camera setup
	glm::vec3 eye(0.0f, 20.0f, 20.0f);
	glm::vec3 focalPoint = glm::vec3(0.0f, 5.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	float fov = 90.0f;
    float aperture = 0.5f;
    int dofSamples = 1;
    m_camera = new PinholeCamera(600, 400, eye, focalPoint, up, fov, aperture, dofSamples);
}


Scene::~Scene()
{
}
