#include "Raytracer/RayTracer.h"
#include "Shaders/LambertShader.h"
#include "Maths/Ray.h"
#include "Maths/PolynomialSolver.h"
#include "Raytracer/Intersection.h"

#include <iostream>
#include <thread>
#include <chrono>
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
}


RayTracer::~RayTracer()
{
	delete m_scene;
}

glm::ivec2 toXY(int index, int width)
{
    int x = index % width;
    int y = index / width;

    return glm::ivec2(x, y);
}

void RayTracer::Render()
{
    // initialise FreeImage library
    FreeImage_Initialise();

	FIBITMAP *bitmap = FreeImage_Allocate(m_width, m_height, 32);
	if (!bitmap)
	{
		return;
	}
    RGBQUAD pixels[m_width][m_height];

    // initialise threads
    std::vector<std::thread> threads(std::thread::hardware_concurrency() - 1);
    int dataSize = m_width * m_height;
    int numThreads = threads.size() + 1;
    int chunkSize = dataSize / numThreads;
    int numBigChunks = dataSize % numThreads;
    int bigChunkSize = chunkSize + (numBigChunks>0 ? 1 : 0);
    int startChunk = 0;
    int threadId=0;

    // initialise rendering function to pass to threads
    auto threadFunc = [&](int startChunk, int endChunk){
        RGBQUAD pixelColour;
        glm::ivec2 coord;
        for(unsigned int index = startChunk; index < endChunk; index++)
        {
            coord = toXY(index, m_width);
            for (int dofSample = 0; dofSample < m_scene->m_camera->m_numDofSamples; dofSample++)
            {
                // produce ray for this pixel
                Ray sourceRay = m_scene->m_camera->ComputeRay(coord.x, coord.y, dofSample);
                m_pixels[index] += TraceRay(sourceRay, 4);
            }
            m_pixels[index] /= (float)m_scene->m_camera->m_numDofSamples;

            pixelColour.rgbRed = 255 * m_pixels[index].x;
            pixelColour.rgbGreen = 255 * m_pixels[index].y;
            pixelColour.rgbBlue = 255 * m_pixels[index].z;

            FreeImage_SetPixelColor(bitmap, coord.x, coord.y, &pixelColour);
//            pixels[coord.x][coord.y] = pixelColour;
        }
    };

    // start timer
    std::cout << "rendering\n-------------------\n";
    auto startTime = std::chrono::system_clock::now();

    // multithreaded rendering
    for(threadId=0; threadId<numBigChunks; threadId++)
    {
        threads[threadId] = std::thread(threadFunc, startChunk, (startChunk+bigChunkSize));
        startChunk+=bigChunkSize;
    }
    for(; threadId<numThreads-1; threadId++)
    {
        threads[threadId] = std::thread(threadFunc, startChunk, (startChunk+chunkSize));
        startChunk+=chunkSize;
    }
    threadFunc(startChunk, dataSize);

    // join threads
    for(int i=0; i<numThreads-1; i++)
    {
        if(threads[i].joinable())
        {
            threads[i].join();
        }
    }

//    for (int i = 0; i<m_width * m_height; i++)
//    {
//        glm::ivec2 coord = toXY(i, m_width);
//        FreeImage_SetPixelColor(bitmap, coord.x, coord.y, &pixels[coord.x][coord.y]);
//    }

    // end timer
    auto endTime = std::chrono::system_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout<<"Elapsed time: "<<elapsedTime.count()<<"\n";

    // save image
    if (FreeImage_Save(FIF_BMP, bitmap, "./FinalRender1.png"))
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
		// check if ray intersects
		if ((*mesh)->Intersect(intersectionDistanceList, _sourceRay))
		{
			// check if intersect dist is less than current min
			for (unsigned int intersectPnts = 0; intersectPnts < intersectionDistanceList.m_dist.size(); intersectPnts++)
			{
				if (intersectionDistanceList.m_dist[intersectPnts] < minIntersectionDist && intersectionDistanceList.m_dist[intersectPnts] > EPSILON)
				{
					// update min dist and current interescted obj
					minIntersectionDist = intersectionDistanceList.m_dist[intersectPnts];
					currentIntersection.m_Prim = *mesh;
					currentIntersection.m_Point = _sourceRay.m_point + ((float)minIntersectionDist * _sourceRay.m_dir);
					currentIntersection.m_dist = minIntersectionDist;
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
		glm::vec3 shadowDir = (*light)->m_position - currentIntersection.m_Point;
		double shadowMinIntersectionDist = glm::length(shadowDir);
		Intersection shadowCurrentIntersection;
		glm::vec3 lightIntensity = (*light)->m_intensity;

		// produce shadow ray - interection point to light source
		Ray shadowRay(currentIntersection.m_Point, glm::normalize(shadowDir));

		// Foreach object 
		std::vector<AbstractPrimitive*>::iterator mesh;
        for (mesh = m_scene->m_meshes.begin(); mesh != m_scene->m_meshes.end(); ++mesh)
		{
			// check if ray intersects anything
			if ((*mesh)->Intersect(shadowIntersectionDistanceList, shadowRay))
			{
				// check if intersect dist is less than current min or distance to light source
				for (unsigned int intersectPnts = 0; intersectPnts < shadowIntersectionDistanceList.m_dist.size(); intersectPnts++)
				{
					if (shadowIntersectionDistanceList.m_dist[intersectPnts] < shadowMinIntersectionDist && shadowIntersectionDistanceList.m_dist[intersectPnts]>EPSILON)
					{
						// update min dist and current interescted obj
						shadowMinIntersectionDist = shadowIntersectionDistanceList.m_dist[intersectPnts];
						shadowCurrentIntersection.m_Prim = *mesh;
						shadowCurrentIntersection.m_Point = shadowRay.m_point + ((float)shadowMinIntersectionDist * shadowRay.m_dir);
						shadowCurrentIntersection.m_dist = shadowMinIntersectionDist;

						// Attenutate light by transmitivity of objects material
						lightIntensity *= (*mesh)->m_material->m_transmittivity;
					}
				}
			}
		}

		// Shade with newly attenuated(or not) light
        //lightIntensity *= glm::exp(-(*light)->m_attenuation*shadowMinIntersectionDist);
        currentIntersection.m_Prim->m_material->m_surfaceColour = currentIntersection.m_Prim->GetColour(currentIntersection.m_Point);
		pixelCol += currentIntersection.m_Prim->m_shader->Shade(currentIntersection.m_Point,
																currentIntersection.m_Prim->Normal(currentIntersection.m_Point),
																currentIntersection.m_Prim->m_material,
																_sourceRay,
																(*light)->m_position,
                                                                lightIntensity);
		
	} // Next light


	//----------------------------------------------------------------------------------------------------------
	// recursive part of raytracing - reflection and refractions
	if (_depth > 0)
	{
		glm::vec3 reflectionCol;
		glm::vec3 refractionCol;
		float bias = 0.01f;
		glm::vec3 hitPoint = currentIntersection.m_Point;
		glm::vec3 hitNorm = currentIntersection.m_Prim->Normal(currentIntersection.m_Point);

		
		bool inside = false;

		if (glm::dot(_sourceRay.m_dir, hitNorm) > 0)
		{
			hitNorm = -hitNorm;
			inside = true;
		}
		

		if (currentIntersection.m_Prim->m_material->m_transmittivity != glm::vec3(0.0f))
		{
			// Transmitive material
			glm::vec3 refractedRayDir;

			float facingRatio = -glm::dot(_sourceRay.m_dir, hitNorm);
			float fresnelEffect = glm::mix(powf(1 - facingRatio, 3), 1.0f, 0.1f);

			float IoR = currentIntersection.m_Prim->m_material->m_indexOfRefraction;
			float eta = inside ? IoR : 1.0f / IoR;
			float cosI = -glm::dot(hitNorm, _sourceRay.m_dir);
			float k = 1 - eta * eta  * (1 - cosI * cosI);
			refractedRayDir = _sourceRay.m_dir * eta + hitNorm * (eta * cosI - sqrtf(k));
			refractedRayDir = glm::refract(_sourceRay.m_dir, hitNorm, eta);

			Ray refractedRay(hitPoint + (bias * refractedRayDir), refractedRayDir);
			refractionCol += currentIntersection.m_Prim->m_material->m_transmittivity * TraceRay(refractedRay, _depth - 1);

			// reflected ray for fresnel effect
			Ray reflectedRay = Ray(hitPoint + (bias*hitNorm), glm::reflect(_sourceRay.m_dir, hitNorm));
			reflectionCol += TraceRay(reflectedRay, _depth - 1);

			// Apply fresnel effect
			reflectionCol *= fresnelEffect;
			refractionCol *= (1.0f - fresnelEffect);
		}
		else if (currentIntersection.m_Prim->m_material->m_reflectivity != glm::vec3(0.0f))
		{
			// reflective material

			// Generate reflected ray
			Ray reflectedRay = Ray(hitPoint + (bias*hitNorm), glm::reflect(_sourceRay.m_dir, hitNorm));
			reflectionCol += currentIntersection.m_Prim->m_material->m_reflectivity * TraceRay(reflectedRay, _depth - 1);
		}
						

		pixelCol += (reflectionCol + refractionCol);
		
	}


	return glm::clamp(pixelCol, glm::vec3(0.0f), glm::vec3(1.0f));
}
