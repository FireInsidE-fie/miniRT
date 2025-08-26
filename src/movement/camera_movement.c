#include "minirt.h"
#include "vector.h"
#include "movement.h"

#include <X11/X.h>
#include <stdint.h>

/**
 * @brief Applies position changes when the proper key is held.
 */
static void	update_camera_pos(t_core *core)
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
		core->scene.camera.position = vec_add(vec_scalar(
					core->scene.camera.forward, MOVE_INTERVAL),
				core->scene.camera.position);
	if (core->key_state[KEY_S] && core->render_mode == 0)
		core->scene.camera.position = vec_add(core->scene.camera.position,
				vec_scalar(core->scene.camera.forward, -MOVE_INTERVAL));
}

/**
 * @brief Applies Yaw or Pitch rotations when the proper key is held.
 */
static void	update_camera_rot(t_core *core)
{
	if (core->key_state[KEY_J] && core->render_mode == 0)
		rotate_camera_yaw(&core->scene.camera, -ROTATE_ANGLE);
	if (core->key_state[KEY_L] && core->render_mode == 0)
		rotate_camera_yaw(&core->scene.camera, ROTATE_ANGLE);
	if (core->key_state[KEY_I] && core->render_mode == 0)
		rotate_camera_pitch(&core->scene.camera, -ROTATE_ANGLE);
	if (core->key_state[KEY_K] && core->render_mode == 0)
		rotate_camera_pitch(&core->scene.camera, ROTATE_ANGLE);
}

/**
 * @brief Checks if camera movements needs to be made each fast_render loop

	update_camera() is called in the fast render loop,
	applying the movements depending on the key_state value of each key.

	key_state[KEY_J] = 1 would mean the J key is currently held.
 */
void	update_camera(t_core *core)
{
	update_camera_pos(core);
	update_camera_rot(core);
}
