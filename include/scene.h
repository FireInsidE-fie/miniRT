#ifndef SCENE_H
# define SCENE_H

# include "ambient.h"
# include "camera.h"
# include "light.h"
# include "point3.h"

// Structs //

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	N
}	t_type;

// TODO: rotation or direction
typedef struct s_shape
{
	t_type			type;
	t_point3		position;
	t_material		mat;
	float			radius;				// For spheres and cylinders
	float			height;				// For cylinders
	t_vec3			normal;				// For planes
	t_vec3			direction;
	struct s_shape	*next;
}	t_shape;

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		*lights;
	t_shape		*shapes;
}	t_scene;

// Functions //

t_scene	*get_scene(void);
void	add_shape(t_shape *new_shape);
void	clear_shapes(void *first);
void	print_scene(t_scene *scene);

#endif // SCENE_H
