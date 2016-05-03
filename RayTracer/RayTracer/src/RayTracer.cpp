#include "RayTracer.h"
#include "LambertShader.h"
#include "Ray.h"
#include "PolynomialSolver.h"
#include "Intersection.h"
#include <iostream>


RayTracer::RayTracer(unsigned int _width, unsigned int _height) : 
m_width(_width),
m_height(_height)
{
	m_pixels = new glm::vec3[m_width * m_height];

	m_meshes.push_back( new SpherePrimitive(glm::vec4(0.0f, 0.0f, 10.0f, 1.0f), 2.0) );
}


RayTracer::~RayTracer()
{
}


void RayTracer::Render()
{
	std::cout << "rendering\n---------\n";
	glm::vec4 camPos = glm::vec4(0.0f, 0.0f, -10.0f, 1.0f);

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			// produce ray for this pixel
			Ray sourceRay = Ray(glm::vec4(0.0f, 0.0f, -10.0f, 1.0f), glm::vec3(0.1f*(x - (m_width*0.5f)), 0.1f*(y - (m_height*0.5f)), 10.0f));

			// initialise object list, min dist and PixelColour
			glm::vec3 pixelCol(0.0f, 0.0f, 0.0f);
			DistList intersectionDistanceList;
			double minIntersectionDist = 1e20;
			Intersection currentIntersection;			

			// Foreach object 
			std::vector<AbstractPrimitive*>::iterator mesh;
			for (mesh = m_meshes.begin(); mesh != m_meshes.end(); ++mesh)
			{
				intersectionDistanceList = (*mesh)->Intersect(sourceRay);
				// check if ray intersects
				if (intersectionDistanceList.m_dist.size() != 0)
				{
					std::cout << "Intersection \n";
					// check if intersect dist is less than current min
					if (intersectionDistanceList.m_dist[0] < minIntersectionDist)
					{
						// update min dist and current interescted obj
						minIntersectionDist = intersectionDistanceList.m_dist[0];
						currentIntersection.m_Prim = *mesh;
						std::cout << "New min dist \n";
					}
				}
			}
			
				

			// if current intersected object != NULL
				// foreach light source
					// produce shadow ray - interection point to light source

					// Foreach object 
					// check if ray intersects
						// bool RayIntersects = true; break;
				
					// if !RayInterects
						// PixelColour += Get shaded colour given light source and object material
			// else
				// PixelColour = background

		}

	}

	std::cout << "Rendering finished\n";
	int end;
	std::cin >> end;

}