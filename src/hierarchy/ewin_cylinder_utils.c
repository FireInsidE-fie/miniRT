/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ewin_cylinder_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:27:05 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:28:31 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hierarchy.h"

void	apply_cyl_rad(t_ewin *ewin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 190 && y <= 220)
		ewin->shape->radius += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 190 && y <= 220)
		ewin->shape->radius -= 0.1f;
}

void	apply_cyl_dir(t_ewin *ewin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 40 && y <= 70)
		ewin->shape->direction.z += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 40 && y <= 70)
		ewin->shape->direction.z -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 90 && y <= 120)
		ewin->shape->direction.y += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 90 && y <= 120)
		ewin->shape->direction.y -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 140 && y <= 170)
		ewin->shape->direction.x += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 140 && y <= 170)
		ewin->shape->direction.x -= 0.1f;
}

void	apply_cyl_height(t_ewin *ewin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 240 && y <= 270)
		ewin->shape->height += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 240 && y <= 270)
		ewin->shape->height -= 0.1f;
}

void	apply_cyl_pos(t_ewin *ewin, int x, int y)
{
	if (x >= 250 && x <= 280 && y >= 40 && y <= 70)
		ewin->shape->position.z += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 40 && y <= 70)
		ewin->shape->position.z -= 0.1f;
	else if (x >= 250 && x <= 280 && y >= 90 && y <= 120)
		ewin->shape->position.y += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 90 && y <= 120)
		ewin->shape->position.y -= 0.1f;
	else if (x >= 250 && x <= 280 && y >= 140 && y <= 170)
		ewin->shape->position.x += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 140 && y <= 170)
		ewin->shape->position.x -= 0.1f;
}
