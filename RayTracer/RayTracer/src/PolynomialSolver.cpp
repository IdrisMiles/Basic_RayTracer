#include "PolynomialSolver.h"
#include <math.h>
#include "MathHelper.h"

PolynomialSolver::PolynomialSolver()
{
}


PolynomialSolver::~PolynomialSolver()
{
}


void PolynomialSolver::linearRoot(PolyReturn &_result, double c1, double c0)
{
	//c1*x + c0 = 0
	if (c1 == 0)
	{
		_result.m_values[0] = 0;
	}
	else
	{
		_result.m_numVal++;
		_result.m_numVal = MathHelper::fdiv(-c0,c1);
	}

}


void PolynomialSolver::QuadraticRoots(PolyReturn &_result, double c2, double c1, double c0)
{
	//c2*x^2 + c1*x + c0 = 0
	if (c2 == 0)
	{
		linearRoot(_result, c1, c0);
	}
	else
	{
		//			 -c1 +- sqrt(c1^2 -4*c2*c0)
		//	roots = __________________
		//					2*c2

		double d = (c2 * c2) - (4 * c2 * c0);
		if (d == 0)
		{
			_result.m_numVal++;
			_result.m_values[0] = MathHelper::fdiv(-c1, 2 * c2);
		}
		else if (d > 0)
		{
			_result.m_numVal += 2;
			_result.m_values[0] = MathHelper::fdiv(-c1 + sqrt(d), 2 * c2);
			_result.m_values[0] = MathHelper::fdiv(-c1 - sqrt(d), 2 * c2);
		}
		else
		{
			_result.m_numVal = 0;
		}
	}
}


void PolynomialSolver::CubicRoots(PolyReturn &_result, double c3, double c2, double c1, double c0)
{
	// c3*x^3 + c2*x^2 + c1*x + c0 = 0

	PolyReturn quadraticRes;
	double k, p, q, w, cos3a, t, p_d3_e3, a;
	int i;

	if (c3 == 0)
	{
		QuadraticRoots(_result, c2, c1, c0);
	}
	else
	{
		if (c2 == 0 && c1 == 0)
		{
			_result.m_numVal = 1;
			_result.m_values[0] = cbrt(MathHelper::fdiv(-c0, c3));
		}
		else
		{
			if (c0 == 0)
			{
				_result.m_numVal = 1;
				_result.m_values[0] = 0;
				QuadraticRoots(quadraticRes, c3, c2, c1);
				for (i = 0; i < quadraticRes.m_numVal; i++)
					if (quadraticRes.m_values[i] != 0)
						_result.m_values[_result.m_numVal++] = quadraticRes.m_values[i];
			}
			else
			{
				if (c2 != 0)
				{
					k = MathHelper::fdiv(-c2, 3 * c3);
					p = MathHelper::fdiv(3 * c3 * c1 - c2 * c2, -3 * c3 * c3);
					q = MathHelper::fdiv(2 * c2 * c2 * c2 - 9 * c3 * c2 * c1 + 27 * c3 * c3 * c0, -27 * c3 * c3 * c3);
				}
				else
				{
					k = 0;
					p = MathHelper::fdiv(-c1, c3);
					q = MathHelper::fdiv(-c0, c3);
				}

				p_d3_e3 = p * p / 27 * p;
				w = q / 4 * q - p_d3_e3;

				if (w < 0)
				{
					cos3a = MathHelper::fdiv(q, 2 * sqrt(p_d3_e3));
					a = acos(cos3a) / 3;
					t = sqrt(p * 1.33333333333333);
					_result.m_numVal= 3;
					_result.m_values[0] = t * cos(a) + k;
					_result.m_values[1] = t * cos(a + 120 * 180.0f / 3.14f) + k;
					_result.m_values[2] = t * cos(a + 240 * 180.0f / 3.14f) + k;
				}
				else
				{
					if (w == 0)
					{
						_result.m_numVal = 1;
						_result.m_values[0] = 2 * cbrt(q / 2) + k;
					}
					else
					{
						_result.m_numVal = 1;
						_result.m_values[0] = cbrt(q / 2 + sqrt(w)) + cbrt(q / 2 - sqrt(w)) + k;
					}
				}
			}
		}
	}
}