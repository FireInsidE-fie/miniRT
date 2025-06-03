#ifndef MINIRT_H
# define MINIRT_H

// Macros //
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// Structs //

// Struct for a point in 3D space
typedef struct s_point3
{
	double	x;
	double	y;
	double	z;
}	t_point3;

// Vectors are also represented with a value for each of the coordinates
typedef t_point3	t_vector3;

// Holds all MLX-related data
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

// A MLX image
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

// Functions //

// MiniLibX helper functions - mlx.c
t_mlx	*get_graphics(void);
int		init_window(void);

#endif //MINIRT_H
