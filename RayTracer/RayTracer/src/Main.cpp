#include <iostream>

#include "RayTracer.h"

int main(int argc, char* arv[])
{
	
	RayTracer r = RayTracer(600, 400);
	r.Render();

	int end;
	std::cin >> end;

	return 0;
}