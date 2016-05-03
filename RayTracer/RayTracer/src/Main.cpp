#include <iostream>

#include "RayTracer.h"

int main(int argc, char* arv[])
{
	
	RayTracer r = RayTracer(600, 400);
	r.Render();

	return 0;
}