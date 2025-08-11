#include "libft.h"

#include <stdbool.h>
#include <stdio.h>

float	ft_atof(char *str)
{
	float	result;

	result = ft_atoi(str);
	while (*str && (*str == '-' || ft_isdigit(*str)))
		++str;
	if (*str == '.')
		result += ft_atoi(++str) / 10.0f;
	printf("[!] - ft_atof gave %.2f back!\n", result);
	return (result);
}
