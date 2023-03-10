/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:30:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 16:25:38 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/*
** https://gamedev.stackexchange.com/questions/16212/
quaternions-and-rotation-around-world-axis
** this is one line of url
*/
int	mouse_hook_down(int keycode, int x, int y, t_vars *vars)
{
	int				i;
	int				j;
	t_quaternion	q2;
	t_fdf			*fdf;

	printf("x:%i,y:%i", x, y);
	fdf = vars->fdf;
	// quaternion_x_rotation(PI_4, &q1);
	if (keycode == 1)
	{
		fdf->hold.left_m = true;
		fdf = vars->fdf;
		quaternion_y_rotation(0.1, &q2);
		quaternion_normalize(&q2, &q2);
		quaternion_multiply(&q2, &(fdf->orientation), &(fdf->orientation));
		// quaternion_multiply(&(fdf->orientation), &q2, &(fdf->orientation));
		display(vars);
	}
	if (keycode == 2)
	{
		fdf->hold.right_m = true;
		fdf = vars->fdf;
		quaternion_y_rotation(-0.1, &q2);
		quaternion_normalize(&q2, &q2);
		quaternion_multiply(&q2, &(fdf->orientation), &(fdf->orientation));
		// quaternion_multiply(&(fdf->orientation), &q2, &(fdf->orientation));
		display(vars);
	}
	if (keycode == 3)
		fdf->hold.middle_m = true;
	if (keycode == 4)
	{
		fdf = vars->fdf;
		quaternion_x_rotation(-0.1, &q2);
		quaternion_normalize(&q2, &q2);
		quaternion_multiply(&q2, &(fdf->orientation), &(fdf->orientation));
		// quaternion_multiply(&(fdf->orientation), &q2, &(fdf->orientation));
		display(vars);
	}
	if (keycode == 5)
	{
		quaternion_x_rotation(0.1, &q2);
		quaternion_normalize(&q2, &q2);
		quaternion_multiply(&q2, &(fdf->orientation), &(fdf->orientation));
		// quaternion_multiply(&(fdf->orientation), &q2, &(fdf->orientation));
		display(vars);
	}
	if (keycode == 8)
	{
		i = 0;
		while (i < fdf->grid_height)
		{
			j = 0;
			while (j < fdf->grid_width)
			{
				scale(fdf->v_grid[i][j].v, 0.9);
				j++;
			}
			i++;
		}
		fdf->line_dis_2 *= 0.9;
		display(vars);
	}
	if (keycode == 9)
	{
		i = 0;
		while (i < fdf->grid_height)
		{
			j = 0;
			while (j < fdf->grid_width)
			{
				scale(fdf->v_grid[i][j].v, 1.0 / 0.9);
				j++;
			}
			i++;
		}
		fdf->line_dis_2 *= 1.0 / 0.9;
		display(vars);
	}
	ft_printf("%i\n", keycode);
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

int	mouse_move_hook(int x, int y, t_vars *vars)
{
	(void)vars;
	(void)x;
	(void)y;
	// ft_printf("x:%i,y:%i\n", x, y);
	return (0);
}
