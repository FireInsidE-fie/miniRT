#include "material.h"
#include "minirt.h"
#include "mlx.h"
#include "vector.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define KEY_A 97
#define KEY_D 100
#define KEY_E 101
#define KEY_Q 113
#define KEY_R 114
#define KEY_S 115
#define KEY_W 119
#define KEY_L 108
#define KEY_H 104
#define KEY_I 105
#define KEY_K 107
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364
#define MOVE_INTERVAL 0.08
#define	ROTATE_ANGLE 0.016

#define MAX_PITCH_RAD (M_PI / 2.0 - 0.01) // 89.4 max
#define MIN_PITCH_RAD (-M_PI / 2.0 + 0.01)
/**
 * @brief Swaps miniRT between full render and fast render modes.
 */
void	swap_render_mode(t_core *core)
{
	if (core->render_mode == 1)
		core->render_mode = 0;
	else
	{
		printf("[!] - Rendering...\n");
		core->render.is_rendering = 1;
		core->render_mode = 1;
	}
	// Reset render position
	core->render.x = -WIN_WIDTH / 2;
	core->render.y = -WIN_HEIGHT / 2;
	if (core->render_mode == 0)
		mlx_loop_hook(core->mlx, fast_render, core);
	else
		mlx_loop_hook(core->mlx, render, core);
}

t_vec3 rotate_vector(t_vec3 v, t_vec3 axis, float angle)
{
    t_vec3 u;
	
	u = axis;
    vec_normalize(&u);
    return (
		vec_add(
			vec_add(
				vec_scalar(v, cos(angle)),
				vec_scalar(cross_product(&u, &v), sin(angle))
			),
		vec_scalar(u, dot_product(&u, &v) * (1 - cos(angle))))
	);
}


void	camera_build_basis(t_camera *cam)
{
	cam->forward = cam->direction;
	vec_normalize(&cam->forward);
	cam->right = cross_product(&(t_point3){0, 1, 0}, &cam->forward);
	vec_normalize(&cam->right);
	cam->up = cross_product(&cam->forward, &cam->right);
	vec_normalize(&cam->up);
}

void rotate_camera_pitch(t_camera *cam, float angle)
{
    float new_pitch;
	
	new_pitch = cam->pitch + angle;
    // Clamp avoiding clipping
    if (new_pitch > MAX_PITCH_RAD)
        angle = MAX_PITCH_RAD - cam->pitch;
    else if (new_pitch < MIN_PITCH_RAD)
        angle = MIN_PITCH_RAD - cam->pitch;
    cam->direction = rotate_vector(cam->direction, cam->right, angle);
    cam->pitch += angle;
    camera_build_basis(cam);
}

void rotate_camera_yaw(t_camera *cam, float angle)
{
    cam->direction = rotate_vector(cam->direction, cam->up, angle);
    camera_build_basis(cam);
}

/**
 * @brief MLX trigger for key presses, closing the window when `ESC`
 * or movement keys are pressed.
 */

 /*
	NEW MOVEMENT, Will refactor comments later but here's the brief.

	Core has a key_state int array that contains the status of each key pressed,
	up to 256 because most key codes are in that range (damn you ESC and Arrow keys).

	key_press sets the state to 1 when pressed/held, and key_release() sets it back
	to 0.

	update_camera() is called in the fast render loop, applying the movements depending
	on the key_state value of each key.
 */

static int key_press(int key, void *param)
{
    t_core *core;
	
	core = param;
	if (key == KEY_ESC)
		rt_kill(0);
	if (key == KEY_R && core->render.is_rendering == 0)
		swap_render_mode(core);
    if (key >= 0 && key < 256)
        core->key_state[key] = 1;
    return (0);
}

static int key_release(int key, void *param)
{
    t_core *core;
	
	core = param;
    if (key >= 0 && key < 256)
        core->key_state[key] = 0;
    return (0);
}


void	update_camera(t_core *core)
{
	if (core->key_state[KEY_A] && core->render_mode == 0)
		core->scene.camera.position = vec_add(core->scene.camera.position,
		vec_scalar(core->scene.camera.right, -MOVE_INTERVAL));
	if (core->key_state[KEY_D] && core->render_mode == 0)
		core->scene.camera.position = vec_add(core->scene.camera.position,
		vec_scalar(core->scene.camera.right, MOVE_INTERVAL));
	if (core->key_state[KEY_E] && core->render_mode == 0)
		core->scene.camera.position.y += MOVE_INTERVAL;
	if (core->key_state[KEY_Q] && core->render_mode == 0)
		core->scene.camera.position.y -= MOVE_INTERVAL;
	if (core->key_state[KEY_W] && core->render_mode == 0)
		core->scene.camera.position = vec_add(vec_scalar(core->scene.camera.forward, MOVE_INTERVAL),
		core->scene.camera.position);
	if (core->key_state[KEY_S] && core->render_mode == 0)
		core->scene.camera.position = vec_add(core->scene.camera.position,
		vec_scalar(core->scene.camera.forward, -MOVE_INTERVAL));
	if (core->key_state[KEY_H] && core->render_mode == 0)
		rotate_camera_yaw(&core->scene.camera, -ROTATE_ANGLE);
	if (core->key_state[KEY_L] && core->render_mode == 0)
		rotate_camera_yaw(&core->scene.camera, ROTATE_ANGLE);
	if (core->key_state[KEY_I] && core->render_mode == 0)
		rotate_camera_pitch(&core->scene.camera, -ROTATE_ANGLE);
	if (core->key_state[KEY_K] && core->render_mode == 0)
		rotate_camera_pitch(&core->scene.camera, ROTATE_ANGLE);
}

/**
 * @brief Creates hooks for the minilibX, quitting the program when the main
 * window is destroyed or the `ESC` key is pressed.
 */
static void	init_hooks(t_core *core)
{
	core = get_core();
	mlx_hook(core->win, KeyPress, KeyPressMask, key_press, core);
	mlx_hook(core->win, KeyRelease, KeyReleaseMask, key_release, core);
	mlx_hook(core->win, DestroyNotify, 0, rt_kill, 0);
}

/**
 * @brief Creates the MLX window.
 *
 * @return 0 if all went well, 1 if window initialization failed.
 */
int	init_window(void)
{
	t_core	*core;

	core = get_core();
	core->win
		= mlx_new_window(core->mlx, WIN_WIDTH, WIN_HEIGHT, "Obsolete Meat");
	if (!core->win)
		return (1);
	core->altwin
		= mlx_new_window(core->mlx, 400, 615, "Obsolete Meat - Hierarchy");
	render_shape_list(core);
	init_hooks(core);
	return (0);
}

/**
 * @brief Puts a given color on a pixel of a MLX image.
 */
void	img_put_pixel(t_img *img, int x, int y, t_color *color)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(uint32_t *)dest = color_to_int(color);
}
