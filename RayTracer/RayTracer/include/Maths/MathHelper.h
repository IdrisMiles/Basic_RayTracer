#pragma once
#ifndef _MATHHELPER__H_
#define _MATHHELPER__H_

static const double LARGE_VAL = 1e10;

class MathHelper
{
public:
	MathHelper();
	~MathHelper();

	static double fdiv(double a, double b);

	static int sign(double a);



};

#endif //_MATHHELPER__H_
