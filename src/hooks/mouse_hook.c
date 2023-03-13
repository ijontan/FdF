/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:30:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 20:40:11 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/*
** https://gamedev.stackexchange.com/questions/16212/
quaternions-and-rotation-around-world-axis
** this is one line of url
*/
static void	z_rot(t_vars *vars, double angle)
{
	t_quaternion	q2;

	quaternion_z_rotation(angle, &q2);
	quaternion_normalize(&q2, &q2);
	quaternion_multiply(&q2, &(vars->fdf->orientation),
		&(vars->fdf->orientation));
	display(vars);
}

int	mouse_hook_down(int keycode, int x, int y, t_vars *vars)
{
	vars->fdf->hold.prev_x = x;
	vars->fdf->hold.prev_y = y;
	if (keycode == 1)
		vars->fdf->hold.left_m = true;
	if (keycode == 2)
		vars->fdf->hold.right_m = true;
	if (keycode == 3)
		vars->fdf->hold.middle_m = true;
	if (keycode == 4)
		z_rot(vars, -0.1);
	if (keycode == 5)
		z_rot(vars, 0.1);
	return (0);
}

int	mouse_hook_up(int keycode, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		vars->fdf->hold.left_m = false;
	if (keycode == 2)
		vars->fdf->hold.right_m = false;
	if (keycode == 3)
		vars->fdf->hold.middle_m = false;
	return (0);
}

static void	xy_rot(int x, int y, t_vars *vars)
{
	t_quaternion	q1;

	quaternion_y_rotation((vars->fdf->hold.prev_x - x) / 600, &q1);
	vars->fdf->hold.prev_x = x;
	quaternion_normalize(&q1, &q1);
	quaternion_multiply(&q1, &(vars->fdf->orientation),
		&(vars->fdf->orientation));
	quaternion_x_rotation(-(vars->fdf->hold.prev_y - y) / 600, &q1);
	vars->fdf->hold.prev_y = y;
	quaternion_normalize(&q1, &q1);
	quaternion_multiply(&q1, &(vars->fdf->orientation),
		&(vars->fdf->orientation));
	display(vars);
}

int	mouse_move_hook(int x, int y, t_vars *vars)
{
	if (vars->fdf->hold.right_m)
		xy_rot(x, y, vars);
	if (vars->fdf->hold.left_m)
	{
		translate(vars->fdf->global_position, (x - vars->fdf->hold.prev_x), (y
				- vars->fdf->hold.prev_y), 0);
		vars->fdf->hold.prev_x = x;
		vars->fdf->hold.prev_y = y;
		display(vars);
	}
	if (vars->fdf->hold.middle_m)
		ft_printf("middle:: x:%i,y:%i\n", x, y);
	return (0);
}
