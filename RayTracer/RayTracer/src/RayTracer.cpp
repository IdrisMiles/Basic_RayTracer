#include "RayTracer.h"
#include "LambertShader.h"
#include "Ray.h"
#include "PolynomialSolver.h"
#include "Intersection.h"
#include <iostream>

#include <FreeImage.h>

#define EPSILON 1e-3
#define COORD2DINDEX(x, y, width) x+(y*width)

RayTracer::RayTracer(unsigned int _width, unsigned int _height) : 
m_width(_width),
m_height(_height)
{
	m_pixels.resize(m_width * m_height);

	m_scene = new Scene();

	FreeImage_Initialise();
}


RayTracer::~RayTracer()
{
	delete m_scene;
}


void RayTracer::Render()
{

	FIBITMAP *bitmap = FreeImage_Allocate(m_width, m_height, 32);
	if (!bitmap)
	{
		return;
	}
	RGBQUAD pixelColour;


	std::cout << "rendering\n-------------------\n";
	glm::vec4 camPos = glm::vec4(0.0f, 0.0f, -10.0f, 1.0f);

	
	for (unsigned int y = 0; y < m_height; y++)
	{
		for (unsigned int x = 0; x < m_width; x++)
		{

			// produce ray for this pixel
			Ray sourceRay = Ray(camPos, glm::normalize(glm::vec3(0.1f*(x - (m_width*0.5f)), 0.1f*(y - (m_height*0.5f)), 10.0f)));
			m_pixels[COORD2DINDEX(x, y, m_width)] = TraceRay(sourceRay);

			pixelColour.rgbRed = m_pixels[COORD2DINDEX(x, y, m_width)].x;
			pixelColour.rgbGreen = m_pixels[COORD2DINDEX(x, y, m_width)].y;
			pixelColour.rgbBlue = m_pixels[COORD2DINDEX(x, y, m_width)].z;
			FreeImage_SetPixelColor(bitmap, x, y, &pixelColour);
		}

	}

	
	if (FreeImage_Save(FIF_BMP, bitmap, "FinalRender.png"))
	{
		std::cout << "Successfully saved render\n";
	}

	FreeImage_Unload(bitmap);
	FreeImage_DeInitialise();

	std::cout << "Rendering finished\n";

}



glm::vec3 RayTracer::TraceRay(const Ray &_sourceRay)
{
	// initialise object list, min dist and PixelColour
	glm::vec3 pixelCol(0.0f, 0.0f, 0.0f);
	DistList intersectionDistanceList;
	double minIntersectionDist = 1e20;
	Intersection currentIntersection;

	// Foreach object 
	std::vector<AbstractPrimitive*>::iterator mesh;
	for (mesh = m_scene->m_meshes.begin(); mesh != m_scene->m_meshes.end(); ++mesh)
	{
		intersectionDistanceList = (*mesh)->Intersect(_sourceRay);
		// check if ray intersects
		if (intersectionDistanceList.m_dist.size() != 0)
		{
			// check if intersect dist is less than current min
			for (unsigned int intersectPnts = 0; intersectPnts < intersectionDistanceList.m_dist.size(); intersectPnts++)
			{
				if (intersectionDistanceList.m_dist[intersectPnts] < minIntersectionDist && intersectionDistanceList.m_dist[intersectPnts] > EPSILON)
				{
					// update min dist and current interescted obj
					minIntersectionDist = intersectionDistanceList.m_dist[0];
					currentIntersection.m_Prim = *mesh;
				}
			}
		}
	}


	// if current intersected object != NULL
	if (currentIntersection.m_Prim != NULL)
	{
		// foreach light source
		// produce shadow ray - interection point to light source

		// Foreach object 
		// check if ray intersects
		// bool RayIntersects = true; break;

		// if !RayInterects
		// PixelColour += Get shaded colour given light source and object material

		return glm::vec3(255.0f, 0.0f, 0.0f);

	}
	else
	{
		// PixelColour = background
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}