/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:30:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/09 20:09:15 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
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
		fdf = vars->fdf;
		quaternion_x_rotation(0.05, &q2);
		i = 0;
		i = 0;
		while (i < fdf->grid_height)
		{
			j = 0;
			while (j < fdf->grid_width)
			{
				quaternion_rotate(&q2, fdf->v_grid[i][j].v,
						fdf->v_grid[i][j].v);
				j++;
			}
			i++;
		}
		display(vars);
	}
	if (keycode == 2)
	{
		fdf = vars->fdf;
		quaternion_x_rotation(-0.05, &q2);
		i = 0;
		i = 0;
		while (i < fdf->grid_height)
		{
			j = 0;
			while (j < fdf->grid_width)
			{
				quaternion_rotate(&q2, fdf->v_grid[i][j].v,
						fdf->v_grid[i][j].v);
				j++;
			}
			i++;
		}
		display(vars);
	}
	if (keycode == 3)
		ft_printf("middle click\n");
	if (keycode == 4)
	{
		fdf = vars->fdf;
		quaternion_z_rotation(0.05, &q2);
		i = 0;
		i = 0;
		while (i < fdf->grid_height)
		{
			j = 0;
			while (j < fdf->grid_width)
			{
				quaternion_rotate(&q2, fdf->v_grid[i][j].v,
						fdf->v_grid[i][j].v);
				j++;
			}
			i++;
		}
		display(vars);
	}
	if (keycode == 5)
	{
		quaternion_z_rotation(-0.05, &q2);
		i = 0;
		while (i < fdf->grid_height)
		{
			j = 0;
			while (j < fdf->grid_width)
			{
				quaternion_rotate(&q2, fdf->v_grid[i][j].v,
						fdf->v_grid[i][j].v);
				j++;
			}
			i++;
		}
		display(vars);
	}
	ft_printf("%i\n", keycode);
	return (0);
}

int	mouse_move_hook(int x, int y, t_vars *vars)
{
	(void)vars;
	ft_printf("x:%i,y:%i\n", x, y);
	return (0);
}
