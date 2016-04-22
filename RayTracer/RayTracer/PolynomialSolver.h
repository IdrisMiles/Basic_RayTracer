#pragma once


struct PolyReturn
{
	short m_numVal = 0;
	double m_values[5];
};

class PolynomialSolver
{
public:
	PolynomialSolver();
	~PolynomialSolver();

	//root of linear equation: c1*x + c0 = 0
	// if successful return _result.m_values[0] = x
	static void linearRoot(PolyReturn &_result, double c1, double c0);


	// distinct real roots of quadratic equation: c2*x^2 + c1*x + c0 = 0
	// if successful return _result.m_values[0] = x1, _result.m_values[1] = x2
	static void QuadraticRoots(PolyReturn &_result, double c2, double c1, double c0);


	// real roots of cubic equation: c3*x^2 + c2*x^2 + c1*x + c0 = 0
	static void CubicRoots(PolyReturn &_result, double c3, double c2, double c1, double c0);
};

