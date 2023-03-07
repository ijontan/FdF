/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:16:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/07 21:28:20 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

void	apply_rotation(t_fdf *fdf)
{
	int				i;
	int				j;
	t_quaternion	q1;
	t_quaternion	q2;
	double			tmp_v[3];

	tmp_v[0] = 1;
	tmp_v[1] = 1;
	tmp_v[2] = 0;
	quaternion_from_axis_angle(tmp_v, PI_4, &q1);
	// quaternion_x_rotation(PI_4, &q1);
	quaternion_z_rotation(PI_4, &q2);
	i = 0;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
		{
			quaternion_rotate(&q1, fdf->v_grid[i][j].v, tmp_v);
			quaternion_rotate(&q2, tmp_v, fdf->v_grid[i][j].v);
			j++;
		}
		i++;
	}
}

int	main(int ac, char const **av)
{
	t_vars	vars;
	t_fdf	*fdf;

	vars.win_h = 1080;
	vars.win_w = 1920;
	if (ac != 2)
		return (1);
	fdf = malloc(sizeof(t_fdf));
	parse_map((char *)(av[1]), fdf);
	print_map(fdf);
	create_vertices(fdf);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.win_w, vars.win_h, "my win");
	apply_rotation(fdf);
	display(&vars, fdf);
	mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_mouse_hook(vars.win, &mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
