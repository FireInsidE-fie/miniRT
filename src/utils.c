#include "utils.h"

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	else if (x > max)
		return (max);
	return (x);
}
