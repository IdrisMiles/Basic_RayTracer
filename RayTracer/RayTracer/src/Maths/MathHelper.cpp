#include "Maths/MathHelper.h"


MathHelper::MathHelper()
{
}


MathHelper::~MathHelper()
{
}


double MathHelper::fdiv(double a, double b)
{
	if (b == 0) // if denominator = 0
	{
		return (a == 0) ? 0 : LARGE_VAL*sign(a);
	}
	else
	{
		if (a == 0) // if numerator = 0
		{
			return 0;
		}
		else // "normal" case
		{
			return /*((a + b) == a) ? LARGE_VAL*sign(a)*sign(b) : */a / b;
		}
	}
}

int MathHelper::sign(double a)
{
	return (a == 0) ? 0 : ((a < 0) ? -1 : 1);
}

