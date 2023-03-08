/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:30:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/08 23:46:23 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_hook(int keycode, t_vars *vars)
{
	int				i;
	int				j;
	t_quaternion	q2;
	t_fdf			*fdf;

	fdf = vars->fdf;
	// quaternion_x_rotation(PI_4, &q1);
	if (keycode == 1)
		ft_printf("left click\n");
	if (keycode == 2)
		ft_printf("right click\n");
	if (keycode == 3)
		ft_printf("middle click\n");
	if (keycode == 4)
	{
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
	}
	ft_printf("%i\n", keycode);
	return (0);
}
