#include "minirt.h"

#define KEY_A 97
#define KEY_D 100
#define KEY_E 101
#define KEY_Q 113
#define KEY_R 114
#define KEY_S 115
#define KEY_W 119
#define KEY_L 108
#define KEY_J 106
#define KEY_I 105
#define KEY_K 107
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364
#define MOVE_INTERVAL 0.70
#define ROTATE_ANGLE 0.06

void	update_camera(t_core *core);
void	rotate_camera_yaw(t_camera *cam, float angle);
void	rotate_camera_pitch(t_camera *cam, float angle);
