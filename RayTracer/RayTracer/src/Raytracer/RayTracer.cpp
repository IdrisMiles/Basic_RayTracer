#include "Raytracer/RayTracer.h"
#include "Shaders/LambertShader.h"
#include "Maths/Ray.h"
#include "Maths/PolynomialSolver.h"
#include "Raytracer/Intersection.h"

#include <iostream>
#include <FreeImage.h>

#define EPSILON 1e-3
#define COORD2DINDEX(x, y, width) x+(y*width)

RayTracer::RayTracer()
{
	// Load scene
	m_scene = new Scene();
	m_width = m_scene->m_camera->m_width;
	m_height = m_scene->m_camera->m_height;

	// allocate pixel buffer
	m_pixels.resize(m_width * m_height);

	// initialise FreeImage library
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

	//glm::vec4 camPos = glm::vec4(0.0f, 0.0f, 10.0f, 1.0f);

	
	for (unsigned int y = 0; y < m_height; y++)
	{
		for (unsigned int x = 0; x < m_width; x++)
		{

			// produce ray for this pixel
			Ray sourceRay = m_scene->m_camera->ComputeRay(x, y);//Ray(camPos, glm::normalize(glm::vec3(0.1f*(x - (m_width*0.5f)), 0.1f*(y - (m_height*0.5f)), -10.0f)));
			m_pixels[COORD2DINDEX(x, y, m_width)] = TraceRay(sourceRay, 4);

			pixelColour.rgbRed = 255 * m_pixels[COORD2DINDEX(x, y, m_width)].x;
			pixelColour.rgbGreen = 255 * m_pixels[COORD2DINDEX(x, y, m_width)].y;
			pixelColour.rgbBlue = 255 * m_pixels[COORD2DINDEX(x, y, m_width)].z;

			// Image is stored top left to bottom right, 
			// renderer traces rays from bottom left to top right
			// So must reverse y
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



glm::vec3 RayTracer::TraceRay(const Ray &_sourceRay, const int &_depth)
{
	// initialise object list, min dist and PixelColour
	glm::vec3 pixelCol(0.0f, 0.0f, 0.0f);
	DistList intersectionDistanceList;
	double minIntersectionDist = 1e20;
	Intersection currentIntersection;

	//----------------------------------------------------------------------------------------------------------
	// Primary Raytrace

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
					currentIntersection.m_Point = _sourceRay.m_point + glm::vec4(((float)minIntersectionDist * glm::vec3(_sourceRay.m_dir)),0.0f);
				}
			}
		}
	}


	//----------------------------------------------------------------------------------------------------------
	// Check for early exit

	// if current intersected object != NULL
	if (currentIntersection.m_Prim == NULL)
	{
		// PixelColour = background
		//pixelCol = glm::vec3(0.5f);
		return pixelCol;
	}


	//----------------------------------------------------------------------------------------------------------
	// Shadow Raytrace

	// foreach light source
	std::vector<AbstractLight*>::iterator light;
	for (light = m_scene->m_lights.begin(); light != m_scene->m_lights.end(); ++light)
	{
		// initialise vars
		DistList shadowIntersectionDistanceList;
		glm::vec3 shadowDir = glm::vec3((*light)->m_position - currentIntersection.m_Point);
		double shadowMinIntersectionDist = shadowDir.length();
		Intersection shadowCurrentIntersection;
		glm::vec3 lightIntensity = (*light)->m_intensity;

		// produce shadow ray - interection point to light source
		Ray shadowRay(currentIntersection.m_Point, glm::normalize(shadowDir));

		// Foreach object 
		std::vector<AbstractPrimitive*>::iterator mesh;
		for (mesh = m_scene->m_meshes.begin(); mesh != m_scene->m_meshes.end(); ++mesh)
		{
			shadowIntersectionDistanceList = (*mesh)->Intersect(shadowRay);
			// check if ray intersects anything
			if (shadowIntersectionDistanceList.m_dist.size() != 0)
			{
				// check if intersect dist is less than current min or distance to light source
				for (unsigned int intersectPnts = 0; intersectPnts < shadowIntersectionDistanceList.m_dist.size(); intersectPnts++)
				{
					if (shadowIntersectionDistanceList.m_dist[intersectPnts] < shadowMinIntersectionDist && shadowIntersectionDistanceList.m_dist[intersectPnts]>EPSILON)
					{
						// update min dist and current interescted obj
						shadowMinIntersectionDist = shadowIntersectionDistanceList.m_dist[0];
						shadowCurrentIntersection.m_Prim = *mesh;
						shadowCurrentIntersection.m_Point = shadowRay.m_point + glm::vec4(((float)shadowMinIntersectionDist * glm::vec3(shadowRay.m_dir)), 0.0f);

						// Attenutate light by transmitivity of objects material
						lightIntensity *= (*mesh)->m_material->m_transmittivity;
					}
				}
			}
		}

		// Shade with newly attenuated(or not) light
		currentIntersection.m_Prim->m_material->m_surfaceColour = currentIntersection.m_Prim->GetColour(currentIntersection.m_Point);
		pixelCol += currentIntersection.m_Prim->m_shader->Shade(glm::vec3(currentIntersection.m_Point), 
																currentIntersection.m_Prim->Normal(currentIntersection.m_Point),
																currentIntersection.m_Prim->m_material, 
																_sourceRay, 
																glm::vec3((*light)->m_position), 
																lightIntensity);
			
	} // Next light

	if (_depth > 0)
	{
		glm::vec4 hitPoint = currentIntersection.m_Point;
		glm::vec3 hitNorm = currentIntersection.m_Prim->Normal(currentIntersection.m_Point);

		// Generate reflected ray
		Ray reflectedRay = Ray(hitPoint, glm::reflect(_sourceRay.m_dir, hitNorm));
		pixelCol += currentIntersection.m_Prim->m_material->m_reflectivity * TraceRay(reflectedRay, _depth - 1);

		// Generate refracted ray

		Ray refractedRay = Ray(hitPoint, glm::refract(_sourceRay.m_dir, hitNorm, currentIntersection.m_Prim->m_material->m_indexOfRefraction));
		pixelCol += currentIntersection.m_Prim->m_material->m_transmittivity * TraceRay(refractedRay, _depth - 1);
		
	}


	return glm::clamp(pixelCol, glm::vec3(0.0f), glm::vec3(1.0f));
}