#include <iostream>

#include "Raytracer/RayTracer.h"

int main(int argc, char* arv[])
{
	
	RayTracer r = RayTracer();
	r.Render();

	int end;
	std::cin >> end;

	return 0;
}
