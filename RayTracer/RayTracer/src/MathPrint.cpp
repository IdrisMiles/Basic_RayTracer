#include "..\include\MathPrint.h"
#include <iostream>


MathPrint::MathPrint()
{
}


MathPrint::~MathPrint()
{
}

void MathPrint::PrintMat4(glm::mat4 _mat)
{
	std::cout << "____________________________\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << _mat[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "____________________________\n";
}


void MathPrint::PrintMat3(glm::mat3 _mat)
{
	std::cout << "____________________________\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << _mat[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "____________________________\n";
}

void MathPrint::PrintVec4(glm::vec4 _vec)
{
	std::cout << "[\t";
	for (int i = 0; i < 4; i++)
	{
		std::cout << _vec[i] << "\t";
	}
	std::cout << "]\n";
}

void MathPrint::PrintVec3(glm::vec3 _vec)
{
	std::cout << "[\t";
	for (int i = 0; i < 3; i++)
	{
		std::cout << _vec[i] << "\t";
	}
	std::cout << "]\n";
}