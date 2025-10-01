#include "export.h"
#include "libft.h"

#include <math.h>

// builds the full float number

static char	*get_ftoa(char *fractmp, int integer)
{
	char	*tmp;
	int		intlen;
	int		fraclen;
	char	*result;

	tmp = ft_itoa(integer);
	intlen = (int)ft_strlen(tmp);
	fraclen = (int)ft_strlen(fractmp);
	result = ft_calloc(sizeof(char), (ft_strlen(tmp) + fraclen + 2));
	ft_strlcpy(result, tmp, intlen + 1);
	result[intlen] = '.';
	ft_strlcat(result, fractmp, intlen + fraclen + 2);
	free(tmp);
	free(fractmp);
	return (result);
}

// Returns the fractional part of the float, rounded to 6 numbers

static	char	*get_ftoa_frac(float fracpart)
{
	char	*tmpfrac;
	char	*result;
	int		i;
	int		j;
	int		num;

	i = 6;
	j = 0;
	num = (int)(round(fracpart));
	tmpfrac = ft_itoa(num);
	result = ft_calloc(sizeof(char), 7);
	while (i > (int)ft_strlen(tmpfrac))
	{
		i--;
		result[j] = '0';
		j++;
	}
	ft_strlcat(result, tmpfrac, 7);
	free(tmpfrac);
	return (result);
}

/*
 *  modff() splits a float into two parts.
 *  12.00003f would be splitted as 12.0 and 0.000030.
 *  ftoa() returns an heap-allocated string.
*/
char	*ftoa(float n)
{
	float	intpart;
	float	fracpart;
	char	*result;
	int		tmp;
	int		integer;

	tmp = 6;
	fracpart = modff(n, &intpart);
	if (fracpart < 0)
		fracpart = -fracpart;
	while (tmp > 0)
	{
		fracpart *= 10;
		tmp--;
	}
	result = get_ftoa_frac(fracpart);
	integer = (int)intpart;
	result = get_ftoa(result, integer);
	return (result);
}

void	write_triad(float x, float y, float z, int fd)
{
	char	*str;

	str = ftoa(x);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(",", fd);
	free(str);
	str = ftoa(y);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(",", fd);
	free(str);
	str = ftoa(z);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(" ", fd);
	free(str);
}

void	write_export(float n, int fd)
{
	char	*str;

	str = ftoa(n);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(" ", fd);
	free(str);
}
