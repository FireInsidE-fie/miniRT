#include "utils.h"
#include "libft.h"
#include "minirt.h"

#include <stdint.h>
#include <stdbool.h>

bool	is_in_range(double x, t_range range)
{
	return (x >= range.min && x <= range.max);
}

/**
 * @brief Clamps a value between the `min` and `max` values.
 */
double	clamp(double x, t_range range)
{
	if (x < range.min)
		return (range.min);
	else if (x > range.max)
		return (range.max);
	return (x);
}

/**
 * @brief Checks if a given string ends in .rt (pre-checks before parsing).
 * @return true if path is a .rt file, false otherwise.
 */
bool	check_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		++i;
	if (i <= 3)
		return (false);
	if (ft_strncmp(path + i - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}

/**
 * @brief Converts a stringified number into a floating point representation.
 * Takes care of missing decimal parts, and accounts for trailing 0s.
 */
float	ft_atof(char *str)
{
	float	result;
	float	decimal;
	int		zeros;
	int		sign;

	while (*str == '0' && ft_isdigit(*(str + 1)))
		++str;
	result = ft_atoi(str);
	sign = 1;
	while (*str && (*str == '-' || ft_isdigit(*str)))
	{
		if (*(str++) == '-')
			sign = -1;
	}
	if (*str == '.' && ft_isdigit(*(str + 1)))
	{
		zeros = 0;
		while (*(++str) == '0')
			++zeros;
		decimal = ft_atoi(str);
		while (decimal >= 1.0f || zeros-- > 0)
			decimal /= 10;
		result += decimal * sign;
	}
	return (result);
}

/**
 * @brief Puts a given color on a pixel of a MLX image.
 */
void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(uint32_t *)dest = color;
}
