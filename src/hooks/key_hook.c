/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:16:20 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 17:48:14 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_vars *vars)
{
	t_quaternion	q1;
	int				i;
	int				j;

	if (keycode == 18)
	{
		vars->fdf->slerp_var.start_o = vars->fdf->orientation;
		vars->fdf->slerp_var.end_o = quaternion_create_id();
		quaternion_z_rotation(-PI_4, &q1);
		quaternion_multiply(&q1, &vars->fdf->slerp_var.end_o,
				&vars->fdf->slerp_var.end_o);
		quaternion_x_rotation(-PI_4, &q1);
		quaternion_multiply(&q1, &vars->fdf->slerp_var.end_o,
				&vars->fdf->slerp_var.end_o);
		vars->fdf->slerp_var.t = 0.0;
		vars->fdf->slerp_var.sign = 1;
	}
	if (keycode == 19)
	{
		vars->fdf->slerp_var.start_o = vars->fdf->orientation;
		vars->fdf->slerp_var.end_o = vars->fdf->orientation;
		vars->fdf->slerp_var.out_o = vars->fdf->orientation;
		vars->fdf->slerp_var.t = 0.0;
		vars->fdf->slerp_var.sign = -1;
	}
	if (keycode == 96)
	{
	}
	if (keycode == 125)
	{
		if (vars->fdf->focal_len >= 209715200)
			return (1);
		vars->fdf->focal_len = (vars->fdf->focal_len - 130) * 2;
		display(vars);
	}
	if (keycode == 126)
	{
		if (vars->fdf->focal_len < 130)
			return (1);
		vars->fdf->focal_len = vars->fdf->focal_len / 2 + 130;
		display(vars);
	}
	if (keycode == 1)
	{
		i = 0;
		while (i < vars->fdf->grid_height)
		{
			j = 0;
			while (j < vars->fdf->grid_width)
			{
				scale(vars->fdf->v_grid[i][j].v, 0.9);
				j++;
			}
			i++;
		}
		vars->fdf->line_dis_2 *= 0.9;
		display(vars);
	}
	if (keycode == 13)
	{
		i = 0;
		while (i < vars->fdf->grid_height)
		{
			j = 0;
			while (j < vars->fdf->grid_width)
			{
				scale(vars->fdf->v_grid[i][j].v, 1.0 / 0.9);
				j++;
			}
			i++;
		}
		vars->fdf->line_dis_2 *= 1.0 / 0.9;
		display(vars);
	}
	(void)vars;
	ft_printf("%i\n", keycode);
	return (0);
}
